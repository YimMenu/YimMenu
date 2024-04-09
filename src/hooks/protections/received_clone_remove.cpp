#include "hooking/hooking.hpp"
#include "util/notify.hpp"

namespace big
{
	void hooks::received_clone_remove(CNetworkObjectMgr* mgr, CNetGamePlayer* src, CNetGamePlayer* dst, int16_t object_id, uint32_t ownership_token)
	{
		if (dst->m_player_info->m_ped->m_net_object->m_object_id == object_id) [[unlikely]]
		{
			notify::crash_blocked(src, "player ped removal");
			return;
		}

		g_hooking->get_original<hooks::received_clone_remove>()(mgr, src, dst, object_id, ownership_token);
	}
}