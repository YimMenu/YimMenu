#pragma once
#include "native_hooks.hpp"
#include "core/globals.hpp"
#include "natives.hpp"

namespace big
{
	namespace maintransition
	{
		inline void NETWORK_SESSION_HOST(rage::scrNativeCallContext* src)
		{
			if (g->session.session_join_queued)
			{
				g_pointers->m_join_session_by_info(*g_pointers->m_network, &g->session.session_info, 0, 0, nullptr, 0);
				g->session.session_join_queued = false;
				src->set_return_value<BOOL>(TRUE);
			}
			else
			{
				src->set_return_value<BOOL>(NETWORK::NETWORK_SESSION_HOST(src->get_arg<int>(0), src->get_arg<int>(1), src->get_arg<BOOL>(2)));
			}
		};

		inline void NETWORK_HAS_RECEIVED_HOST_BROADCAST_DATA(rage::scrNativeCallContext* src)
		{
			if (g->tunables.fast_join)
			{
				LOG(G3LOG_DEBUG) << "NETWORK_HAS_RECEIVED_HOST_BROADCAST_DATA skipped";
				src->set_return_value<BOOL>(TRUE);
			}
			else
			{
				src->set_return_value<BOOL>(NETWORK::NETWORK_HAS_RECEIVED_HOST_BROADCAST_DATA());
			}
		}

		inline void ON_ENTER_MP(rage::scrNativeCallContext* src)
		{
			if (g->tunables.fast_join)
			{
				LOG(G3LOG_DEBUG) << "ON_ENTER_MP skipped";
			}
			else
			{
				DLC::ON_ENTER_MP();
			}
		}

		//
		// PLAYER_SWITCH
		//

		inline void N0x933BBEEB8C61B5F4(rage::scrNativeCallContext* src)
		{
			if (g->tunables.fast_join)
			{
				src->set_return_value<BOOL>(true);
				LOG(G3LOG_DEBUG) << "N0x933BBEEB8C61B5F4 skipped";
			}
			else
			{
				src->set_return_value<BOOL>(STREAMING::N0x933BBEEB8C61B5F4());
			}
		}

		inline void SET_ENTITY_VISIBLE(rage::scrNativeCallContext* src)
		{
			if (g->tunables.fast_join)
			{
				ENTITY::SET_ENTITY_VISIBLE(self::ped, true, false);
			}
			else
			{
				ENTITY::SET_ENTITY_VISIBLE(src->get_arg<Entity>(0), src->get_arg<BOOL>(1), src->get_arg<BOOL>(2));
			}
		}

		inline void SET_ENTITY_COORDS(rage::scrNativeCallContext* src)
		{
			if (!g->tunables.fast_join)
			{
				ENTITY::SET_ENTITY_COORDS(src->get_arg<Entity>(0), src->get_arg<float>(1), src->get_arg<float>(2), src->get_arg<float>(3), src->get_arg<BOOL>(4), src->get_arg<BOOL>(5), src->get_arg<BOOL>(6), src->get_arg<BOOL>(7));
			}
		}

		inline void SET_ENTITY_COLLISION(rage::scrNativeCallContext* src)
		{
			if (g->tunables.fast_join)
			{
				return;
			}
			else
			{
				ENTITY::SET_ENTITY_COLLISION(src->get_arg<Entity>(0), src->get_arg<BOOL>(1), src->get_arg<BOOL>(2));
			}
		}

		inline void SET_PLAYER_CONTROL(rage::scrNativeCallContext* src)
		{
			if (g->tunables.fast_join)
			{
				LOG(G3LOG_DEBUG) << "SET_PLAYER_CONTROL skipped";
			}
			else
			{
				PLAYER::SET_PLAYER_CONTROL(src->get_arg<Player>(0), src->get_arg<BOOL>(1), src->get_arg<int>(2));
			}
		}

		inline void FREEZE_ENTITY_POSITION(rage::scrNativeCallContext* src)
		{
			if (g->tunables.fast_join)
			{
				return;
			}
			else
			{
				ENTITY::FREEZE_ENTITY_POSITION(src->get_arg<Entity>(0), src->get_arg<BOOL>(1));
			}
		}

		//
		// PLAYER_SWITCH END
		//

	}
}