#include "core/enums.hpp"
#include "core/settings.hpp"
#include "util/vehicle.hpp"
#include "views/view.hpp"

const int wheelIndexes[4]         = {0, 1, 4, 5};
const char* driving_style_names[] = {"Law-Abiding", "The Road Is Yours"};

namespace big
{
	void view_low_rider_veh_controls()
	{
		ImGui::SeparatorText("Lowrider vehicle controls");

		static int is_lowrider = 1; // 0 = no, 1 = undefined, 2 = yes

		if (self::veh)
		{
			if (is_lowrider == 1)
			{
				is_lowrider = 0;

				int& is_lowrider_ref = is_lowrider; // Helper reference

				g_fiber_pool->queue_job([&is_lowrider_ref]() {
					if (VEHICLE::IS_TOGGLE_MOD_ON(self::veh, 18))
						is_lowrider_ref = 2;
				});
			}
		}
		else if (is_lowrider != 1)
			is_lowrider = 1;

		if (is_lowrider == 2)
		{
			static float maxWheelRaiseFactor;

			ImGui::PushItemWidth(200);
			ImGui::SliderFloat("maxWheelRaiseFactor", &maxWheelRaiseFactor, 1, 4);
			ImGui::PopItemWidth();

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

	void view_seat_changer()
	{
		ImGui::SeparatorText("Seat Changer");

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
		}
		else if (is_veh_checked)
		{
			is_veh_checked = false;
			seats.clear();
		}

		if (seats.size())
		{
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
			components::small_text("Please sit in a vehicle");
	}

	void view::fun_vehicle()
	{
		view_seat_changer();

		ImGui::Spacing();
		ImGui::SeparatorText("Auto Drive");
		{
			if (self::veh)
			{
				float auto_drive_speed_in_miph = vehicle::mps_to_miph(g.vehicle.auto_drive_speed);
				if (ImGui::SliderFloat("Top Speed (mi/h)", &auto_drive_speed_in_miph, 2.2369f, 335.535f, "%.1f"))
					g.vehicle.auto_drive_speed = vehicle::miph_to_mps(auto_drive_speed_in_miph);

				if (ImGui::BeginCombo("Driving Style", driving_style_names[(int)g.vehicle.auto_drive_style]))
				{
					for (int i = 0; i < 2; i++)
						if (ImGui::Selectable(driving_style_names[i], g.vehicle.auto_drive_style == (AutoDriveStyle)i))
							g.vehicle.auto_drive_style = (AutoDriveStyle)i;
					ImGui::EndCombo();
				}

				if (components::button("To Objective"))
					g.vehicle.auto_drive_destination = AutoDriveDestination::OBJECTITVE;
				ImGui::SameLine();
				if (components::button("To Waypoint"))
					g.vehicle.auto_drive_destination = AutoDriveDestination::WAYPOINT;
			}
			else
				components::small_text("Please sit in a vehicle");
		}

		ImGui::Spacing();
		view_low_rider_veh_controls();
	}
}
