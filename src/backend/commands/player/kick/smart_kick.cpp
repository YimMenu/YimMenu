#include "backend/player_command.hpp"
#include "core/data/infractions.hpp"
#include "core/scr_globals.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "script.hpp"
#include "services/player_database/player_database_service.hpp"

namespace big
{
	class smart_kick : player_command
	{
		using player_command::player_command;

		virtual CommandAccessLevel get_access_level() override
		{
			return CommandAccessLevel::TOXIC;
		}

		virtual void execute(player_ptr player, const command_arguments& _args, const std::shared_ptr<command_context> ctx) override
		{
			if (g_player_service->get_self()->is_host())
			{
				dynamic_cast<player_command*>(command::get("breakup"_J))->call(player, {});
			}
			else
			{
				if (player->is_host())
					dynamic_cast<player_command*>(command::get("oomkick"_J))->call(player, {});
				else
				{
					if (auto rockstar_id = player->get_rockstar_id())
					{
						if (auto db_player = g_player_database_service->get_player_by_rockstar_id(rockstar_id);
						    db_player && db_player->infractions.contains((int)Infraction::ATTACKING_WITH_GODMODE))
						{
							dynamic_cast<player_command*>(command::get("oomkick"_J))->call(player, {});
							return;
						}
					}

					if (g.protections.desync_kick)
						dynamic_cast<player_command*>(command::get("desync"_J))->call(player, {});
				}
			}
		}
	};

	smart_kick g_smart_kick("smartkick", "SMART_KICK", "SMART_KICK_DESC", 0, false);
}
