#include "hooking/hooking.hpp"
#include "gta/net_game_event.hpp"
#include "util/sync_trees.hpp"
#include "util/model_info.hpp"
#include "util/globals.hpp"
#include "util/math.hpp"

#include "services/players/player_service.hpp"

#include <netsync/nodes/ped/CPedGameStateDataNode.hpp>
#include <netsync/nodes/ped/CPedTaskTreeDataNode.hpp>
#include <netsync/nodes/physical/CPhysicalScriptGameStateDataNode.hpp>
#include <netsync/nodes/proximity_migrateable/CSectorDataNode.hpp>
#include <netsync/nodes/dynamic_entity/CDynamicEntityGameStateDataNode.hpp>
#include <netsync/nodes/player/CPlayerAppearanceDataNode.hpp>
#include <netsync/nodes/player/CPlayerCameraDataNode.hpp>
#include <netsync/nodes/player/CPlayerGameStateDataNode.hpp>
#include <netsync/nodes/player/CPlayerCreationDataNode.hpp>
#include <netsync/nodes/player/CPlayerGamerDataNode.hpp>
#include <netsync/nodes/player/CPlayerSectorPosNode.hpp>
#include <netsync/nodes/ped/CPedHealthDataNode.hpp>
#include <netsync/nodes/ped/CPedTaskSpecificDataNode.hpp>

namespace
{
	using namespace big;
	static bool is_in_cutscene()
	{
		if (g_local_player && g_local_player->m_player_info)
			return g_local_player->m_player_info->m_game_state == eGameState::InMPCutscene;
		return false;
	}

	static bool is_in_interior()
	{
		int id = 0;
		if (auto self_ptr = g_player_service->get_self(); self_ptr->is_valid())
			id = self_ptr->id();
		return globals::get_interior_from_player(id) != 0;
	}

	static player_ptr get_random_player()
	{
		int players = math::rand(g_player_service->players().size() + 1);

		for (auto& player : g_player_service->players())
			if (player.second->get_ped() && !players--)
				return player.second;

		if (g_player_service->get_self()->get_ped() && g_player_service->get_self()->get_ped()->m_net_object)
			return g_player_service->get_self();
		else
			return nullptr;
	}
}

