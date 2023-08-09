#include "core/data/speed_units.hpp"
#include "core/enums.hpp"
#include "fiber_pool.hpp"
#include "script.hpp"
#include "services/gta_data/gta_data_service.hpp"
#include "services/model_preview/model_preview_service.hpp"
#include "util/mobile.hpp"
#include "util/vehicle.hpp"
#include "views/view.hpp"

#include <imgui_internal.h>

namespace big
{
	void view::fun_vehicle()
	{
		ImGui::SeparatorText("SEAT_CHANGER"_T.data());
		{
			static std::map<int, bool> seats;
			static bool ready = true;

			if (self::veh == 0)
			{
				seats.clear();
			}

			if (self::veh != 0 && ready == true)
			{
				ready = false;

				g_fiber_pool->queue_job([] {
					std::map<int, bool> tmp_seats;

					int num_of_seats = VEHICLE::GET_VEHICLE_MAX_NUMBER_OF_PASSENGERS(self::veh);

					for (int i = -1; i < num_of_seats; i++)
					{
						tmp_seats[i] = VEHICLE::IS_VEHICLE_SEAT_FREE(self::veh, i, true);
					}

					seats = tmp_seats;
					ready = true;
				});
			}

			if (seats.size() == 0)
			{
				ImGui::Text("PLEASE_ENTER_VEHICLE"_T.data());
			}
			else
			{
				for (auto& it : seats)
				{
					int idx = it.first;

					if (!it.second)
					{
						ImGui::BeginDisabled();
					}

					std::string name = "DRIVER"_T.data();

					if (idx >= 0)
					{
						name = "FUN_VEHICLE_SEAT"_T.data() + std::to_string(idx + 1);
					}

					if ((idx + 1) % 4 != 0)
					{
						ImGui::SameLine();
					}

					components::button(name, [idx] {
						PED::SET_PED_INTO_VEHICLE(self::ped, self::veh, idx);
					});
					if (!it.second)
					{
						ImGui::EndDisabled();
					}
				}
			}
		}
		ImGui::SeparatorText("AUTO_DRIVE"_T.data());
		{
			float auto_drive_speed_user_unit = vehicle::mps_to_speed(g.vehicle.auto_drive_speed, g.vehicle.speed_unit);
			if (ImGui::SliderFloat(
			        std::vformat("FUN_VEHICLE_TOP_SPEED"_T, std::make_format_args(speed_unit_strings[(int)g.vehicle.speed_unit]))
			            .c_str(),
			        &auto_drive_speed_user_unit,
			        vehicle::mps_to_speed(0.f, g.vehicle.speed_unit),
			        vehicle::mps_to_speed(150.f, g.vehicle.speed_unit),
			        "%.1f"))
			{
				g.vehicle.auto_drive_speed = vehicle::speed_to_mps(auto_drive_speed_user_unit, g.vehicle.speed_unit);
			}

			const char* driving_style_names[] = {"LAW_ABIDING"_T.data(), "ROAD_IS_YOURS"_T.data()};
			if (ImGui::BeginCombo("DRIVING_STYLE"_T.data(), driving_style_names[(int)g.vehicle.auto_drive_style]))
			{
				for (int i = 0; i < 2; i++)
				{
					if (ImGui::Selectable(driving_style_names[i], g.vehicle.auto_drive_style == (AutoDriveStyle)i))
					{
						g.vehicle.auto_drive_style = (AutoDriveStyle)i;
						g_notification_service->push_success("AUTO_DRIVE"_T.data(),
						    std::vformat("DRIVING_STYLE_SET_TO"_T.data(), std::make_format_args(driving_style_names[i])));
					}

					if (g.vehicle.auto_drive_style == (AutoDriveStyle)i)
					{
						ImGui::SetItemDefaultFocus();
					}
				}

				ImGui::EndCombo();
			}

			if (components::button("TO_OBJECTIVE"_T))
				g.vehicle.auto_drive_destination = AutoDriveDestination::OBJECTITVE;

			ImGui::SameLine();

			if (components::button("TO_WAYPOINT"_T))
				g.vehicle.auto_drive_destination = AutoDriveDestination::WAYPOINT;

			ImGui::SameLine();

			if (components::button("WANDER"_T))
				g.vehicle.auto_drive_destination = AutoDriveDestination::WANDER;

			ImGui::SameLine();

			if (components::button("EMERGENCY_STOP"_T))
				g.vehicle.auto_drive_destination = AutoDriveDestination::EMERGENCY_STOP;
		}

		ImGui::SeparatorText("DIRT_LEVEL"_T.data());
		{
			if (g_local_player == nullptr || g_local_player->m_vehicle == nullptr)
			{
				ImGui::Text("PLEASE_ENTER_VEHICLE"_T.data());
			}
			else if (g.vehicle.keep_vehicle_clean)
			{
				ImGui::Text("KEEP_VEHICLE_CLEAN"_T.data());
			}
			else if (g.vehicle.keep_vehicle_repaired) 
			{
				ImGui::Text("KEEP_VEHICLE_REPAIRED"_T.data());
			}
			else
			{
				ImGui::SliderFloat("DIRT_LEVEL"_T.data(), &g_local_player->m_vehicle->m_dirt_level, 0.f, 15.f, "%.1f");
			}
		}

		ImGui::SeparatorText("RAINBOW_PAINT"_T.data());
		{
			components::command_checkbox<"rainbowpri">("PRIMARY"_T);
			ImGui::SameLine();
			components::command_checkbox<"rainbowsec">("SECONDARY"_T);
			ImGui::SameLine();
			components::command_checkbox<"rainbowneons">("NEON"_T);
			ImGui::SameLine();
			components::command_checkbox<"rainbowsmoke">("SMOKE"_T);

			const char* rgb_types[] = {"OFF"_T.data(), "FADE"_T.data(), "SPASM"_T.data()};

			ImGui::SetNextItemWidth(120);
			if (ImGui::BeginCombo("RGB_TYPE"_T.data(), rgb_types[(int)g.vehicle.rainbow_paint.type]))
			{
				for (int i = 0; i < 3; i++)
				{
					bool itemSelected = (int)g.vehicle.rainbow_paint.type == i;

					if (ImGui::Selectable(rgb_types[i], itemSelected))
					{
						g.vehicle.rainbow_paint.type = (RainbowPaintType)i;
					}

					if (itemSelected)
					{
						ImGui::SetItemDefaultFocus();
					}
				}

				ImGui::EndCombo();
			}
			if (g.vehicle.rainbow_paint.type != RainbowPaintType::Off)
			{
				ImGui::SameLine();
				ImGui::SetNextItemWidth(150);
				components::command_int_slider<"rainbowspeed">("RGB_SPEED"_T);
			}
		}
		ImGui::Separator();

		const char* boost_behaviors[] = {"DEFAULT"_T.data(),
		    "INSTANT_REFILL"_T.data(),
		    "INFINITE"_T.data(),
		    "HOLD_FOR_BOOST"_T.data()};
		if (ImGui::BeginCombo("BOOST_BEHAVIOR"_T.data(), boost_behaviors[static_cast<int>(g.vehicle.boost_behavior)]))
		{
			for (int i = 0; i < 4; i++)
			{
				bool itemSelected = g.vehicle.boost_behavior == static_cast<eBoostBehaviors>(i);

				if (ImGui::Selectable(boost_behaviors[i], itemSelected))
				{
					g.vehicle.boost_behavior = static_cast<eBoostBehaviors>(i);
				}

				if (itemSelected)
				{
					ImGui::SetItemDefaultFocus();
				}
			}

			ImGui::EndCombo();
		}
		ImGui::SeparatorText("VEHICLE_FLY"_T.data());
		{
			ImGui::BeginGroup();

			components::command_checkbox<"vehiclefly">("ENABLED"_T);
			ImGui::Checkbox("DONT_STOP"_T.data(), &g.vehicle.fly.dont_stop);

			ImGui::EndGroup();
			ImGui::SameLine();
			ImGui::BeginGroup();

			ImGui::Checkbox("DISABLE_COLLISION"_T.data(), &g.vehicle.fly.no_collision);
			ImGui::Checkbox("STOP_ON_EXIT"_T.data(), &g.vehicle.fly.stop_on_exit);

			ImGui::EndGroup();

			float fly_speed_user_unit = vehicle::mps_to_speed(g.vehicle.fly.speed, g.vehicle.speed_unit);
			if (ImGui::SliderFloat(
			        std::vformat("FUN_VEHICLE_SPEED"_T.data(), std::make_format_args(speed_unit_strings[(int)g.vehicle.speed_unit]))
			            .c_str(),
			        &fly_speed_user_unit,
			        vehicle::mps_to_speed(0.f, g.vehicle.speed_unit),
			        vehicle::mps_to_speed(150.f, g.vehicle.speed_unit),
			        "%.1f"))
			{
				g.vehicle.fly.speed = vehicle::speed_to_mps(fly_speed_user_unit, g.vehicle.speed_unit);
			}
		}
	}
}
