#include "hooking/hooking.hpp"
#include "services/players/player_service.hpp"
#include "util/notify.hpp"
#include "gta/pools.hpp"
#include "gta_util.hpp"

#include <network/netObjectIds.hpp>

namespace big
{
	void hooks::received_clone_create(CNetworkObjectMgr* mgr, CNetGamePlayer* src, CNetGamePlayer* dst, eNetObjType object_type, int32_t object_id, int32_t object_flag, rage::datBitBuffer* buffer, int32_t timestamp)
	{
		if (object_type < eNetObjType::NET_OBJ_TYPE_AUTOMOBILE || object_type > eNetObjType::NET_OBJ_TYPE_TRAIN) [[unlikely]]
		{
			notify::crash_blocked(src, "out of bounds object type");
			return;
		}

		// can delete objects here too
		if (dst && dst->m_player_info && dst->m_player_info->m_ped && dst->m_player_info->m_ped->m_net_object
		    && object_id == dst->m_player_info->m_ped->m_net_object->m_object_id) [[unlikely]]
		{
			notify::crash_blocked(src, "player create");
			return;
		}

		if (g_local_player && g_local_player->m_vehicle && g_local_player->m_vehicle->m_net_object
		    && object_id == g_local_player->m_vehicle->m_net_object->m_object_id) [[unlikely]]
		{
			if (auto plyr = g_player_service->get_by_id(src->m_player_id))
			{
				g.reactions.delete_vehicle.process(plyr);
			}
			return;
		}

		if (auto object = g_pointers->m_gta.m_get_net_object(*g_pointers->m_gta.m_network_object_mgr, object_id, true)) [[likely]]
		{
			if (object->m_object_type == (int)eNetObjType::NET_OBJ_TYPE_PLAYER && object->m_owner_id != src->m_player_id) [[unlikely]]
			{
				std::string target = "<UNKNOWN>";

				if (auto tgt = g_player_service->get_by_id(object->m_owner_id))
					target = tgt->get_name();

				LOGF(stream::net_sync, WARNING, "Rejecting clone create from {}, who is trying to delete {}'s player ped", src->get_name(), target);
				return;
			}
		}

		switch (object_type)
		{
		case eNetObjType::NET_OBJ_TYPE_AUTOMOBILE:
		case eNetObjType::NET_OBJ_TYPE_BIKE:
		case eNetObjType::NET_OBJ_TYPE_BOAT:
		case eNetObjType::NET_OBJ_TYPE_HELI:
		case eNetObjType::NET_OBJ_TYPE_PLANE:
		case eNetObjType::NET_OBJ_TYPE_SUBMARINE:
		case eNetObjType::NET_OBJ_TYPE_TRAILER:
		case eNetObjType::NET_OBJ_TYPE_TRAIN:
			if ((*g_pointers->m_gta.m_vehicle_allocator)->m_size < 10) [[unlikely]]
			{
				// We don't have enough memory to handle this
				g_notification_service.push_warning("Protections", "Low vehicle allocator size");
				return;
			}
		}

		if (gta_util::get_net_object_ids()->is_object_id_usable(object_id))
		{
			LOGF(stream::net_sync, WARNING, "{} sent us an object create request with an object ID that is in our usable object ID list. Somebody lied to us...", src->get_name());
			gta_util::get_net_object_ids()->remove_object_id(object_id);
		}

		auto plyr = g_player_service->get_by_id(src->m_player_id);

		if (plyr && plyr->block_clone_create) [[unlikely]]
			return;

		g.m_syncing_player      = src;
		g.m_syncing_object_type = object_type;

		g.debug.fuzzer.thread_id = GetCurrentThreadId();
		if (g.debug.fuzzer.enabled_object_types[(int)object_type]) [[unlikely]]
			g.debug.fuzzer.active = true;
		g.debug.fuzzer.syncing_object_id = object_id;
		g_hooking->get_original<hooks::received_clone_create>()(mgr, src, dst, object_type, object_id, object_flag, buffer, timestamp);
		g.debug.fuzzer.active = false;
	}
}