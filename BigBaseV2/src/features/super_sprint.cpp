#include "features.hpp"

namespace big
{
	static bool bLastSuperSprint = false;

	void features::super_sprint()
	{
		bool bSuperSprint = g_settings.options["super_sprint"].get<bool>();

		if (bSuperSprint)
		{
			QUEUE_JOB_BEGIN_CLAUSE(= )
			{
				if (PAD::IS_CONTROL_PRESSED(0, 32))
				{
					Ped player = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_playerId);

					Vector3 offset = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(player, 0, 0.6, 0);
					ENTITY::APPLY_FORCE_TO_ENTITY(player, 1, 0.0f, 1.3, 0, 0.0f, 0.0f, 0.0f, 0, 1, 1, 1, 0, 1);

					PLAYER::SET_PLAYER_SPRINT(g_playerId, 1);
					PLAYER::SET_RUN_SPRINT_MULTIPLIER_FOR_PLAYER(g_playerId, 1.49);
				}
			}QUEUE_JOB_END_CLAUSE
		}
		else if (!bSuperSprint && bSuperSprint != bLastSuperSprint)
		{
			QUEUE_JOB_BEGIN_CLAUSE(= )
			{
				PLAYER::SET_RUN_SPRINT_MULTIPLIER_FOR_PLAYER(g_playerId, 1.0);
			}QUEUE_JOB_END_CLAUSE
		}

		bLastSuperSprint = bSuperSprint;
	}
}