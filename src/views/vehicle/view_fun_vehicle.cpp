#include "core/enums.hpp"
#include "core/settings/vehicle.hpp"
#include "util/vehicle.hpp"
#include "views/view.hpp"

constexpr int wheelIndexes[4]     = {0, 1, 4, 5};
const char* driving_style_names[] = {"Law-Abiding", "The Road Is Yours"};

constexpr auto MAX_VEHICLE_DOORS = 6;
const char* const doornames[MAX_VEHICLE_DOORS]{
    "Front left",
    "Front right",
    "Back left",
    "Back right",
    "Bonnet",
    "Trunk",
};

namespace big
{
	void view::fun_vehicle()
	{
		if (ImGui::CollapsingHeader("Vehicle controls"))
		{
			static Vehicle curr_veh;
			static eVehicleLockState door_locked_state;

			if (self::veh && curr_veh != self::veh)
			{
				curr_veh = self::veh;

				eVehicleLockState& door_locked_state_ref = door_locked_state; // Helper reference
				g_fiber_pool->queue_job([&door_locked_state_ref] {
					door_locked_state_ref = (eVehicleLockState)VEHICLE::GET_VEHICLE_DOOR_LOCK_STATUS(curr_veh);
				});
			}

			if (curr_veh)
			{
				ImGui::SeparatorText("Engine");
				{
					components::button("Engine On", [] {
						VEHICLE::SET_VEHICLE_ENGINE_ON(curr_veh, true, true, false);
					});
					ImGui::SameLine();
					components::button("Engine Off", [] {
						VEHICLE::SET_VEHICLE_ENGINE_ON(curr_veh, false, true, false);
					});
				}
				ImGui::SeparatorText("Doors");
				{
					components::button(door_locked_state == eVehicleLockState::VEHICLELOCK_LOCKED ? "Unlock doors" : "Lock doors", [=] {
						if (door_locked_state == eVehicleLockState::VEHICLELOCK_LOCKED)
							VEHICLE::SET_VEHICLE_DOORS_LOCKED(curr_veh, (int)eVehicleLockState::VEHICLELOCK_NONE);
						else
							VEHICLE::SET_VEHICLE_DOORS_LOCKED(curr_veh, (int)eVehicleLockState::VEHICLELOCK_LOCKED);
						door_locked_state = (eVehicleLockState)VEHICLE::GET_VEHICLE_DOOR_LOCK_STATUS(curr_veh);
					});

					components::button("Open All", [=] {
						vehicle::operate_vehicle_door(curr_veh, eDoorId::VEH_EXT_DOOR_INVALID_ID, true);
					});
					ImGui::SameLine();
					components::button("Close All", [=] {
						vehicle::operate_vehicle_door(curr_veh, eDoorId::VEH_EXT_DOOR_INVALID_ID, false);
					});
					for (int i = 0; i < MAX_VEHICLE_DOORS; i++)
					{
						components::button(doornames[i], [=] {
							vehicle::operate_vehicle_door(curr_veh, (eDoorId)i, !(VEHICLE::GET_VEHICLE_DOOR_ANGLE_RATIO(curr_veh, i) > 0.0f));
						});
						if (i % 2 == 0)
							ImGui::SameLine();
					}
				}
				ImGui::SeparatorText("Windows");
				{
					components::button("Roll Down All", [] {
						VEHICLE::ROLL_DOWN_WINDOWS(curr_veh);
					});
					ImGui::SameLine();
					components::button("Roll Up All", [] {
						for (int i = 0; i < 4; i++)
							VEHICLE::ROLL_UP_WINDOW(curr_veh, i);
					});
				}
				ImGui::SeparatorText("lights");
				{
					components::button("Interior lights on", [] {
						VEHICLE::SET_VEHICLE_INTERIORLIGHT(curr_veh, true);
					});
					ImGui::SameLine();
					components::button("Interior lights off", [] {
						VEHICLE::SET_VEHICLE_INTERIORLIGHT(curr_veh, false);
					});
				}
			}
			else
				components::small_text("Please sit in a vehicle");
		}
		ImGui::Spacing();
		if (ImGui::CollapsingHeader("Seat Changer"))
		{
			static bool is_veh_checked;
			static std::map<int, bool> seats;

			if (self::veh)
			{
				if (!is_veh_checked)
				{
					is_veh_checked = true;
					g_fiber_pool->queue_job([] {
						std::map<int, bool> tmp_seats;

						int num_of_seats = VEHICLE::GET_VEHICLE_MAX_NUMBER_OF_PASSENGERS(self::veh);

						for (int i = -1; i < num_of_seats; i++)
							tmp_seats[i] = VEHICLE::IS_VEHICLE_SEAT_FREE(self::veh, i, true);

						seats = tmp_seats;
					});
				}

				for (auto& it : seats)
				{
					int idx = it.first;

					if (!it.second)
						ImGui::BeginDisabled();

					bool& is_veh_checked_ref = is_veh_checked; // Helper reference

					components::button(idx >= 0 ? ("Seat " + std::to_string(idx + 1)) : "Driver", [idx, &is_veh_checked_ref] {
						if (VEHICLE::IS_VEHICLE_SEAT_FREE(self::veh, idx, true))
							PED::SET_PED_INTO_VEHICLE(self::ped, self::veh, idx);

						is_veh_checked_ref = false; // recheck available seats
					});

					if (!it.second)
						ImGui::EndDisabled();

					if ((idx + 2) % 5 != 0)
						ImGui::SameLine();
				}
				ImGui::NewLine();
			}
			else
			{
				components::small_text("Please sit in a vehicle");
				if (is_veh_checked)
				{
					is_veh_checked = false;
					seats.clear();
				}
			}
		}
		ImGui::Spacing();
		if (ImGui::CollapsingHeader("Auto Drive"))
		{
			if (self::veh)
			{
				float auto_drive_speed_in_miph = vehicle::mps_to_miph(g_vehicle.auto_drive_speed);
				if (ImGui::SliderFloat("Top Speed (mi/h)", &auto_drive_speed_in_miph, 2.2369f, 335.535f, "%.1f"))
					g_vehicle.auto_drive_speed = vehicle::miph_to_mps(auto_drive_speed_in_miph);

				if (ImGui::BeginCombo("Driving Style", driving_style_names[(int)g_vehicle.auto_drive_style]))
				{
					for (int i = 0; i < 2; i++)
						if (ImGui::Selectable(driving_style_names[i], g_vehicle.auto_drive_style == (AutoDriveStyle)i))
							g_vehicle.auto_drive_style = (AutoDriveStyle)i;
					ImGui::EndCombo();
				}

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
		ImGui::Spacing();
		if (ImGui::CollapsingHeader("Lowrider Vehicle controls"))
		{
			static int is_lowrider = 1; // 0 = no, 1 = undefined, 2 = yes
			static bool force;

			if (self::veh)
			{
				if (is_lowrider == 1)
				{
					is_lowrider          = 0;
					int& is_lowrider_ref = is_lowrider; // Helper reference
					g_fiber_pool->queue_job([&is_lowrider_ref]() {
						if (VEHICLE::IS_TOGGLE_MOD_ON(self::veh, 18))
							is_lowrider_ref = 2;
					});
				}

				ImGui::Checkbox("force###forceLowrider", &force);
				ImGui::Spacing();

				if (force || is_lowrider == 2)
				{
					static float maxWheelRaiseFactor;

					ImGui::SetNextItemWidth(200);
					ImGui::SliderFloat("maxWheelRaiseFactor", &maxWheelRaiseFactor, 1, 4);

					ImGui::BeginGroup();
					{
						for (int i = 0; i < 4; ++i)
						{
							components::button("Raise Wheel " + std::to_string(i + 1) + " (smooth)", [&, wheelIndex = wheelIndexes[i]] {
								bool raised = VEHICLE::GET_HYDRAULIC_SUSPENSION_RAISE_FACTOR(self::veh, wheelIndex) < maxWheelRaiseFactor ? false : true;
								if (raised)
									VEHICLE::SET_HYDRAULIC_WHEEL_STATE(self::veh, wheelIndex, 0, maxWheelRaiseFactor, 1);
								else
								{
									VEHICLE::SET_HYDRAULIC_WHEEL_STATE(self::veh, wheelIndex, 4, maxWheelRaiseFactor, 1);
									script::get_current()->yield(250ms);
									VEHICLE::SET_HYDRAULIC_WHEEL_STATE(self::veh, wheelIndex, 1, maxWheelRaiseFactor, 1);
								}
							});
							// ImGui::SameLine();
							// components::button("Raise Wheel " + std::to_string(i + 1) + " (instant)", [&, wheelIndex = wheelIndexes[i]] {
							// 	bool raised = VEHICLE::GET_HYDRAULIC_SUSPENSION_RAISE_FACTOR(self::veh, wheelIndex) < maxWheelRaiseFactor ? false : true;
							// 	VEHICLE::SET_HYDRAULIC_SUSPENSION_RAISE_FACTOR(self::veh, wheelIndex, raised ? 0 : maxWheelRaiseFactor);
							// });
						}
					}
					ImGui::EndGroup();
					ImGui::SameLine();
					ImGui::BeginGroup();
					{
						components::button("Raise all wheels (smooth)", [&] {
							VEHICLE::SET_HYDRAULIC_WHEEL_STATE(self::veh, 0, 4, maxWheelRaiseFactor, 0);
							VEHICLE::SET_HYDRAULIC_WHEEL_STATE(self::veh, 1, 4, maxWheelRaiseFactor, 0);
							VEHICLE::SET_HYDRAULIC_WHEEL_STATE(self::veh, 4, 4, maxWheelRaiseFactor, 0);
							VEHICLE::SET_HYDRAULIC_WHEEL_STATE(self::veh, 5, 4, maxWheelRaiseFactor, 0);

							VEHICLE::SET_HYDRAULIC_WHEEL_STATE(self::veh, 0, 1, maxWheelRaiseFactor, 0);
							VEHICLE::SET_HYDRAULIC_WHEEL_STATE(self::veh, 1, 1, maxWheelRaiseFactor, 0);
							VEHICLE::SET_HYDRAULIC_WHEEL_STATE(self::veh, 4, 1, maxWheelRaiseFactor, 0);
							VEHICLE::SET_HYDRAULIC_WHEEL_STATE(self::veh, 5, 1, maxWheelRaiseFactor, 0);
						});
						components::button("Lower all wheels (smooth)", [&] {
							VEHICLE::SET_HYDRAULIC_VEHICLE_STATE(self::veh, 0);
						});
						components::button("Jump wheels", [&] {
							VEHICLE::SET_HYDRAULIC_SUSPENSION_RAISE_FACTOR(self::veh, 0, maxWheelRaiseFactor);
							VEHICLE::SET_HYDRAULIC_SUSPENSION_RAISE_FACTOR(self::veh, 1, maxWheelRaiseFactor);
							VEHICLE::SET_HYDRAULIC_SUSPENSION_RAISE_FACTOR(self::veh, 4, maxWheelRaiseFactor);
							VEHICLE::SET_HYDRAULIC_SUSPENSION_RAISE_FACTOR(self::veh, 5, maxWheelRaiseFactor);
							script::get_current()->yield(250ms);
							VEHICLE::SET_HYDRAULIC_SUSPENSION_RAISE_FACTOR(self::veh, 0, 0);
							VEHICLE::SET_HYDRAULIC_SUSPENSION_RAISE_FACTOR(self::veh, 1, 0);
							VEHICLE::SET_HYDRAULIC_SUSPENSION_RAISE_FACTOR(self::veh, 4, 0);
							VEHICLE::SET_HYDRAULIC_SUSPENSION_RAISE_FACTOR(self::veh, 5, 0);
						});
					}
					ImGui::EndGroup();
				}
				else
					components::small_text("Please sit in a lowrider vehicle");
			}
			else
			{
				components::small_text("Please sit in a vehicle");
				if (is_lowrider != 1)
					is_lowrider = 1;
			}
		}
	}
}
