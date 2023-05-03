#include "hud_color_override.hpp"

#include "natives.hpp"

namespace big
{
	void hudcolor_looped::on_enable()
	{
		for (int i = 0; i < hud_colors.size(); i++)
		{
			color col{};
			HUD::GET_HUD_COLOUR(i, &col.r, &col.g, &col.b, &col.a);
			g.self.hud.hud_color_defaults[i] = col;
		}

		if (!g.self.hud.color_override_initialized)
		{
			g.self.hud.hud_color_overrides        = g.self.hud.hud_color_defaults;
			g.self.hud.color_override_initialized = true;
		}
		else
		{
			for (int i = 0; i < hud_colors.size(); i++)
			{
				auto& col = g.self.hud.hud_color_overrides[i];
				HUD::REPLACE_HUD_COLOUR_WITH_RGBA(i, col.r, col.g, col.b, col.a);
			}
		}
	}

	void hudcolor_looped::on_tick()
	{
	}

	void hudcolor_looped::on_disable()
	{
		for (int i = 0; i < hud_colors.size(); i++)
		{
			auto& col = g.self.hud.hud_color_defaults[i];
			HUD::REPLACE_HUD_COLOUR_WITH_RGBA(i, col.r, col.g, col.b, col.a);
		}
	}
}
