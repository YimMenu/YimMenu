#pragma once

#include "backend/looped_command.hpp"

namespace big
{
	class auto_tp_to_waypoint : public looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override;
	};

	namespace cmd
	{
		inline auto_tp_to_waypoint g_auto_tp_to_waypoint("autotptowp", "Auto-Teleport To Waypoint", "Automatically teleports you to a waypoint as soon as you set one.",
		    g.self.auto_tp);
	}
}
