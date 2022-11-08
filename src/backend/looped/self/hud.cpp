#include "backend/looped/looped.hpp"
#include "natives.hpp"
#include "core/data/hud_component_names.hpp"
#include <algorithm>

namespace big
{
	static bool bLastHideRadar = false;

	void looped::self_hud()
	{
		const bool bHideRadar = g->self.hide_radar;
		const bool bHideAmmo = g->self.hide_ammo;
		auto& bHudComponents = g->self.hud_components_states;

		if (bHideRadar)
		{
			HUD::DISPLAY_RADAR(false);
		}
		else if (bHideRadar != bLastHideRadar)
		{
			HUD::DISPLAY_RADAR(true);
		}
		bLastHideRadar = bHideRadar;

		if (bHideAmmo)
		{
			HUD::DISPLAY_AMMO_THIS_FRAME(false);
		}

		if (
			std::all_of(
				std::begin(bHudComponents),
				std::end(bHudComponents),
				[](bool i) { return i; }
			)
		) {
			HUD::DISPLAY_HUD(false);
		}
		else
		{
			HUD::DISPLAY_HUD(true);
			for (int i = 0; i < (int)HudComponents::HUD_WEAPONS; i++)
			{
				if (bHudComponents[i])
					HUD::HIDE_HUD_COMPONENT_THIS_FRAME(i + 1);
			}
		}
	}
}
