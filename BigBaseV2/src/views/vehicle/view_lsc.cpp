#include "fiber_pool.hpp"
#include "natives.hpp"
#include "script.hpp"
#include "services/vehicle_helper/vehicle_helper.hpp"
#include "core/data/lsc_types.hpp"
#include "views/view.hpp"
#include "util/vehicle.hpp"
#include <imgui_internal.h>

namespace big
{
	void view::lsc()
	{
		static Vehicle player_vehicle = 0;
		static bool ready = true;

		static std::map<int, int> owned_mods;
		static std::map<int, std::string> slot_display_names;
		static std::map<int, std::map<int, std::string>> mod_display_names;
		static std::map<std::string, std::vector<int>> front_wheel_map;
		static std::map<std::string, std::vector<int>> rear_wheel_map;

		static int primary_color_rgb[3] = { 255, 255, 255 };
		static int secondary_color_rgb[3] = { 255, 255, 255 };
		static int tire_smoke_color_rgb[3] = { 255, 255, 255 };
		static int neon_light_color_rgb[3] = { 255, 255, 255 };

		static int selected_slot = -1;
		static bool is_bennys = false;
		static int front_wheel_stock_mod = -1;
		static bool front_wheel_custom = false;
		static int rear_wheel_stock_mod = -1;
		static bool rear_wheel_custom = false;

		static bool can_tires_burst = false;
		static bool tiresmoke = false;
		static bool turbo = false;

		static bool xenon = false;
		static bool neon_left = false;
		static bool neon_right = false;
		static bool neon_front = false;
		static bool neon_back = false;

		static int primary_color = 0; 
		static int secondary_color = 0; 
		static int pearlescent = 0; 
		static int wheel_color = 0; 
		static int interior_color = 0; 
		static int dashboard_color = 0;
		static int headlight_color = 0;

		static Hash veh_model_hash = 0;

		if (self::veh == 0 || player_vehicle != self::veh)
		{
			if (self::veh == 0)
			{
				owned_mods.clear();
				slot_display_names.clear();
				mod_display_names.clear();
				front_wheel_map.clear();
				rear_wheel_map.clear();
				player_vehicle = 0;

				selected_slot = -1;
				ImGui::Text("Please enter a vehicle.");
				return;
			}
		}

		if (player_vehicle != self::veh && ready == true)
		{
			ready = false;
			player_vehicle = self::veh;

			g_fiber_pool->queue_job([] {
				if (!HUD::HAS_THIS_ADDITIONAL_TEXT_LOADED("MOD_MNU", 10))
				{
					HUD::CLEAR_ADDITIONAL_TEXT(10, TRUE);
					HUD::REQUEST_ADDITIONAL_TEXT("MOD_MNU", 10);
					script::get_current()->yield();
				}

				VEHICLE::GET_VEHICLE_COLOURS(player_vehicle, &primary_color, &secondary_color);
				VEHICLE::GET_VEHICLE_EXTRA_COLOURS(player_vehicle, &pearlescent, &wheel_color);
				VEHICLE::GET_VEHICLE_INTERIOR_COLOR_(player_vehicle, &interior_color);
				VEHICLE::GET_VEHICLE_DASHBOARD_COLOR_(player_vehicle, &dashboard_color);
				headlight_color = VEHICLE::GET_VEHICLE_XENON_LIGHTS_COLOR_(player_vehicle);

				VEHICLE::GET_VEHICLE_CUSTOM_PRIMARY_COLOUR(player_vehicle, &primary_color_rgb[0], &primary_color_rgb[1], &primary_color_rgb[2]);
				VEHICLE::GET_VEHICLE_CUSTOM_SECONDARY_COLOUR(player_vehicle, &secondary_color_rgb[0], &secondary_color_rgb[1], &secondary_color_rgb[2]);
				VEHICLE::GET_VEHICLE_TYRE_SMOKE_COLOR(player_vehicle, &tire_smoke_color_rgb[0], &tire_smoke_color_rgb[1], &tire_smoke_color_rgb[2]);
				VEHICLE::GET_VEHICLE_NEON_LIGHTS_COLOUR_(player_vehicle, &neon_light_color_rgb[0], &neon_light_color_rgb[1], &neon_light_color_rgb[2]);

				can_tires_burst = !VEHICLE::GET_VEHICLE_TYRES_CAN_BURST(player_vehicle);
				tiresmoke = VEHICLE::IS_TOGGLE_MOD_ON(player_vehicle, MOD_TYRE_SMOKE);
				turbo = VEHICLE::IS_TOGGLE_MOD_ON(player_vehicle, MOD_TURBO);

				xenon = VEHICLE::IS_TOGGLE_MOD_ON(player_vehicle, MOD_XENON_LIGHTS);
				neon_left = VEHICLE::IS_VEHICLE_NEON_LIGHT_ENABLED_(player_vehicle, NEON_LEFT);
				neon_right = VEHICLE::IS_VEHICLE_NEON_LIGHT_ENABLED_(player_vehicle, NEON_RIGHT);
				neon_front = VEHICLE::IS_VEHICLE_NEON_LIGHT_ENABLED_(player_vehicle, NEON_FRONT);
				neon_back = VEHICLE::IS_VEHICLE_NEON_LIGHT_ENABLED_(player_vehicle, NEON_BACK);

				front_wheel_custom = VEHICLE::GET_VEHICLE_MOD_VARIATION(player_vehicle, MOD_FRONTWHEEL);
				rear_wheel_custom = VEHICLE::GET_VEHICLE_MOD_VARIATION(player_vehicle, MOD_REARWHEEL);

				std::map<int, int> tmp_owned_mods;
				std::map<int, std::string> tmp_slot_display_names;
				std::map<int, std::map<int, std::string>> tmp_mod_display_names;
				std::map<std::string, std::vector<int>> tmp_front_wheel_map;
				std::map<std::string, std::vector<int>> tmp_rear_wheel_map;

				tmp_slot_display_names[MOD_PLATE_STYLE] = "Plate Style";
				tmp_slot_display_names[MOD_WINDOW_TINT] = "Window Tint";
				tmp_slot_display_names[MOD_WHEEL_TYPE] = "Wheel Type";

				tmp_owned_mods[MOD_PLATE_STYLE] = VEHICLE::GET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(player_vehicle);
				tmp_mod_display_names[MOD_PLATE_STYLE].insert(lsc_plate_styles.begin(), lsc_plate_styles.end());

				tmp_owned_mods[MOD_WINDOW_TINT] = VEHICLE::GET_VEHICLE_WINDOW_TINT(player_vehicle);
				tmp_mod_display_names[MOD_WINDOW_TINT].insert(lsc_window_tint_types.begin(), lsc_window_tint_types.end());

				tmp_owned_mods[MOD_WHEEL_TYPE] = VEHICLE::GET_VEHICLE_WHEEL_TYPE(player_vehicle);
				tmp_mod_display_names[MOD_WHEEL_TYPE].insert(lsc_wheel_styles.begin(), lsc_wheel_styles.end());

				is_bennys = tmp_owned_mods[MOD_WHEEL_TYPE] == WHEEL_TYPE_BENNYS_ORIGINAL ||
					tmp_owned_mods[MOD_WHEEL_TYPE] == WHEEL_TYPE_BENNYS_BESPOKE ||
					tmp_owned_mods[MOD_WHEEL_TYPE] == WHEEL_TYPE_OPEN_WHEEL ||
					tmp_owned_mods[MOD_WHEEL_TYPE] == WHEEL_TYPE_STREET ||
					tmp_owned_mods[MOD_WHEEL_TYPE] == WHEEL_TYPE_TRACK;

				for (int slot = MOD_SPOILERS; slot <= MOD_LIVERY; slot++)
				{
					int count = VEHICLE::GET_NUM_VEHICLE_MODS(player_vehicle, slot);
					if (count > 0)
					{
						int owner_mod = VEHICLE::GET_VEHICLE_MOD(player_vehicle, slot);
						tmp_owned_mods[slot] = owner_mod;

						std::string slot_name = vehicle_helper::get_mod_slot_name(slot, player_vehicle);
						if (slot_name.empty())
						{
							continue;
						}
						tmp_slot_display_names[slot] = slot_name;

						std::map<int, std::string> mod_names;
						for (int mod = -1; mod < count; mod++)
						{
							bool is_repeated = false;

							std::string mod_name = vehicle_helper::get_mod_name(mod, slot, count, player_vehicle);
							if (mod_name.empty() || mod_name == "NULL")
							{
								continue;
							}

							if (slot == MOD_FRONTWHEEL)
							{
								if (is_bennys)
								{
									if (mod_name.rfind("Chrome ", 0) == 0)
									{
										std::string new_mod_name = mod_name.substr(7);

										if (tmp_front_wheel_map[new_mod_name].size() > 0)
										{
											mod_name = new_mod_name;
										}

									}
								}

								tmp_front_wheel_map[mod_name].push_back(mod);

								if (mod == owner_mod)
								{
									front_wheel_stock_mod = tmp_front_wheel_map[mod_name][0];
								}

								if (tmp_front_wheel_map[mod_name].size() > 1)
								{
									is_repeated = true;

									if (!is_bennys)
									{
										if (mod == owner_mod)
										{
											front_wheel_custom = true;
										}
									}
								}
							}
							else if(slot == MOD_REARWHEEL)
							{
								tmp_rear_wheel_map[mod_name].push_back(mod);

								if (mod == owner_mod)
								{
									rear_wheel_stock_mod = tmp_rear_wheel_map[mod_name][0];
								}

								if (tmp_rear_wheel_map[mod_name].size() > 1)
								{
									is_repeated = true;

									if (mod == owner_mod)
									{
										rear_wheel_custom = true;
									}
								}
							}

							if (!is_repeated)
							{
								mod_names[mod] = mod_name;
							}
						}
						tmp_mod_display_names[slot] = mod_names;
					}
				}

				owned_mods = tmp_owned_mods;
				slot_display_names = tmp_slot_display_names;
				mod_display_names = tmp_mod_display_names;
				front_wheel_map = tmp_front_wheel_map;
				rear_wheel_map = tmp_rear_wheel_map;

				ready = true;
			});
		}

		components::button("Start LS Customs", [] {
			g->vehicle.ls_customs = true;
		});
		ImGui::SameLine();
		if (components::button("Max Vehicle"))
		{
			g_fiber_pool->queue_job([] {
				vehicle::max_vehicle(self::veh);

				// refresh mod names
				player_vehicle = 0;
			});
		}

		ImGui::Separator();

		static char plate[9];

		ImGui::SetNextItemWidth(200.f);
		components::input_text_with_hint("##plate", "Plate Number", plate, sizeof(plate), ImGuiInputTextFlags_None);
		ImGui::SameLine();
		if (components::button("Change Plate Number"))
		{
			g_fiber_pool->queue_job([] {
				vehicle::set_plate(self::veh, plate);
			});
		}

		ImGui::Separator();
		components::small_text("Mod Options");

		if (ImGui::Checkbox("Bulletproof Tires", &can_tires_burst))
		{
			g_fiber_pool->queue_job([] {
				VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(player_vehicle, !can_tires_burst);
			});
		}
		ImGui::SameLine();
		if (ImGui::Checkbox("Turbo", &turbo))
		{
			g_fiber_pool->queue_job([] {
				VEHICLE::TOGGLE_VEHICLE_MOD(player_vehicle, MOD_TURBO, turbo);
			});
		}
		ImGui::SameLine();
		if (ImGui::Checkbox("Tiresmoke", &tiresmoke))
		{
			g_fiber_pool->queue_job([] {
				VEHICLE::TOGGLE_VEHICLE_MOD(player_vehicle, MOD_TYRE_SMOKE, tiresmoke);
			});
		}

		ImGui::Separator();

		ImGui::BeginGroup();

		components::small_text("Slot");
		if (ImGui::ListBoxHeader("##slot", ImVec2(200, 200)))
		{
			for (const auto& [slot, name] : slot_display_names)
			{
				if (ImGui::Selectable(name.c_str(), slot == selected_slot))
				{
					selected_slot = slot;
				}
			}
			ImGui::ListBoxFooter();
		}

		ImGui::EndGroup();

		if (selected_slot != -1)
		{
			static auto wheel_stock_mod = &front_wheel_stock_mod;
			static auto wheel_custom = &front_wheel_custom;
			static bool is_wheel_mod = false;

			if (selected_slot == MOD_FRONTWHEEL)
			{
				is_wheel_mod = true;
			}
			else if (selected_slot == MOD_REARWHEEL)
			{
				wheel_stock_mod = &rear_wheel_stock_mod;
				wheel_custom = &rear_wheel_custom;
				is_wheel_mod = true;
			}
			else
			{
				is_wheel_mod = false;
			}

			ImGui::SameLine();
			ImGui::BeginGroup();

			components::small_text("Mod");
			if (ImGui::ListBoxHeader("##mod", ImVec2(240, 200)))
			{
				for (const auto& it : mod_display_names[selected_slot])
				{
					const auto& mod = it.first;
					const auto& name = it.second;

					bool item_selected = mod == owned_mods[selected_slot];

					if (is_wheel_mod)
					{
						item_selected = mod == *wheel_stock_mod;
					}

					if (ImGui::Selectable(name.c_str(), item_selected))
					{
						g_fiber_pool->queue_job([&mod] {
							NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(self::veh);

							if (selected_slot >= 0)
							{
								VEHICLE::SET_VEHICLE_MOD(player_vehicle, selected_slot, mod, false);
								owned_mods[selected_slot] = mod;

								if (is_wheel_mod)
								{
									*wheel_stock_mod = mod;
									*wheel_custom = false;
								}
							}
							else if (selected_slot == MOD_WINDOW_TINT)
							{
								VEHICLE::SET_VEHICLE_WINDOW_TINT(player_vehicle, mod);
								owned_mods[selected_slot] = mod;
							}
							else if (selected_slot == MOD_WHEEL_TYPE)
							{
								VEHICLE::SET_VEHICLE_WHEEL_TYPE(player_vehicle, mod);
								VEHICLE::SET_VEHICLE_MOD(player_vehicle, MOD_FRONTWHEEL, 0, false);
								VEHICLE::SET_VEHICLE_MOD(player_vehicle, MOD_REARWHEEL, 0, false);
								player_vehicle = 0;
							}
							else if (selected_slot == MOD_PLATE_STYLE)
							{
								VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(player_vehicle, mod);
								owned_mods[selected_slot] = mod;
							}
						});
					}
				}
				ImGui::ListBoxFooter();
			}

			ImGui::EndGroup();

			if (
				is_wheel_mod && *wheel_stock_mod != -1
			) {
				auto wheel_map = front_wheel_map;

				if (selected_slot == MOD_REARWHEEL)
				{
					wheel_map = rear_wheel_map;
				}

				ImGui::SameLine();
				ImGui::BeginGroup();

				components::small_text("Style");
				if (ImGui::ListBoxHeader("##style", ImVec2(200, 200)))
				{
					std::string mod_name = mod_display_names[selected_slot][*wheel_stock_mod];
					auto wheel_mods = wheel_map[mod_name];

					for (int i = 0; i < wheel_mods.size(); i++)
					{
						int& mod = wheel_mods[i];

						bool should_custom = false;

						// bennys fix
						if (!is_bennys)
						{
							if (i == 0)
							{
								if (ImGui::Selectable("Stock", mod == owned_mods[selected_slot] && *wheel_custom == false))
								{
									g_fiber_pool->queue_job([&mod] {
										VEHICLE::SET_VEHICLE_MOD(player_vehicle, selected_slot, mod, false);
										player_vehicle = 0;
										});
								}
							}

							should_custom = true;
						}

						std::string label = "Style " + std::to_string(mod);
						if (ImGui::Selectable(label.c_str(), mod == owned_mods[selected_slot] && *wheel_custom == should_custom))
						{
							g_fiber_pool->queue_job([&mod, should_custom] {
								VEHICLE::SET_VEHICLE_MOD(player_vehicle, selected_slot, mod, should_custom);
								player_vehicle = 0;
							});
						}
					}
					ImGui::ListBoxFooter();
				}

				ImGui::EndGroup();
			}
		}



		ImGui::Separator();
		components::small_text("Neon Light Options");

		if (ImGui::Checkbox("Headlight##headlight_en", &xenon))
		{
			g_fiber_pool->queue_job([] {
				VEHICLE::TOGGLE_VEHICLE_MOD(player_vehicle, MOD_XENON_LIGHTS, xenon);
			});
		}
		ImGui::SameLine();
		if (ImGui::Checkbox("Left", &neon_left))
		{
			g_fiber_pool->queue_job([] {
				VEHICLE::SET_VEHICLE_NEON_LIGHT_ENABLED_(player_vehicle, NEON_LEFT, neon_left);
			});
		}
		ImGui::SameLine();
		if (ImGui::Checkbox("Right", &neon_right))
		{
			g_fiber_pool->queue_job([] {
				VEHICLE::SET_VEHICLE_NEON_LIGHT_ENABLED_(player_vehicle, NEON_RIGHT, neon_right);
			});
		}
		ImGui::SameLine();
		if (ImGui::Checkbox("Front", &neon_front))
		{
			g_fiber_pool->queue_job([] {
				VEHICLE::SET_VEHICLE_NEON_LIGHT_ENABLED_(player_vehicle, NEON_FRONT, neon_front);
			});
		}
		ImGui::SameLine();
		if (ImGui::Checkbox("Back", &neon_back))
		{
			g_fiber_pool->queue_job([] {
				VEHICLE::SET_VEHICLE_NEON_LIGHT_ENABLED_(player_vehicle, NEON_BACK, neon_back);
			});
		}
		ImGui::SameLine();
		components::button("Check All##neon_check_all", [] {
			xenon = true;
			neon_left = true;
			neon_right = true;
			neon_front = true;
			neon_back = true;

			VEHICLE::TOGGLE_VEHICLE_MOD(player_vehicle, MOD_XENON_LIGHTS, xenon);
			VEHICLE::SET_VEHICLE_NEON_LIGHT_ENABLED_(player_vehicle, NEON_LEFT, neon_left);
			VEHICLE::SET_VEHICLE_NEON_LIGHT_ENABLED_(player_vehicle, NEON_RIGHT, neon_right);
			VEHICLE::SET_VEHICLE_NEON_LIGHT_ENABLED_(player_vehicle, NEON_FRONT, neon_front);
			VEHICLE::SET_VEHICLE_NEON_LIGHT_ENABLED_(player_vehicle, NEON_BACK, neon_back);
		});
		ImGui::SameLine();
		components::button("Uncheck All##neon_uncheck_all", [] {
			xenon = false;
			neon_left = false;
			neon_right = false;
			neon_front = false;
			neon_back = false;

			VEHICLE::TOGGLE_VEHICLE_MOD(player_vehicle, MOD_XENON_LIGHTS, xenon);
			VEHICLE::SET_VEHICLE_NEON_LIGHT_ENABLED_(player_vehicle, NEON_LEFT, neon_left);
			VEHICLE::SET_VEHICLE_NEON_LIGHT_ENABLED_(player_vehicle, NEON_RIGHT, neon_right);
			VEHICLE::SET_VEHICLE_NEON_LIGHT_ENABLED_(player_vehicle, NEON_FRONT, neon_front);
			VEHICLE::SET_VEHICLE_NEON_LIGHT_ENABLED_(player_vehicle, NEON_BACK, neon_back);
		});

		ImGui::Separator();
		components::small_text("Color Options");

		static int color_to_change = 0;
		static int color_type = 8;

		if (
			(color_to_change == 7 && !xenon) ||
			(color_to_change == 5 && !tiresmoke)
		) {
			color_to_change = 0;
			color_type = 8;
		}

		if (ImGui::ListBoxHeader("##color_options", ImVec2(120, 254)))
		{
			if (ImGui::Selectable("Primary", color_to_change == 0, ImGuiSelectableFlags_SelectOnClick))
			{
				color_to_change = 0;
			}

			if (ImGui::Selectable("Secondary", color_to_change == 1))
			{
				color_to_change = 1;
			}

			if (ImGui::Selectable("Pearlescent", color_to_change == 2))
			{
				color_to_change = 2;
				color_type = 4;
			}

			if (ImGui::Selectable("Interior", color_to_change == 3))
			{
				color_to_change = 3;
				color_type = 6;
			}

			if (ImGui::Selectable("Dashboard", color_to_change == 4))
			{
				color_to_change = 4;
				color_type = 7;
			}

			if (!tiresmoke)
			{
				ImGui::BeginDisabled();
			}
			if (ImGui::Selectable("Tire Smoke", color_to_change == 5))
			{
				color_to_change = 5;
				color_type = 8;
			}
			if (!tiresmoke)
			{
				ImGui::EndDisabled();
			}

			if (ImGui::Selectable("Wheel Color", color_to_change == 6))
			{
				color_to_change = 6;
				color_type = 5;
			}

			if (!xenon)
			{
				ImGui::BeginDisabled();
			}
			if (ImGui::Selectable("Headlight##headlight_col", color_to_change == 7))
			{
				color_to_change = 7;
				color_type = 9;
			}
			if (!xenon)
			{
				ImGui::EndDisabled();
			}

			if (ImGui::Selectable("Neon", color_to_change == 8))
			{
				color_to_change = 8;
				color_type = 8;
			}

			ImGui::ListBoxFooter();
		}


		if (color_to_change == 0 || color_to_change == 1)
		{
			if (color_type > 3)
			{
				color_type = 8;
			}

			// primary and secondary color

			ImGui::SameLine();
			if (ImGui::ListBoxHeader("##colors", ImVec2(140, 254)))
			{
				if (ImGui::Selectable("Custom", color_type == 8, ImGuiSelectableFlags_SelectOnClick))
				{
					color_type = 8;
				}
				if (ImGui::Selectable("Remove Custom", false))
				{
					g_fiber_pool->queue_job([] {
						if (color_to_change == 0)
						{
							VEHICLE::CLEAR_VEHICLE_CUSTOM_PRIMARY_COLOUR(player_vehicle);
						}
						else
						{
							VEHICLE::CLEAR_VEHICLE_CUSTOM_SECONDARY_COLOUR(player_vehicle);
						}
						VEHICLE::SET_VEHICLE_COLOURS(player_vehicle, primary_color, secondary_color);
					});
				}

				if (ImGui::Selectable("Chrome", color_type == 0))
				{
					color_type = 0;
				}
				if (ImGui::Selectable("Classic", color_type == 1))
				{
					color_type = 1;
				}
				if (ImGui::Selectable("Matte", color_type == 2))
				{
					color_type = 2;
				}
				if (ImGui::Selectable("Metals", color_type == 3))
				{
					color_type = 3;
				}
				ImGui::ListBoxFooter();
			}
		}
		else if (color_to_change == 7)
		{
			ImGui::SameLine();
		}


		if (color_type == 8)
		{
			// custom color

			static float color[3] = { 1, 1, 1 };
			auto color_rgb = primary_color_rgb;

			if (color_to_change == 1)
			{
				color_rgb = secondary_color_rgb;
			}
			else if (color_to_change == 2)
			{
				color_rgb = tire_smoke_color_rgb;
			}
			else if (color_to_change == 3)
			{
				color_rgb = neon_light_color_rgb;
			}

			color[0] = (float)color_rgb[0] / 255;
			color[1] = (float)color_rgb[1] / 255;
			color[2] = (float)color_rgb[2] / 255;

			if (color_to_change == 5)
			{
				ImGui::SameLine();
				if (ImGui::ListBoxHeader("##tire_smoke_rgb", ImVec2(140, 254)))
				{
					for (const auto& it : lsc_tire_smoke_rgb)
					{
						auto& name = it.first;
						auto& rgb = it.second;

						if (ImGui::Selectable(name.c_str(), false))
						{
							g_fiber_pool->queue_job([&rgb] {
								VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(player_vehicle, rgb[0], rgb[1], rgb[2]);
							});
							color_rgb[0] = rgb[0];
							color_rgb[1] = rgb[1];
							color_rgb[2] = rgb[2];
						}

					}

					ImGui::ListBoxFooter();
				}
			}
			else if (color_to_change == 8)
			{
				ImGui::SameLine();
				if (ImGui::ListBoxHeader("##neon_rgb", ImVec2(140, 254)))
				{
					for (const auto& it : lsc_neon_rgb)
					{
						auto& name = it.first;
						auto& rgb = it.second;

						if (ImGui::Selectable(name.c_str(), false))
						{
							g_fiber_pool->queue_job([&rgb] {
								VEHICLE::SET_VEHICLE_NEON_LIGHTS_COLOUR_(player_vehicle, rgb[0], rgb[1], rgb[2]);
							});
							color_rgb[0] = rgb[0];
							color_rgb[1] = rgb[1];
							color_rgb[2] = rgb[2];
						}
					}

					ImGui::ListBoxFooter();
				}
			}

			ImGui::SameLine();
			ImGui::SetNextItemWidth(214);
			if (ImGui::ColorPicker3("Custom VehColor", color, ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_DisplayHex))
			{
				color_rgb[0] = (int)(color[0] * 255);
				color_rgb[1] = (int)(color[1] * 255);
				color_rgb[2] = (int)(color[2] * 255);

				g_fiber_pool->queue_job([color_rgb] {
					switch (color_to_change)
					{
					case 0:
						VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(player_vehicle, color_rgb[0], color_rgb[1], color_rgb[2]);
						break;
					case 1:
						VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(player_vehicle, color_rgb[0], color_rgb[1], color_rgb[2]);
						break;
					case 5:
						VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(player_vehicle, color_rgb[0], color_rgb[1], color_rgb[2]);
						break;
					case 8:
						VEHICLE::SET_VEHICLE_NEON_LIGHTS_COLOUR_(player_vehicle, color_rgb[0], color_rgb[1], color_rgb[2]);
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
			case 4:
				selected_color = pearlescent;
				break;
			case 5:
				selected_color = wheel_color;
				break;
			case 6:
				selected_color = interior_color;
				break;
			case 7:
				selected_color = dashboard_color;
				break;
			case 9:
				selected_color = headlight_color;
				break;
			default:
				selected_color = (color_to_change == 0) ? primary_color : secondary_color;
			}

			if (color_type != 9)
			{
				ImGui::SameLine();
			}

			if (ImGui::ListBoxHeader("##color", ImVec2(180, 254)))
			{
				switch (color_type)
				{
				case 0: //Chrome
				{
					if (ImGui::Selectable("Chrome", selected_color == COLOR_CHROME))
					{
						if (color_to_change == 0)
						{
							primary_color = COLOR_CHROME;
						}
						else
						{
							secondary_color = COLOR_CHROME;
						}

						g_fiber_pool->queue_job([] {
							VEHICLE::SET_VEHICLE_COLOURS(player_vehicle, primary_color, secondary_color);
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
							{
								primary_color = color;
							}
							else
							{
								secondary_color = color;
							}

							g_fiber_pool->queue_job([] {
								VEHICLE::SET_VEHICLE_COLOURS(player_vehicle, primary_color, secondary_color);
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
							{
								primary_color = color;
							}
							else
							{
								secondary_color = color;
							}

							g_fiber_pool->queue_job([] {
								VEHICLE::SET_VEHICLE_COLOURS(player_vehicle, primary_color, secondary_color);
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
							{
								primary_color = color;
							}
							else
							{
								secondary_color = color;
							}

							g_fiber_pool->queue_job([] {
								VEHICLE::SET_VEHICLE_COLOURS(player_vehicle, primary_color, secondary_color);
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
							selected_color = color;
							pearlescent = color;

							g_fiber_pool->queue_job([] {
								VEHICLE::SET_VEHICLE_EXTRA_COLOURS(player_vehicle, pearlescent, wheel_color);
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
							selected_color = color;
							wheel_color = color;

							g_fiber_pool->queue_job([] {
								VEHICLE::SET_VEHICLE_EXTRA_COLOURS(player_vehicle, pearlescent, wheel_color);
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
							selected_color = color;
							interior_color = color;

							g_fiber_pool->queue_job([] {
								VEHICLE::SET_VEHICLE_INTERIOR_COLOR_(player_vehicle, interior_color);
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
							selected_color = color;
							dashboard_color = color;

							g_fiber_pool->queue_job([] {
								VEHICLE::SET_VEHICLE_DASHBOARD_COLOR_(player_vehicle, dashboard_color);
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
							selected_color = color;
							headlight_color = color;

							g_fiber_pool->queue_job([] {
								VEHICLE::SET_VEHICLE_XENON_LIGHTS_COLOR_(player_vehicle, headlight_color);
							});
						}
					}
					break;
				}
				}

				ImGui::ListBoxFooter();
			}
		}
	}
}
