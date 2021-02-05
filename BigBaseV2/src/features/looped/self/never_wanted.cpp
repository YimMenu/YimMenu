#include "features/self.hpp"
#include "natives.hpp"

namespace big
{
	static bool bLastNeverWanted = false;

	void self::never_wanted()
	{
		bool bNeverWanted = g_settings.options["never_wanted"].get<bool>();

		if (bNeverWanted && PLAYER::GET_PLAYER_WANTED_LEVEL(g_player.id) > 0)
		{
			PLAYER::SET_PLAYER_WANTED_LEVEL(g_player.id, 0, true);
			PLAYER::SET_MAX_WANTED_LEVEL(0);
		}
		else if (!bNeverWanted && bNeverWanted != bLastNeverWanted)
		{
			PLAYER::SET_MAX_WANTED_LEVEL(5);
		}

		bLastNeverWanted = bNeverWanted;
	}
}