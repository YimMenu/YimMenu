#include "hooking.hpp"
#include "gta_util.hpp"
#include <network/Network.hpp>
#include <network/RemoteGamerInfoMsg.hpp>

namespace big
{
	bool hooks::serialize_join_request_message(RemoteGamerInfoMsg* info, void* data, int size, int* bits_serialized)
	{
		if (info->m_unk == 0)
			info->m_unk = 1;

		info->m_required_player_count = 0;
		return g_hooking->get_original<hooks::serialize_join_request_message>()(info, data, size, bits_serialized);
	}
}