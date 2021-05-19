#include "core/data/custom_weapons.hpp"
#include "core/globals.hpp"
#include "gui/window/main/tabs.hpp"

namespace big
{
	void tab_main::tab_weapons()
	{
		if (ImGui::BeginTabItem("Weapons"))
		{
			if (ImGui::TreeNode("Custom Weapons"))
			{
				int selected = (int)g.weapons.custom_weapon;

				if (ImGui::BeginCombo("Weapon", custom_weapons[selected].name))
				{
					for (custom_weapon weapon : custom_weapons)
					{
						if (ImGui::Selectable(weapon.name, weapon.id == (CustomWeapons)selected))
						{
							g.weapons.custom_weapon = weapon.id;
						}

						if (weapon.id == (CustomWeapons)selected)
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