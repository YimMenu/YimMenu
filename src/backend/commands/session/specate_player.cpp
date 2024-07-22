#include "backend/player_command.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "util/globals.hpp"

namespace big
{
	class spectate_player : player_command
	{
		using player_command::player_command;

		virtual CommandAccessLevel get_access_level() override
		{
			return CommandAccessLevel::ADMIN;
		}

		virtual void execute(player_ptr player, const command_arguments& _args, const std::shared_ptr<command_context> ctx) override
		{
			if (player == g_player_service->get_self())
			{
				g.player.spectating = false;
				return;
			}

			g_player_service->set_selected(player);
			g.player.spectating = true;
		}
	};

	spectate_player g_spectate_player("spectate", "SPECTATE", "SPECTATE_DESC", 0);
	spectate_player g_spectate_player_shortcut("spec", "SPECTATE", "SPECTATE_DESC", 0);
}