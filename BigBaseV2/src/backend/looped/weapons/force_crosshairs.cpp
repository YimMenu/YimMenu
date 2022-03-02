#include "backend/looped/looped.hpp"
#include "natives.hpp"

namespace big
{
	void looped::weapons_force_crosshairs()
	{
		if (g->weapons.force_crosshairs) {
			HUD::SHOW_HUD_COMPONENT_THIS_FRAME(14 /*RETICLE*/);
		}
	}
}