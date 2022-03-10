#include "backend/looped/looped.hpp"
#include "natives.hpp"

namespace big
{
	static bool bLastInvisibility = false;

	void looped::self_invisibility()
	{
		bool bInvisibility = g->self.invisibility;

		if (NETWORK::NETWORK_IS_SESSION_STARTED() || !g->self.local_visibility)
		{
			if (bInvisibility || (!bInvisibility && bInvisibility != bLastInvisibility))
			{
				ENTITY::SET_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID(), !g->self.invisibility, 0);

				bLastInvisibility = g->self.invisibility;
			}
		}

		if (g->self.local_visibility)
		{
			NETWORK::SET_ENTITY_LOCALLY_VISIBLE(PLAYER::PLAYER_PED_ID());
		}
	}
}
