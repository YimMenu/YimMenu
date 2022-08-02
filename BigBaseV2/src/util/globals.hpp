#pragma once
#include "script_global.hpp"
#include "util/system.hpp"

namespace big::globals
{
	inline auto gpbd_fm_3 = script_global(1892703);

	inline void clear_wanted_player(Player target)
	{
		constexpr size_t arg_count = 3;
		int64_t args[arg_count] = {
			static_cast<int64_t>(eRemoteEvent::ClearWantedLevel),
			self::id,
			* gpbd_fm_3.at(target, 599).at(510).as<int*>()
		};

		g_pointers->m_trigger_script_event(1, args, arg_count, 1 << target);
	}

	inline const char* get_organization_name(Player target)
	{
		return gpbd_fm_3.at(target, 599).at(10).at(105).as<char*>();
	}
}
