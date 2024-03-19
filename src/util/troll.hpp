#pragma once
#include "core/scr_globals.hpp"
#include "gta/enums.hpp"
#include "pointers.hpp"
#include "script_global.hpp"
#include "services/players/player_service.hpp"

namespace big::troll
{
	inline void set_bounty_on_player(player_ptr target, int value, bool anonymous)
	{
		const size_t arg_count  = 23;
		int64_t args[arg_count] = {(int64_t)eRemoteEvent::Bounty,
		    self::id,
		    -1,
		    target->id(),
		    1,
		    value,
		    0,
		    anonymous ? 1 : 0,
		    0,
		    0,
		    0,
		    0,
		    0,
		    0,
		    0,
		    0,
		    0,
		    0,
		    0,
		    0,
		    0,
		    *scr_globals::gsbd_fm_events.at(9).as<int*>(),
		    *scr_globals::gsbd_fm_events.at(10).as<int*>()};

		g_pointers->m_gta.m_trigger_script_event(1, args, arg_count, -1, (int)eRemoteEvent::Bounty);
	}
}
