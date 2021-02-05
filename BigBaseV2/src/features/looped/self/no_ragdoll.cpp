#include "features/self.hpp"
#include "natives.hpp"

namespace big
{
	static bool bLastNoRagdoll = false;

	void self::no_ragdoll()
	{
		bool bNoRagdoll = g_settings.options["ragdoll"].get<bool>();

		if (bNoRagdoll || (!bNoRagdoll && bNoRagdoll != bLastNoRagdoll))
		{
			Ped player = PLAYER::PLAYER_PED_ID();

			PED::SET_PED_CAN_RAGDOLL(player, !bNoRagdoll);
			PED::SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(player, !bNoRagdoll);
			PED::SET_PED_RAGDOLL_ON_COLLISION(player, !bNoRagdoll);

			bLastNoRagdoll = bNoRagdoll;
		}
	}
}