#include "hooking.hpp"
#include "core/globals.hpp"

namespace big {

	/* Return types of this hook:
	
	case 1:
		LOG(INFO) << "Player is not in our roaming bubble";
		break;
	case 2:
		LOG(INFO) << "Wrong owner";
		break;
	case 4:
		LOG(INFO) << "Can't apply data - no network object";
		break;
	case 6:
		LOG(INFO) << "Can't apply data - no game object";
		break;
	case 7:
		LOG(INFO) << "Can't apply data - network closed";
		break;
	case 8:
		LOG(INFO) << "Succesfull sync";
		break;
	*/
	

	signed __int64 hooks::received_clone_sync(CNetworkObjectMgr* mgr,
		CNetGamePlayer* src,
		CNetGamePlayer* dst,
		unsigned __int16 sync_type,
		unsigned __int16 obj_id,
		rage::datBitBuffer* buffer,
		unsigned __int16 a7,
		unsigned int timestamp) {

		auto sync_tree = g_pointers->m_get_sync_tree_for_type(mgr, sync_type);
		auto tree_name = g_pointers->m_get_sync_type_info(sync_type, 0);
		auto net_obj = g_pointers->m_get_net_object(mgr, obj_id, true);
		bool invalidsync = false;

		if(!net_obj) net_obj = g_pointers->m_get_net_object_for_player(mgr, obj_id, src, true);

		if (!net_obj) return 2;

		if (!sync_tree || sync_type < 0 || sync_type > 14) invalidsync = true;

		if (net_obj->m_object_type != sync_type) invalidsync = true;

		//TO BE ADDED
		//Node specific entity type checks


		if (invalidsync) {

			if (g->notifications.invalid_sync.log) LOG(WARNING) << "Invalid sync: " << "Type: " << sync_type << " Tree name: " << tree_name << " From: " << src->get_name();
			if (g->notifications.invalid_sync.notify) g_notification_service->push_warning("Invalid sync " + std::string(src->get_name()), "Type: " + std::to_string(sync_type) + "\nType name: " + tree_name);

			return 2;
		}

		auto result = g_hooking->m_received_clone_sync_hook.get_original<decltype(&received_clone_sync)>()(mgr, src, dst, sync_type, obj_id, buffer, a7, timestamp);

		return result;

	}

}