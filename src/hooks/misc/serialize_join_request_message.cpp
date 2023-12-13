#include "gta_util.hpp"
#include "hooking.hpp"

#include <network/Network.hpp>
#include <network/RemoteGamerInfoMsg.hpp>

namespace big
{
	bool hooks::serialize_join_request_message(RemoteGamerInfoMsg* info, void* data, int size, int* bits_serialized)
	{
		if (info->unk_0xC0 == 0)
			info->unk_0xC0 = 1;

		info->m_num_handles = 0;
		return g_hooking->get_original<hooks::serialize_join_request_message>()(info, data, size, bits_serialized);
	}
}