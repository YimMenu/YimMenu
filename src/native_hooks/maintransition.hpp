#pragma once
#include "core/enums.hpp"
#include "gta_util.hpp"
#include "native_hooks.hpp"
#include "natives.hpp"
#include "pointers.hpp"

namespace big
{
	namespace maintransition
	{

		//
		// PLAYER_SWITCH
		//

		/**
		 * @brief This hook lets you stop player-switch in "Pre-HUD Checks"
		 */
		inline void IS_SWITCH_TO_MULTI_FIRSTPART_FINISHED(rage::scrNativeCallContext* src)
		{
			if (g.tunables.seamless_join)
				src->set_return_value<BOOL>(true);
			else
				src->set_return_value<BOOL>(STREAMING::IS_SWITCH_TO_MULTI_FIRSTPART_FINISHED());
		}

		/**
		 * @brief Prevets map from unloading.
		 */
		inline void SET_FOCUS_ENTITY(rage::scrNativeCallContext* src)
		{
			if (g.tunables.seamless_join)
				STREAMING::SET_FOCUS_ENTITY(self::ped);
			else
				STREAMING::SET_FOCUS_ENTITY(src->get_arg<Entity>(0));
		}

		/**
		 * @brief Draw hud and radar in transition.
		 * @bug Doesn't work.
		 */
		inline void HIDE_HUD_AND_RADAR_THIS_FRAME(rage::scrNativeCallContext* src)
		{
			if (!g.tunables.seamless_join)
				HUD::HIDE_HUD_AND_RADAR_THIS_FRAME();
		}

		/**
		 * @brief Let's you controll your ped when going sp to mp.
		 */
		inline void ACTIVATE_FRONTEND_MENU(rage::scrNativeCallContext* src)
		{
			Hash menuhash = src->get_arg<Hash>(0);
			if (g.tunables.seamless_join && menuhash != RAGE_JOAAT("FE_MENU_VERSION_EMPTY_NO_BACKGROUND"))
				HUD::ACTIVATE_FRONTEND_MENU(menuhash, src->get_arg<BOOL>(1), src->get_arg<int>(2));

			if (!g.tunables.seamless_join)
				HUD::ACTIVATE_FRONTEND_MENU(menuhash, src->get_arg<BOOL>(1), src->get_arg<int>(2));
		}

		/**
		 * @brief Let's you controll your ped when going sp to mp.
		 */
		inline void RESTART_FRONTEND_MENU(rage::scrNativeCallContext* src)
		{
			Hash menuhash = src->get_arg<Hash>(0);

			if (g.tunables.seamless_join)
			{
				if (menuhash != RAGE_JOAAT("FE_MENU_VERSION_EMPTY_NO_BACKGROUND"))
				{
					HUD::RESTART_FRONTEND_MENU(menuhash, src->get_arg<int>(1));
				}
			}
			else
			{
				HUD::RESTART_FRONTEND_MENU(menuhash, src->get_arg<int>(1));
			}
		}

		/**
		 * @brief Prevents the game from freezing your screen.
		 */
		inline void TOGGLE_PAUSED_RENDERPHASES(rage::scrNativeCallContext* src)
		{
			if (g.tunables.seamless_join)
				GRAPHICS::RESET_PAUSED_RENDERPHASES();
			else
				GRAPHICS::TOGGLE_PAUSED_RENDERPHASES(src->get_arg<int>(0));
		}

		/**
		 * @brief Makes you visible.
		 */
		inline void SET_ENTITY_VISIBLE(rage::scrNativeCallContext* src)
		{
			if (g.tunables.seamless_join && src->get_arg<Entity>(0) == self::ped)
				ENTITY::SET_ENTITY_VISIBLE(self::ped, true, false);
			else
				ENTITY::SET_ENTITY_VISIBLE(src->get_arg<Entity>(0), src->get_arg<BOOL>(1), src->get_arg<BOOL>(2));
		}

		/**
		 * @brief Prevents the game from teleporting you.
		 */
		inline void SET_ENTITY_COORDS(rage::scrNativeCallContext* src)
		{
			if (!g.tunables.seamless_join || *scr_globals::transition_state.as<eTransitionState*>() == eTransitionState::TRANSITION_STATE_CONFIRM_FM_SESSION_JOINING || src->get_arg<Entity>(0) != self::ped)
				ENTITY::SET_ENTITY_COORDS(src->get_arg<Entity>(0), src->get_arg<float>(1), src->get_arg<float>(2), src->get_arg<float>(3), src->get_arg<BOOL>(4), src->get_arg<BOOL>(5), src->get_arg<BOOL>(6), src->get_arg<BOOL>(7));
		}

		/**
		 * @brief Prevents you from falling.
		 */
		inline void SET_ENTITY_COLLISION(rage::scrNativeCallContext* src)
		{
			if (!g.tunables.seamless_join || src->get_arg<Entity>(0) != self::ped)
				ENTITY::SET_ENTITY_COLLISION(src->get_arg<Entity>(0), src->get_arg<BOOL>(1), src->get_arg<BOOL>(2));
		}

		/**
		 * @brief Allows controll in session switch.
		 */
		inline void SET_PLAYER_CONTROL(rage::scrNativeCallContext* src)
		{
			if (!g.tunables.seamless_join)
				PLAYER::SET_PLAYER_CONTROL(src->get_arg<Player>(0), src->get_arg<BOOL>(1), src->get_arg<int>(2));
		}

		/**
		 * @brief Allows controll in session switch.
		 */
		inline void FREEZE_ENTITY_POSITION(rage::scrNativeCallContext* src)
		{
			if (!g.tunables.seamless_join || src->get_arg<Entity>(0) != self::ped)
				ENTITY::FREEZE_ENTITY_POSITION(src->get_arg<Entity>(0), src->get_arg<BOOL>(1));
		}

		/**
		 * @brief Prevents player from teleporting after switch.
		 */
		inline void NETWORK_RESURRECT_LOCAL_PLAYER(rage::scrNativeCallContext* src)
		{
			if (!g.tunables.seamless_join)
				NETWORK::NETWORK_RESURRECT_LOCAL_PLAYER(src->get_arg<float>(0), src->get_arg<float>(1), src->get_arg<float>(2), src->get_arg<float>(3), src->get_arg<BOOL>(4), src->get_arg<BOOL>(5), src->get_arg<BOOL>(6), src->get_arg<int>(7), src->get_arg<int>(8));
		}

		//
		// PLAYER_SWITCH END
		//


		/**
		 * 
		 * @param src 
		 */
		inline void CLEAR_PED_TASKS_IMMEDIATELY(rage::scrNativeCallContext* src)
		{
			if (!g.tunables.seamless_join)
				TASK::CLEAR_PED_TASKS_IMMEDIATELY(src->get_arg<Ped>(0));
		}
	}
}