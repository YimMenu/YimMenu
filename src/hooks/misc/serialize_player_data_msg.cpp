#include "gta_util.hpp"
#include "hooking.hpp"

#include <network/CNetGamePlayerDataMsg.hpp>
#include <network/Network.hpp>

namespace big
{
	bool hooks::serialize_player_data_msg(CNetGamePlayerDataMsg* msg, rage::datBitBuffer* buffer)
	{
		return g_hooking->get_original<hooks::serialize_player_data_msg>()(msg, buffer);
	}
}