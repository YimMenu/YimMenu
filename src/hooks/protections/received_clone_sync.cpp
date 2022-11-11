#include "hooking.hpp"
#include "core/globals.hpp"
#include "base/CObject.hpp"
#include "entities/fwEntity.hpp"
#include "rage/netSyncDataNodeBase.hpp"
#include "rage/netSyncTree.hpp"
#include "gta/net_object_mgr.hpp"
#include "datanodes/door/CDoorCreationDataNode.hpp"
#include "datanodes/object/CObjectCreationDataNode.hpp"
#include "datanodes/ped/CPedAttachDataNode.hpp"
#include "datanodes/ped/CPedCreationDataNode.hpp"
#include "datanodes/pickup/CPickupCreationDataNode.hpp"
#include "datanodes/physical/CPhysicalAttachDataNode.hpp"
#include "datanodes/player/CPlayerAppearanceDataNode.hpp"
#include "datanodes/proximity_migrateable/CSectorDataNode.hpp"
#include "datanodes/train/CTrainGameStateDataNode.hpp"
#include "datanodes/vehicle/CVehicleCreationDataNode.hpp"
#include "network/netObject.hpp"
#include "natives.hpp"
#include "base/CBaseModelInfo.hpp"
#include "vehicle/CVehicleModelInfo.hpp"
#include "util/model_info.hpp"
#define CLASS_TO_MANGLED_NAME(c) "?AV"#c"@@"

namespace big
{
	constexpr uint64_t operator ""_fnv1a(char const* str, std::size_t len)
	{
		auto const fnv_offset_basis = 14695981039346656037ULL;
		auto const fnv_prime = 1099511628211ULL;

		auto value = fnv_offset_basis;
		for (auto i = 0; i < len; i++) {
			value ^= static_cast<size_t>(str[i]);
			value *= fnv_prime;
		}
		value ^= value >> 32;

		return value;
	}

	constexpr uint32_t crash_models[] = { RAGE_JOAAT("prop_dummy_01"), RAGE_JOAAT("prop_dummy_car"), RAGE_JOAAT("prop_dummy_light"), RAGE_JOAAT("prop_dummy_plane"), RAGE_JOAAT("slod_human"),
		RAGE_JOAAT("slod_small_quadped"), RAGE_JOAAT("slod_large_quadped"), RAGE_JOAAT("prop_distantcar_night"), RAGE_JOAAT("prop_distantcar_day"), RAGE_JOAAT("hei_bh1_08_details4_em_night"),
		RAGE_JOAAT("dt1_18_sq_night_slod"), RAGE_JOAAT("ss1_12_night_slod"), -1288391198, RAGE_JOAAT("h4_prop_bush_bgnvla_med_01"), RAGE_JOAAT("h4_prop_bush_bgnvla_lrg_01"),
		RAGE_JOAAT("h4_prop_bush_buddleia_low_01"), RAGE_JOAAT("h4_prop_bush_ear_aa"), RAGE_JOAAT("h4_prop_bush_ear_ab"), RAGE_JOAAT("h4_prop_bush_fern_low_01"),
		RAGE_JOAAT("h4_prop_bush_fern_tall_cc"), RAGE_JOAAT("h4_prop_bush_mang_ad"), RAGE_JOAAT("h4_prop_bush_mang_low_aa"), RAGE_JOAAT("h4_prop_bush_mang_low_ab"),
		RAGE_JOAAT("h4_prop_bush_seagrape_low_01"), RAGE_JOAAT("prop_h4_ground_cover"), RAGE_JOAAT("h4_prop_weed_groundcover_01"), RAGE_JOAAT("h4_prop_grass_med_01"),
		RAGE_JOAAT("h4_prop_grass_tropical_lush_01"), RAGE_JOAAT("h4_prop_grass_wiregrass_01"), RAGE_JOAAT("h4_prop_weed_01_plant"), RAGE_JOAAT("h4_prop_weed_01_row"),
		RAGE_JOAAT("urbanweeds02_l1"), RAGE_JOAAT("proc_forest_grass01"), RAGE_JOAAT("prop_small_bushyba"), RAGE_JOAAT("arbitergt"), RAGE_JOAAT("astron2"), RAGE_JOAAT("cyclone2"),
		RAGE_JOAAT("ignus2"), RAGE_JOAAT("s95"), RAGE_JOAAT("hc_gunman"), RAGE_JOAAT("v_res_d_dildo_a"), RAGE_JOAAT("v_res_d_dildo_b"), RAGE_JOAAT("v_res_d_dildo_c"),
		RAGE_JOAAT("v_res_d_dildo_d"), RAGE_JOAAT("v_res_d_dildo_e"), RAGE_JOAAT("v_res_d_dildo_f"), RAGE_JOAAT("v_res_skateboard"), RAGE_JOAAT("prop_battery_01"), RAGE_JOAAT("prop_barbell_01"),
		RAGE_JOAAT("prop_barbell_02"), RAGE_JOAAT("prop_bandsaw_01"), RAGE_JOAAT("prop_bbq_3"), RAGE_JOAAT("v_med_curtainsnewcloth2"), RAGE_JOAAT("bh1_07_flagpoles"),
		92962485, RAGE_JOAAT("ig_wade") };

