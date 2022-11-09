#include "backend/looped/looped.hpp"
#include "natives.hpp"

namespace big
{
	void looped::always_controll()
	{
		if (g->tunables.always_control)
		{
			PAD::ENABLE_ALL_CONTROL_ACTIONS(0);
			PAD::ENABLE_ALL_CONTROL_ACTIONS(2);
			PLAYER::SET_PLAYER_CONTROL(self::id, true, 0);
		}
	}
}
