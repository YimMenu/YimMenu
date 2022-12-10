#pragma once
#include "native_hooks.hpp"
#include "natives.hpp"
#include "core/scr_globals.hpp"
#include "fiber_pool.hpp"
#include "util/scripts.hpp"

namespace big
{
	namespace all_scripts
	{
		void IS_DLC_PRESENT(rage::scrNativeCallContext* src)
		{
			const auto hash = src->get_arg<rage::joaat_t>(0);
			
			bool return_value = DLC::IS_DLC_PRESENT(hash);
			if (hash == 0x96F02EE6)
				return_value = return_value || g->settings.dev_dlc;

			src->set_return_value(return_value);
		}

		inline void NETWORK_BAIL(rage::scrNativeCallContext* src)
		{
			if (SCRIPT::GET_HASH_OF_THIS_SCRIPT_NAME() == RAGE_JOAAT("freemode"))
			{
				std::string text = std::format("NETWORK_BAIL({}, {}, {})", src->get_arg<int>(0), src->get_arg<int>(1), src->get_arg<int>(2));
				LOG(WARNING) << "Prevented freemode " << text;
				g_notification_service->push_warning("freemode", text);
			}
			else
			{
				LOG(G3LOG_DEBUG) << std::format("NETWORK::NETWORK_BAIL({}, {}, {}); // In: {}", src->get_arg<int>(0), src->get_arg<int>(1), src->get_arg<int>(2), SCRIPT::GET_THIS_SCRIPT_NAME());;
				NETWORK::NETWORK_BAIL(src->get_arg<int>(0), src->get_arg<int>(1), src->get_arg<int>(2));
			}
		}

		inline void SC_TRANSITION_NEWS_SHOW(rage::scrNativeCallContext* src)
		{
			if (g->tunables.fast_join)
			{
				src->set_return_value<BOOL>(false);
			}
			else
			{
				src->set_return_value<BOOL>(SOCIALCLUB::SC_TRANSITION_NEWS_SHOW(src->get_arg<Any>(0)));
			}
		}

		inline void SC_TRANSITION_NEWS_SHOW_TIMED(rage::scrNativeCallContext* src)
		{
			if (g->tunables.fast_join)
			{
				src->set_return_value<BOOL>(false);
			}
			else
			{
				src->set_return_value<BOOL>(SOCIALCLUB::SC_TRANSITION_NEWS_SHOW_TIMED(src->get_arg<Any>(0), src->get_arg<Any>(0)));
			}
		}

		void NETWORK_HAS_RECEIVED_HOST_BROADCAST_DATA(rage::scrNativeCallContext* src)
		{
			if (SCRIPT::GET_HASH_OF_THIS_SCRIPT_NAME() == RAGE_JOAAT("freemode") && g->session.force_script_host)
			{
				g_fiber_pool->queue_job([]
				{
					scripts::force_host(RAGE_JOAAT("freemode"));
					if (auto script = gta_util::find_script_thread(RAGE_JOAAT("freemode")); script && script->m_net_component)
						script->m_net_component->block_host_migration(true);
				});
			}

			*scr_globals::gsbd.as<int*>() = 4;
			src->set_return_value<BOOL>(TRUE);
		}

		inline void CLEAR_PED_TASKS_IMMEDIATELY(rage::scrNativeCallContext* src)
		{
			if(!(SCRIPT::GET_HASH_OF_THIS_SCRIPT_NAME() == RAGE_JOAAT("maintransition")))
				TASK::CLEAR_PED_TASKS_IMMEDIATELY(src->get_arg<Ped>(0));

			if(src->get_arg<Ped>(0) == self::ped)
				LOG(G3LOG_DEBUG) << std::format("TASK::CLEAR_PED_TASKS_IMMEDIATELY({}); // In: {}",  src->get_arg<Ped>(0), SCRIPT::GET_THIS_SCRIPT_NAME());
		}

		inline void TASK_START_SCENARIO_IN_PLACE(rage::scrNativeCallContext* src)
		{
			if(src->get_arg<Ped>(0) == self::ped)
				LOG(G3LOG_DEBUG) << std::format("TASK::TASK_START_SCENARIO_IN_PLACE({}, {}, {}, {}); // In: {}", src->get_arg<Ped>(0), src->get_arg<char*>(1), src->get_arg<int>(2), src->get_arg<BOOL>(3), SCRIPT::GET_THIS_SCRIPT_NAME());
			else
				TASK::TASK_START_SCENARIO_IN_PLACE(src->get_arg<Ped>(0), src->get_arg<char*>(1), src->get_arg<int>(2), src->get_arg<BOOL>(3));
		}

		inline void SET_ENTITY_SHOULD_FREEZE_WAITING_ON_COLLISION(rage::scrNativeCallContext* src)
		{
			if(src->get_arg<Ped>(0) == self::ped)
				LOG(G3LOG_DEBUG) << std::format("ENTITY::SET_ENTITY_SHOULD_FREEZE_WAITING_ON_COLLISION({}, {}); // In: {}", src->get_arg<Ped>(0), src->get_arg<BOOL>(1), SCRIPT::GET_THIS_SCRIPT_NAME());

			if(!(SCRIPT::GET_HASH_OF_THIS_SCRIPT_NAME() == RAGE_JOAAT("maintransition")))
				ENTITY::SET_ENTITY_SHOULD_FREEZE_WAITING_ON_COLLISION(src->get_arg<Ped>(0), src->get_arg<BOOL>(1));
		}
	}
}