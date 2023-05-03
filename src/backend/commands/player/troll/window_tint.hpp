#pragma once

#include "backend/player_command.hpp"

namespace big
{
	class black_tint : public player_command
	{
		using player_command::player_command;

		virtual void execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx);
	};

	namespace cmd
	{
		inline black_tint g_black_tint("blacktint", "Black Window Tint", "Makes their windows black.", 0);
	}
}
