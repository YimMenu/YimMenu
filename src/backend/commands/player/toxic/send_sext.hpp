#pragma once

#include "backend/player_command.hpp"

namespace big
{
	class send_sext : public player_command
	{
		using player_command::player_command;

		virtual CommandAccessLevel get_access_level();

		virtual void execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx);
	};

	namespace cmd
	{
		inline send_sext g_send_sext("sext", "Send Sext", "Sends a random sext (with an image attachment) to the player", 0);
	}
}
