#pragma once

#include "backend/player_command.hpp"

namespace big
{
	class send_to_apartment : public player_command
	{
		using player_command::player_command;

		virtual std::optional<std::vector<std::uint64_t>> parse_args_p(const std::vector<std::string>& args, const std::shared_ptr<command_context> ctx);

		virtual CommandAccessLevel get_access_level();

		virtual void execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx);
	};

	namespace cmd
	{
		inline send_to_apartment g_send_to_apartment("apartmenttp", "TP To Apartment", "Teleports the player to the specified apartment index", 1);
	}
}
