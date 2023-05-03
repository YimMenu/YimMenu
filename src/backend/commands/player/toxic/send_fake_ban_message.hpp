#pragma once

#include "backend/player_command.hpp"

namespace big
{
	class send_fake_ban_message : public player_command
	{
		using player_command::player_command;

		virtual CommandAccessLevel get_access_level();

		virtual void execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx);
	};

	namespace cmd
	{
		inline send_fake_ban_message g_send_fake_ban_message("fakeban", "Send Fake Ban Message", "Sends a fake ban notification to the player", 0);
	}
}
