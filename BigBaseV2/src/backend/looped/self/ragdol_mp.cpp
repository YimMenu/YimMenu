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
			if (PAD::IS_CONTROL_JUST_PRESSED(0, 45)) 
			{
				if (!PED::IS_PED_RAGDOLL(self::ped) && NETWORK::NETWORK_IS_SESSION_STARTED())
				{
					PED::SET_PED_TO_RAGDOLL(self::ped, 2000, 6000, 2, false, true, false);
				}
			}
		}
	}
}