	constexpr uint32_t cage_models[] = { RAGE_JOAAT("prop_rub_cage01a"), RAGE_JOAAT("prop_fnclink_05crnr1"), RAGE_JOAAT("prop_gold_cont_01"), RAGE_JOAAT("prop_gold_cont_01b"),
		RAGE_JOAAT("prop_feeder1"), RAGE_JOAAT("stt_prop_stunt_tube_s"), RAGE_JOAAT("prop_feeder1_cr"), RAGE_JOAAT("p_cablecar_s") };

	inline bool is_model_a_crash_model(uint32_t model) {
		for (auto iterator : crash_models)
		{
			if (iterator == model) return true;
		}
		return false;
	}

	inline bool is_model_a_cage_model(uint32_t model) {
		for (auto iterator : cage_models)
		{
			if (iterator == model) return true;
		}
		return false;
	}

	template<typename T>
	T* get_node_from_object(rage::netSyncNodeBase* node)
	{
		constexpr uint64_t hash = CLASS_TO_MANGLED_NAME(T)""_fnv1a;
		if (node->IsParentNode())
		{
			for (auto child = node->m_first_child; child; child = child->m_next_sibling) {
				T* attach_node = get_node_from_object<T>(child);
				if (attach_node != nullptr)
					return attach_node;
			}
		}
		else if (node->IsDataNode())
		{
			if (typeid(*node).hash_code() == hash)
				return dynamic_cast<T*>(node);
		}
		return nullptr;
	}

	bool is_attachment_infinite(CPhysicalAttachDataNode* node, uint16_t object_id) {
		if (rage::netObject* attached_object = (*g_pointers->m_network_object_mgr)->find_object_by_id(node->m_attached_to, false); attached_object)
		{
			if (rage::netSyncTree* tree = attached_object->GetSyncTree(); tree)
			{
				if (rage::netSyncNodeBase* base_node = tree->m_sync_node; base_node) {
					const auto attached_attach_node = get_node_from_object<CPhysicalAttachDataNode>(base_node);
					if (attached_attach_node && attached_attach_node->m_attached)
					{
						if (attached_attach_node->m_attached_to == object_id) {
							return true;
						}
						else {
							return is_attachment_infinite(attached_attach_node, object_id);
						}
					}
				}
			}
		}

		return false;
	}

	bool is_ped_attachment_infinite(CPedAttachDataNode* node, uint16_t object_id) {
		if (rage::netObject* attached_object = (*g_pointers->m_network_object_mgr)->find_object_by_id(node->m_attached_to, false); attached_object)
		{
			if (rage::netSyncTree* tree = attached_object->GetSyncTree(); tree)
			{
				if (rage::netSyncNodeBase* base_node = tree->m_sync_node; base_node) {
					const auto attached_attach_node = get_node_from_object<CPedAttachDataNode>(base_node);
					if (attached_attach_node && attached_attach_node->m_attached)
					{
						if (attached_attach_node->m_attached_to == object_id) {
							return true;
						}
						else {
							return is_ped_attachment_infinite(attached_attach_node, object_id);
						}
					}
				}
			}
		}

		return false;
	}

