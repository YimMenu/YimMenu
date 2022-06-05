#include "backend/looped/looped.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "script_global.hpp"
#include "core/enums.hpp"

namespace big
{
	void looped::ragdoll_mp()
	{
		if (g->self.allow_ragdoll)
		{
			if (PAD::IS_CONTROL_JUST_PRESSED(0, 45) && PED::IS_PED_JUMPING(self::ped) && !PED::IS_PED_RAGDOLL(self::ped) && NETWORK::NETWORK_IS_SESSION_STARTED())
			{
				PED::SET_PED_TO_RAGDOLL(self::ped, 2000, 6000, 0, false, true, false);
				ENTITY::APPLY_FORCE_TO_ENTITY(self::ped, 1, self::pos.x, self::pos.y, self::pos.z + 8.0f, 0.f, 0.f, 0.5f, 0, false, true, true, false, true);
			}
		}
	}
}