#include "backend/player_command.hpp"
#include "core/scr_globals.hpp"
#include "natives.hpp"
#include "pointers.hpp"

namespace big
{
	class ceo_kick : player_command
	{
		using player_command::player_command;

		virtual CommandAccessLevel get_access_level()
		{
			return CommandAccessLevel::AGGRESSIVE;
		}

		virtual void execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx)
		{
			auto leader = *scr_globals::gpbd_fm_3.at(player->id(), scr_globals::size::gpbd_fm_3).at(10).as<int*>();

			if (leader == -1)
				return;

			else if (leader == player->id())
			{
				const size_t arg_count  = 2;
				int64_t args[arg_count] = {(int64_t)eRemoteEvent::CeoKick, (int64_t)self::id};

				g_pointers->m_trigger_script_event(1, args, arg_count, 1 << player->id());
				return;
			}
			else
			{
				// use a more private method to remove associate
				const size_t arg_count  = 3;
				int64_t args[arg_count] = {(int64_t)eRemoteEvent::MarkPlayerAsBeast, (int64_t)self::id, leader};

				g_pointers->m_trigger_script_event(1, args, arg_count, 1 << player->id());
			}
		}
	};

	ceo_kick g_ceo_kick("ceokick", "CEO Kick", "Kicks an associate from the CEO/MC. You cannot kick leaders of CEOs/MCs anymore", 0);
}