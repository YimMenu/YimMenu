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
			if (g->session.join_queued)
			{
				g_pointers->m_join_session_by_info(gta_util::get_network(), &g->session.info, 1, 1 | 2 | 4, nullptr, 0);
				g->session.join_queued = false;
				src->set_return_value<BOOL>(TRUE);
			}
			else
			{
				LOG(G3LOG_DEBUG) << std::format("NETWORK::NETWORK_SESSION_HOST({}, {}, {});", src->get_arg<int>(0), src->get_arg<int>(1), src->get_arg<BOOL>(2));
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
				// LOG(G3LOG_DEBUG) << "IS_SWITCH_TO_MULTI_FIRSTPART_FINISHED skipped";
			}
			else
			{
				src->set_return_value<BOOL>(STREAMING::IS_SWITCH_TO_MULTI_FIRSTPART_FINISHED());
			}
		}

		inline void SET_FOCUS_ENTITY(rage::scrNativeCallContext* src)
		{
			if (g->tunables.fast_join)
			{
				STREAMING::SET_FOCUS_ENTITY(self::ped);
			}
			else
			{
				STREAMING::SET_FOCUS_ENTITY(src->get_arg<Entity>(0));
			}
		}

		inline void HIDE_HUD_AND_RADAR_THIS_FRAME(rage::scrNativeCallContext* src)
		{
			if (!g->tunables.fast_join)
			{
				HUD::HIDE_HUD_AND_RADAR_THIS_FRAME();
			}
		}

		inline void ACTIVATE_FRONTEND_MENU(rage::scrNativeCallContext* src)
		{
			if (!g->tunables.fast_join)
			{
				HUD::ACTIVATE_FRONTEND_MENU(src->get_arg<int>(0), src->get_arg<BOOL>(1), src->get_arg<int>(2));
			}
		}

		inline void RESTART_FRONTEND_MENU(rage::scrNativeCallContext* src)
		{
			if (!g->tunables.fast_join)
			{
				HUD::RESTART_FRONTEND_MENU(src->get_arg<int>(0), src->get_arg<int>(1));
			}
		}

		inline void TOGGLE_PAUSED_RENDERPHASES(rage::scrNativeCallContext* src)
		{
			if (g->tunables.fast_join)
			{
				GRAPHICS::RESET_PAUSED_RENDERPHASES();
			}
			else
			{
				GRAPHICS::TOGGLE_PAUSED_RENDERPHASES(src->get_arg<int>(0));
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
				LOG(G3LOG_DEBUG) << std::format("PLAYER::SET_PLAYER_CONTROL({}, {}, {});", src->get_arg<Player>(0), src->get_arg<BOOL>(1), src->get_arg<int>(2));
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

		inline void NETWORK_RESURRECT_LOCAL_PLAYER(rage::scrNativeCallContext* src)
		{
			// LOG(G3LOG_DEBUG) << std::format("NETWORK::NETWORK_RESURRECT_LOCAL_PLAYER({}, {}, {}, {}, {}, {}, {}, {}, {});", src->get_arg<float>(0), src->get_arg<float>(1), src->get_arg<float>(2), src->get_arg<float>(3), src->get_arg<BOOL>(4), src->get_arg<BOOL>(5), src->get_arg<BOOL>(6), src->get_arg<int>(7), src->get_arg<int>(8));
			if (!g->tunables.fast_join)
			{
				NETWORK::NETWORK_RESURRECT_LOCAL_PLAYER(src->get_arg<float>(0), src->get_arg<float>(1), src->get_arg<float>(2), src->get_arg<float>(3), src->get_arg<BOOL>(4), src->get_arg<BOOL>(5), src->get_arg<BOOL>(6), src->get_arg<int>(7), src->get_arg<int>(8));
			}
		}
		
		//
		// PLAYER_SWITCH END
		//

		inline void GET_EVER_HAD_BAD_PACK_ORDER(rage::scrNativeCallContext* src)
		{
			// LOG(G3LOG_DEBUG) << "DLC::GET_EVER_HAD_BAD_PACK_ORDER(); // Returns: " << DLC::GET_EVER_HAD_BAD_PACK_ORDER();
			src->set_return_value<BOOL>(false);
		}
	}
}