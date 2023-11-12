#include "core/data/vehicle_ammo_special.hpp"
#include "core/enums.hpp"
#include "core/settings/vehicle.hpp"
#include "util/delete_entity.hpp"
#include "util/mobile.hpp"
#include "util/teleport.hpp"
#include "util/vehicle.hpp"
#include "views/view.hpp"


constexpr int wheelIndexes[4]{0, 1, 4, 5};
const char* driving_style_names[]{"Law-Abiding", "The Road Is Yours"};
constexpr auto MAX_VEHICLE_DOORS = 6;
const char* const doornames[MAX_VEHICLE_DOORS]{
    "D_1",
    "D_2",
    "D_3",
    "D_4",
    "Bon",
    "Trk",
};
const std::map<const char*, const char*> radio_stations{{"RADIO_27_DLC_PRHEI4", "iFruit Radio"}, {"RADIO_01_CLASS_ROCK", "Los Santos Rock Radio"}, {"RADIO_02_POP", "Non-Stop-Pop FM"}, {"RADIO_03_HIPHOP_NEW", "Radio Los Santos"}, {"RADIO_04_PUNK", "Channel X"}, {"RADIO_06_COUNTRY", "Rebel Radio"}, {"RADIO_07_DANCE_01", "Soulwax FM"}, {"RADIO_08_MEXICAN", "East Los FM"}, {"RADIO_09_HIPHOP_OLD", "West Coast Classics"}, {"RADIO_12_REGGAE", "Blue Ark"}, {"RADIO_13_JAZZ", "Worldwide FM"}, {"RADIO_14_DANCE_02", "FlyLo FM"}, {"RADIO_15_MOTOWN", "The Lowdown 91.1"}, {"RADIO_20_THELAB", "The Lab"}, {"RADIO_16_SILVERLAKE", "Radio Mirror Park"}, {"RADIO_17_FUNK", "Space 103.2"}, {"RADIO_18_90S_ROCK", "Vinewood Boulevard Radio"}, {"RADIO_21_DLC_XM17", "Blonded Los Santos 97.8 FM"}, {"RADIO_22_DLC_BATTLE_MIX1_RADIO", "Los Santos Underground Radio"}, {"RADIO_19_USER", "Self Radio"}, {"OFF", "Off"}};

void render_range_comp(const char* name, float& ref, float step, float step_fast, const char* format, float orig_val, float defVal)
{
	ImGui::InputFloat(name, &ref, step, step_fast, format);
	ImGui::Text(("Original: " + std::to_string(orig_val)).c_str());
	ImGui::SameLine(0, 2.0f * ImGui::GetTextLineHeight());
	ImGui::Text(("Default: " + std::to_string(defVal)).c_str());
	ImGui::Spacing();
}

namespace big
{
	static void jump_lowrider_wheels(bool fl, bool fr, bool bl, bool br, float maxWheelRaiseFactor)
	{
		if (fl)
			VEHICLE::SET_HYDRAULIC_SUSPENSION_RAISE_FACTOR(self::last_veh, 0, maxWheelRaiseFactor);
		if (fr)
			VEHICLE::SET_HYDRAULIC_SUSPENSION_RAISE_FACTOR(self::last_veh, 1, maxWheelRaiseFactor);
		if (bl)
			VEHICLE::SET_HYDRAULIC_SUSPENSION_RAISE_FACTOR(self::last_veh, 4, maxWheelRaiseFactor);
		if (br)
			VEHICLE::SET_HYDRAULIC_SUSPENSION_RAISE_FACTOR(self::last_veh, 5, maxWheelRaiseFactor);

		script::get_current()->yield(250ms);

		VEHICLE::SET_HYDRAULIC_SUSPENSION_RAISE_FACTOR(self::last_veh, 0, 0);
		VEHICLE::SET_HYDRAULIC_SUSPENSION_RAISE_FACTOR(self::last_veh, 1, 0);
		VEHICLE::SET_HYDRAULIC_SUSPENSION_RAISE_FACTOR(self::last_veh, 4, 0);
		VEHICLE::SET_HYDRAULIC_SUSPENSION_RAISE_FACTOR(self::last_veh, 5, 0);
	}

