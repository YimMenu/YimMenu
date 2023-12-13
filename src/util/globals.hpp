#pragma once
#include "core/scr_globals.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "script_global.hpp"

#include <script/globals/GPBD_FM_3.hpp>
#include <script/globals/GlobalPlayerBD.hpp>

namespace big::globals
{
	inline void clear_wanted_player(Player target)
	{
		constexpr size_t arg_count = 4;
		int64_t args[arg_count]    = {static_cast<int64_t>(eRemoteEvent::ClearWantedLevel),
		       self::id, 1 << target,
		       (int64_t)scr_globals::gpbd_fm_3.as<GPBD_FM_3*>()->Entries[target].ScriptEventReplayProtectionCounter};

		g_pointers->m_gta.m_trigger_script_event(1, args, arg_count, 1 << target, (int)eRemoteEvent::ClearWantedLevel);
	}

	inline void give_remote_otr(Player target)
	{
		constexpr size_t arg_count = 8;
		int64_t args[arg_count]    = {static_cast<int64_t>(eRemoteEvent::RemoteOffradar),
		       (int64_t)self::id,
		       1 << target,
		       (int64_t)(NETWORK::GET_NETWORK_TIME() + 1),
		       0,
		       true,
		       false,
		       (int64_t)scr_globals::gpbd_fm_3.as<GPBD_FM_3*>()->Entries[target].ScriptEventReplayProtectionCounter};

		g_pointers->m_gta.m_trigger_script_event(1, args, arg_count, 1 << target, (int)eRemoteEvent::RemoteOffradar);
	}

	inline Interior get_interior_from_player(Player player)
	{
		return scr_globals::globalplayer_bd.as<GlobalPlayerBD*>()->Entries[player].CurrentInteriorIndex;
	}
}
