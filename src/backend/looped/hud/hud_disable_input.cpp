#include "backend/looped/looped.hpp"
#include "natives.hpp"

namespace big
{
	void looped::hud_disable_input()
	{
		if (g.self.hud.typing)
		{
			PAD::DISABLE_ALL_CONTROL_ACTIONS(0);
			g.self.hud.typing--;
		}
		g.settings.hotkeys.is_mp_chat_active = HUD::IS_MP_TEXT_CHAT_TYPING();
	}
}