#include "backend/looped/looped.hpp"
#include "natives.hpp"

namespace big
{
	static bool bLastInvisibility = false;

	void looped::self_invisibility()
	{
		Ped ped = self::ped;

		bool bInvisibility = g->self.invisibility;

		if (bInvisibility || (!bInvisibility && bInvisibility != bLastInvisibility))
		{
			ENTITY::SET_ENTITY_VISIBLE(ped, !g->self.invisibility, 0);

			bLastInvisibility = g->self.invisibility;
		}

		if (NETWORK::NETWORK_IS_SESSION_STARTED())
		{
			if (g->self.invisibility && g->self.local_visibility)
			{
				NETWORK::SET_ENTITY_LOCALLY_VISIBLE(ped);
			}
		}
		else 
		{
			if (g->self.local_visibility)
			{
				ENTITY::SET_ENTITY_VISIBLE(ped, true, 0);
			}
		}
	}
}