namespace big
{
	void hooks::write_node_data(void* data_node, rage::netObject* net_object, rage::datBitBuffer* buffer, void* log, bool update)
	{
		bool node_updated = false;
		rage::datBitBuffer original_buffer = *buffer;
		g_hooking->get_original<hooks::write_node_data>()(data_node, net_object, buffer, log, update);

		const auto& node = sync_node_finder::find(reinterpret_cast<uint64_t>(data_node));

		switch (node)
		{
		case sync_node_id("CPhysicalScriptGameStateDataNode"): 
		{
			auto node = reinterpret_cast<CPhysicalScriptGameStateDataNode*>(data_node);
			if (g.spoofing.spoof_hide_veh_god && g_local_player && self::veh && g_local_player->m_vehicle && g_local_player->m_vehicle->m_net_object == net_object)
			{
				node->m_godmode         = false;
				node->m_bullet_proof    = false;
				node->m_fire_proof      = false;
				node->m_smoke_proof     = false;
				node->m_steam_proof     = false;
				node->m_collision_proof = false;
				node->m_explosion_proof = false;
				node->m_melee_proof     = false;
				node_updated = true;
			}
			break;
		}
		case sync_node_id("CPlayerAppearanceDataNode"):
		{
			auto node = reinterpret_cast<CPlayerAppearanceDataNode*>(data_node);
			if (g.spoofing.spoof_player_model)
			{
				if (const auto model_hash = rage::joaat(g.spoofing.player_model); model_info::does_model_exist(model_hash))
				{
					node->m_model_hash = model_hash;
				}
				node->m_has_head_blend_data         = false;
				node->components.m_component_bitset = 0;
				node_updated            = true;
			}
			break;
		}
		case sync_node_id("CPlayerCreationDataNode"):
		{
			auto node = reinterpret_cast<CPlayerCreationDataNode*>(data_node);
			if (g.spoofing.spoof_player_model)
			{
				if (const auto model_hash = rage::joaat(g.spoofing.player_model); model_info::does_model_exist(model_hash))
				{
					node->m_model = model_hash;
				}
				node_updated                        = true;
			}
			break;
		}
		case sync_node_id("CPlayerCameraDataNode"):
		{
			auto node = reinterpret_cast<CPlayerCameraDataNode*>(data_node);
			if (g.spoofing.spoof_hide_spectate && g.player.spectating)
			{
				node->m_free_cam_pos_x += 50.0f;
				node->m_free_cam_pos_y -= 50.0f;
				node->m_camera_x -= 50.0f;
				node_updated = true;
			}
			break;
		}
		case sync_node_id("CPlayerGamerDataNode"):
		{
			auto node = reinterpret_cast<CPlayerGamerDataNode*>(data_node);
			if (g.spoofing.spoof_crew_data)
			{
				node->m_clan_data.m_clan_member_id    = 1;
				node->m_clan_data.m_clan_id           = 41564112;
				node->m_clan_data.m_clan_id_2         = 41564112;
				node->m_clan_data.m_clan_color        = 420;
				node->m_clan_data.m_clan_member_count = 15;
				node->m_clan_data.m_clan_created_time = 420;

				strcpy(node->m_clan_data.m_clan_tag, g.spoofing.crew_tag.c_str());
				node->m_clan_data.m_is_system_clan = g.spoofing.rockstar_crew;
				node->m_clan_data.m_is_clan_open   = g.spoofing.square_crew_tag;

				if (g.spoofing.rockstar_crew)
				{
					strcpy(node->m_clan_data.m_clan_name, "Rockstar");
				}
				node_updated = true;
			}
			break;
		}
		case sync_node_id("CPlayerGameStateDataNode"):
		{
			auto node = reinterpret_cast<CPlayerGameStateDataNode*>(data_node);

			if (g.spoofing.spoof_hide_god && !is_in_cutscene() && !is_in_interior())
			{
				node->m_is_invincible   = false;
				node->m_bullet_proof    = false;
				node->m_collision_proof = false;
				node->m_explosion_proof = false;
				node->m_fire_proof      = false;
				node->m_melee_proof     = false;
				node->m_steam_proof     = false;
				node->m_water_proof     = false;
				node_updated            = true;
			}

			if (g.spoofing.spoof_hide_spectate)
			{
				node->m_is_spectating     = false;
				node->m_spectating_net_id = 0;
				node_updated              = true;
			}

			break;
		}
		case sync_node_id("CPedGameStateDataNode"):
		{
			auto node = reinterpret_cast<CPedGameStateDataNode*>(data_node);

			if (g.session.harass_players && g.m_sync_target_player < 32 && *g_pointers->m_gta.m_is_session_started && g_local_player
			    && net_object == g_local_player->m_net_object)
			{
				auto plyr       = g_player_service->get_by_id(g.m_sync_target_player);
				if (plyr)
				if (auto ped = plyr->get_ped(); ped && plyr->is_valid())
				{
					node->m_vehicle = *(int16_t*)(((__int64)ped->m_net_object) + 0x3D8); // 66 85 D2 4C 8B D1 0F 95 C0 or IS_REMOTE_PLAYER_IN_NON_CLONED_VEHICLE
					node->m_seat    = 2; // test
					node->m_in_seat = true;
					node->m_in_vehicle = true;
					node_updated    = true;
				}
			}

			break;
		}
		case sync_node_id("CPedTaskTreeDataNode"):
		{
			auto node = reinterpret_cast<CPedTaskTreeDataNode*>(data_node);

			if (g.session.harass_players)
			{
				node->m_task_bitset = 0;
				node_updated = true;
			}

			break;
		}
		case sync_node_id("CSectorDataNode"):
		{
			auto node = reinterpret_cast<CSectorDataNode*>(data_node);

			if (g.session.harass_players && g.m_sync_target_player < 32 && *g_pointers->m_gta.m_is_session_started && g_local_player
			    && net_object == g_local_player->m_net_object)
			{
				auto plyr = g_player_service->get_by_id(g.m_sync_target_player);
				if (plyr)
				{
					if (auto ped = plyr->get_ped(); ped && plyr->is_valid())
					{
						g_pointers->m_gta.m_get_sector_data(ped->get_position(), &node->m_pos_x, &node->m_pos_y, &node->m_pos_z, nullptr);
						node_updated = true;
					}
				}
			}
			break;
		}
		case sync_node_id("CPlayerSectorPosNode"):
		{
			auto node = reinterpret_cast<CPlayerSectorPosNode*>(data_node);

			if (g.session.harass_players && g.m_sync_target_player < 32 && *g_pointers->m_gta.m_is_session_started && g_local_player
			    && net_object == g_local_player->m_net_object)
			{
				auto plyr = g_player_service->get_by_id(g.m_sync_target_player);
				if (plyr)
				{
					if (auto ped = plyr->get_ped(); ped && plyr->is_valid())
					{
						std::uint16_t _;
						g_pointers->m_gta.m_get_sector_data(ped->get_position(), &_, &_, &_, &node->m_sector_pos);
						node->m_is_standing_on_entity = false;
						node_updated                  = true;
					}
				}
			}
			break;
		}
		case sync_node_id("CPedHealthDataNode"):
		{
			auto node = reinterpret_cast<CPedHealthDataNode*>(data_node);

			if (g.m_sync_target_player < 32 && *g_pointers->m_gta.m_is_session_started && g_local_player
			    && net_object == g_local_player->m_net_object)
			{
				auto plyr = g_player_service->get_by_id(g.m_sync_target_player);
				if (plyr && (plyr->spam_killfeed || g.session.spam_killfeed))
				{
					if (auto ped = plyr->get_ped(); ped && plyr->is_valid())
					{
						if (math::rand(2) != 0)
						{
							// dead
							auto rand_plyr = get_random_player();

							if (rand_plyr)
							{
								node->m_weapon_damage_entity = rand_plyr->get_ped()->m_net_object->m_object_id;
							}

							node->m_weapon_damage_hash      = "WEAPON_EXPLOSION"_J;
							node->m_has_max_health          = false;
							node->m_hurt_started            = true;
							node->m_health                  = 0;
							node->m_weapon_damage_component = 5;
						}
						else
						{
							// alive
							node->m_has_max_health = true;
							node->m_health         = 100;
						}

						node_updated = true;
					}
				}
			}
			break;
		}
		}
		
		if (node_updated)
		{
			*buffer = original_buffer;
			g_hooking->get_original<hooks::write_node_data>()(data_node, net_object, buffer, log, false);
		}
	}
}

static_assert(offsetof(CPedGameStateDataNode, CPedGameStateDataNode::m_seat) == 0x138);