	static inline void render_first_block()
	{
		components::button("Mors Mutual Fix All Vehicles", [] {
			int amount_fixed = mobile::mors_mutual::fix_all();
			g_notification_service->push_success("Mobile", std::vformat("{} vehicle{} been fixed.", std::make_format_args(amount_fixed, amount_fixed == 1 ? " has" : "s have")));
		});
		ImGui::SameLine();
		components::button("Repair", [] {
			vehicle::repair(self::veh);
		});
		ImGui::SameLine(0, 2.0f * ImGui::GetTextLineHeight());
		components::button("Delete Current", [] {
			if (ENTITY::DOES_ENTITY_EXIST(self::veh))
				TASK::CLEAR_PED_TASKS_IMMEDIATELY(self::ped), entity::delete_entity(self::veh);
		});
		ImGui::SameLine(0, 2.0f * ImGui::GetTextLineHeight());
		components::button("Freeze", [&] {
			ENTITY::FREEZE_ENTITY_POSITION(self::veh, true);
		});
		ImGui::SameLine();
		components::button("UnFreeze", [&] {
			ENTITY::FREEZE_ENTITY_POSITION(self::veh, false);
		});
	}

	static inline void render_teleport()
	{
		components::command_button<"pvtp">();
		ImGui::SameLine();
		components::button("Bring PV", [] {
			vehicle::bring(mobile::mechanic::get_personal_vehicle(), self::pos, true);
		});
		ImGui::SameLine();
		components::button("TP to last vehicle", [] {
			if (self::last_veh)
				teleport::into_vehicle(self::last_veh);
		});
	}

	static inline void render_general()
	{
		ImGui::BeginGroup();
		{
			components::command_checkbox<"vehgodmode">();

			components::command_checkbox<"vehjump">();

			components::command_checkbox<"blockhoming">();
		}
		ImGui::EndGroup();
		ImGui::SameLine();
		ImGui::BeginGroup();
		{
			components::command_checkbox<"seatbelt">();

			components::command_checkbox<"veh_boost">();
		}
		ImGui::EndGroup();
		ImGui::SameLine();
		ImGui::BeginGroup();
		{
			components::command_checkbox<"allvehsinheists">();

			components::command_checkbox<"customvehweaps">();
			components::options_modal("Custom Vehicle Weapons", [] {
				components::sub_title("Missile");

				render_range_comp("Speed##rocket",
				    g_vehicle_ammo_special.rocket_launch_speed,
				    10,
				    100,
				    "%.1f",
				    g_vehicle_ammo_special.m_rocket_launch_speed,
				    ROCKET_LAUNCH_SPEED);
				render_range_comp("Range##rocket",
				    g_vehicle_ammo_special.rocket_range,
				    50,
				    100,
				    "%.1f",
				    g_vehicle_ammo_special.m_rocket_range,
				    ROCKET_RANGE);
				render_range_comp("Lock-on Range",
				    g_vehicle_ammo_special.rocket_lock_on_range,
				    50,
				    100,
				    "%.1f",
				    g_vehicle_ammo_special.m_rocket_lock_on_range,
				    ROCKET_LOCK_ON_RANGE);
				render_range_comp("Lock-on Time",
				    g_vehicle_ammo_special.rocket_time_before_homing,
				    0.01,
				    0.1,
				    "%.2f",
				    g_vehicle_ammo_special.m_rocket_time_before_homing,
				    ROCKET_TIME_BEFORE_HOMING);
				render_range_comp("Life Time",
				    g_vehicle_ammo_special.rocket_lifetime,
				    0.1,
				    1,
				    "%.1f",
				    g_vehicle_ammo_special.m_rocket_lifetime,
				    ROCKET_LIFETIME);

				ImGui::Checkbox("Smart Missiles", &g_vehicle_ammo_special.rocket_improve_tracking);
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("Improves current missile's tracking ability.");

				ImGui::Spacing();

				components::button("Apply Original", [] {
					g_vehicle_ammo_special.rocket_launch_speed  = g_vehicle_ammo_special.m_rocket_launch_speed;
					g_vehicle_ammo_special.rocket_range         = g_vehicle_ammo_special.m_rocket_range;
					g_vehicle_ammo_special.rocket_lock_on_range = g_vehicle_ammo_special.m_rocket_lock_on_range;
					g_vehicle_ammo_special.rocket_time_before_homing = g_vehicle_ammo_special.m_rocket_time_before_homing;
					g_vehicle_ammo_special.rocket_lifetime = g_vehicle_ammo_special.m_rocket_lifetime;
				});
				ImGui::SameLine();
				components::button("Apply Defaults", [] {
					g_vehicle_ammo_special.rocket_launch_speed       = ROCKET_LAUNCH_SPEED;
					g_vehicle_ammo_special.rocket_range              = ROCKET_RANGE;
					g_vehicle_ammo_special.rocket_lock_on_range      = ROCKET_LOCK_ON_RANGE;
					g_vehicle_ammo_special.rocket_time_before_homing = ROCKET_TIME_BEFORE_HOMING;
					g_vehicle_ammo_special.rocket_lifetime           = ROCKET_LIFETIME;
				});
			});
		}
		ImGui::EndGroup();
	}

