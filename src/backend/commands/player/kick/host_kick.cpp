#include "backend/player_command.hpp"
#include "natives.hpp"

namespace big
{
	class host_kick : player_command
	{
		using player_command::player_command;

		virtual CommandAccessLevel get_access_level()
		{
			return CommandAccessLevel::TOXIC;
		}

		virtual void execute(player_ptr player, const command_arguments& _args, const std::shared_ptr<command_context> ctx)
		{
			if (!g_player_service->get_self()->is_host())
			{
				g_notification_service->push_error("Host kick", "Host kick failed");
				return;
			}

            NETWORK::NETWORK_SESSION_KICK_PLAYER(player->id());
		}
	};

	host_kick g_host_kick("hostkick", "HOST_KICK", "HOST_KICK_DESC", 0, false);
}