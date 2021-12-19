#include "core/data/custom_weapons.hpp"
#include "main_tabs.hpp"
#include "fiber_pool.hpp"
#include "natives.hpp"
#include "script.hpp"

namespace big
{
	void tab_main::tab_weapons()
	{
		if (ImGui::BeginTabItem("Weapons"))
		{
			if (ImGui::TreeNode("Weapons"))
			{
				if (ImGui::Button("impulse 101"))
				{
					QUEUE_JOB_BEGIN_CLAUSE()
					{
						//PED::_0xB782F8238512BAD5(PLAYER::PLAYER_PED_ID(), nullptr); //This causes a crash at GTA5.exe+5845356 and nothing of value was in the log in the stack dump because of the context switch to GTA 5's memory. If you encounter something similar, you will have to figure out where the crash occured in the GTA 5 exe, and trace back that native, and figure out which function is calling the native that is crashing.
						WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xB1CA77B1, 20, false, false);   //weapon_rpg
						WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xA284510B, 20, false, false);   //weapon_grenadelauncher
						WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x42BF8A85, 9999, false, false); //weapon_minigun
						WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x7F7497E5, 20, false, false);   //weapon_firework
						WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x6D544C99, 20, false, false);   //weapon_railgun
						WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x63AB0442, 20, false, false);   //weapon_hominglauncher
						WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x0781FE4A, 20, false, false);   //weapon_compactlauncher

						WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x9D07F764, 9999, false, false); //weapon_mg
						WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x7FD62962, 9999, false, false); //weapon_combatmg
						WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x61012683, 9999, false, false); //weapon_gusenberg
						WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x0C472FE2, 9999, false, false); //weapon_heavysniper
						WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xC734385A, 9999, false, false); //weapon_marksmanrifle
						WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xAF113F99, 9999, false, false); //weapon_advancedrifle
						WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xA89CB99E, 9999, false, false); //weapon_musket
						WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x13532244, 9999, false, false); //weapon_microsmg
						WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x2BE6766B, 9999, false, false); //weapon_smg
						WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xEFE7E2DF, 9999, false, false); //weapon_assaultsmg
						WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x47757124, 20, false, false);   //weapon_flaregun
						WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x060EC506, 9999, false, false); //weapon_fireextinguisher
						WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xFBAB5776, 2, false, false); //gadget_parachute
						WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x34A67B97, 2, false, false); //weapon_petrolcan

						WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x93E220BD, 30, false, false); //weapon_grenade
						WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x787F0BB, 9, false, false); //weapon_snowball
						WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x23C9F95C, 2, false, false); //weapon_ball
						WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xBA45E8B8, 30, false, false); //weapon_pipebomb
						WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xFDBC8A50, 30, false, false); //weapon_smokegrenade
						WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x497FACC3, 30, false, false); //weapon_flare
						WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0x84BD7BFD, 1, false, false); //weapon_crowbar
						WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xFBAB5776, 2, false, false); //
						WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xFBAB5776, 2, false, false); //
						WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xFBAB5776, 2, false, false); //
						WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xFBAB5776, 2, false, false); //
					}
					QUEUE_JOB_END_CLAUSE
				}

				static char weapon_name[255];
				ImGui::InputText("Weapon name", weapon_name, 255);

				ImGui::Separator();

				if (ImGui::Button("Give Weapon"))
				{
					Hash hash = MISC::GET_HASH_KEY(weapon_name);
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), hash, 1000, 1);
				}

				ImGui::SameLine();

				if (ImGui::Button("Remove Weapon"))
				{
					Hash hash = MISC::GET_HASH_KEY(weapon_name);
					WEAPON::REMOVE_WEAPON_FROM_PED(PLAYER::PLAYER_PED_ID(), hash);
				}
				ImGui::TreePop();

			}
			if (ImGui::TreeNode("Custom Weapons"))
			{
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
					ImGui::InputText("##vehicle_gun_model", g.weapons.vehicle_gun_model, 12);

					break;
				}

				ImGui::TreePop();
			}

			ImGui::EndTabItem();
		}
	}
}