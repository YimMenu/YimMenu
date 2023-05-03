#include "force_crosshairs.hpp"

#include "natives.hpp"

namespace big
{
	void force_crosshairs::on_tick()
	{
		HUD::SHOW_HUD_COMPONENT_THIS_FRAME(static_cast<int>(HudComponents::RETICLE));
	}
}
