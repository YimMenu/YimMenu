#pragma once
#include "pointers.hpp"
#include "script_global.hpp"

namespace big::globals
{
	namespace size
	{
		constexpr int globalplayer_bd = 453;
		constexpr int gpbd_fm_3 = 599;
		constexpr int gpbd_fm_1 = 888;
	}

	static inline script_global gpbd_fm_3(1892703);
	static inline script_global gsbd_fm_events(1920255);

	inline void clear_wanted_player(Player target)
	{
		constexpr size_t arg_count = 3;
		int64_t args[arg_count] = {
			static_cast<int64_t>(eRemoteEvent::ClearWantedLevel),
			self::id,
			*script_global(1892703).at(target, 599).at(510).as<int*>()
		};

		g_pointers->m_trigger_script_event(1, args, arg_count, 1 << target);
	}

	inline void disable_kill_trigger(bool toggle)
	{
		*script_global(2815059).at(6753).as<int*>() = toggle; // "TRI_WARP" 2nd nested if statement below this text in freemode.c
	}
}
