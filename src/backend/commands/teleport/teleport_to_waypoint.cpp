#include "backend/command.hpp"
#include "natives.hpp"
#include "util/teleport.hpp"

namespace big
{
	class teleport_to_waypoint : command
	{
		using command::command;

		virtual void execute(const command_arguments&, const std::shared_ptr<command_context> ctx) override
		{
			teleport::to_waypoint();
		}
	};

	teleport_to_waypoint g_teleport_to_waypoint("waypointtp", "VIEW_HOTKEY_SETTINGS_TELEPORT_TO_WAYPOINT", "BACKEND_TELEPORT_TO_WAYPOINT_DESC", 0);
}