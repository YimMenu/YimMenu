#include "backend/player_command.hpp"
#include "core/scr_globals.hpp"
#include "natives.hpp"
#include "pointers.hpp"

#include <script/globals/GPBD_FM_3.hpp>

namespace big
{
	class bail_kick : player_command
	{
		using player_command::player_command;

		virtual CommandAccessLevel get_access_level()
		{
			return CommandAccessLevel::TOXIC;
		}

		virtual void execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx)
		{
			const size_t arg_count  = 3;
			int64_t args[arg_count] = {(int64_t)eRemoteEvent::NetworkBail,
			    (int64_t)self::id,
			    scr_globals::gpbd_fm_3.as<GPBD_FM_3*>()->Entries[player->id()].ScriptEventReplayProtectionCounter};

			g_pointers->m_trigger_script_event(1, args, arg_count, 1 << player->id());
		}
	};

	bail_kick g_bail_kick("bailkick", "Bail Kick", "Blocked by most menus", 0);
}