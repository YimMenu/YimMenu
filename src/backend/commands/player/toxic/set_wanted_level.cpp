#include "backend/player_command.hpp"
#include "core/scr_globals.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "script.hpp"
#include "util/globals.hpp"

#include <script/globals/GlobalPlayerBD.hpp>

namespace big
{
	class set_wanted_level : player_command
	{
		using player_command::player_command;

		virtual std::optional<command_arguments> parse_args_p(const std::vector<std::string>& args, const std::shared_ptr<command_context> ctx)
		{
			const auto level = std::atoi(args[0].c_str());

			if (level < 0 || level > 5)
			{
				ctx->report_error(std::format("Wanted level {} is invalid [0 - 5]", level));
				return std::nullopt;
			}

			command_arguments result(1);
			result.push(level);
			return result;
		}

		virtual CommandAccessLevel get_access_level()
		{
			return CommandAccessLevel::AGGRESSIVE;
		}

		virtual void execute(player_ptr player, const command_arguments& _args, const std::shared_ptr<command_context> ctx)
		{
			const auto wanted_level = _args.get<int>(0);
			if (player->id() == self::id)
			{
				PLAYER::SET_PLAYER_WANTED_LEVEL(self::id, wanted_level, FALSE);
			}
			else
			{
				int id = player->id();

				if (PLAYER::GET_PLAYER_WANTED_LEVEL(id) > wanted_level)
				{
					// clear existing wanted
					globals::clear_wanted_player(id);

					for (int i = 0; PLAYER::GET_PLAYER_WANTED_LEVEL(id) > wanted_level && i < 3600; i++)
						script::get_current()->yield(1ms);
				}

				if (wanted_level > 0)
				{
					auto& gpbd = scr_globals::globalplayer_bd.as<GlobalPlayerBD*>()->Entries[self::id];

					gpbd.RemoteWantedLevelPlayer = id;
					gpbd.RemoteWantedLevelAmount = wanted_level;

					for (int i = 0; PLAYER::GET_PLAYER_WANTED_LEVEL(id) < wanted_level && i < 3600; i++)
						script::get_current()->yield(1ms);

					gpbd.RemoteWantedLevelPlayer = -1;
					gpbd.RemoteWantedLevelAmount = -1;
				}
			}
		}
	};

	set_wanted_level g_set_wanted_level("wanted", "SET_WANTED_LEVEL", "SET_WANTED_LEVEL_DESC", 1, false);
}