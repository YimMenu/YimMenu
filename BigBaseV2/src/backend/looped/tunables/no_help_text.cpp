#include "backend/looped/looped.hpp"
#include "natives.hpp"

namespace big
{
	void looped::disable_help_text()
	{
		if (g->tunables.disable_help_text)
		{
			HUD::HIDE_HELP_TEXT_THIS_FRAME();
		}
	}
}
