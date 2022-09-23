#pragma once
#include "native_hooks.hpp"
#include "core/globals.hpp"
#include "gta_util.hpp"
#include "natives.hpp"
#include "pointers.hpp"

namespace big
{
	namespace maintransition
	{
		inline void NETWORK_SESSION_HOST(rage::scrNativeCallContext* src)
		{
			if (g->session.session_join_queued)
			{
				g_pointers->m_join_session_by_info(gta_util::get_network(), &g->session.session_info, 0, 0, nullptr, 0);
				g->session.session_join_queued = false;
				src->set_return_value<BOOL>(TRUE);
			}
			else
			{
				src->set_return_value<BOOL>(NETWORK::NETWORK_SESSION_HOST(src->get_arg<int>(0), src->get_arg<int>(1), src->get_arg<BOOL>(2)));
			}
		};

		//
		// PLAYER_SWITCH
		//

		inline void IS_SWITCH_TO_MULTI_FIRSTPART_FINISHED(rage::scrNativeCallContext* src)
		{
			if (g->tunables.fast_join)
			{
				src->set_return_value<BOOL>(true);
				LOG(G3LOG_DEBUG) << "IS_SWITCH_TO_MULTI_FIRSTPART_FINISHED skipped";
			}
			else
			{
				src->set_return_value<BOOL>(STREAMING::IS_SWITCH_TO_MULTI_FIRSTPART_FINISHED());
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
			if (!g->tunables.fast_join)
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
			if (!g->tunables.fast_join)
			{
				ENTITY::FREEZE_ENTITY_POSITION(src->get_arg<Entity>(0), src->get_arg<BOOL>(1));
			}
		}

		inline void SET_GAME_PAUSES_FOR_STREAMING(rage::scrNativeCallContext* src)
		{
			if (g->tunables.fast_join)
			{
				LOG(G3LOG_DEBUG) << "SET_GAME_PAUSES_FOR_STREAMING skipped";
			}
			else
			{
				STREAMING::SET_GAME_PAUSES_FOR_STREAMING(src->get_arg<BOOL>(0));
			}
		}

		inline void CHANGE_PLAYER_PED(rage::scrNativeCallContext* src)
		{
			if (g->tunables.fast_join)
			{
				LOG(G3LOG_DEBUG) << "CHANGE_PLAYER_PED skipped";
			}
			else
			{
				PLAYER::CHANGE_PLAYER_PED(src->get_arg<Player>(0), src->get_arg<Ped>(1), src->get_arg<BOOL>(2), src->get_arg<BOOL>(3));
			}
		}



		//
		// PLAYER_SWITCH END
		//

	}
}