#include "backend/player_command.hpp"
#include "core/scr_globals.hpp"
#include "pointers.hpp"

#include <script/globals/GPBD_FM_3.hpp>

namespace big
{
	class ceo_kick : player_command
	{
		using player_command::player_command;

		virtual CommandAccessLevel get_access_level() override
		{
			return CommandAccessLevel::AGGRESSIVE;
		}

		virtual void execute(player_ptr player, const command_arguments& _args, const std::shared_ptr<command_context> ctx) override
		{
			auto leader = scr_globals::gpbd_fm_3.as<GPBD_FM_3*>()->Entries[player->id()].BossGoon.Boss;

			if (leader == -1)
				return;

			else if (leader == player->id())
			{
				const size_t arg_count  = 3;
				int64_t args[arg_count] = {
				    (int64_t)eRemoteEvent::CeoKick,
				    (int64_t)self::id,
				    1 << player->id(),
				};

				g_pointers->m_gta.m_trigger_script_event(1, args, arg_count, 1 << player->id(), (int)eRemoteEvent::CeoKick);
				return;
			}
			else
			{
				// use a more private method to remove associate
				const size_t arg_count  = 4;
				int64_t args[arg_count] = {(int64_t)eRemoteEvent::MarkPlayerAsBeast, (int64_t)self::id, 1 << player->id(), leader};

				g_pointers->m_gta.m_trigger_script_event(1, args, arg_count, 1 << player->id(), (int)eRemoteEvent::MarkPlayerAsBeast);
			}
		}
	};

	ceo_kick g_ceo_kick("ceokick", "CEO_KICK", "CEO_KICK_DESC", 0);
}