#pragma once
#include "gta/enums.hpp"
#include "pointers.hpp"
#include "script_global.hpp"
#include "services/players/player_service.hpp"

namespace big::troll
{
	inline void set_bounty_on_player(player_ptr target, int value, bool anonymous)
	{
		const size_t arg_count  = 22;
		int64_t args[arg_count] = {(int64_t)eRemoteEvent::Bounty,
		    self::id,
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
		    *script_global(1923597).at(9).as<int64_t*>(),
		    *script_global(1923597).at(10).as<int64_t*>()};

		g_pointers->m_trigger_script_event(1, args, arg_count, 1 << target->id());
	}

}
