#pragma once

#include "backend/command.hpp"

namespace big
{
	class teleport_to_waypoint : public command
	{
		using command::command;

		virtual void execute(const std::vector<std::uint64_t>&, const std::shared_ptr<command_context> ctx);
	};

	namespace cmd
	{
		inline teleport_to_waypoint g_teleport_to_waypoint("waypointtp", "Teleport To Waypoint", "Teleports you to your waypoint", 0);
	}
}
