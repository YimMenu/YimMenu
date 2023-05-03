#pragma once

#include "backend/looped_command.hpp"

namespace big
{
	class force_crosshairs : public looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override;
	};

	namespace cmd
	{
		inline force_crosshairs g_force_crosshairs("crosshairs", "Force Crosshairs", "Shows the crosshair even when you are not aiming",
		    g.weapons.force_crosshairs); // do we need this?
	}
}
