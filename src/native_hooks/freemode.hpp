#pragma once
#include "script_function.hpp"

namespace big
{
	namespace freemode
	{
		inline void NETWORK_BAIL(rage::scrNativeCallContext* src)
		{
			LOG(INFO) << "NETWORK_BAIL prevented";
		}

		inline void IS_PLAYER_PLAYING(rage::scrNativeCallContext* src)
		{
			// block undead OTR
			if (g.session.decloak_players && src->get_arg<Player>(0) != self::id && !NETWORK::NETWORK_IS_ACTIVITY_SESSION())
				src->set_return_value<BOOL>(TRUE);
			else
				src->set_return_value<BOOL>(PLAYER::IS_PLAYER_PLAYING(src->get_arg<Player>(0)));
		};

		inline void SET_ENTITY_VISIBLE(rage::scrNativeCallContext* src)
		{
			auto entity = src->get_arg<Entity>(0);
			auto toggle = src->get_arg<bool>(1);
			auto outfit = src->get_arg<bool>(2);

			if (g.self.invisibility && entity == self::ped && toggle)
				return;
			else
				ENTITY::SET_ENTITY_VISIBLE(entity, toggle, outfit);
		}

		void SET_BIGMAP_ACTIVE(rage::scrNativeCallContext* src)
		{
			if (!g.m_mission_creator_thread)
				HUD::SET_BIGMAP_ACTIVE(src->get_arg<BOOL>(0), src->get_arg<BOOL>(1));
		};

		void SET_BLIP_DISPLAY(rage::scrNativeCallContext* src)
		{
			if ((!g.m_mission_creator_thread) || src->get_arg<Blip>(0) != HUD::GET_MAIN_PLAYER_BLIP_ID())
				HUD::SET_BLIP_DISPLAY(src->get_arg<Blip>(0), src->get_arg<BOOL>(1));
		};

		void NETWORK_HAS_RECEIVED_HOST_BROADCAST_DATA(rage::scrNativeCallContext* src)
		{
			if (NETWORK::NETWORK_IS_ACTIVITY_SESSION() || NETWORK::NETWORK_IS_HOST_OF_THIS_SCRIPT())
			{
				src->set_return_value<BOOL>(NETWORK::NETWORK_HAS_RECEIVED_HOST_BROADCAST_DATA());
			}
			else
			{
				if (SCRIPT::GET_HASH_OF_THIS_SCRIPT_NAME() == RAGE_JOAAT("freemode") && g.session.force_script_host)
				{
					g_fiber_pool->queue_job([] {
						scripts::force_host(RAGE_JOAAT("freemode"));
						if (auto script = gta_util::find_script_thread(RAGE_JOAAT("freemode")); script && script->m_net_component)
							script->m_net_component->block_host_migration(true);
					});
				}

				if (SCRIPT::GET_HASH_OF_THIS_SCRIPT_NAME() == RAGE_JOAAT("fmmc_launcher") && g.session.force_script_host)
				{
					g_fiber_pool->queue_job([] {
						scripts::force_host(RAGE_JOAAT("fmmc_launcher"));
						if (auto script = gta_util::find_script_thread(RAGE_JOAAT("fmmc_launcher")); script && script->m_net_component)
							script->m_net_component->block_host_migration(true);
					});
				}

				scr_functions::set_freemode_session_active({});
				src->set_return_value<BOOL>(TRUE);
			}
		}
	}
}