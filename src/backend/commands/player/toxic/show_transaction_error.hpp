#pragma once

#include "backend/player_command.hpp"

namespace big
{
	class show_transaction_error : public player_command
	{
		using player_command::player_command;

		virtual CommandAccessLevel get_access_level();

		virtual void execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx);
	};

	namespace cmd
	{
		inline show_transaction_error g_show_transaction_error("error", "Show Transaction Error", "Shows a transaction error to the player", 0);
	}
}
