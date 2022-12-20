#include "backend/looped/looped.hpp"
#include "natives.hpp"

namespace big
{
	static bool bLastNoRagdoll = false;

	void looped::self_no_ragdoll()
	{
		bool bNoRagdoll = g.self.no_ragdoll;

		if (bNoRagdoll || (!bNoRagdoll && bNoRagdoll != bLastNoRagdoll))
		{
			PED::SET_PED_CAN_RAGDOLL(self::ped, !g.self.no_ragdoll);

			bLastNoRagdoll = g.self.no_ragdoll;
		}
	}
}
