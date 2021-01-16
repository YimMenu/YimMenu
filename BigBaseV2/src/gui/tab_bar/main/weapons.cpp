#include "gui/tab_bar.hpp"

namespace big
{
	static const double min = 1, max = 5;

	void tabbar::render_weapons()
	{
		if (ImGui::BeginTabItem("Weapons"))
		{
			if (ImGui::TreeNode("Custom Weapons"))
			{
				uint8_t selected = g_settings.options["custom_gun"]["type"];

				if (ImGui::BeginCombo("Weapon", custom_guns[selected].name))
				{
					for (custom_gun gun : custom_guns)
					{
						if (ImGui::Selectable(gun.name, gun.id == selected))
						{
							g_settings.options["custom_gun"]["type"] = gun.id;

							g_settings.save();
						}

						if (gun.id == selected)
							ImGui::SetItemDefaultFocus();
					}

					ImGui::EndCombo();
				}

				switch (selected)
				{
				case 0:
					ImGui::Text("No custom weapon selected.");

					break;

				case 2:
					if (ImGui::SliderScalar("Multiplier", ImGuiDataType_Double, g_settings.options["custom_gun"]["gravity_velocity_multiplier"].get<double*>(), &min, &max))
						g_settings.save();

					break;
				case 4:
					ImGui::Text("Set the vehicle model to spawn.");



					break;
				}

				ImGui::TreePop();
			}

			ImGui::EndTabItem();
		}
	}
}