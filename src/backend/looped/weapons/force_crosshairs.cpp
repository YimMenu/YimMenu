#include "backend/looped_command.hpp"
#include "natives.hpp"

namespace big
{
	class force_crosshairs : looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override
		{
			HUD::SHOW_HUD_COMPONENT_THIS_FRAME(static_cast<int>(HudComponents::RETICLE));
		}
	};

	force_crosshairs g_force_crosshairs("crosshairs", "Force Crosshairs", "Shows the crosshair even when you are not aiming",
	    g.weapons.force_crosshairs);// do we need this?
}
