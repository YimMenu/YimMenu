#include "gta_util.hpp"
#include "hooking.hpp"

#include <network/CNetGamePlayerDataMsg.hpp>
#include <network/Network.hpp>

namespace big
{
	bool hooks::serialize_player_data_msg(CNetGamePlayerDataMsg* msg, rage::datBitBuffer* buffer)
	{
		int old_group = msg->m_matchmaking_group;

		bool ret                 = g_hooking->get_original<hooks::serialize_player_data_msg>()(msg, buffer);
		msg->m_matchmaking_group = old_group;
		return ret;
	}
}