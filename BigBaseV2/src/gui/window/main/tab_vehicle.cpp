#include "core/data/speedo_meters.hpp"
#include "fiber_pool.hpp"
#include "main_tabs.hpp"
#include "script.hpp"
#include "util/blip.hpp"
#include "util/entity.hpp"
#include "util/notify.hpp"
#include "util/vehicle.hpp"
#include "features.hpp"

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
				ImGui::Checkbox("Untargetable +", &g.vehicle.untargetable);

				if (ImGui::Button("Repair"))
				{
					QUEUE_JOB_BEGIN_CLAUSE()
					{
						Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);

						vehicle::repair(veh);
						VEHICLE::SET_VEHICLE_CAN_SAVE_IN_GARAGE(veh, true);
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

						NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false));

						while (!NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false)))
							script::get_current()->yield(5ms);
						VEHICLE::SET_VEHICLE_MAX_SPEED_(PED::GET_VEHICLE_PED_IS_USING(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::PLAYER_ID())), max_vehicle_speed);
			}
			ImGui::Separator();
			
			if (ImGui::SliderFloat("Vehicle torque", &features::max_vehicle_torque, 0.f, 6000.f) ||
				ImGui::Button("Apply"))
			{
		
					VEHICLE::_SET_VEHICLE_ENGINE_TORQUE_MULTIPLIER(PED::GET_VEHICLE_PED_IS_USING(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::PLAYER_ID())), features::max_vehicle_torque);
				
			}
			if (ImGui::SliderFloat("Vehicle Engine", &features::max_vehicle_engine, 0.f, 6000.f) ||
				ImGui::Button("Apply"))
			{
					VEHICLE::_SET_VEHICLE_ENGINE_POWER_MULTIPLIER(PED::GET_VEHICLE_PED_IS_USING(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(PLAYER::PLAYER_ID())), features::max_vehicle_engine);
			}

			static int selected_door = 0;
				const char* const vehicle_doors[]
				{
					"driver",
					"Passenger ",
					"Left Rear",
					"Right Rear",
					"hood",
					"5",
					"6",
					"7"
				};
				ImGui::Combo("vehicle door", &selected_door, vehicle_doors, IM_ARRAYSIZE(vehicle_doors));
				if (ImGui::Button("open selected door"))
				{
					g_fiber_pool->queue_job([]
					{
						VEHICLE::SET_VEHICLE_DOOR_OPEN(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), selected_door, false, true);
					});
				}

				ImGui::SameLine();

				if (ImGui::Button("close selected door"))
				{
					g_fiber_pool->queue_job([]
					{
						VEHICLE::SET_VEHICLE_DOOR_SHUT(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), selected_door, true);
					});
				}

			ImGui::EndTabItem();
		}
	}
}