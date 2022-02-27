#include "backend/looped/looped.hpp"
#include "natives.hpp"

namespace big
{
	void looped::self_no_ragdoll()
	{
		Ped player = PLAYER::PLAYER_PED_ID();

		if (g->self.no_ragdoll) {
			PED::SET_PED_CAN_RAGDOLL(player, !g->self.no_ragdoll);
			PED::SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(player, !g->self.no_ragdoll);
			PED::SET_PED_RAGDOLL_ON_COLLISION(player, !g->self.no_ragdoll);
		}
			
	}
}
