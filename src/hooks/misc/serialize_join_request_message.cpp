#include "hooking/hooking.hpp"
#include <network/CNetGamePlayerDataMsg.hpp>
#include <network/RemoteGamerInfoMsg.hpp>
#include <network/CMsgJoinRequest.hpp>

namespace big
{
	bool hooks::serialize_join_request_message(RemoteGamerInfoMsg* info, void* data, int size, int* bits_serialized)
	{
		if (info->unk_0xC0 == 0)
			info->unk_0xC0 = 1; // TODO: do we need this anymore?

		if (g.protections.desync_kick)
			info->m_gamer_info.m_nat_type = 0;

		info->m_num_handles = 0;

		return g_hooking->get_original<hooks::serialize_join_request_message>()(info, data, size, bits_serialized);
	}

	bool hooks::serialize_join_request_message_2(CMsgJoinRequest* msg, void* buf, int size, int* bits_serialized)
	{
		auto& data = msg->m_player_data_msg;

		if (g.session.join_in_sctv_slots)
			data.m_matchmaking_group = 4;

		if (g.protections.desync_kick)
			data.m_nat_type = 0;

		return g_hooking->get_original<hooks::serialize_join_request_message_2>()(msg, buf, size, bits_serialized);
	}
}