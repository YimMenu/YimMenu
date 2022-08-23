#include "hooking.hpp"
#include "core/globals.hpp"
#include "natives.hpp"
#include "network/netObject.hpp"
#include "rage/fwEntity.hpp"
#include "base/CObject.hpp"

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
	
	const CVehicleModelInfo* get_model_data(rage::joaat_t hash) {
		auto modelTble = g_pointers->m_model_table;
		for (auto i = modelTble->m_lookup_table[hash % modelTble->m_lookup_key]; i; i = i->m_next)
		{
			if (i->m_hash == hash)
			{
				if (const auto model = modelTble->m_data[i->m_idx]; model)
				{
					return reinterpret_cast<CVehicleModelInfo*>(model);
				}
			}
		}
		return nullptr;
	}
	int64_t hooks::received_clone_sync(CNetworkObjectMgr* mgr, CNetGamePlayer* src, CNetGamePlayer* dst, eObjType sync_type, uint16_t obj_id, rage::datBitBuffer* buffer, uint16_t unk, uint32_t timestamp) {
		if (auto sync_tree = g_pointers->m_get_sync_tree_for_type(mgr, sync_type); sync_tree && *g_pointers->m_is_session_started)
		{
			if (auto net_obj = g_pointers->m_get_net_object(mgr, obj_id, true); net_obj)
			{
				auto tree_name = g_pointers->m_get_sync_type_info(sync_type, 0);
				bool invalidsync = false;

				if (sync_type < eObjType::carObjType || sync_type > eObjType::unkObjType14)
				{
					if (g->notifications.out_of_allowed_range_sync_type.log)
						LOG(WARNING) << "Out of range sync: " << "Type: " << sync_type << " Tree name: " << tree_name << " From: " << src->get_name();
					if (g->notifications.out_of_allowed_range_sync_type.notify)
						g_notification_service->push_warning(fmt::format("Out Of Allowed Sync Range from {}", src->get_name()), fmt::format("Type {} in sync tree {}", sync_type, tree_name));
				}
				else if (net_obj->m_object_type != sync_type)
				{
					if (g->notifications.mismatch_sync_type.log)
						LOG(WARNING) << "Mismatch sync: " << "Type: " << sync_type << " Tree name: " << tree_name << " From: " << src->get_name();
					if (g->notifications.mismatch_sync_type.notify)
						g_notification_service->push_warning(fmt::format("Mismatch Sync from {}", src->get_name()), fmt::format("Type {} in sync tree {}", sync_type, tree_name));

					return 2;
				}
				else if (auto game_obj = net_obj->GetGameObject(); game_obj)
				{
					if (auto model_info = game_obj->m_model_info)
					{
						if (!STREAMING::IS_MODEL_VALID(model_info->m_model_hash))
						{
							return 2;
						}
						else if (reinterpret_cast<CVehicleModelInfo*>(model_info)->m_vehicle_type != get_model_data(model_info->m_model_hash)->m_vehicle_type)
						{
							return 2;
						}
						else if (model_info->m_model_type != get_model_data(model_info->m_model_hash)->m_model_type)
						{
							return 2;
						}
					}
				}
			}
			else if (sync_type != eObjType::pedObjType) //We don't want to not sync a player, so we ensure it's not a ped
			{
				return 2;
			}
		}
		return g_hooking->m_received_clone_sync_hook.get_original<decltype(&received_clone_sync)>()(mgr, src, dst, sync_type, obj_id, buffer, unk, timestamp);

	}

}