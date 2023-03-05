#include "natives.hpp"
#include "backend/looped_command.hpp"

namespace big
{

	class hudcolor_looped : looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override
		{
			if (g.self.hud.shcolor)
			{
				HUD::REPLACE_HUD_COLOUR_WITH_RGBA(g.self.hud.index, g.self.hud.r, g.self.hud.g, g.self.hud.b, g.self.hud.a);
			}
			if (g.self.hud.mhcolor)
			{
				HUD::SET_CUSTOM_MP_HUD_COLOR(g.self.hud.hcolor);
			}
			if (g.self.hud.mtcolor)
			{
				HUD::OVERRIDE_MP_TEXT_CHAT_COLOR(0, g.self.hud.tcolor);
			}
		}
	};

	hudcolor_looped g_hudcolor_looped("hudcolor", "Hudcolor Overide", "Replaces features of your hud with custom colors you set",
	    g.self.hud.hudcolor);
	bool_command g_shcolor("singlehudcol", "Hud Color", "enables the singlehudcol", g.self.hud.shcolor);
	bool_command g_mhcolor("mphudcol", "MP Hud Color", "enables the mphudcol", g.self.hud.mhcolor);
	bool_command g_mtcolor("mptextcol", "MP Text Color", "enables the mptextcol", g.self.hud.mtcolor);
}
