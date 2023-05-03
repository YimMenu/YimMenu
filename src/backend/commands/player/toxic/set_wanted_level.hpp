#pragma once

#include "backend/player_command.hpp"

namespace big
{
	class set_wanted_level : public player_command
	{
		using player_command::player_command;

		virtual std::optional<std::vector<std::uint64_t>> parse_args_p(const std::vector<std::string>& args, const std::shared_ptr<command_context> ctx);

		virtual CommandAccessLevel get_access_level();

		virtual void execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx);
	};

	namespace cmd
	{
		inline set_wanted_level g_set_wanted_level("wanted", "Set Wanted Level", "Sets the specified wanted level to the player", 1, false);
	}
}
