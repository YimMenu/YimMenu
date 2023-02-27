#include "backend/player_command.hpp"
#include "core/scr_globals.hpp"
#include "natives.hpp"
#include "pointers.hpp"

#include <script/globals/GPBD_FM_3.hpp>

namespace big
{
	class show_transaction_error : player_command
	{
		using player_command::player_command;

		virtual CommandAccessLevel get_access_level()
		{
			return CommandAccessLevel::AGGRESSIVE;
		}

		virtual void execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx)
		{
			const size_t arg_count  = 8;
			int64_t args[arg_count] = {(int64_t)eRemoteEvent::TransactionError,
			    (int64_t)self::id,
			    1,
			    0,
			    0,
			    scr_globals::gpbd_fm_3.as<GPBD_FM_3*>()->Entries[player->id()].ScriptEventReplayProtectionCounter,
			    *scr_globals::gsbd_fm_events.at(9).as<int*>(),
			    *scr_globals::gsbd_fm_events.at(10).as<int*>()};

			g_pointers->m_trigger_script_event(1, args, arg_count, 1 << player->id());
		}
	};

	show_transaction_error g_show_transaction_error("error", "Show Transaction Error", "Shows a transaction error to the player", 0);
}