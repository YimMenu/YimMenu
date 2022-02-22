#include "backend/looped/looped.hpp"
#include "natives.hpp"

namespace big
{
	static bool bLastGodMode = false;

	void looped::self_godmode()
	{
		bool bGodMode = g->self.godmode;

		if (bGodMode || (!bGodMode && bGodMode != bLastGodMode))
		{
			ENTITY::SET_ENTITY_INVINCIBLE(PLAYER::PLAYER_PED_ID(), g->self.godmode);

			bLastGodMode = g->self.godmode;
		}
	}
}