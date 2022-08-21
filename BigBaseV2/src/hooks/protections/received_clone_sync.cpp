#include "hooking.hpp"
#include "core/globals.hpp"
#include "base/CObject.hpp"
#include "rage/fwEntity.hpp"
#include "rage/netSyncDataNodeBase.hpp"
#include "rage/netSyncTree.hpp"
#include "gta/net_object_mgr.hpp"
#include "datanodes/CDoorCreationDataNode.hpp"
#include "datanodes/CObjectCreationDataNode.hpp"
#include "datanodes/CPedAttachDataNode.hpp"
#include "datanodes/CPedCreationDataNode.hpp"
#include "datanodes/CPickupCreationDataNode.hpp"
#include "datanodes/CPhysicalAttachDataNode.hpp"
#include "datanodes/CPlayerAppearanceDataNode.hpp"
#include "datanodes/CSectorDataNode.hpp"
#include "datanodes/CTrainGameStateDataNode.hpp"
#include "datanodes/CVehicleCreationDataNode.hpp"
#include "network/netObject.hpp"
#include "natives.hpp"

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

	uint32_t crash_models[] = { RAGE_JOAAT("prop_dummy_01"), RAGE_JOAAT("prop_dummy_car"), RAGE_JOAAT("prop_dummy_light"), RAGE_JOAAT("prop_dummy_plane"), RAGE_JOAAT("slod_human"),
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

	uint32_t cage_models[] = { RAGE_JOAAT("prop_rub_cage01a"), RAGE_JOAAT("prop_fnclink_05crnr1"), RAGE_JOAAT("prop_gold_cont_01"), RAGE_JOAAT("prop_feeder1"), RAGE_JOAAT("stt_prop_stunt_tube_s"),
		RAGE_JOAAT("prop_feeder1_cr"), RAGE_JOAAT("p_cablecar_s") };

	inline bool is_model_a_crash_model(uint32_t model) {
		for (int i = 0; i < sizeof(crash_models) / sizeof(uint32_t); i++)
		{
			if (crash_models[i] == model) return true;
		}
		return false;
	}

	inline bool is_model_a_cage_model(uint32_t model) {
		for (int i = 0; i < sizeof(cage_models) / sizeof(uint32_t); i++)
		{
			if (cage_models[i] == model) return true;
		}
		return false;
	}
	
	CPhysicalAttachDataNode* get_attach_node_from_object(rage::netSyncNodeBase* node)
	{
		if (node->IsParentNode())
		{
			for (auto child = node->m_first_child; child; child = child->m_next_sibling) {
				CPhysicalAttachDataNode* attach_node = get_attach_node_from_object(child);
				if(attach_node != nullptr)
					return attach_node;
			}
		}
		else if (node->IsDataNode())
		{
			if (typeid(*node).hash_code() == 0xE6B80DD4C167CFF) //CPhysicalAttachDataNode
				return dynamic_cast<CPhysicalAttachDataNode*>(node);
		}
		return nullptr;
	}

	bool is_attachment_infinite(CPhysicalAttachDataNode* node, uint16_t object_id) {
		if (rage::netObject* attached_object = (*g_pointers->m_network_object_mgr)->find_object_by_id(node->m_attached_to, false); attached_object)
		{
			if (rage::netSyncTree* tree = attached_object->GetSyncTree(); tree)
			{
				if (rage::netSyncNodeBase* base_node = tree->m_sync_node; base_node) {

					CPhysicalAttachDataNode* attached_attach_node = get_attach_node_from_object(base_node);
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

	bool check_node(rage::netSyncNodeBase* node, CNetGamePlayer* sender, uint16_t object_id)
	{
		if (node->IsParentNode())
		{
			bool block = false;
			for (auto child = node->m_first_child; child; child = child->m_next_sibling) {
				if (check_node(child, sender, object_id))
					block = true;
			}
			return block;
		}
		else if (node->IsDataNode())
		{
			//LOG(INFO) << typeid(*node).name() << ": " << HEX_TO_UPPER(typeid(*node).hash_code()); //Use this to get hashes for each node
			switch (typeid(*node).hash_code()) {
				case 0x53564E6A8BA84671: //CDoorCreationDataNode
				{
					CDoorCreationDataNode* creation_node = dynamic_cast<CDoorCreationDataNode*>(node);
					if (is_model_a_crash_model(creation_node->m_model))
					{
						if (g->notifications.invalid_sync.log)
							LOG(WARNING) << "Invalid door model: " << "Model: " << HEX_TO_UPPER(creation_node->m_model) << " From : " << sender->get_name();
						if (g->notifications.invalid_sync.notify)
							g_notification_service->push_warning(fmt::format("Invalid door model from {}", sender->get_name()), fmt::format("Model: 0x{:x}", creation_node->m_model));
						return true;
					}
					break;
				}
				case 0xF01A0C93246DF2F0: //CPickupCreationDataNode
				{
					CPickupCreationDataNode* creation_node = dynamic_cast<CPickupCreationDataNode*>(node);
					if (is_model_a_crash_model(creation_node->m_custom_model))
					{
						if (g->notifications.invalid_sync.log)
							LOG(WARNING) << "Invalid pickup model: " << "Model: " << HEX_TO_UPPER(creation_node->m_custom_model) << " From : " << sender->get_name();
						if (g->notifications.invalid_sync.notify)
							g_notification_service->push_warning(fmt::format("Invalid pickup model from {}", sender->get_name()), fmt::format("Model: 0x{:x}", creation_node->m_custom_model));
						return true;
					}
					break;
				}
				case 0xE6B80DD4C167CFF: //CPhysicalAttachDataNode
				{
					CPhysicalAttachDataNode* attach_node = dynamic_cast<CPhysicalAttachDataNode*>(node);
					if (attach_node->m_attached && attach_node->m_attached_to == object_id)
					{
						if (g->notifications.invalid_sync.log)
							LOG(WARNING) << "Infinite attachment: " << "Node: " << typeid(*node).name() << " From : " << sender->get_name();
						if (g->notifications.invalid_sync.notify)
							g_notification_service->push_warning(fmt::format("Infinite attachment from {}", sender->get_name()), fmt::format("Node: {}", typeid(*node).name()));
						return true;
					}
					else if (attach_node->m_attached)
					{
						if (is_attachment_infinite(attach_node, object_id))
						{
							if (g->notifications.invalid_sync.log)
								LOG(WARNING) << "Infinite attachment v2: " << "Node: " << typeid(*node).name() << " From : " << sender->get_name();
							if (g->notifications.invalid_sync.notify)
								g_notification_service->push_warning(fmt::format("Infinite attachment v2 from {}", sender->get_name()), fmt::format("Node: {}", typeid(*node).name()));
							return true;
						}
					}
					break;
				}
				case 0x2AEC964801142EA: //CPedCreationDataNode
				{
					CPedCreationDataNode* creation_node = dynamic_cast<CPedCreationDataNode*>(node);
					if (is_model_a_crash_model(creation_node->m_model))
					{
						if (g->notifications.invalid_sync.log)
							LOG(WARNING) << "Invalid ped model: " << "Model: " << HEX_TO_UPPER(creation_node->m_model) << " From : " << sender->get_name();
						if (g->notifications.invalid_sync.notify)
							g_notification_service->push_warning(fmt::format("Invalid ped model from {}", sender->get_name()), fmt::format("Model: 0x{:x}", creation_node->m_model));
						return true;
					}
					else if (creation_node->m_has_prop && is_model_a_crash_model(creation_node->m_prop_model)) {
						if (g->notifications.invalid_sync.log)
							LOG(WARNING) << "Invalid ped prop model: " << "Model: " << HEX_TO_UPPER(creation_node->m_prop_model) << " From : " << sender->get_name();
						if (g->notifications.invalid_sync.notify)
							g_notification_service->push_warning(fmt::format("Invalid ped prop model from {}", sender->get_name()), fmt::format("Model: 0x{:x}", creation_node->m_prop_model));
						return true;
					}
					break;
				}
				case 0xD3A0FBD0D1CFD23A: //CPedAttachDataNode
				{
					CPedAttachDataNode* attach_node = dynamic_cast<CPedAttachDataNode*>(node);
					if (attach_node->m_attached && attach_node->m_attached_to == object_id)
					{
						if (g->notifications.invalid_sync.log)
							LOG(WARNING) << "Infinite ped attachment: " << "Node: " << typeid(*node).name() << " From : " << sender->get_name();
						if (g->notifications.invalid_sync.notify)
							g_notification_service->push_warning(fmt::format("Infinite ped attachment from {}", sender->get_name()), fmt::format("Node: {}", typeid(*node).name()));
						return true;
					}
					break;
				}
				case 0xDAAA9ED23C818699: //CVehicleCreationDataNode
				{
					CVehicleCreationDataNode* vehicle_creation_node = dynamic_cast<CVehicleCreationDataNode*>(node);
					if (is_model_a_crash_model(vehicle_creation_node->m_model)) {
						if (g->notifications.invalid_sync.log)
							LOG(WARNING) << "Invalid vehicle model: " << "Model: " << HEX_TO_UPPER(vehicle_creation_node->m_model) << " From : " << sender->get_name();
						if (g->notifications.invalid_sync.notify)
							g_notification_service->push_warning(fmt::format("Invalid vehicle model from {}", sender->get_name()), fmt::format("Model: 0x{:x}", vehicle_creation_node->m_model));
						return true;
					}
					break;
				}
				case 0xC3E47C3C3507E5A4: //CObjectCreationDataNode
				{
					CObjectCreationDataNode* creation_node = dynamic_cast<CObjectCreationDataNode*>(node);
					if (is_model_a_crash_model(creation_node->m_model)) {
						if (g->notifications.invalid_sync.log)
							LOG(WARNING) << "Invalid object model: " << "Model: " << HEX_TO_UPPER(creation_node->m_model) << " From : " << sender->get_name();
						if (g->notifications.invalid_sync.notify)
							g_notification_service->push_warning(fmt::format("Invalid object model from {}", sender->get_name()), fmt::format("Model: 0x{:x}", creation_node->m_model));
					}
					else if (is_model_a_cage_model(creation_node->m_model)) {
						if (g->notifications.invalid_sync.log)
							LOG(WARNING) << "Cage model: " << "Model: " << HEX_TO_UPPER(creation_node->m_model) << " From : " << sender->get_name();
						if (g->notifications.invalid_sync.notify)
							g_notification_service->push_warning(fmt::format("Cage model from {}", sender->get_name()), fmt::format("Model: 0x{:x}", creation_node->m_model));
					}
					break;
				}
				case 0x2AEE7E3A2D2E84FF: //CPlayerAppearanceDataNode
				{
					CPlayerAppearanceDataNode* player_appearance_node = dynamic_cast<CPlayerAppearanceDataNode*>(node);
					if (is_model_a_crash_model(player_appearance_node->m_model_hash)) {
						if (g->notifications.invalid_sync.log)
							LOG(WARNING) << "Invalid player model: " << "Model: " << HEX_TO_UPPER(player_appearance_node->m_model_hash) << " From : " << sender->get_name();
						if (g->notifications.invalid_sync.notify)
							g_notification_service->push_warning(fmt::format("Invalid player model from {}", sender->get_name()), fmt::format("Model: 0x{:x}", player_appearance_node->m_model_hash));
						return true;
					}
					break;
				}
				case 0x38335CCD1B62BF09: //CSectorDataNode
				{
					CSectorDataNode* sector_node = dynamic_cast<CSectorDataNode*>(node);
					if (sector_node->m_pos_x == 712 || sector_node->m_pos_y == 712 || sector_node->m_pos_z == 712)
					{
						if (g->notifications.invalid_sync.log)
							LOG(WARNING) << "Invalid sector position." << " From : " << sender->get_name();
						if (g->notifications.invalid_sync.notify)
							g_notification_service->push_warning(fmt::format("Invalid sector position from {}", sender->get_name()), "Invalid sector position.");
						return true;
					}
				}
			}
		}
		return false;
	}

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

				if (sync_type < eObjType::carObjType || sync_type > eObjType::unkObjType14)
				{
					if (g->notifications.out_of_allowed_range_sync_type.log)
						LOG(WARNING) << "Out of Bounds sync: " << "Type: " << sync_type << " Tree name: " << tree_name << " From: " << src->get_name();
					if (g->notifications.out_of_allowed_range_sync_type.notify)
						g_notification_service->push_warning(fmt::format("Out Of Bounds Sync Type from {}", src->get_name()), fmt::format("Type {} in sync tree {}", sync_type, tree_name));
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
						else if (model_info->m_model_type != get_model_data(model_info->m_model_hash)->m_model_type)
						{
							return 2;
						}
						else if ((sync_type >= eObjType::bikeObjType && sync_type <= eObjType::heliObjType) || (sync_type >= eObjType::planeObjType && sync_type <= eObjType::submarineObjType) || (sync_type >= eObjType::trailerObjType && sync_type <= eObjType::trainObjType))
						{
							if(reinterpret_cast<CVehicleModelInfo*>(model_info)->m_vehicle_type != get_model_data(model_info->m_model_hash)->m_vehicle_type)
								return 2;
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
						return 6;
				}
			}

		}
		return g_hooking->m_received_clone_sync_hook.get_original<decltype(&received_clone_sync)>()(mgr, src, dst, sync_type, obj_id, buffer, unk, timestamp);

	}

}