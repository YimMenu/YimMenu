#include "backend/player_command.hpp"
#include "script.hpp"
#include "services/bad_players/bad_players.hpp"

namespace big
{
	class multi_kick : player_command
	{
		using player_command::player_command;

		virtual CommandAccessLevel get_access_level() override
		{
			return CommandAccessLevel::TOXIC;
		}

		virtual void execute(player_ptr player, const command_arguments& _args, const std::shared_ptr<command_context> ctx) override
		{
			if (player && player->is_valid())
			{
				player->timeout();

				if (!player->is_blocked)
				{
					player->is_blocked = true;
					bad_players_nm::add_player(player, true, player->is_spammer);
				}

				dynamic_cast<player_command*>(command::get(RAGE_JOAAT("endkick")))->call(player, {});
				dynamic_cast<player_command*>(command::get(RAGE_JOAAT("nfkick")))->call(player, {});
				dynamic_cast<player_command*>(command::get(RAGE_JOAAT("oomkick")))->call(player, {});
			}
		}
	};

	multi_kick g_multi_kick("multikick", "Multi kick", "End, Null & OOM kick", 0, false);
}
