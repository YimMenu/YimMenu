#include "hooking.hpp"
#include "core/globals.hpp"
#include "network/netObject.hpp"
#include "base/CBaseModelInfo.hpp"
#include "vehicle/CVehicleModelInfo.hpp"
#include "base/CObject.hpp"
#include "util/model_info.hpp"

namespace big
{
	enum SyncResponse : int64_t
	{
		NoSyncTreeFound = 1, // No sync tree found
		PlayerIsNotInOurRoamingBubble = 1, // Player is not in our roaming bubble
		WrongOwner = 2, // Wrong owner
		ObjectIsBeingReassinged = 2, // Object is being reassigned
		CantApplyData_NoNetworkObject = 4, // Can't apply data - no network object
		CantApplyData = 6, // Can't apply data
		CantApplyData_NoGameObject = 6, // Can't apply data - no game object
		CantApplyData_NetworkClosed = 7, // Can't apply data - network closed
		SuccessfullSync = 8
	};
	
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
						g_notification_service->push_warning(std::format("Out Of Allowed Sync Range from {}", src->get_name()), std::format("Type {} in sync tree {}", std::uint16_t(sync_type), tree_name));
				}
				else if (net_obj->m_object_type != sync_type)
				{
					if (g->notifications.mismatch_sync_type.log)
						LOG(WARNING) << "Mismatch sync: " << "Type: " << sync_type << " Tree name: " << tree_name << " From: " << src->get_name();
					if (g->notifications.mismatch_sync_type.notify)
						g_notification_service->push_warning(std::format("Mismatch Sync from {}", src->get_name()), std::format("Type {} in sync tree {}", std::uint16_t(sync_type), tree_name));

					return SyncResponse::WrongOwner;
				}
				else if (auto game_obj = net_obj->GetGameObject(); game_obj)
				{
					if (auto model_info = game_obj->m_model_info)
					{
						const auto model = model_info::get_model(model_info->m_model_hash);
						if (!model || model_info->m_model_type != model->m_model_type)
						{
							return SyncResponse::WrongOwner;
						}

						if (model->m_model_type == eModelType::Vehicle &&
							reinterpret_cast<CVehicleModelInfo*>(model_info)->m_vehicle_type != reinterpret_cast<CVehicleModelInfo*>(model)->m_vehicle_type)
						{
							return SyncResponse::WrongOwner;
						}
					}
				}
			}
			else if (sync_type != eObjType::pedObjType) //We don't want to not sync a player, so we ensure it's not a ped
			{
				return SyncResponse::WrongOwner;
			}
		}
		return g_hooking->m_received_clone_sync_hook.get_original<decltype(&received_clone_sync)>()(mgr, src, dst, sync_type, obj_id, buffer, unk, timestamp);

	}

}