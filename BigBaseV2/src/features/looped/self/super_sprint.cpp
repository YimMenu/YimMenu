#include "features/self.hpp"
#include "natives.hpp"

namespace big
{
	static bool bLastSuperSprint = false;
	static bool bSkyDiving = false;

	void self::super_sprint()
	{
		Ped player = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player.id);

		if (PED::IS_PED_IN_ANY_VEHICLE(player, true)) return;

		bool bSuperSprint = g_settings.options["super_sprint"].get<bool>();

		if (bSuperSprint)
		{
			if (TASK::IS_PED_SPRINTING(player))
			{
				Vector3 offset = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(player, 0, 0.6, 0);
				ENTITY::APPLY_FORCE_TO_ENTITY(player, 1, 0.0f, 1.3, bSkyDiving ? 1.f : 0.f, 0.0f, 0.0f, 0.0f, 0, 1, 1, 1, 0, 1);

				PLAYER::SET_PLAYER_SPRINT(g_player.id, 1);
				PLAYER::SET_RUN_SPRINT_MULTIPLIER_FOR_PLAYER(g_player.id, 1.49);
			}
			else
			{
				PLAYER::SET_RUN_SPRINT_MULTIPLIER_FOR_PLAYER(g_player.id, 1.0);
			}
		}
		else if (!bSuperSprint && bSuperSprint != bLastSuperSprint)
		{
			PLAYER::SET_RUN_SPRINT_MULTIPLIER_FOR_PLAYER(g_player.id, 1.0);
		}

		bLastSuperSprint = bSuperSprint;
	}
}