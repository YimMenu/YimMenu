#include "backend/player_command.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "core/scr_globals.hpp"
#include "util/globals.hpp"
#include "script.hpp"

namespace big
{
	class set_wanted_level : player_command
	{
		using player_command::player_command;

		virtual std::optional<std::vector<std::uint64_t>> parse_args_p(const std::vector<std::string>& args, const std::shared_ptr<command_context> ctx)
		{
			uint64_t level = std::atoi(args[0].c_str());

			if (level < 0 || level > 5)
			{
				ctx->report_error(std::format("Wanted level {} is invalid", level));
				return std::nullopt;
			}

			return std::vector<std::uint64_t>{ level };
		}

		virtual CommandAccessLevel get_access_level()
		{
			return CommandAccessLevel::AGGRESSIVE;
		}

		virtual void execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx)
		{
			if (player->id() == self::id)
			{
				PLAYER::SET_PLAYER_WANTED_LEVEL(self::id, _args[0], FALSE);
			}
			else
			{
				int id = player->id();

				if (PLAYER::GET_PLAYER_WANTED_LEVEL(id) > _args[0])
				{
					// clear existing wanted
					globals::clear_wanted_player(id);

					for (int i = 0; PLAYER::GET_PLAYER_WANTED_LEVEL(id) > _args[0] && i < 3600; i++)
						script::get_current()->yield(1ms);
				}

				if (_args[0] > 0)
				{
					*scr_globals::globalplayer_bd.at(self::id, scr_globals::size::globalplayer_bd).at(214).as<Player*>() = id;
					*scr_globals::globalplayer_bd.at(self::id, scr_globals::size::globalplayer_bd).at(215).as<int*>() = _args[0];

					for (int i = 0; PLAYER::GET_PLAYER_WANTED_LEVEL(id) < _args[0] && i < 3600; i++)
						script::get_current()->yield(1ms);

					*scr_globals::globalplayer_bd.at(self::id, scr_globals::size::globalplayer_bd).at(214).as<Player*>() = -1; // reset to prevent wanted from being constantly set
					*scr_globals::globalplayer_bd.at(self::id, scr_globals::size::globalplayer_bd).at(215).as<int*>() = -1;
				}
			}
		}
	};

	set_wanted_level g_set_wanted_level("wanted", "Set Wanted Level", "Sets the specified wanted level to the player", 1, false);
}