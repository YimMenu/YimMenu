#include "core/data/speedo_meters.hpp"
#include "fiber_pool.hpp"
#include "main_tabs.hpp"
#include "script.hpp"
#include "util/blip.hpp"
#include "util/entity.hpp"
#include "util/notify.hpp"
#include "util/vehicle.hpp"

namespace big
{
	static char model[12];

	void tab_main::tab_vehicle()
	{
		if (ImGui::BeginTabItem("Vehicle"))
		{
			if (ImGui::TreeNode("General"))
			{
				ImGui::Checkbox("God Mode", &g.vehicle.god_mode);
				ImGui::SameLine();

				if (ImGui::Button("Bring Personal Vehicle"))
				{
					QUEUE_JOB_BEGIN_CLAUSE()
					{
						Vector3 location;

						if (!blip::get_blip_location(location, 225, 0) && !blip::get_blip_location(location, 226, 0)) return notify::above_map("No personal vehicle found, was it destroyed?");

						Vehicle veh = vehicle::get_closest_to_location(location, 2.f);
						if (veh == 0) return notify::above_map("Invalid vehicle handle...");

						location = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);

						vehicle::bring(veh, location);
					}QUEUE_JOB_END_CLAUSE
				}

				if (ImGui::Button("Repair"))
				{
					QUEUE_JOB_BEGIN_CLAUSE()
					{
						Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);

						vehicle::repair(veh);
					}QUEUE_JOB_END_CLAUSE
				}
				ImGui::SameLine();

				if (ImGui::Button("Handling"))
					g.window.handling = true;

				ImGui::TreePop();
			}

			if (ImGui::TreeNode("Speedo Meter"))
			{
				SpeedoMeter selected = g.vehicle.speedo_meter.type;

				ImGui::Text("Position");

				float pos[2];
				pos[0] = g.vehicle.speedo_meter.x;
				pos[1] = g.vehicle.speedo_meter.y;
				if (ImGui::SliderFloat2("###speedo_pos", pos, .001f, .999f, "%.3f"))
				{
					g.vehicle.speedo_meter.x = pos[0];
					g.vehicle.speedo_meter.y = pos[1];
				}

				ImGui::Checkbox("Left Sided", &g.vehicle.speedo_meter.left_side);

				ImGui::Separator();

				ImGui::Text("Type:");
				if (ImGui::BeginCombo("###speedo_type", speedo_meters[(int)selected].name))
				{
					for (const speedo_meter& speedo : speedo_meters)
					{
						if (ImGui::Selectable(speedo.name, speedo.id == selected))
						{
							g.vehicle.speedo_meter.type = speedo.id;
						}

						if (speedo.id == selected)
							ImGui::SetItemDefaultFocus();
					}

					ImGui::EndCombo();
				}

				ImGui::TreePop();
			}

			ImGui::Checkbox("Horn Boost", &g.vehicle.horn_boost);

			static float max_vehicle_speed = 300.f;
			if (ImGui::SliderFloat("VEHICLE MAX SPEED", &max_vehicle_speed, 0.f, 6000.f))
			{
				g_fiber_pool->queue_job([]
					{
						NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false));

						while (!NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false)))
							script::get_current()->yield(5ms);
						VEHICLE::SET_VEHICLE_MAX_SPEED_(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), max_vehicle_speed);
					});
			}
			ImGui::Separator();


			static int selected_seat = 0;
			const char* const vehicle_seats[]
			{
				"Passenger ",
				"Left Rear",
				"RightRear",
			};

			ImGui::Combo("##vehicle_seat", &selected_seat, vehicle_seats, IM_ARRAYSIZE(vehicle_seats));

			ImGui::SameLine();

			if (ImGui::Button("teleport to nearest vehicle"))
			{
				g_fiber_pool->queue_job([]
					{
						LOG(INFO) << selected_seat;
						auto pos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
						PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), VEHICLE::GET_CLOSEST_VEHICLE(pos.x, pos.y, pos.z, 1000, 0, 70), selected_seat);
					});
			}

			ImGui::EndTabItem();
		}
	}
}