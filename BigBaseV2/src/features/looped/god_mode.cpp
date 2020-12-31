#include "features.hpp"

namespace big
{
	static bool bLastGodMode = false;

	void features::god_mode()
	{
		bool bGodMode = g_settings.options["god_mode"].get<bool>();

		if (bGodMode || (!bGodMode && bGodMode != bLastGodMode))
		{
			QUEUE_JOB_BEGIN_CLAUSE(= )
			{
				ENTITY::SET_ENTITY_INVINCIBLE(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_playerId), bGodMode);
			}QUEUE_JOB_END_CLAUSE

			bLastGodMode = bGodMode;
		}
	}
}