	bool check_node(rage::netSyncNodeBase* node, CNetGamePlayer* sender, uint16_t object_id)
	{
		if (node->IsParentNode())
		{
			for (auto child = node->m_first_child; child; child = child->m_next_sibling) {
				if (check_node(child, sender, object_id))
					return true;
			}
		}
		else if (node->IsDataNode())
		{
			//LOG(INFO) << typeid(*node).name() << ": " << HEX_TO_UPPER(typeid(*node).hash_code()); //Use this to get hashes for each node
			switch (typeid(*node).hash_code()) {
				case "?AVCDoorCreationDataNode@@"_fnv1a: //CDoorCreationDataNode
				{
					const auto creation_node = dynamic_cast<CDoorCreationDataNode*>(node);
					if (is_model_a_crash_model(creation_node->m_model))
					{
						if (g->notifications.invalid_sync.log)
							LOG(WARNING) << "Invalid door model: " << "Model: " << HEX_TO_UPPER(creation_node->m_model) << " From: " << sender->get_name();
						if (g->notifications.invalid_sync.notify)
							g_notification_service->push_warning(std::format("Invalid door model from {}", sender->get_name()), std::format("Model: 0x{:x}", creation_node->m_model));
						return true;
					}
					break;
				}
				case "?AVCPickupCreationDataNode@@"_fnv1a: //CPickupCreationDataNode
				{
					const auto creation_node = dynamic_cast<CPickupCreationDataNode*>(node);
					if (is_model_a_crash_model(creation_node->m_custom_model))
					{
						if (g->notifications.invalid_sync.log)
							LOG(WARNING) << "Invalid pickup model: " << "Model: " << HEX_TO_UPPER(creation_node->m_custom_model) << " From : " << sender->get_name();
						if (g->notifications.invalid_sync.notify)
							g_notification_service->push_warning(std::format("Invalid pickup model from {}", sender->get_name()), std::format("Model: 0x{:x}", creation_node->m_custom_model));
						return true;
					}
					break;
				}
				case "?AVCPhysicalAttachDataNode@@"_fnv1a: //CPhysicalAttachDataNode
				{
					const auto attach_node = dynamic_cast<CPhysicalAttachDataNode*>(node);
					if (attach_node->m_attached && attach_node->m_attached_to == object_id)
					{
						if (g->notifications.invalid_sync.log)
							LOG(WARNING) << "Infinite attachment: " << "Node: " << typeid(*node).name() << " From : " << sender->get_name();
						if (g->notifications.invalid_sync.notify)
							g_notification_service->push_warning(std::format("Infinite attachment from {}", sender->get_name()), std::format("Node: {}", typeid(*node).name()));
						return true;
					}
					else if (attach_node->m_attached && is_attachment_infinite(attach_node, object_id))
					{
						if (g->notifications.invalid_sync.log)
							LOG(WARNING) << "Infinite attachment v2: " << "Node: " << typeid(*node).name() << " From : " << sender->get_name();
						if (g->notifications.invalid_sync.notify)
							g_notification_service->push_warning(std::format("Infinite attachment v2 from {}", sender->get_name()), std::format("Node: {}", typeid(*node).name()));
						return true;
					}
					break;
				}
				case "?AVCPedCreationDataNode@@"_fnv1a: //CPedCreationDataNode
				{
					const auto creation_node = dynamic_cast<CPedCreationDataNode*>(node);
					if (is_model_a_crash_model(creation_node->m_model))
					{
						if (g->notifications.invalid_sync.log)
							LOG(WARNING) << "Invalid ped model: " << "Model: " << HEX_TO_UPPER(creation_node->m_model) << " From : " << sender->get_name();
						if (g->notifications.invalid_sync.notify)
							g_notification_service->push_warning(std::format("Invalid ped model from {}", sender->get_name()), std::format("Model: 0x{:x}", creation_node->m_model));
						return true;
					}
					else if (creation_node->m_has_prop && is_model_a_crash_model(creation_node->m_prop_model)) {
						if (g->notifications.invalid_sync.log)
							LOG(WARNING) << "Invalid ped prop model: " << "Model: " << HEX_TO_UPPER(creation_node->m_prop_model) << " From : " << sender->get_name();
						if (g->notifications.invalid_sync.notify)
							g_notification_service->push_warning(std::format("Invalid ped prop model from {}", sender->get_name()), std::format("Model: 0x{:x}", creation_node->m_prop_model));
						return true;
					}
					break;
				}
				case "?AVCPedAttachDataNode@@"_fnv1a: //CPedAttachDataNode
				{
					const auto attach_node = dynamic_cast<CPedAttachDataNode*>(node);
					if (attach_node->m_attached && attach_node->m_attached_to == object_id)
					{
						if (g->notifications.invalid_sync.log)
							LOG(WARNING) << "Infinite ped attachment: " << "Node: " << typeid(*node).name() << " From : " << sender->get_name();
						if (g->notifications.invalid_sync.notify)
							g_notification_service->push_warning(std::format("Infinite ped attachment from {}", sender->get_name()), std::format("Node: {}", typeid(*node).name()));
						return true;
					}
					else if (attach_node->m_attached && is_ped_attachment_infinite(attach_node, object_id))
					{
						if (g->notifications.invalid_sync.log)
							LOG(WARNING) << "Infinite ped attachment v2: " << "Node: " << typeid(*node).name() << " From : " << sender->get_name();
						if (g->notifications.invalid_sync.notify)
							g_notification_service->push_warning(std::format("Infinite ped attachment v2 from {}", sender->get_name()), std::format("Node: {}", typeid(*node).name()));
						return true;
					}
					break;
				}
				case "?AVCVehicleCreationDataNode@@"_fnv1a: //CVehicleCreationDataNode
				{
					const auto vehicle_creation_node = dynamic_cast<CVehicleCreationDataNode*>(node);
					if (is_model_a_crash_model(vehicle_creation_node->m_model)) {
						if (g->notifications.invalid_sync.log)
							LOG(WARNING) << "Invalid vehicle model: " << "Model: " << HEX_TO_UPPER(vehicle_creation_node->m_model) << " From : " << sender->get_name();
						if (g->notifications.invalid_sync.notify)
							g_notification_service->push_warning(std::format("Invalid vehicle model from {}", sender->get_name()), std::format("Model: 0x{:x}", vehicle_creation_node->m_model));
						return true;
					}
					break;
				}
				case "?AVCObjectCreationDataNode@@"_fnv1a: //CObjectCreationDataNode
				{
					const auto creation_node = dynamic_cast<CObjectCreationDataNode*>(node);
					if (is_model_a_crash_model(creation_node->m_model)) {
						if (g->notifications.invalid_sync.log)
							LOG(WARNING) << "Invalid object model: " << "Model: " << HEX_TO_UPPER(creation_node->m_model) << " From : " << sender->get_name();
						if (g->notifications.invalid_sync.notify)
							g_notification_service->push_warning(std::format("Invalid object model from {}", sender->get_name()), std::format("Model: 0x{:x}", creation_node->m_model));
						return true;
					}
					else if (is_model_a_cage_model(creation_node->m_model)) {
						if (g->notifications.invalid_sync.log)
							LOG(WARNING) << "Cage model: " << "Model: " << HEX_TO_UPPER(creation_node->m_model) << " From : " << sender->get_name();
						if (g->notifications.invalid_sync.notify)
							g_notification_service->push_warning(std::format("Cage model from {}", sender->get_name()), std::format("Model: 0x{:x}", creation_node->m_model));
						return true;
					}
					break;
				}
				case "?AVCPlayerAppearanceDataNode@@"_fnv1a: //CPlayerAppearanceDataNode
				{
					const auto player_appearance_node = dynamic_cast<CPlayerAppearanceDataNode*>(node);
					if (is_model_a_crash_model(player_appearance_node->m_model_hash)) {
						if (g->notifications.invalid_sync.log)
							LOG(WARNING) << "Invalid player model: " << "Model: " << HEX_TO_UPPER(player_appearance_node->m_model_hash) << " From : " << sender->get_name();
						if (g->notifications.invalid_sync.notify)
							g_notification_service->push_warning(std::format("Invalid player model from {}", sender->get_name()), std::format("Model: 0x{:x}", player_appearance_node->m_model_hash));
						return true;
					}
					break;
				}
				case "?AVCSectorDataNode@@"_fnv1a: //CSectorDataNode
				{
					const auto sector_node = dynamic_cast<CSectorDataNode*>(node);
					if (sector_node->m_pos_x == 712 || sector_node->m_pos_y == 712 || sector_node->m_pos_z == 712)
					{
						if (g->notifications.invalid_sync.log)
							LOG(WARNING) << "Invalid sector position." << " From : " << sender->get_name();
						if (g->notifications.invalid_sync.notify)
							g_notification_service->push_warning(std::format("Invalid sector position from {}", sender->get_name()), "Invalid sector position.");
						return true;
					}
					break;
				}
			}
		}
		return false;
	}