	static inline void render_fun_feats()
	{
		static bool is_veh_checked;
		static eVehicleLockState door_locked_state;
		static bool veh_all_door_open     = false;
		static const char* selected_radio = "OFF";
		static std::map<int, bool> seats;
		static bool force_lowrider;
		static float maxWheelRaiseFactor = 2;
		static bool indicator_left, indicator_right;

		if (self::last_veh)
		{
			if (!is_veh_checked)
			{
				is_veh_checked = true;
				g_fiber_pool->queue_job([] {
					std::map<int, bool> tmp_seats;

					int num_of_seats = VEHICLE::GET_VEHICLE_MAX_NUMBER_OF_PASSENGERS(self::last_veh);

					for (int i = -1; i < num_of_seats; i++)
						tmp_seats[i] = VEHICLE::IS_VEHICLE_SEAT_FREE(self::last_veh, i, true);

					seats = tmp_seats;

					door_locked_state = (eVehicleLockState)VEHICLE::GET_VEHICLE_DOOR_LOCK_STATUS(self::last_veh);
				});
			}

			ImGui::BeginGroup();
			{
				components::sub_title("Basic Controls");

				components::small_text("Seats");
				{
					for (auto& it : seats)
					{
						int idx = it.first;

						if (!it.second)
							ImGui::BeginDisabled();

						bool& is_veh_checked_ref = is_veh_checked; // Helper reference

						components::button(idx >= 0 ? ("S_" + std::to_string(idx + 1)) : "S_0", [idx, &is_veh_checked_ref] {
							if (VEHICLE::IS_VEHICLE_SEAT_FREE(self::last_veh, idx, true))
								PED::SET_PED_INTO_VEHICLE(self::ped, self::last_veh, idx);

							is_veh_checked_ref = false; // recheck available seats
						});

						if (!it.second)
							ImGui::EndDisabled();

						// if ((idx + 2) % 5 != 0)
						ImGui::SameLine();
					}
					ImGui::NewLine();
				}

				components::small_text("Doors");
				{
					components::button(door_locked_state == eVehicleLockState::VEHICLELOCK_LOCKED ? "Unlock doors" : "Lock doors", [=] {
						if (door_locked_state == eVehicleLockState::VEHICLELOCK_LOCKED)
							VEHICLE::SET_VEHICLE_DOORS_LOCKED(self::last_veh, (int)eVehicleLockState::VEHICLELOCK_NONE);
						else
							VEHICLE::SET_VEHICLE_DOORS_LOCKED(self::last_veh, (int)eVehicleLockState::VEHICLELOCK_LOCKED);
						door_locked_state = (eVehicleLockState)VEHICLE::GET_VEHICLE_DOOR_LOCK_STATUS(self::last_veh);
					});
					ImGui::SameLine();
					components::button("Toggle Doors", [] {
						vehicle::operate_vehicle_door(self::last_veh, eDoorId::VEH_EXT_DOOR_INVALID_ID, veh_all_door_open = !veh_all_door_open);
					});
					ImGui::SameLine();
					for (int i = 0; i < MAX_VEHICLE_DOORS; i++)
					{
						components::button(doornames[i], [=] {
							vehicle::operate_vehicle_door(self::last_veh, (eDoorId)i, !(VEHICLE::GET_VEHICLE_DOOR_ANGLE_RATIO(self::last_veh, i) > 0.0f));
						});
						ImGui::SameLine();
					}
					ImGui::NewLine();
				}

				ImGui::BeginGroup();
				components::small_text("Windows");
				{
					components::button("Roll Down All", [] {
						VEHICLE::ROLL_DOWN_WINDOWS(self::last_veh);
					});
					ImGui::SameLine();
					components::button("Roll Up All", [] {
						for (int i = 0; i < 4; i++)
							VEHICLE::ROLL_UP_WINDOW(self::last_veh, i);
					});
				}
				ImGui::EndGroup();
				ImGui::SameLine();
				ImGui::BeginGroup();
				components::small_text("Interior lights");
				{
					components::button("On###ILON", [] {
						VEHICLE::SET_VEHICLE_INTERIORLIGHT(self::last_veh, true);
					});
					ImGui::SameLine();
					components::button("Off###ILOFF", [] {
						VEHICLE::SET_VEHICLE_INTERIORLIGHT(self::last_veh, false);
					});
				}
				ImGui::EndGroup();
				ImGui::SameLine();
				ImGui::BeginGroup();
				components::small_text("Signal");
				{
					components::button("Left###SignalL", [] {
						VEHICLE::SET_VEHICLE_INDICATOR_LIGHTS(self::last_veh, 1, indicator_left = !indicator_left);
					});
					ImGui::SameLine();
					components::button("Right###SignalR", [] {
						VEHICLE::SET_VEHICLE_INDICATOR_LIGHTS(self::last_veh, 0, indicator_right = !indicator_right);
					});
				}
				ImGui::EndGroup();

				components::small_text("Radio");
				{
					components::button("Reset to active radio", [] {
						auto curr_station = AUDIO::GET_PLAYER_RADIO_STATION_NAME();

						if (!curr_station)
							selected_radio = "OFF";
						else
						{
							auto it = std::find_if(radio_stations.begin(), radio_stations.end(), [curr_station](const std::pair<const char* const, const char*>& e) {
								return std::strcmp(e.first, curr_station) == 0;
							});
							if (it != radio_stations.end())
								selected_radio = it->first;
						}
					});
					ImGui::Spacing();
					if (ImGui::BeginListBox("###radioStations", {300, 200}))
					{
						for (auto& radio : radio_stations)
							if (ImGui::Selectable(radio.second, radio.first == selected_radio))
							{
								selected_radio = radio.first;
								g_fiber_pool->queue_job([=] {
									AUDIO::SET_VEH_RADIO_STATION(self::last_veh, radio.first);
								});
							}
							else if (radio.first == selected_radio)
								ImGui::SetItemDefaultFocus();

						ImGui::EndListBox();
					}
				}
			}
			ImGui::EndGroup();
			ImGui::SameLine(0, 2.0f * ImGui::GetTextLineHeight());
			ImGui::BeginGroup();
			{
				ImGui::BeginGroup();
				{
					components::sub_title("Auto Drive");
					if (self::veh)
					{
						float auto_drive_speed_in_miph = vehicle::mps_to_miph(g_vehicle.auto_drive_speed);

						ImGui::PushItemWidth(200);
						if (ImGui::SliderFloat("Top Speed (mi/h)", &auto_drive_speed_in_miph, 2.2369f, 335.535f, "%.1f"))
							g_vehicle.auto_drive_speed = vehicle::miph_to_mps(auto_drive_speed_in_miph);

						if (ImGui::BeginCombo("Driving Style", driving_style_names[(int)g_vehicle.auto_drive_style]))
						{
							for (int i = 0; i < 2; i++)
								if (ImGui::Selectable(driving_style_names[i], g_vehicle.auto_drive_style == (AutoDriveStyle)i))
									g_vehicle.auto_drive_style = (AutoDriveStyle)i;
							ImGui::EndCombo();
						}
						ImGui::PopItemWidth();

						ImGui::BeginDisabled(g_vehicle.is_auto_driving);
						if (components::button("To Objective"))
							g_vehicle.auto_drive_destination = AutoDriveDestination::OBJECTITVE;
						ImGui::SameLine();
						if (components::button("To Waypoint"))
							g_vehicle.auto_drive_destination = AutoDriveDestination::WAYPOINT;
						ImGui::EndDisabled();
					}
					else
						components::small_text("Please sit in a vehicle");
				}
				ImGui::EndGroup();

				ImGui::Dummy(ImVec2(0.0f, ImGui::GetTextLineHeight()));

				ImGui::BeginGroup();
				{
					components::sub_title("Lowrider Controls");

					ImGui::Checkbox("force###forceLowrider", &force_lowrider);

					ImGui::Spacing();

					if (force_lowrider)
					{
						ImGui::SetNextItemWidth(200);
						ImGui::SliderFloat("maxWheelRaiseFactor", &maxWheelRaiseFactor, 1, 4);

						ImGui::Spacing();

						for (int i = 0; i < 4; ++i)
						{
							components::button("Raise W" + std::to_string(i + 1), [&, wheelIndex = wheelIndexes[i]] {
								bool raised = VEHICLE::GET_HYDRAULIC_SUSPENSION_RAISE_FACTOR(self::last_veh, wheelIndex) < maxWheelRaiseFactor ? false : true;
								if (raised)
									VEHICLE::SET_HYDRAULIC_WHEEL_STATE(self::last_veh, wheelIndex, 0, maxWheelRaiseFactor, 1);
								else
								{
									VEHICLE::SET_HYDRAULIC_WHEEL_STATE(self::last_veh, wheelIndex, 4, maxWheelRaiseFactor, 1);
									script::get_current()->yield(250ms);
									VEHICLE::SET_HYDRAULIC_WHEEL_STATE(self::last_veh, wheelIndex, 1, maxWheelRaiseFactor, 1);
								}
							});
							ImGui::SameLine();
							// components::button("Raise Wheel " + std::to_string(i + 1) + " (instant)", [&, wheelIndex = wheelIndexes[i]] {
							// 	bool raised = VEHICLE::GET_HYDRAULIC_SUSPENSION_RAISE_FACTOR(self::last_veh, wheelIndex) < maxWheelRaiseFactor ? false : true;
							// 	VEHICLE::SET_HYDRAULIC_SUSPENSION_RAISE_FACTOR(self::last_veh, wheelIndex, raised ? 0 : maxWheelRaiseFactor);
							// });
						}
						ImGui::NewLine();

						components::button("Raise all", [&] {
							VEHICLE::SET_HYDRAULIC_WHEEL_STATE(self::last_veh, 0, 4, maxWheelRaiseFactor, 0);
							VEHICLE::SET_HYDRAULIC_WHEEL_STATE(self::last_veh, 1, 4, maxWheelRaiseFactor, 0);
							VEHICLE::SET_HYDRAULIC_WHEEL_STATE(self::last_veh, 4, 4, maxWheelRaiseFactor, 0);
							VEHICLE::SET_HYDRAULIC_WHEEL_STATE(self::last_veh, 5, 4, maxWheelRaiseFactor, 0);

							VEHICLE::SET_HYDRAULIC_WHEEL_STATE(self::last_veh, 0, 1, maxWheelRaiseFactor, 0);
							VEHICLE::SET_HYDRAULIC_WHEEL_STATE(self::last_veh, 1, 1, maxWheelRaiseFactor, 0);
							VEHICLE::SET_HYDRAULIC_WHEEL_STATE(self::last_veh, 4, 1, maxWheelRaiseFactor, 0);
							VEHICLE::SET_HYDRAULIC_WHEEL_STATE(self::last_veh, 5, 1, maxWheelRaiseFactor, 0);
						});
						ImGui::SameLine();
						components::button("Lower all", [&] {
							VEHICLE::SET_HYDRAULIC_VEHICLE_STATE(self::last_veh, 0);
						});

						components::button("Jump all", [&] {
							jump_lowrider_wheels(true, true, true, true, maxWheelRaiseFactor);
						});
						ImGui::SameLine();
						components::button("Jump L", [&] {
							jump_lowrider_wheels(true, false, true, false, maxWheelRaiseFactor);
						});
						ImGui::SameLine();
						components::button("Jump R", [&] {
							jump_lowrider_wheels(false, true, false, true, maxWheelRaiseFactor);
						});
						ImGui::SameLine();
						components::button("Jump F", [&] {
							jump_lowrider_wheels(true, true, false, false, maxWheelRaiseFactor);
						});
						ImGui::SameLine();
						components::button("Jump B", [&] {
							jump_lowrider_wheels(false, false, true, true, maxWheelRaiseFactor);
						});
					}
				}
				ImGui::EndGroup();
			}
			ImGui::EndGroup();
		}
		else
		{
			components::small_text("Please sit in a vehicle");
			if (is_veh_checked)
			{
				force_lowrider = is_veh_checked = false;
				seats.clear();
			}
		}
	}

	void view::vehicle()
	{
		ImGui::Spacing();

		render_first_block();

		ImGui::SeparatorText("###teleport");

		render_teleport();

		ImGui::SeparatorText("###General");

		render_general();

		ImGui::SeparatorText("Fun###funFeatures");

		render_fun_feats();
	}
}
