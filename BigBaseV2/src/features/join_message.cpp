#include "features.hpp"

namespace big
{
	void features::join_message()
	{
		bool bJoinMessage = g_settings.options["join_message"].get<bool>();

		if (bJoinMessage)
		{
			for (int i = 0; i < 32; i++) {
				if (!g_players[i].is_online && ENTITY::DOES_ENTITY_EXIST(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i))) {
					char joinMsg[64];
					strcpy(joinMsg, g_players[i].name);
					strcat(joinMsg, "is joining");

					features::notify::above_map(joinMsg);
				}
			}
		}
	}
}