#include "backend/looped/looped.hpp"
#include "natives.hpp"

namespace big
{
	void looped::self_no_ragdoll()
	{
		Ped player = PLAYER::PLAYER_PED_ID();

		PED::SET_PED_CAN_RAGDOLL(player, !g.self.no_ragdoll);
	}
}
