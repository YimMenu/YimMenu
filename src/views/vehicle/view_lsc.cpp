#include "core/data/lsc_types.hpp"
#include "fiber_pool.hpp"
#include "natives.hpp"
#include "services/notifications/notification_service.hpp"
#include "services/vehicle_helper/vehicle_helper.hpp"
#include "util/vehicle.hpp"
#include "views/view.hpp"

#include <imgui_internal.h>

namespace big
{
	void view::lsc()
	{
		static Vehicle current_veh;
		static bool preparing_veh;

		static std::map<int, int32_t> owned_mods;
		static std::map<int, std::string> slot_display_names;
		static std::map<int, std::map<int, std::string>> mod_display_names;

		static std::map<std::string, std::vector<int>> front_wheel_map;
		static std::map<std::string, std::vector<int>> rear_wheel_map;
		static int front_wheel_stock_mod = -1;
		static int rear_wheel_stock_mod  = -1;

		static Hash model;
		static bool is_bennys = false;

		static int selected_slot = -1;

		if (self::veh)
		{
			if (current_veh != self::veh)
			{
				current_veh   = self::veh;
				preparing_veh = true;
				selected_slot = -1;

				g_fiber_pool->queue_job([] {
					if (!HUD::HAS_THIS_ADDITIONAL_TEXT_LOADED("MOD_MNU", 10))
					{
						HUD::CLEAR_ADDITIONAL_TEXT(10, TRUE);
						HUD::REQUEST_ADDITIONAL_TEXT("MOD_MNU", 10);
						script::get_current()->yield();
					}

					model      = ENTITY::GET_ENTITY_MODEL(current_veh);
					owned_mods = vehicle::get_owned_mods_from_vehicle(current_veh);
					is_bennys = owned_mods[MOD_WHEEL_TYPE] == WHEEL_TYPE_BENNYS_ORIGINAL || owned_mods[MOD_WHEEL_TYPE] == WHEEL_TYPE_BENNYS_BESPOKE || owned_mods[MOD_WHEEL_TYPE] == WHEEL_TYPE_OPEN_WHEEL || owned_mods[MOD_WHEEL_TYPE] == WHEEL_TYPE_STREET || owned_mods[MOD_WHEEL_TYPE] == WHEEL_TYPE_TRACK;

					VEHICLE::SET_VEHICLE_MOD_KIT(current_veh, 0);

					std::map<int, std::string> tmp_slot_display_names;
					std::map<int, std::map<int, std::string>> tmp_mod_display_names;
					std::map<std::string, std::vector<int>> tmp_front_wheel_map;
					std::map<std::string, std::vector<int>> tmp_rear_wheel_map;

					tmp_slot_display_names[MOD_PLATE_STYLE] = "Plate Style";
					tmp_slot_display_names[MOD_WINDOW_TINT] = "Window Tint";
					tmp_slot_display_names[MOD_WHEEL_TYPE]  = "Wheel Type";

					tmp_mod_display_names[MOD_PLATE_STYLE].insert(lsc_plate_styles.begin(), lsc_plate_styles.end());
					tmp_mod_display_names[MOD_WINDOW_TINT].insert(lsc_window_tint_types.begin(), lsc_window_tint_types.end());
					tmp_mod_display_names[MOD_WHEEL_TYPE].insert(lsc_wheel_styles.begin(), lsc_wheel_styles.end());

					for (int slot = MOD_SPOILERS; slot <= MOD_LIGHTBAR; slot++)
					{
						int count = VEHICLE::GET_NUM_VEHICLE_MODS(current_veh, slot);
						if (count > 0)
						{
							int owner_mod = owned_mods[slot];

							std::string slot_name = vehicle_helper::get_mod_slot_name(model, current_veh, slot);
							if (slot_name.empty())
								continue;

							slot_name.append("##");
							slot_name.append(std::to_string(slot));
							tmp_slot_display_names[slot] = slot_name;

							std::map<int, std::string> mod_names;

							for (int mod = -1; mod < count; mod++)
							{
								if (vehicle_helper::check_mod_blacklist(model, slot, mod))
									continue;

								bool is_repeated = false;

								std::string mod_name = vehicle_helper::get_mod_name(model, current_veh, slot, mod, count);

								if (mod_name.empty() || mod_name == "NULL")
									continue;

								if (slot == MOD_FRONTWHEEL)
								{
									if (is_bennys && mod_name.rfind("Chrome ", 0) == 0)
									{
										std::string new_mod_name = mod_name.substr(7);

										if (tmp_front_wheel_map[new_mod_name].size() > 0)
											mod_name = new_mod_name;
									}

									tmp_front_wheel_map[mod_name].push_back(mod);

									if (mod == owner_mod)
										front_wheel_stock_mod = tmp_front_wheel_map[mod_name][0];
									if (tmp_front_wheel_map[mod_name].size() > 1)
										is_repeated = true;
								}
								else if (slot == MOD_REARWHEEL)
								{
									if (is_bennys && mod_name.rfind("Chrome ", 0) == 0)
									{
										std::string new_mod_name = mod_name.substr(7);

										if (tmp_rear_wheel_map[new_mod_name].size() > 0)
											mod_name = new_mod_name;
									}

									tmp_rear_wheel_map[mod_name].push_back(mod);

									if (mod == owner_mod)
										rear_wheel_stock_mod = tmp_rear_wheel_map[mod_name][0];
									if (tmp_rear_wheel_map[mod_name].size() > 1)
										is_repeated = true;
								}

								if (!is_repeated)
									mod_names[mod] = mod_name;
							}

							tmp_mod_display_names[slot] = mod_names;
						}
					}

					if (tmp_mod_display_names.count(MOD_HORNS) > 0)
						tmp_mod_display_names[MOD_HORNS].insert(lsc_missing_horns.begin(), lsc_missing_horns.end());

					slot_display_names = tmp_slot_display_names;
					mod_display_names  = tmp_mod_display_names;
					front_wheel_map    = tmp_front_wheel_map;
					rear_wheel_map     = tmp_rear_wheel_map;

					preparing_veh = false;
				});
			}
			else if (!preparing_veh)
			{
				{
					static char plate[9];

					ImGui::SetNextItemWidth(150);
					components::input_text_with_hint("##plate", "Plate Number", plate, sizeof(plate), ImGuiInputTextFlags_None);
					ImGui::SameLine();
					components::button("Change Plate", [] {
						vehicle::set_plate(self::veh, plate);
					});
					ImGui::SameLine();
					components::button("Max Vehicle", [] {
						vehicle::max_vehicle(self::veh);
						current_veh = 0;
					});
					ImGui::SameLine();
					components::button("Max Performance", [] {
						vehicle::max_vehicle_performance(self::veh);
						current_veh = 0;
					});
				}
				ImGui::SeparatorText("Mod Options");
				{
					if (ImGui::Checkbox("Burstible tires", (bool*)&owned_mods[MOD_TIRE_CAN_BURST]))
						g_fiber_pool->queue_job([] {
							VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(current_veh, owned_mods[MOD_TIRE_CAN_BURST]);
						});
					ImGui::SameLine();
					if (ImGui::Checkbox("Low Grip Tires", (bool*)&owned_mods[MOD_DRIFT_TIRE]))

						g_fiber_pool->queue_job([] {
							VEHICLE::SET_DRIFT_TYRES(current_veh, owned_mods[MOD_DRIFT_TIRE]);
						});
					ImGui::SameLine();
					if (ImGui::Checkbox("Turbo", (bool*)&owned_mods[MOD_TURBO]))

						g_fiber_pool->queue_job([] {
							VEHICLE::TOGGLE_VEHICLE_MOD(current_veh, MOD_TURBO, owned_mods[MOD_TURBO]);
						});
					ImGui::SameLine();
					if (ImGui::Checkbox("Tire Smoke", (bool*)&owned_mods[MOD_TYRE_SMOKE]))

						g_fiber_pool->queue_job([] {
							VEHICLE::TOGGLE_VEHICLE_MOD(current_veh, MOD_TYRE_SMOKE, owned_mods[MOD_TYRE_SMOKE]);
						});
				}
				ImGui::SeparatorText("Mod Slots");
				{
					ImGui::BeginGroup();
					{
						components::sub_title("Slot");
						if (ImGui::BeginListBox("##slot", ImVec2(200, 200)))
						{
							for (const auto& [slot, name] : slot_display_names)
								if (ImGui::Selectable(name.c_str(), slot == selected_slot))
									selected_slot = slot;

							ImGui::EndListBox();
						}
					}
					ImGui::EndGroup();

					if (selected_slot != -1)
					{
						auto wheel_stock_mod = &front_wheel_stock_mod;
						auto wheel_custom    = &owned_mods[MOD_FRONTWHEEL_VAR];
						bool is_wheel_mod    = false;

						if (selected_slot == MOD_FRONTWHEEL)
							is_wheel_mod = true;
						else if (selected_slot == MOD_REARWHEEL)
						{
							wheel_stock_mod = &rear_wheel_stock_mod;
							wheel_custom    = &owned_mods[MOD_REARWHEEL_VAR];
							is_wheel_mod    = true;
						}
						else
							is_wheel_mod = false;

						ImGui::SameLine();
						ImGui::BeginGroup();
						{
							components::sub_title("Mod");
							if (ImGui::BeginListBox("##mod", ImVec2(240, 200)))
							{
								for (const auto& it : mod_display_names[selected_slot])
								{
									const auto& mod  = it.first;
									const auto& name = it.second;

									bool item_selected = mod == owned_mods[selected_slot];

									if (is_wheel_mod)
										item_selected = mod == *wheel_stock_mod;

									if (ImGui::Selectable(name.c_str(), item_selected))
									{
										g_fiber_pool->queue_job([&mod, is_wheel_mod, wheel_stock_mod, wheel_custom] {
											entity::take_control_of(self::veh);

											if (selected_slot >= 0)
											{
												if (!VEHICLE::IS_VEHICLE_MOD_GEN9_EXCLUSIVE(current_veh, selected_slot, mod))
												{
													VEHICLE::SET_VEHICLE_MOD(current_veh, selected_slot, mod, false);
													owned_mods[selected_slot] = mod;

													if (is_wheel_mod)
													{
														*wheel_stock_mod = mod;
														*wheel_custom    = false;
													}
												}
												else
													g_notification_service->push_error("LSC", "Selected mod is invalid");
											}
											else if (selected_slot == MOD_WINDOW_TINT)
											{
												VEHICLE::SET_VEHICLE_WINDOW_TINT(current_veh, mod);
												owned_mods[selected_slot] = mod;
											}
											else if (selected_slot == MOD_WHEEL_TYPE)
											{
												VEHICLE::SET_VEHICLE_WHEEL_TYPE(current_veh, mod);
												VEHICLE::SET_VEHICLE_MOD(current_veh, MOD_FRONTWHEEL, 0, false);
												VEHICLE::SET_VEHICLE_MOD(current_veh, MOD_REARWHEEL, 0, false);
												current_veh = 0;
											}
											else if (selected_slot == MOD_PLATE_STYLE)
											{
												VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(current_veh, mod);
												owned_mods[selected_slot] = mod;
											}
										});
									}
								}
								ImGui::EndListBox();
							}
						}
						ImGui::EndGroup();
					}
				}
				ImGui::SeparatorText("Neon Light Options");
				{
					ImGui::PushID("##headlight_en");
					if (ImGui::Checkbox("Headlight", (bool*)&owned_mods[MOD_XENON_LIGHTS]))
						g_fiber_pool->queue_job([] {
							VEHICLE::TOGGLE_VEHICLE_MOD(current_veh, MOD_XENON_LIGHTS, owned_mods[MOD_XENON_LIGHTS]);
						});
					ImGui::PopID();
					ImGui::SameLine();
					if (ImGui::Checkbox("Left", (bool*)&owned_mods[MOD_NEON_LEFT_ON]))
						g_fiber_pool->queue_job([] {
							VEHICLE::SET_VEHICLE_NEON_ENABLED(current_veh, NEON_LEFT, owned_mods[MOD_NEON_LEFT_ON]);
						});
					ImGui::SameLine();
					if (ImGui::Checkbox("Right", (bool*)&owned_mods[MOD_NEON_RIGHT_ON]))
						g_fiber_pool->queue_job([] {
							VEHICLE::SET_VEHICLE_NEON_ENABLED(current_veh, NEON_RIGHT, owned_mods[MOD_NEON_RIGHT_ON]);
						});
					ImGui::SameLine();
					if (ImGui::Checkbox("Front", (bool*)&owned_mods[MOD_NEON_FRONT_ON]))
						g_fiber_pool->queue_job([] {
							VEHICLE::SET_VEHICLE_NEON_ENABLED(current_veh, NEON_FRONT, owned_mods[MOD_NEON_FRONT_ON]);
						});
					ImGui::SameLine();
					if (ImGui::Checkbox("Back", (bool*)&owned_mods[MOD_NEON_BACK_ON]))
						g_fiber_pool->queue_job([] {
							VEHICLE::SET_VEHICLE_NEON_ENABLED(current_veh, NEON_BACK, owned_mods[MOD_NEON_BACK_ON]);
						});
					ImGui::SameLine();
					ImGui::PushID("##neon_check_all");
					components::button("Check all", [] {
						owned_mods[MOD_XENON_LIGHTS]  = true;
						owned_mods[MOD_NEON_LEFT_ON]  = true;
						owned_mods[MOD_NEON_RIGHT_ON] = true;
						owned_mods[MOD_NEON_FRONT_ON] = true;
						owned_mods[MOD_NEON_BACK_ON]  = true;

						VEHICLE::TOGGLE_VEHICLE_MOD(current_veh, MOD_XENON_LIGHTS, owned_mods[MOD_XENON_LIGHTS]);
						VEHICLE::SET_VEHICLE_NEON_ENABLED(current_veh, NEON_LEFT, owned_mods[MOD_NEON_LEFT_ON]);
						VEHICLE::SET_VEHICLE_NEON_ENABLED(current_veh, NEON_RIGHT, owned_mods[MOD_NEON_RIGHT_ON]);
						VEHICLE::SET_VEHICLE_NEON_ENABLED(current_veh, NEON_FRONT, owned_mods[MOD_NEON_FRONT_ON]);
						VEHICLE::SET_VEHICLE_NEON_ENABLED(current_veh, NEON_BACK, owned_mods[MOD_NEON_BACK_ON]);
					});
					ImGui::PopID();
					ImGui::SameLine();
					ImGui::PushID("##neon_uncheck_all");
					components::button("Uncheck all", [] {
						owned_mods[MOD_XENON_LIGHTS]  = false;
						owned_mods[MOD_NEON_LEFT_ON]  = false;
						owned_mods[MOD_NEON_RIGHT_ON] = false;
						owned_mods[MOD_NEON_FRONT_ON] = false;
						owned_mods[MOD_NEON_BACK_ON]  = false;

						VEHICLE::TOGGLE_VEHICLE_MOD(current_veh, MOD_XENON_LIGHTS, owned_mods[MOD_XENON_LIGHTS]);
						VEHICLE::SET_VEHICLE_NEON_ENABLED(current_veh, NEON_LEFT, owned_mods[MOD_NEON_LEFT_ON]);
						VEHICLE::SET_VEHICLE_NEON_ENABLED(current_veh, NEON_RIGHT, owned_mods[MOD_NEON_RIGHT_ON]);
						VEHICLE::SET_VEHICLE_NEON_ENABLED(current_veh, NEON_FRONT, owned_mods[MOD_NEON_FRONT_ON]);
						VEHICLE::SET_VEHICLE_NEON_ENABLED(current_veh, NEON_BACK, owned_mods[MOD_NEON_BACK_ON]);
					});
					ImGui::PopID();
				}
				ImGui::SeparatorText("Color Options");
				{
					static int color_to_change = 0;
					static int color_type      = 8;

					if ((color_to_change == 7 && !owned_mods[MOD_XENON_LIGHTS]) || (color_to_change == 5 && !owned_mods[MOD_TYRE_SMOKE]))
					{
						color_to_change = 0;
						color_type      = 8;
					}

					if (ImGui::BeginListBox("##color_options", ImVec2(120, 254)))
					{
						if (ImGui::Selectable("Primary", color_to_change == 0, ImGuiSelectableFlags_SelectOnClick))
							color_to_change = 0;
						if (ImGui::Selectable("Secondary", color_to_change == 1))
							color_to_change = 1;
						if (ImGui::Selectable("Pearlescent", color_to_change == 2))
						{
							color_to_change = 2;
							color_type      = 4;
						}
						if (ImGui::Selectable("Interior", color_to_change == 3))
						{
							color_to_change = 3;
							color_type      = 6;
						}
						if (ImGui::Selectable("Dashboard", color_to_change == 4))
						{
							color_to_change = 4;
							color_type      = 7;
						}

						if (!owned_mods[MOD_TYRE_SMOKE])
							ImGui::BeginDisabled();
						if (ImGui::Selectable("Tire Smoke", color_to_change == 5))
						{
							color_to_change = 5;
							color_type      = 8;
						}
						if (!owned_mods[MOD_TYRE_SMOKE])
							ImGui::EndDisabled();

						if (ImGui::Selectable("Wheel Color", color_to_change == 6))
						{
							color_to_change = 6;
							color_type      = 5;
						}

						if (!owned_mods[MOD_XENON_LIGHTS])
							ImGui::BeginDisabled();
						ImGui::PushID("##headlight_col");
						if (ImGui::Selectable("Headlight", color_to_change == 7))
						{
							color_to_change = 7;
							color_type      = 9;
						}
						ImGui::PopID();
						if (!owned_mods[MOD_XENON_LIGHTS])
							ImGui::EndDisabled();

						if (ImGui::Selectable("Neon", color_to_change == 8))
						{
							color_to_change = 8;
							color_type      = 8;
						}

						ImGui::EndListBox();
					}

					if (color_to_change == 0 || color_to_change == 1)
					{
						if (color_type > 3)
							color_type = 8;

						// primary and secondary color

						ImGui::SameLine();
						if (ImGui::BeginListBox("##colors", ImVec2(140, 254)))
						{
							if (ImGui::Selectable("Custom", color_type == 8, ImGuiSelectableFlags_SelectOnClick))
								color_type = 8;

							if (ImGui::Selectable("Remove Custom", false))
								g_fiber_pool->queue_job([] {
									if (color_to_change == 0)
										VEHICLE::CLEAR_VEHICLE_CUSTOM_PRIMARY_COLOUR(current_veh);
									else
										VEHICLE::CLEAR_VEHICLE_CUSTOM_SECONDARY_COLOUR(current_veh);
									VEHICLE::SET_VEHICLE_COLOURS(current_veh, owned_mods[MOD_PRIMARY_COL], owned_mods[MOD_SECONDARY_COL]);
								});

							if (ImGui::Selectable("Chrome", color_type == 0))
								color_type = 0;
							if (ImGui::Selectable("Classic", color_type == 1))
								color_type = 1;
							if (ImGui::Selectable("Matte", color_type == 2))
								color_type = 2;
							if (ImGui::Selectable("Metals", color_type == 3))
								color_type = 3;

							ImGui::EndListBox();
						}
					}
					else if (color_to_change == 7)
						ImGui::SameLine();

					if (color_type == 8)
					{
						// custom color

						static float color[3] = {1, 1, 1};
						auto color_r          = &owned_mods[MOD_PRIMARY_COL_R];
						auto color_g          = &owned_mods[MOD_PRIMARY_COL_G];
						auto color_b          = &owned_mods[MOD_PRIMARY_COL_B];

						if (color_to_change == 1)
						{
							color_r = &owned_mods[MOD_SECONDARY_COL_R];
							color_g = &owned_mods[MOD_SECONDARY_COL_G];
							color_b = &owned_mods[MOD_SECONDARY_COL_B];
						}
						else if (color_to_change == 2)
						{
							color_r = &owned_mods[MOD_TIRESMOKE_COL_R];
							color_g = &owned_mods[MOD_TIRESMOKE_COL_G];
							color_b = &owned_mods[MOD_TIRESMOKE_COL_B];
						}
						else if (color_to_change == 3)
						{
							color_r = &owned_mods[MOD_NEON_COL_R];
							color_g = &owned_mods[MOD_NEON_COL_G];
							color_b = &owned_mods[MOD_NEON_COL_B];
						}

						color[0] = (float)*color_r / 255;
						color[1] = (float)*color_g / 255;
						color[2] = (float)*color_b / 255;

						if (color_to_change == 5)
						{
							ImGui::SameLine();
							if (ImGui::BeginListBox("##tire_smoke_rgb", ImVec2(140, 254)))
							{
								for (const auto& it : lsc_tire_smoke_rgb)
								{
									auto& name = it.first;
									auto& rgb  = it.second;

									if (ImGui::Selectable(name.c_str(), false))
									{
										g_fiber_pool->queue_job([&rgb] {
											VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(current_veh, rgb[0], rgb[1], rgb[2]);
										});
										*color_r = rgb[0];
										*color_g = rgb[1];
										*color_b = rgb[2];
									}
								}

								ImGui::EndListBox();
							}
						}
						else if (color_to_change == 8)
						{
							ImGui::SameLine();
							if (ImGui::BeginListBox("##neon_rgb", ImVec2(140, 254)))
							{
								for (const auto& it : lsc_neon_rgb)
								{
									auto& name = it.first;
									auto& rgb  = it.second;

									if (ImGui::Selectable(name.c_str(), false))
									{
										g_fiber_pool->queue_job([&rgb] {
											VEHICLE::SET_VEHICLE_NEON_COLOUR(current_veh, rgb[0], rgb[1], rgb[2]);
										});
										*color_r = rgb[0];
										*color_g = rgb[1];
										*color_b = rgb[2];
									}
								}

								ImGui::EndListBox();
							}
						}

						ImGui::SameLine();
						ImGui::SetNextItemWidth(214);
						if (ImGui::ColorPicker3("Custom Vehicle Color", color, ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_DisplayHex))
						{
							*color_r = (int)(color[0] * 255);
							*color_g = (int)(color[1] * 255);
							*color_b = (int)(color[2] * 255);

							g_fiber_pool->queue_job([color_r, color_g, color_b] {
								switch (color_to_change)
								{
								case 0:
									VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(current_veh, *color_r, *color_g, *color_b);
									break;
								case 1:
									VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(current_veh, *color_r, *color_g, *color_b);
									break;
								case 5:
									VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(current_veh, *color_r, *color_g, *color_b);
									break;
								case 8:
									VEHICLE::SET_VEHICLE_NEON_COLOUR(current_veh, *color_r, *color_g, *color_b);
									break;
								}
							});
						}
					}
					else
					{
						// standard color

						int selected_color = 0;
						switch (color_type)
						{
						case 4: selected_color = owned_mods[MOD_PEARLESCENT_COL]; break;
						case 5: selected_color = owned_mods[MOD_WHEEL_COL]; break;
						case 6: selected_color = owned_mods[MOD_INTERIOR_COL]; break;
						case 7: selected_color = owned_mods[MOD_DASHBOARD_COL]; break;
						case 9: selected_color = owned_mods[MOD_XENON_COL]; break;
						default:
							selected_color = (color_to_change == 0) ? owned_mods[MOD_PRIMARY_COL] : owned_mods[MOD_SECONDARY_COL];
						}

						if (color_type != 9)
							ImGui::SameLine();

						if (ImGui::BeginListBox("##color", ImVec2(180, 254)))
						{
							switch (color_type)
							{
							case 0: //Chrome
							{
								if (ImGui::Selectable("Chrome", selected_color == COLOR_CHROME))
								{
									if (color_to_change == 0)
										owned_mods[MOD_PRIMARY_COL] = COLOR_CHROME;
									else
										owned_mods[MOD_SECONDARY_COL] = COLOR_CHROME;
									g_fiber_pool->queue_job([] {
										VEHICLE::SET_VEHICLE_COLOURS(current_veh, owned_mods[MOD_PRIMARY_COL], owned_mods[MOD_SECONDARY_COL]);
									});
								}
								break;
							}
							case 1: //Classic
							{
								for (const auto& [color, name] : lsc_classic_colors)
								{
									if (ImGui::Selectable(name.c_str(), selected_color == color))
									{
										selected_color = color;
										if (color_to_change == 0)
											owned_mods[MOD_PRIMARY_COL] = color;
										else
											owned_mods[MOD_SECONDARY_COL] = color;
										g_fiber_pool->queue_job([] {
											VEHICLE::SET_VEHICLE_COLOURS(current_veh, owned_mods[MOD_PRIMARY_COL], owned_mods[MOD_SECONDARY_COL]);
										});
									}
								}
								break;
							}
							case 2: //Matte
							{
								for (const auto& [color, name] : lsc_matte_colors)
								{
									if (ImGui::Selectable(name.c_str(), selected_color == color))
									{
										selected_color = color;
										if (color_to_change == 0)
											owned_mods[MOD_PRIMARY_COL] = color;
										else
											owned_mods[MOD_SECONDARY_COL] = color;
										g_fiber_pool->queue_job([] {
											VEHICLE::SET_VEHICLE_COLOURS(current_veh, owned_mods[MOD_PRIMARY_COL], owned_mods[MOD_SECONDARY_COL]);
										});
									}
								}
								break;
							}
							case 3: //Metals
							{
								for (const auto& [color, name] : lsc_metal_colors)
								{
									if (ImGui::Selectable(name.c_str(), selected_color == color))
									{
										selected_color = color;
										if (color_to_change == 0)
											owned_mods[MOD_PRIMARY_COL] = color;
										else
											owned_mods[MOD_SECONDARY_COL] = color;
										g_fiber_pool->queue_job([] {
											VEHICLE::SET_VEHICLE_COLOURS(current_veh, owned_mods[MOD_PRIMARY_COL], owned_mods[MOD_SECONDARY_COL]);
										});
									}
								}
								break;
							}
							case 4: //Pearlescent
							{
								for (const auto& [color, name] : lsc_classic_colors)
								{
									if (ImGui::Selectable(name.c_str(), selected_color == color))
									{
										selected_color                  = color;
										owned_mods[MOD_PEARLESCENT_COL] = color;
										g_fiber_pool->queue_job([] {
											VEHICLE::SET_VEHICLE_EXTRA_COLOURS(current_veh, owned_mods[MOD_PEARLESCENT_COL], owned_mods[MOD_WHEEL_COL]);
										});
									}
								}
								break;
							}
							case 5: //Wheel Color
							{
								for (const auto& [color, name] : lsc_classic_colors)
								{
									if (ImGui::Selectable(name.c_str(), selected_color == color))
									{
										selected_color            = color;
										owned_mods[MOD_WHEEL_COL] = color;
										g_fiber_pool->queue_job([] {
											VEHICLE::SET_VEHICLE_EXTRA_COLOURS(current_veh, owned_mods[MOD_PEARLESCENT_COL], owned_mods[MOD_WHEEL_COL]);
										});
									}
								}
								break;
							}
							case 6: //Interior Color
							{
								for (const auto& [color, name] : lsc_classic_colors)
								{
									if (ImGui::Selectable(name.c_str(), selected_color == color))
									{
										selected_color               = color;
										owned_mods[MOD_INTERIOR_COL] = color;
										g_fiber_pool->queue_job([] {
											VEHICLE::SET_VEHICLE_EXTRA_COLOUR_5(current_veh, owned_mods[MOD_INTERIOR_COL]);
										});
									}
								}
								break;
							}
							case 7: //Dashboard Color
							{
								for (const auto& [color, name] : lsc_classic_colors)
								{
									if (ImGui::Selectable(name.c_str(), selected_color == color))
									{
										selected_color                = color;
										owned_mods[MOD_DASHBOARD_COL] = color;
										g_fiber_pool->queue_job([] {
											VEHICLE::SET_VEHICLE_EXTRA_COLOUR_6(current_veh, owned_mods[MOD_DASHBOARD_COL]);
										});
									}
								}
								break;
							}
							case 9: //Headlight Color
							{
								for (const auto& [color, name] : lsc_headlight_colors)
								{
									if (ImGui::Selectable(name.c_str(), selected_color == color))
									{
										selected_color            = color;
										owned_mods[MOD_XENON_COL] = color;
										g_fiber_pool->queue_job([] {
											VEHICLE::SET_VEHICLE_XENON_LIGHT_COLOR_INDEX(current_veh, owned_mods[MOD_XENON_COL]);
										});
									}
								}
								break;
							}
							}

							ImGui::EndListBox();
						}
					}
				}
			}
		}
		else
			ImGui::Text("Please enter a vehicle.");
	}
}
