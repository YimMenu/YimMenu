#include "backend/player_command.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "gta/net_object_mgr.hpp"
#include "core/scr_globals.hpp"

namespace big
{
	class kick_from_interior : player_command
	{
		using player_command::player_command;

		virtual CommandAccessLevel get_access_level()
		{
			return CommandAccessLevel::AGGRESSIVE;
		}

		virtual void execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx)
		{
			const size_t arg_count = 8;
			int64_t args[arg_count]{
				(int64_t)eRemoteEvent::KickFromInterior,
				(int64_t)self::id,
				*scr_globals::globalplayer_bd.at(player->id(), scr_globals::size::globalplayer_bd).at(321).at(7).as<int64_t*>(),
				*scr_globals::globalplayer_bd.at(player->id(), scr_globals::size::globalplayer_bd).at(321).at(8).as<int64_t*>(),
			};

			g_pointers->m_trigger_script_event(1, args, arg_count, 1 << player->id());
		}
	};

	kick_from_interior g_kick_from_interior("intkick", "Kick From Interior", "Kicks the player from the interior they are in", 0);
}