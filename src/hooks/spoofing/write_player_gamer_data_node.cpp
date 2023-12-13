#include "hooking.hpp"

#include <netsync/nodes/player/CPlayerGamerDataNode.hpp>

namespace big
{
	void hooks::write_player_gamer_data_node(rage::netObject* player, CPlayerGamerDataNode* node)
	{
		g_hooking->get_original<write_player_gamer_data_node>()(player, node);

		if (g.spoofing.spoof_crew_data)
		{
			node->m_clan_data.m_clan_member_id    = 1;
			node->m_clan_data.m_clan_id           = 41564112;
			node->m_clan_data.m_clan_id_2         = 41564112;
			node->m_clan_data.m_clan_color        = 420;
			node->m_clan_data.m_clan_member_count = 15;
			node->m_clan_data.m_clan_created_time = 420;

			strcpy(node->m_clan_data.m_clan_tag, g.spoofing.crew_tag.c_str());
			node->m_clan_data.m_is_system_clan = g.spoofing.rockstar_crew;
			node->m_clan_data.m_is_clan_open   = g.spoofing.square_crew_tag;

			if (g.spoofing.rockstar_crew)
			{
				strcpy(node->m_clan_data.m_clan_name, "Rockstar");
			}
		}
	}
}
