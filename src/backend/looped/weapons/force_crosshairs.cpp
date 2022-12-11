#include "backend/looped/looped.hpp"
#include "natives.hpp"
#include "core/enums.hpp"

namespace big
{
	void looped::weapons_force_crosshairs()
	{
		if (g->weapons.force_crosshairs) {
			HUD::SHOW_HUD_COMPONENT_THIS_FRAME(static_cast<int>(HudComponents::RETICLE));
		}
	}
}