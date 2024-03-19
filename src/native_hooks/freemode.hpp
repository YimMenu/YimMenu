#pragma once
#include "script_function.hpp"
#include "services/vehicle/vehicle_control_service.hpp"

namespace big
{
	namespace freemode
	{
		void GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH(rage::scrNativeCallContext* src)
		{
			const auto hash = src->get_arg<rage::joaat_t>(0);

			if (hash == "director_mode"_J || hash == "main"_J)
			{
				src->set_return_value(0);
				return;
			}

			src->set_return_value(SCRIPT::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH(hash));
		}

		void STAT_GET_INT(rage::scrNativeCallContext* src)
		{
			if (g_vehicle_control_service.m_driver_performing_task && (src->get_arg<Hash>(0) == "MP0_PERSONAL_VEHICLE_ACCESS"_J || src->get_arg<Hash>(0) == "MP1_PERSONAL_VEHICLE_ACCESS"_J))
			{
				src->set_return_value<int>(0);
				return;
			}

			src->set_return_value(STATS::STAT_GET_INT(src->get_arg<Hash>(0), src->get_arg<int*>(1), src->get_arg<int>(2)));
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
				HUD::SET_BIGMAP_ACTIVE(src->get_arg<bool>(0), src->get_arg<bool>(1));
		};

		void SET_BLIP_DISPLAY(rage::scrNativeCallContext* src)
		{
			if ((!g.m_mission_creator_thread) || src->get_arg<Blip>(0) != HUD::GET_MAIN_PLAYER_BLIP_ID())
				HUD::SET_BLIP_DISPLAY(src->get_arg<Blip>(0), src->get_arg<bool>(1));
		};

		void NETWORK_HAS_RECEIVED_HOST_BROADCAST_DATA(rage::scrNativeCallContext* src)
		{
			if (NETWORK::NETWORK_IS_ACTIVITY_SESSION() || NETWORK::NETWORK_IS_IN_TRANSITION() || NETWORK::NETWORK_IS_TRANSITION_TO_GAME() || NETWORK::NETWORK_IS_HOST_OF_THIS_SCRIPT())
			{
				src->set_return_value<BOOL>(NETWORK::NETWORK_HAS_RECEIVED_HOST_BROADCAST_DATA());
			}
			else
			{
				if (g.session.force_script_host && (g.session.fast_join || NETWORK::NETWORK_HAS_RECEIVED_HOST_BROADCAST_DATA()))
				{
					auto hash = SCRIPT::GET_HASH_OF_THIS_SCRIPT_NAME();
					g_fiber_pool->queue_job([hash] {
						scripts::force_host(hash);
						if (auto script = gta_util::find_script_thread(hash); script && script->m_net_component)
							((CGameScriptHandlerNetComponent*)script->m_net_component)->block_host_migration(true);
					});
				}

				if (SCRIPT::GET_HASH_OF_THIS_SCRIPT_NAME() == "freemode"_J && g.session.fast_join)
				{
					scr_functions::set_freemode_session_active({});
					src->set_return_value<BOOL>(TRUE);
				}
				else
				{
					src->set_return_value<BOOL>(NETWORK::NETWORK_HAS_RECEIVED_HOST_BROADCAST_DATA());
				}
			}
		}
	}
}
