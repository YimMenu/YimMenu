#include "core/data/bullet_impact_types.hpp"
#include "core/data/custom_weapons.hpp"
#include "core/data/special_ammo_types.hpp"
#include "fiber_pool.hpp"
#include "gta/joaat.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "services/gta_data/gta_data_service.hpp"
#include "views/view.hpp"

namespace big
{
	void view::weapons()
	{
		components::sub_title("AMMO"_T);

		ImGui::BeginGroup();

		components::command_checkbox<"infammo">();
		components::command_checkbox<"infclip">();
		ImGui::Checkbox("Allow Weapons In Interiors", &g.weapons.interior_weapon);

		ImGui::EndGroup();
		ImGui::SameLine();
		ImGui::BeginGroup();

		ImGui::Checkbox("Increased C4 Limit (Max = 50)", &g.weapons.increased_c4_limit);
		ImGui::Checkbox("Increased Flare Limit (Max = 50)", &g.weapons.increased_flare_limit);

		components::command_checkbox<"rapidfire">();

		ImGui::EndGroup();

		ImGui::Separator();

		ImGui::Checkbox("ENABLE_SPECIAL_AMMO"_T.data(), &g.weapons.ammo_special.toggle);

		eAmmoSpecialType selected_ammo   = g.weapons.ammo_special.type;
		eExplosionTag selected_explosion = g.weapons.ammo_special.explosion_tag;

		if (ImGui::BeginCombo("SPECIAL_AMMO"_T.data(), SPECIAL_AMMOS[(int)selected_ammo].name))
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

		if (ImGui::BeginCombo("BULLET_IMPACT"_T.data(), BULLET_IMPACTS[selected_explosion]))
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

		components::sub_title("MISC"_T);

		components::command_checkbox<"crosshairs">();
		ImGui::SameLine();
		components::command_checkbox<"norecoil">();
		ImGui::SameLine();
		components::command_checkbox<"nospread">();

		components::button("GET_ALL_WEAPONS"_T, [] {
			for (const auto& [_, weapon] : g_gta_data_service->weapons())
			{
				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(self::ped, weapon.m_hash, 9999, false);
			}

			constexpr auto parachute_hash = RAGE_JOAAT("GADGET_PARACHUTE");
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(self::ped, parachute_hash, 0, true);
		});
		ImGui::SameLine();
		components::button("REMOVE_CUR_WEAPON"_T, [] {
			Hash weaponHash;
			WEAPON::GET_CURRENT_PED_WEAPON(self::ped, &weaponHash, 1);
			if (weaponHash != RAGE_JOAAT("WEAPON_UNARMED"))
			{
				WEAPON::REMOVE_WEAPON_FROM_PED(self::ped, weaponHash);
			}
		});

		ImGui::SliderFloat("DMG_MULTIPLR"_T.data(), &g.weapons.increased_damage, 1.f, 10.f, "%.1f");

		ImGui::Separator();

		components::sub_title("CUSTOM_WEAPONS"_T);

		CustomWeapon selected = g.weapons.custom_weapon;

		if (ImGui::BeginCombo("WEAPON"_T.data(), custom_weapons[(int)selected].name))
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
		case CustomWeapon::GRAVITY_GUN:
			ImGui::Checkbox("Launch on release", &g.weapons.gravity_gun.launch_on_release);
			break;
		case CustomWeapon::VEHICLE_GUN:
			// this some ugly ass looking code
			static char vehicle_gun[12];
			std::memcpy(vehicle_gun, g.weapons.vehicle_gun_model.c_str(), 12);
			if (ImGui::InputTextWithHint("SHOOTING_MODEL"_T.data(), "NAME_VEHICLE_MODEL"_T.data(), vehicle_gun, sizeof(vehicle_gun)))
			{
				g.weapons.vehicle_gun_model = vehicle_gun;
			}
			if (ImGui::IsItemActive())
			{
				g_fiber_pool->queue_job([] {
					PAD::DISABLE_ALL_CONTROL_ACTIONS(0);
				});
			}

			break;
		}

		ImGui::Separator();
		components::sub_title("Aim Assistance");
		components::command_checkbox<"triggerbot">();
		ImGui::SameLine();
		components::command_checkbox<"aimbot">();

		if (g.weapons.aimbot.enable)
		{
			components::command_checkbox<"aimatplayer">();
			ImGui::SameLine();
			components::command_checkbox<"aimatnpc">();
			ImGui::SameLine();
			components::command_checkbox<"aimatpolice">();
			ImGui::SameLine();
			components::command_checkbox<"aimatenemy">();

			components::command_checkbox<"smoothing">();
			if (g.weapons.aimbot.smoothing)
			{
				ImGui::SameLine();
				ImGui::PushItemWidth(220);
				ImGui::SliderFloat("Speed", &g.weapons.aimbot.smoothing_speed, 1.f, 12.f, "%.1f");
				ImGui::PopItemWidth();
			}
			ImGui::PushItemWidth(350);
			ImGui::SliderFloat("FOV", &g.weapons.aimbot.fov, 1.f, 360.f, "%.0f");
			ImGui::SliderFloat("Distance", &g.weapons.aimbot.distance, 1.f, 350.f, "%.0f");
			ImGui::PopItemWidth();
		}
	}
}
