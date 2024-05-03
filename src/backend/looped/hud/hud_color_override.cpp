#include "backend/bool_command.hpp"
#include "natives.hpp"

namespace big
{
	class hudcolor : bool_command
	{
		using bool_command::bool_command;

		virtual void on_enable() override
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

		virtual void on_disable() override
		{
			for (int i = 0; i < hud_colors.size(); i++)
			{
				auto& col = g.self.hud.hud_color_defaults[i];
				HUD::REPLACE_HUD_COLOUR_WITH_RGBA(i, col.r, col.g, col.b, col.a);
			}
		}
	};

	hudcolor g_hudcolor_looped("hudcolor", "OVERRIDE_HUD_COLOR", "OVERRIDE_HUD_COLOR_DESC", g.self.hud.color_override);
}
