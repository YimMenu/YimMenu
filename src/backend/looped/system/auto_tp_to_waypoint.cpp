#include "backend/looped_command.hpp"
#include "natives.hpp"
#include "util/teleport.hpp"

namespace big
{
	class auto_tp_to_waypoint : looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override
		{
			teleport::to_blip((int)BlipIcons::Waypoint);
		}
	};

	auto_tp_to_waypoint g_auto_tp_to_waypoint("autotptowp", "Auto-Teleport To Waypoint", "Automatically teleports you to a waypoint as soon as you set one",
	    g.self.auto_tp);
}
