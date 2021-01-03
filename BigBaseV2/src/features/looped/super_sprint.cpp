#include "features.hpp"

namespace big
{
	static bool bLastSuperSprint = false;
	static bool bSkyDiving = false;

	void features::super_sprint()
	{
		bool bSuperSprint = g_settings.options["super_sprint"].get<bool>();

		if (bSuperSprint)
		{
			QUEUE_JOB_BEGIN_CLAUSE(= )
			{
				Ped player = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_playerId);
				Vector3 location = ENTITY::GET_ENTITY_COORDS(player, true);
				float ground;
				MISC::GET_GROUND_Z_FOR_3D_COORD(location.x, location.y, location.z, &ground, 0, 0);

				bool flying = location.z - ground > 3;
				if (flying && !bSkyDiving)
				{
					TASK::TASK_SKY_DIVE(player, true);

					bSkyDiving = true;
				}
				else if (!flying && bSkyDiving)
					bSkyDiving = false;

				if (TASK::IS_PED_SPRINTING(player) || flying)
				{
					Vector3 offset = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(player, 0, 0.6, 0);
					ENTITY::APPLY_FORCE_TO_ENTITY(player, 1, 0.0f, 1.3, bSkyDiving ? 1.f : 0.f, 0.0f, 0.0f, 0.0f, 0, 1, 1, 1, 0, 1);

					PLAYER::SET_PLAYER_SPRINT(g_playerId, 1);
					PLAYER::SET_RUN_SPRINT_MULTIPLIER_FOR_PLAYER(g_playerId, 1.49);
				}
				else
				{
					PLAYER::SET_RUN_SPRINT_MULTIPLIER_FOR_PLAYER(g_playerId, 1.0);
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