#include "core/data/custom_weapons.hpp"
#include "fiber_pool.hpp"
#include "gta/Weapons.h"
#include "script.hpp"
#include "core/data/special_ammo_types.hpp"
#include "views/view.hpp"
#include "features.hpp"
#include "natives.hpp"
#include "util/teleport.hpp"
#include "pointers.hpp"

namespace big
{
	void KillTargets()
	{
		for (int i = 0; i <= 1000; i++)
		{
			Blip_t* blip = g_pointers->pBlipList->m_Blips[i].m_pBlip;
			if (blip)
			{
				if (blip->m_color != BlipColors::Blue) //Don't hit friendlies.
				{
					if (blip->m_icon == BlipIcons::Cop || blip->m_icon == BlipIcons::Enemy || (blip->m_icon == BlipIcons::Circle && blip->m_color == BlipColors::Red))
					{
						static bool bShoot = false;
						bShoot = !bShoot;
						if (bShoot)
						{
							static Hash weaponList[] = { WEAPON_ADVANCEDRIFLE, WEAPON_APPISTOL, WEAPON_ASSAULTRIFLE, WEAPON_ASSAULTSMG, WEAPON_CARBINERIFLE, WEAPON_COMBATMG, WEAPON_COMBATPDW, WEAPON_COMBATPISTOL, WEAPON_HEAVYPISTOL, WEAPON_HEAVYSNIPER, WEAPON_MARKSMANRIFLE, WEAPON_MG, WEAPON_MICROSMG, WEAPON_PISTOL, WEAPON_PISTOL50, WEAPON_SMG, WEAPON_SNIPERRIFLE, WEAPON_SNSPISTOL, WEAPON_SPECIALCARBINE, WEAPON_MINIGUN };
							if (blip->m_scale_x >= 1.0f)
								FIRE::ADD_OWNED_EXPLOSION(PLAYER::PLAYER_PED_ID(), blip->x, blip->y, blip->z, TANKER, 1000.0f, FALSE, TRUE, 0.0f);
							else
							{
								srand((unsigned int)time(NULL));
								MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(blip->x + 0.1f, blip->y, blip->z - 0.15f, blip->x - 0.1f, blip->y, blip->z + 1, 10000, TRUE, weaponList[rand() % (sizeof(weaponList) / 4)], PLAYER::PLAYER_PED_ID(), TRUE, TRUE, 1.0f);
							}
							g_notification_service->push_warning("Nuker", "Killed Enemies");
						}
					}
					if ((blip->m_color == BlipColors::None && (blip->m_icon == EnemyHelicopter || blip->m_icon == PoliceHelicopter)) ||
						((blip->m_color == BlipColors::Red || blip->m_color == BlipColors::RedMission) && (blip->m_icon == PLANE || blip->m_icon == Motorcycle || blip->m_icon == BlipIcons::PersonalVehicleCar || blip->m_icon == Helicopter2 || blip->m_icon == Jet || blip->m_icon == PlayerHelicopter || blip->m_icon == PlaneDrop)))
					{
						FIRE::ADD_OWNED_EXPLOSION(PLAYER::PLAYER_PED_ID(), blip->x, blip->y, blip->z, TANKER, 1000.0f, FALSE, TRUE, 0.0f);
					}
				}
			}
		}
	}
	void view::weapons() {
		if (ImGui::TreeNode("Ammo Options"))
		{
			ImGui::Checkbox("Infinite Ammo", &g->weapons.infinite_ammo);

			ImGui::SameLine();

			ImGui::Checkbox("Infinite Clip", &g->weapons.infinite_mag);

			ImGui::TreePop();
		}

		if (ImGui::TreeNode("Misc"))
		{
			ImGui::Checkbox("Force Crosshairs", &g->weapons.force_crosshairs);

			ImGui::SameLine();

			ImGui::Checkbox("No Recoil", &g->weapons.no_recoil);

			ImGui::SameLine();

			ImGui::Checkbox("No Spread", &g->weapons.no_spread);

			if (ImGui::Button("Kill enemies"))
			{
				QUEUE_JOB_BEGIN_CLAUSE() {
					KillTargets();
				}QUEUE_JOB_END_CLAUSE
			}

			if (ImGui::Button("Get All Weapons"))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					for (auto const& weapon : weapon_list) {
						WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), weapon, 9999, false);
					}
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), -72657034, 0, true);
				}
				QUEUE_JOB_END_CLAUSE
			}

			ImGui::SliderFloat("Damage Multiplier", &g->weapons.increased_damage, 1.f, 10.f, "%.1f");
			
			ImGui::TreePop();
		}

		if (ImGui::TreeNode("Ammo Special"))
		{
			ImGui::Checkbox("Enable Special Ammo", &g->weapons.ammo_special.toggle);

			eAmmoSpecialType selected = g->weapons.ammo_special.type;

			if (ImGui::BeginCombo("Ammo Special", SPECIAL_AMMOS[(int)selected].name))
			{
				for (const auto& special_ammo : SPECIAL_AMMOS)
				{
					if (ImGui::Selectable(special_ammo.name, special_ammo.type == selected))
						g->weapons.ammo_special.type = special_ammo.type;

					if (special_ammo.type == selected)
						ImGui::SetItemDefaultFocus();
				}

				ImGui::EndCombo();
			}

			ImGui::TreePop();
		}

		if (ImGui::TreeNode("Aimbot"))
		{
			ImGui::Checkbox("ESP", &g->self.esp);
			ImGui::Checkbox("AIM", &g->self.aim);


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
			case CustomWeapon::VEHICLE_GUN:
				ImGui::Text("Shooting Model:");
				ImGui::InputText("##vehicle_gun_model", g->weapons.vehicle_gun_model, 12);

				break;
			}

			ImGui::TreePop();
		}
	}
}