/*#pragma once
#include "native_hooks.hpp"
#include "natives.hpp"

namespace big
{
	namespace maintransition
	{
		inline void START_PLAYER_SWITCH(rage::scrNativeCallContext* src)
		{
			if (!g->tunables.fast_join) {
				STREAMING::START_PLAYER_SWITCH(
					src->get_arg<Entity>(0),
					src->get_arg<Entity>(1),
					src->get_arg<int>(2),
					src->get_arg<int>(3)
				);
			}
			g->natives.player_switch = true;
			g->natives.player_switch_type = src->get_arg<int>(3);
		}

		inline void IS_PLAYER_SWITCH_IN_PROGRESS(rage::scrNativeCallContext* src)
		{
			if (g->tunables.fast_join) 
			{
				src->set_return_value<BOOL>(g->natives.player_switch);
			}
			else {
				src->set_return_value<BOOL>(
					STREAMING::IS_PLAYER_SWITCH_IN_PROGRESS()
				);
			}
		}

		inline void GET_PLAYER_SWITCH_TYPE(rage::scrNativeCallContext* src)
		{
			if (g->tunables.fast_join)
			{
				src->set_return_value<INT>(g->natives.player_switch_type);
			}
			else {
				src->set_return_value<INT>(
					STREAMING::GET_PLAYER_SWITCH_TYPE()
				);
			}
		}
	}
}*/