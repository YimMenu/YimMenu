#include "core/data/speedo_meters.hpp"
#include "gui/window/main/tabs.hpp"

namespace big
{
	static char model[12];

	void tab_main::tab_vehicle()
	{
		if (ImGui::BeginTabItem("Vehicle"))
		{
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

			ImGui::EndTabItem();
		}
	}
}