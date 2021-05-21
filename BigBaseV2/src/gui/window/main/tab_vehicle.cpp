#include "core/data/speedo_meters.hpp"
#include "fiber_pool.hpp"
#include "gui/window/main/tabs.hpp"
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
			if (ImGui::Button("Bring Personal Vehicle"))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					Vector3 location;
					if (!blip::get_blip_location(location, 225, 0)) return notify::above_map("No personal vehicle found, was it destroyed?");

					Vehicle veh = vehicle::get_closest_to_location(location, 5.f);
					if (veh == 0) return notify::above_map("Invalid vehicle handle...");

					location = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);

					entity::take_control_of(veh);

					vehicle::bring(veh, location);
				}QUEUE_JOB_END_CLAUSE
			}

			if (ImGui::TreeNode("Speedo Meter"))
			{
				SpeedoMeter selected = g.vehicle.speedo_meter;

				if (ImGui::BeginCombo("Weapon", speedo_meters[(int)selected].name))
				{
					for (speedo_meter speedo : speedo_meters)
					{
						if (ImGui::Selectable(speedo.name, speedo.id == selected))
						{
							g.vehicle.speedo_meter = speedo.id;
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