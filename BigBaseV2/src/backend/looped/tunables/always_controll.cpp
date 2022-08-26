#include "backend/looped/looped.hpp"
#include "natives.hpp"

namespace big
{
	void looped::always_controll()
	{
		if (g->tunables.always_controll)
		{
			PAD::ENABLE_ALL_CONTROL_ACTIONS(0);
			PAD::ENABLE_ALL_CONTROL_ACTIONS(2);
		}
	}
}