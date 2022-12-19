#include "hooking.hpp"
#include "util/notify.hpp"

namespace big
{
	bool hooks::received_clone_create(CNetworkObjectMgr* mgr, CNetGamePlayer* src, CNetGamePlayer* dst, eNetObjType object_type, int32_t object_id, int32_t object_flag, rage::datBitBuffer* buffer, int32_t timestamp)
	{
		if (object_type < eNetObjType::NET_OBJ_TYPE_AUTOMOBILE || object_type > eNetObjType::NET_OBJ_TYPE_TRAIN)
		{
			notify::crash_blocked(src, "out of bounds object type");
			return true;
		}

		g.m_syncing_player = src;
		return g_hooking->get_original<hooks::received_clone_create>()(mgr, src, dst, object_type, object_id, object_flag, buffer, timestamp);
	}
}