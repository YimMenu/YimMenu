#pragma once
#include "gta/enums.hpp"
#include "services/players/player_service.hpp"

namespace big::troll
{
	inline void set_bounty_on_player(player_ptr target)
	{
		const size_t arg_count = 21;
		int64_t args[arg_count] =
		{
			(int64_t)eRemoteEvent::Bounty,
			(int64_t)self::id,
			(int64_t)1,
			(int64_t)10000, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, *script_global(1923597).at(9).as<int64_t*>(), *script_global(1923597).at(10).as<int64_t*>()
		};

		g_pointers->m_trigger_script_event(1, args, arg_count, 1 << target->id());
	}

}