#include "backend/command.hpp"
#include "natives.hpp"
#include "util/teleport.hpp"

namespace big
{
	class teleport_to_waypoint : command
	{
		using command::command;

		virtual void execute(const std::vector<std::uint64_t>&, const std::shared_ptr<command_context> ctx)
		{
			teleport::to_waypoint();
		}
	};

	teleport_to_waypoint g_teleport_to_waypoint("waypointtp", "Teleport To Waypoint", "Teleports you to your waypoint", 0);
}