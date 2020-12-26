#include "features.hpp"

namespace big
{
	static bool bLastNeverWanted = false;

	void features::never_wanted()
	{
		QUEUE_JOB_BEGIN_CLAUSE()
		{
			bool bNeverWanted = g_settings.options["never_wanted"].get<bool>();

			if (bNeverWanted && PLAYER::GET_PLAYER_WANTED_LEVEL(g_playerId) > 0)
			{
				PLAYER::SET_PLAYER_WANTED_LEVEL(g_playerId, 0, true);
				PLAYER::SET_MAX_WANTED_LEVEL(0);
			}
			else if (!bNeverWanted && bNeverWanted != bLastNeverWanted)
			{
				PLAYER::SET_MAX_WANTED_LEVEL(5);
			}

			bLastNeverWanted = bNeverWanted;
		}QUEUE_JOB_END_CLAUSE
	}
}