	int64_t hooks::received_clone_sync(CNetworkObjectMgr* mgr, CNetGamePlayer* src, CNetGamePlayer* dst, eObjType sync_type, uint16_t obj_id, rage::datBitBuffer* buffer, uint16_t unk, uint32_t timestamp) {
		if (auto sync_tree = g_pointers->m_get_sync_tree_for_type(mgr, sync_type); sync_tree && *g_pointers->m_is_session_started)
		{
			if (auto net_obj = g_pointers->m_get_net_object(mgr, obj_id, true); net_obj)
			{
				auto tree_name = g_pointers->m_get_sync_type_info(sync_type, 0);

				if (sync_type < eObjType::carObjType || sync_type > eObjType::unkObjType14)
				{
					if (g->notifications.out_of_allowed_range_sync_type.log)
						LOG(WARNING) << "Out of Bounds sync: " << "Type: " << sync_type << " Tree name: " << tree_name << " From: " << src->get_name();
					if (g->notifications.out_of_allowed_range_sync_type.notify)
						g_notification_service->push_warning(std::format("Out Of Allowed Sync Range from {}", src->get_name()), std::format("Type {} in sync tree {}", std::uint16_t(sync_type), tree_name));
				}
				else if (net_obj->m_object_type != sync_type)
				{
					if (g->notifications.mismatch_sync_type.log)
						LOG(WARNING) << "Mismatch sync: " << "Type: " << sync_type << " Tree name: " << tree_name << " From: " << src->get_name();
					if (g->notifications.mismatch_sync_type.notify)
						g_notification_service->push_warning(std::format("Mismatch Sync from {}", src->get_name()), std::format("Type {} in sync tree {}", std::uint16_t(sync_type), tree_name));

					return eSyncReply::WrongOwner;
				}
				else if (auto game_obj = net_obj->GetGameObject(); game_obj)
				{
					if (auto model_info = game_obj->m_model_info)
					{
						const auto model = model_info::get_model(model_info->m_hash);
						if (!model || model_info->m_model_type != model->m_model_type)
						{
							return eSyncReply::WrongOwner;
						}

						if (model->m_model_type == eModelType::Vehicle &&
							reinterpret_cast<CVehicleModelInfo*>(model_info)->m_vehicle_type != reinterpret_cast<CVehicleModelInfo*>(model)->m_vehicle_type)
						{
							return eSyncReply::WrongOwner;
						}
						else if ((sync_type >= eObjType::bikeObjType && sync_type <= eObjType::heliObjType) || (sync_type >= eObjType::planeObjType && sync_type <= eObjType::submarineObjType) || (sync_type >= eObjType::trailerObjType && sync_type <= eObjType::trainObjType))
						{
							if(reinterpret_cast<CVehicleModelInfo*>(model_info)->m_vehicle_type != model_info::get_vehicle_model(model_info->m_hash)->m_vehicle_type)
								return eSyncReply::WrongOwner;
						}
					}
				}

				uint32_t pos = buffer->m_bitsRead;
				g_pointers->m_read_bitbuffer_into_sync_tree(sync_tree, 2, 0, buffer, 0);
				buffer->Seek(pos);

				//LOG(INFO) << typeid(*tree).name() << ": " << HEX_TO_UPPER(typeid(*tree).hash_code()); //Use this to get hashes for each tree

				if (sync_tree->m_child_node_count)
				{
					if (check_node(sync_tree->m_sync_node, src, obj_id))
						return eSyncReply::CantApplyData;
				}
			}
			else if (sync_type != eObjType::pedObjType) //We don't want to not sync a player, so we ensure it's not a ped
			{
				return eSyncReply::WrongOwner;
			}
		}
		return g_hooking->get_original<received_clone_sync>()(mgr, src, dst, sync_type, obj_id, buffer, unk, timestamp);
	}
}
