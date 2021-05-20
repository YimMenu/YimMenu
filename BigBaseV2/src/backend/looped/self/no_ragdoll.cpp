#include "backend/looped/looped.hpp"
#include "natives.hpp"

namespace big
{
	static bool bLastNoRagdoll = false;

	void looped::self_no_ragdoll()
	{
		bool bNoRagdoll = g.self.no_ragdoll;
		Ped player = PLAYER::PLAYER_PED_ID();

		if ((bNoRagdoll && PED::IS_PED_RUNNING_RAGDOLL_TASK(player)) || (!bNoRagdoll && bNoRagdoll != bLastNoRagdoll))
		{
			if (ENTITY::GET_ENTITY_HEIGHT_ABOVE_GROUND(player) < 1.0)
				TASK::CLEAR_PED_TASKS_IMMEDIATELY(player);

			bLastNoRagdoll = bNoRagdoll;
		}
	}
}