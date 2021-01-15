#include "features.hpp"

namespace big
{
	static bool bLastNoRagdoll = false;

	void features::no_ragdoll()
	{
		bool bNoRagdoll = g_settings.options["ragdoll"].get<bool>();

		if (bNoRagdoll || (!bNoRagdoll && bNoRagdoll != bLastNoRagdoll))
		{
			QUEUE_JOB_BEGIN_CLAUSE(= )
			{
				Ped player = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_playerId);

				PED::SET_PED_CAN_RAGDOLL(player, !bNoRagdoll);
				PED::SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(player, !bNoRagdoll);
				PED::SET_PED_RAGDOLL_ON_COLLISION(player, !bNoRagdoll);
			}QUEUE_JOB_END_CLAUSE

				bLastNoRagdoll = bNoRagdoll;
		}
	}
}