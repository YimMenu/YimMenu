#pragma once

#include "backend/player_command.hpp"

namespace big
{
	// This is pretty much desync except we don't actually remove the player from CNetworkPlayerMgr
	class complaint_kick : public player_command
	{
		using player_command::player_command;

		virtual CommandAccessLevel get_access_level();

		virtual void execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx);
	};

	namespace cmd
	{
		inline complaint_kick g_complaint_kick("desync", "Desync Kick", "This may take around 10 seconds to kick the player. Does not work against the host", 0);
	}
}
