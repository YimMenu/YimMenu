#include "features.hpp"
#include "pointers.hpp"

namespace big
{
	void features::join_message()
	{
		bool bJoinMessage = g_settings.options["join_message"].get<bool>();

		if (bJoinMessage)
		{
			for (uint8_t i = 0; i < 32; i++)
			{
				if (i == g_playerId) continue;

				if (ENTITY::DOES_ENTITY_EXIST(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i)) && !NETWORK::NETWORK_IS_PLAYER_CONNECTED(i))
				{
					char joinMsg[64];
					strcpy(joinMsg, "<C>");
					strcat(joinMsg, g_pointers->m_get_player_name(i));
					strcat(joinMsg, "</C> is joining.");

					features::notify::above_map(joinMsg);
				}
			}
		}
	}
}