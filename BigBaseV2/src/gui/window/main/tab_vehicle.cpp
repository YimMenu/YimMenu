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
						if (ENTITY::IS_ENTITY_DEAD(veh, false)) return notify::above_map("Invalid vehicle handle...");

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
					for (const speedo_meter &speedo : speedo_meters)
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

			ImGui::EndTabItem();
		}
	}
}