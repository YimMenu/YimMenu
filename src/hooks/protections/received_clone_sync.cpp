#include "hooking/hooking.hpp"
#include "services/players/player_service.hpp"
#include "util/notify.hpp"

namespace big
{
	eAckCode hooks::received_clone_sync(CNetworkObjectMgr* mgr, CNetGamePlayer* src, CNetGamePlayer* dst, eNetObjType object_type, uint16_t object_id, rage::datBitBuffer* buffer, uint16_t unk, uint32_t timestamp)
	{
		if (object_type < eNetObjType::NET_OBJ_TYPE_AUTOMOBILE || object_type > eNetObjType::NET_OBJ_TYPE_TRAIN) [[unlikely]]
		{
			notify::crash_blocked(src, "out of bounds object type");
			return eAckCode::ACKCODE_FAIL;
		}

		if (auto net_obj = g_pointers->m_gta.m_get_net_object(mgr, object_id, true); net_obj && net_obj->m_object_type != (int16_t)object_type) [[unlikely]]
		{
			notify::crash_blocked(src, "incorrect object type");
			return eAckCode::ACKCODE_FAIL;
		}

		auto plyr = g_player_service->get_by_id(src->m_player_id);

		if (plyr && plyr->block_clone_sync) [[unlikely]]
			return eAckCode::ACKCODE_FAIL;

		g.m_syncing_player      = src;
		g.m_syncing_object_type = object_type;

		g.debug.fuzzer.thread_id = GetCurrentThreadId();
		if (g.debug.fuzzer.enabled_object_types[(int)object_type]) [[unlikely]]
			g.debug.fuzzer.active = true;
		g.debug.fuzzer.syncing_object_id = object_id;
		auto ret = g_hooking->get_original<received_clone_sync>()(mgr, src, dst, object_type, object_id, buffer, unk, timestamp);
		g.debug.fuzzer.active = false;

		return ret;
	}
}
