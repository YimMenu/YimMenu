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
	}
}