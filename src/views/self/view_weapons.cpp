#include "core/data/custom_weapons.hpp"
#include "fiber_pool.hpp"
#include "natives.hpp"
#include "core/data/special_ammo_types.hpp"
#include "core/data/bullet_impact_types.hpp"
#include "services/gta_data/gta_data_service.hpp"
#include "gta/joaat.hpp"
#include "views/view.hpp"
#include "pointers.hpp"

namespace big
{
	void view::weapons() {
		components::sub_title("Ammo");

		ImGui::BeginGroup();

		components::command_checkbox<"infammo">();
		components::command_checkbox<"infclip">();

		ImGui::EndGroup();
		ImGui::SameLine();
		ImGui::BeginGroup();

		if (ImGui::Checkbox("Bypass C4 Limit", &g.weapons.bypass_c4_limit))
		{
			if (g.weapons.bypass_c4_limit)
				g_pointers->m_bypass_max_count_of_active_sticky_bombs->apply();
			else
				g_pointers->m_bypass_max_count_of_active_sticky_bombs->restore();
		}
		components::command_checkbox<"rapidfire">();

		ImGui::EndGroup();

		ImGui::Separator();

		ImGui::Checkbox("Enable Special Ammo", &g.weapons.ammo_special.toggle);

		eAmmoSpecialType selected_ammo = g.weapons.ammo_special.type;
		eExplosionTag selected_explosion = g.weapons.ammo_special.explosion_tag;

		if (ImGui::BeginCombo("Special Ammo", SPECIAL_AMMOS[(int)selected_ammo].name))
		{
			for (const auto& special_ammo : SPECIAL_AMMOS)
			{
				if (ImGui::Selectable(special_ammo.name, special_ammo.type == selected_ammo))
				{
					g.weapons.ammo_special.type = special_ammo.type;
				}

				if (special_ammo.type == selected_ammo)
				{
					ImGui::SetItemDefaultFocus();
				}
			}

			ImGui::EndCombo();
		}

		if (ImGui::BeginCombo("Bullet Impact", BULLET_IMPACTS[selected_explosion]))
		{
			for (const auto& [type, name] : BULLET_IMPACTS)
			{
				if (ImGui::Selectable(name, type == selected_explosion))
				{
					g.weapons.ammo_special.explosion_tag = type;
				}

				if (type == selected_explosion)
				{
					ImGui::SetItemDefaultFocus();
				}
			}

			ImGui::EndCombo();
		}

		ImGui::Separator();

		components::sub_title("Misc");

		components::command_checkbox<"crosshairs">();
		ImGui::SameLine();
		components::command_checkbox<"norecoil">();
		ImGui::SameLine();
		components::command_checkbox<"nospread">();

		components::button("Get All Weapons", []
		{
			for (const auto& [_, weapon] : g_gta_data_service->weapons())
			{
				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(self::ped, weapon.m_hash, 9999, false);
			}

			constexpr auto parachute_hash = RAGE_JOAAT("GADGET_PARACHUTE");
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(self::ped, parachute_hash, 0, true);
		});
		ImGui::SameLine();
		components::button("Remove Current Weapon", []
		{
			Hash weaponHash;
			WEAPON::GET_CURRENT_PED_WEAPON(self::ped, &weaponHash, 1);
			if (weaponHash != RAGE_JOAAT("WEAPON_UNARMED"))
			{
				WEAPON::REMOVE_WEAPON_FROM_PED(self::ped, weaponHash);
			}
		});

		ImGui::SliderFloat("Damage Multiplier", &g.weapons.increased_damage, 1.f, 10.f, "%.1f");

		ImGui::Separator();

		components::sub_title("Custom Weapons");

		CustomWeapon selected = g.weapons.custom_weapon;

		if (ImGui::BeginCombo("Weapon", custom_weapons[(int)selected].name))
		{
			for (const custom_weapon& weapon : custom_weapons)
			{
				if (ImGui::Selectable(weapon.name, weapon.id == selected))
				{
					g.weapons.custom_weapon = weapon.id;
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
			// this some ugly ass looking code
			static char vehicle_gun[12];
			std::memcpy(vehicle_gun, g.weapons.vehicle_gun_model.c_str(), 12);
			if (ImGui::InputTextWithHint("Shooting Model", "Name of the vehicle model", vehicle_gun, sizeof(vehicle_gun)))
			{
				g.weapons.vehicle_gun_model = vehicle_gun;
			}
			if (ImGui::IsItemActive())
			{
				g_fiber_pool->queue_job([]
				{
					PAD::DISABLE_ALL_CONTROL_ACTIONS(0);
				});
			}

			break;
		}
	}
}
