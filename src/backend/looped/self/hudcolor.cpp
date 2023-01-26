#include "natives.hpp"
#include "backend/looped_command.hpp"

namespace big
{

	class hudcolor_looped : looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override
		{
			if(g.self.shcolor)
			{
				HUD::REPLACE_HUD_COLOUR_WITH_RGBA(g.self.index, g.self.r, g.self.g, g.self.b, g.self.a);
			}
			if(g.self.mhcolor)
			{
				HUD::SET_CUSTOM_MP_HUD_COLOR(g.self.hcolor);
			}
			if(g.self.mtcolor)
			{
				HUD::OVERRIDE_MP_TEXT_CHAT_COLOR(0, g.self.tcolor);
			}
		}
	};

	hudcolor_looped g_hudcolor_looped("hudcolor", "Hudcolor Overide", "Replaces features of your hud with custom colors you set", g.self.hudcolor);
	bool_command g_shcolor("singlehudcol", "Hud Color", "enables the singlehudcol", g.self.shcolor);
	bool_command g_mhcolor("mphudcol", "MP Hud Color", "enables the mphudcol", g.self.mhcolor);
	bool_command g_mtcolor("mptextcol", "MP Text Color", "enables the mptextcol", g.self.mtcolor);
}
