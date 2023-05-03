#include "no_ragdoll.hpp"

#include "fiber_pool.hpp"
#include "natives.hpp"

namespace big
{
	void no_ragdoll::on_tick()
	{
		PED::SET_PED_CAN_RAGDOLL(self::ped, false);
	}

	void no_ragdoll::on_disable()
	{
		PED::SET_PED_CAN_RAGDOLL(self::ped, true);
	}
}
