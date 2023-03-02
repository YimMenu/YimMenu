#pragma once
#include "core/scr_globals.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "script_global.hpp"

namespace big::globals
{
	inline void clear_wanted_player(Player target)
	{
		constexpr size_t arg_count = 3;
		int64_t args[arg_count]    = {static_cast<int64_t>(eRemoteEvent::ClearWantedLevel),
		       self::id,
		       *scr_globals::gpbd_fm_3.at(target, scr_globals::size::gpbd_fm_3).at(510).as<int*>()};

		g_pointers->m_trigger_script_event(1, args, arg_count, 1 << target);
	}

	inline void give_remote_otr(Player target)
	{
		constexpr size_t arg_count = 7;
		int64_t args[arg_count]    = {static_cast<int64_t>(eRemoteEvent::RemoteOffradar),
		       (int64_t)self::id,
		       (int64_t)(NETWORK::GET_NETWORK_TIME() + 1),
		       0,
		       true,
		       false,
		       *scr_globals::gpbd_fm_3.at(target, scr_globals::size::gpbd_fm_3).at(510).as<int64_t*>()};

		g_pointers->m_trigger_script_event(1, args, arg_count, 1 << target);
	}

	inline Interior get_interior_from_player(Player player)
	{
		return *scr_globals::globalplayer_bd.at(player, scr_globals::size::globalplayer_bd).at(245).as<Interior*>();
	}
}
