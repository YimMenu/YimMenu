#include "backend/looped/looped.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "gta/replay.hpp"
#include "gta/enums.hpp"

namespace big
{
	void looped::pie_menu()
	{
		if (g->pie_menu.enabled)
		{
			if (PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_SELECT_WEAPON))
			{
				if (PAD::IS_CONTROL_JUST_PRESSED(0, (int)ControllerInputs::INPUT_JUMP))
					g->pie_menu.selected = !g->pie_menu.selected;

				if (g->pie_menu.selected)
				{
					HUD::HUD_FORCE_WEAPON_WHEEL(false);
					HUD::HUD_SUPPRESS_WEAPON_WHEEL_RESULTS_THIS_FRAME();
					HUD::HIDE_HUD_COMPONENT_THIS_FRAME(2);
					HUD::HIDE_HUD_COMPONENT_THIS_FRAME(19);
					HUD::HIDE_HUD_COMPONENT_THIS_FRAME(20);
					HUD::HIDE_HUD_COMPONENT_THIS_FRAME(22);
					g->pie_menu.active = true;
				}
				else {
					g->pie_menu.active = false;
				}
			}
			else {
				g->pie_menu.active = false;
			}
		}
	}
}
