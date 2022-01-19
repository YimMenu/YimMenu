#include "fiber_pool.hpp"
#include "gta/enums.hpp"
#include "gta_util.hpp"
#include "player_tabs.hpp"
#include "natives.hpp"
#include "script.hpp"
#include "util/toxic.hpp"

namespace big
{
	void tab_player::tab_toxic()
	{
		if (ImGui::BeginTabItem("Toxic"))
		{
			if (ImGui::Button("Explode Self"))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					toxic::blame_explode_player(g.selected_player.id, g.selected_player.id, eExplosionType::PLANE, 1000, false, true, 0.f);
				}QUEUE_JOB_END_CLAUSE
			}

			if (ImGui::Button("Host Kick"))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					NETWORK::NETWORK_SESSION_KICK_PLAYER(g.selected_player.id);
				}
				QUEUE_JOB_END_CLAUSE
			}

			if (ImGui::Button("Send to island"))
			{
				QUEUE_JOB_BEGIN_CLAUSE(){
					int args[3] = {
			(int)eRemoteEvent::SendToIsland, 0, g.selected_player.id};
					g_pointers->m_trigger_script_event(1, args, 3, -1 << g.selected_player.id);
				}QUEUE_JOB_END_CLAUSE
			}

			if (ImGui::Button("Steal Outfit"))
			{
				g_fiber_pool->queue_job([]
					{
						Ped ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g.selected_player.id);
						Ped player_ped = PLAYER::PLAYER_PED_ID();
						PED::SET_PED_COMPONENT_VARIATION(player_ped, 1, PED::GET_PED_DRAWABLE_VARIATION(ped, 1), PED::GET_PED_TEXTURE_VARIATION(ped, 1), 0);
						//PED::SET_PED_COMPONENT_VARIATION(player_ped, 3, PED::GET_PED_DRAWABLE_VARIATION(ped, 3), 1, 0);
						PED::SET_PED_COMPONENT_VARIATION(player_ped, 4, PED::GET_PED_DRAWABLE_VARIATION(ped, 4), PED::GET_PED_TEXTURE_VARIATION(ped, 4), 0);
						//PED::SET_PED_COMPONENT_VARIATION(player_ped, 5, PED::GET_PED_DRAWABLE_VARIATION(ped, 5), 1, 0);
						PED::SET_PED_COMPONENT_VARIATION(player_ped, 6, PED::GET_PED_DRAWABLE_VARIATION(ped, 6), PED::GET_PED_TEXTURE_VARIATION(ped, 6), 0);
						PED::SET_PED_COMPONENT_VARIATION(player_ped, 7, PED::GET_PED_DRAWABLE_VARIATION(ped, 7), PED::GET_PED_TEXTURE_VARIATION(ped, 7), 0);
						PED::SET_PED_COMPONENT_VARIATION(player_ped, 8, PED::GET_PED_DRAWABLE_VARIATION(ped, 8), PED::GET_PED_TEXTURE_VARIATION(ped, 8), 0);
						PED::SET_PED_COMPONENT_VARIATION(player_ped, 9, PED::GET_PED_DRAWABLE_VARIATION(ped, 9), PED::GET_PED_TEXTURE_VARIATION(ped, 9), 0);
						PED::SET_PED_COMPONENT_VARIATION(player_ped, 10, PED::GET_PED_DRAWABLE_VARIATION(ped, 10), PED::GET_PED_TEXTURE_VARIATION(ped, 10), 0);
						PED::SET_PED_COMPONENT_VARIATION(player_ped, 11, PED::GET_PED_DRAWABLE_VARIATION(ped, 11), PED::GET_PED_TEXTURE_VARIATION(ped, 11), 0);
						PED::SET_PED_PROP_INDEX(player_ped, 0, PED::GET_PED_PROP_INDEX(ped, 0), PED::GET_PED_PROP_TEXTURE_INDEX(ped, 0), true);
						PED::SET_PED_PROP_INDEX(player_ped, 1, PED::GET_PED_PROP_INDEX(ped, 1), PED::GET_PED_PROP_TEXTURE_INDEX(ped, 1), true);
					});


			}
			static char* exlosions[] = {
		"GRENADE",
		"GRENADELAUNCHER",
		"STICKYBOMB",
		"MOLOTOV",
		"ROCKET",
		"TANKSHELL",
		"HI_OCTANE",
		"CAR",
		"PLANE",
		"PETROL_PUMP",
		"BIKE",
		"DIR_STEAM",
		"DIR_FLAME",
		"DIR_WATER_HYDRANT",
		"DIR_GAS_CANISTER",
		"BOAT",
		"SHIP_DESTROY",
		"TRUCK",
		"BULLET",
		"SMOKEGRENADELAUNCHER",
		"SMOKEGRENADE",
		"BZGAS",
		"FLARE",
		"GAS_CANISTER",
		"EXTINGUISHER",
		"_0x988620B8",
		"EXP_TAG_TRAIN",
		"EXP_TAG_BARREL",
		"EXP_TAG_PROPANE",
		"EXP_TAG_BLIMP",
		"EXP_TAG_DIR_FLAME_EXPLODE",
		"EXP_TAG_TANKER",
		"PLANE_ROCKET",
		"EXP_TAG_VEHICLE_BULLET",
		"EXP_TAG_GAS_TANK",
		"EXP_TAG_BIRD_CRAP",
		"EXP_TAG_RAILGUN",
		"EXP_TAG_BLIMP2",
		"EXP_TAG_FIREWORK",
		"EXP_TAG_SNOWBALL",
		"EXP_TAG_PROXMINE",
		"EXP_TAG_VALKYRIE_CANNON",
		"EXP_TAG_AIR_DEFENCE",
		"EXP_TAG_PIPEBOMB",
		"EXP_TAG_VEHICLEMINE",
		"EXP_TAG_EXPLOSIVEAMMO",
		"EXP_TAG_APCSHELL",
		"EXP_TAG_BOMB_CLUSTER",
		"EXP_TAG_BOMB_GAS",
		"EXP_TAG_BOMB_INCENDIARY",
		"EXP_TAG_BOMB_STANDARD",
		"EXP_TAG_TORPEDO",
		"EXP_TAG_TORPEDO_UNDERWATER",
		"EXP_TAG_BOMBUSHKA_CANNON",
		"EXP_TAG_BOMB_CLUSTER_SECONDARY",
		"EXP_TAG_HUNTER_BARRAGE",
		"EXP_TAG_HUNTER_CANNON",
		"EXP_TAG_ROGUE_CANNON",
		"EXP_TAG_MINE_UNDERWATER",
		"EXP_TAG_ORBITAL_CANNON",
		"EXP_TAG_BOMB_STANDARD_WIDE",
		"EXP_TAG_EXPLOSIVEAMMO_SHOTGUN",
		"EXP_TAG_OPPRESSOR2_CANNON",
		"EXP_TAG_MORTAR_KINETIC",
		"EXP_TAG_VEHICLEMINE_KINETIC",
		"EXP_TAG_VEHICLEMINE_EMP",
		"EXP_TAG_VEHICLEMINE_SPIKE",
		"EXP_TAG_VEHICLEMINE_SLICK",
		"EXP_TAG_VEHICLEMINE_TAR",
		"EXP_TAG_SCRIPT_DRONE",
		"EXP_TAG_RAYGUN",
		"EXP_TAG_BURIEDMINE",
		"EXP_TAG_SCRIPT_MISSILE",
		"EXP_TAG_RCTANK_ROCKET",
		"EXP_TAG_BOMB_WATER",
		"EXP_TAG_BOMB_WATER_SECONDARY",
		"_0xF728C4A9",
		"_0xBAEC056F",
		"EXP_TAG_FLASHGRENADE",
		"EXP_TAG_STUNGRENADE",
		"_0x763D3B3B",
		"EXP_TAG_SCRIPT_MISSILE_LARGE",
		"EXP_TAG_SUBMARINE_BIG", };

			static int expl_selected = 0;

			ImGui::Separator();

			ImGui::Combo("##type", &expl_selected, exlosions, sizeof(exlosions) / sizeof(*exlosions));
			static bool isAudible = false;
			static bool isInvisible = false;
			static bool Enable_damage = false;
			static float cameraShake = 0.f;

			if (ImGui::Button("Spawn explosion"))
			{
				g_fiber_pool->queue_job([]
					{
						auto pos = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g.selected_player.id), true);
						FIRE::ADD_EXPLOSION(pos.x, pos.y, pos.z, expl_selected, 1, isAudible, isInvisible, cameraShake, Enable_damage);
					});
			}
			ImGui::SameLine();
			ImGui::Checkbox("isAudible", &isAudible);
			ImGui::SameLine();
			ImGui::Checkbox("isInvisible", &isInvisible);
			ImGui::SameLine();
			ImGui::Checkbox("Enable_damage", &Enable_damage);
			ImGui::SliderFloat("cameraShake", &cameraShake, 0.f, 100.f);

			ImGui::EndTabItem();
		}
	}
}