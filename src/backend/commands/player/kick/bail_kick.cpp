#include "bail_kick.hpp"

#include "core/scr_globals.hpp"
#include "natives.hpp"
#include "pointers.hpp"

#include <script/globals/GPBD_FM_3.hpp>
namespace big
{
	CommandAccessLevel bail_kick::get_access_level()
	{
		return CommandAccessLevel::TOXIC;
	}

	void bail_kick::execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx)
	{
		const size_t arg_count  = 3;
		int64_t args[arg_count] = {(int64_t)eRemoteEvent::NetworkBail,
		    (int64_t)self::id,
		    scr_globals::gpbd_fm_3.as<GPBD_FM_3*>()->Entries[player->id()].ScriptEventReplayProtectionCounter};

		g_pointers->m_gta.m_trigger_script_event(1, args, arg_count, 1 << player->id());
	}
}
