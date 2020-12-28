#include "features.hpp"
#include "pointers.hpp"

namespace big
{
	void features::join_message(Player player)
	{
		bool bJoinMessage = g_settings.options["join_message"].get<bool>();

		if (bJoinMessage)
		{
			char joinMsg[64];
			strcpy(joinMsg, "<C>");
			strcat(joinMsg, g_pointers->m_get_player_name(player));
			strcat(joinMsg, "</C> is joining.");

			features::notify::above_map(joinMsg);
		}
	}
}