#pragma once
#include "script_global.hpp"
#include "util/system.hpp"

namespace big::globals
{
	inline Vehicle get_personal_vehicle()
	{
		return *script_global(2810701).at(298).as<Vehicle*>();
	}

	inline void clear_wanted_player(Player target)
	{
		constexpr size_t arg_count = 3;
		int64_t args[arg_count] = {
			static_cast<int64_t>(eRemoteEvent::ClearWantedLevel),
			self::id,
			*script_global(1893551).at(target, 599).at(510).as<int*>()
		};

		g_pointers->m_trigger_script_event(1, args, arg_count, 1 << target);
	}
}