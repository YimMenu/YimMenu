#include "core/data/custom_weapons.hpp"
#include "fiber_pool.hpp"
#include "natives.hpp"
#include "core/data/special_ammo_types.hpp"
#include "core/data/bullet_impact_types.hpp"
#include "services/gta_data/gta_data_service.hpp"
#include "gta/joaat.hpp"
#include "views/view.hpp"

namespace big
{
	void view::weapons() {
		components::sub_title("Ammo");
		ImGui::Checkbox("Infinite Ammo", &g->weapons.infinite_ammo);

		ImGui::SameLine();

		ImGui::Checkbox("Infinite Clip", &g->weapons.infinite_mag);

		ImGui::Checkbox("Enable Special Ammo", &g->weapons.ammo_special.toggle);

		eAmmoSpecialType selected_ammo = g->weapons.ammo_special.type;
		eImpactType selected_impact = g->weapons.ammo_special.impactType;

		if (ImGui::BeginCombo("Special Ammo", SPECIAL_AMMOS[(int)selected_ammo].name))
		{
			for (const auto& special_ammo : SPECIAL_AMMOS)
			{
				if (ImGui::Selectable(special_ammo.name, special_ammo.type == selected_ammo))
				{
					g->weapons.ammo_special.type = special_ammo.type;
				}

				if (special_ammo.type == selected_ammo)
				{
					ImGui::SetItemDefaultFocus();
				}
			}

			ImGui::EndCombo();
		}

		if (ImGui::BeginCombo("Bullet Impact", BULLET_IMPACTS[selected_impact]))
		{
			for (const auto& [type, name] : BULLET_IMPACTS)
			{
				if (ImGui::Selectable(name, type == selected_impact))
				{
					g->weapons.ammo_special.impactType = type;
				}

				if (type == selected_impact)
				{
					ImGui::SetItemDefaultFocus();
				}
			}

			ImGui::EndCombo();
		}

		ImGui::Separator();

		components::sub_title("Misc");

		ImGui::Checkbox("Force Crosshairs", &g->weapons.force_crosshairs);

		ImGui::SameLine();

		ImGui::Checkbox("No Recoil", &g->weapons.no_recoil);

		ImGui::SameLine();

		ImGui::Checkbox("No Spread", &g->weapons.no_spread);

		components::button("Get All Weapons", [] {
			for (auto const& weapon : g_gta_data_service->get_weapon_arr())
			{
				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(self::ped, weapon.hash, 9999, false);
			}

			constexpr auto parachute_hash = RAGE_JOAAT("GADGET_PARACHUTE");
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(self::ped, parachute_hash, 0, true);
		});
		ImGui::SameLine();
		components::button("Remove Current Weapon", [] {
			Hash weaponHash;
			WEAPON::GET_CURRENT_PED_WEAPON(self::ped, &weaponHash, 1);
			if (weaponHash != RAGE_JOAAT("WEAPON_UNARMED"))
			{
				WEAPON::REMOVE_WEAPON_FROM_PED(self::ped, weaponHash);
			}
		});

		ImGui::SliderFloat("Damage Multiplier", &g->weapons.increased_damage, 1.f, 10.f, "%.1f");

		ImGui::Separator();

		components::sub_title("Custom Weapons");

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
				{
					ImGui::SetItemDefaultFocus();
				}
			}

			ImGui::EndCombo();
		}

		switch (selected)
		{
		case CustomWeapon::VEHICLE_GUN:
			components::input_text_with_hint(
				"Shooting Model",
				"Name of the vehicle model",
				g->weapons.vehicle_gun_model, sizeof(g->weapons.vehicle_gun_model)
			);

			break;
		}
	}
}
