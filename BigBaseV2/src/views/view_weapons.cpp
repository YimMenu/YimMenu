#include "core/data/custom_weapons.hpp"
#include "views/view.hpp"

namespace big
{
	void view::weapons() {
		if (ImGui::TreeNode("Ammo Options"))
		{
			ImGui::Checkbox("Infinite Ammo", &g->weapons.infinite_ammo);

			ImGui::SameLine();

			ImGui::Checkbox("Infinite Clip", &g->weapons.infinite_mag);

			ImGui::TreePop();
		}

		if (ImGui::TreeNode("Custom Weapons"))
		{
			CustomWeapon selected = g->weapons.custom_weapon;

			if (ImGui::BeginCombo("Weapon", custom_weapons[(int)selected].name))
			{
				for (const custom_weapon& weapon : custom_weapons)
				{
					if (ImGui::Selectable(weapon.name, weapon.id == selected))
					{
						g->weapons.custom_weapon = weapon.id;
					}

					if (weapon.id == selected)
						ImGui::SetItemDefaultFocus();
				}

				ImGui::EndCombo();
			}

			switch (selected)
			{
			case CustomWeapon::NONE:
				break;
			case CustomWeapon::CAGE_GUN:
				break;
			case CustomWeapon::DELETE_GUN:
				break;
			case CustomWeapon::GRAVITY_GUN:
				break;
			case CustomWeapon::REPAIR_GUN:
				break;
			case CustomWeapon::VEHICLE_GUN:
				ImGui::Text("Shooting Model:");
				ImGui::InputText("##vehicle_gun_model", g->weapons.vehicle_gun_model, 12);

				break;
			}

			ImGui::TreePop();
		}
	}
}