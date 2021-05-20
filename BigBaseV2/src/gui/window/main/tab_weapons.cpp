#include "core/data/custom_weapons.hpp"
#include "gui/window/main/tabs.hpp"

namespace big
{
	void tab_main::tab_weapons()
	{
		if (ImGui::BeginTabItem("Weapons"))
		{
			if (ImGui::TreeNode("Custom Weapons"))
			{
				CustomWeapon selected = g.weapons.custom_weapon;

				if (ImGui::BeginCombo("Weapon", custom_weapons[(int)selected].name))
				{
					for (custom_weapon weapon : custom_weapons)
					{
						if (ImGui::Selectable(weapon.name, weapon.id == selected))
						{
							g.weapons.custom_weapon = weapon.id;
						}

						if (weapon.id == selected)
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