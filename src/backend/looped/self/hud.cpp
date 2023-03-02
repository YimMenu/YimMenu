#include "backend/looped/looped.hpp"
#include "core/data/hud_component_names.hpp"
#include "natives.hpp"

namespace big
{
	static bool bLastHideRadar    = false;
	static bool bHasHUDBeenHidden = false;

	void looped::self_hud()
	{
		const bool bHideRadar        = g.self.hide_radar;
		const bool bHideAmmo         = g.self.hide_ammo;
		const bool bForceShowElement = g.self.force_show_hud_element;
		const bool bForceShowHUD     = g.self.force_show_hud;
		auto& bHudComponents         = g.self.hud_components_states;

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

		if (bForceShowHUD)
		{
			HUD::DISPLAY_HUD_WHEN_NOT_IN_STATE_OF_PLAY_THIS_FRAME();
			HUD::DISPLAY_HUD_WHEN_PAUSED_THIS_FRAME();
		}

		if (std::all_of(std::begin(bHudComponents), std::end(bHudComponents), [](bool i) {
			    return i;
		    }))
		{
			HUD::DISPLAY_HUD(false);
			bHasHUDBeenHidden = true;
		}
		else
		{
			HUD::DISPLAY_HUD(true);
			bHasHUDBeenHidden = false;
		}

		if (!bHasHUDBeenHidden)
		{
			for (int i = 0; i < static_cast<int>(HudComponents::HUD_WEAPONS); i++)
			{
				if (bHudComponents[i])
					HUD::HIDE_HUD_COMPONENT_THIS_FRAME(i + 1);
				else if (!bHudComponents[i] && bForceShowElement)
					HUD::SHOW_HUD_COMPONENT_THIS_FRAME(i + 1);
			}
		}
	}
}
