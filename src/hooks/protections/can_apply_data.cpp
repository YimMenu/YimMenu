#include "hooking.hpp"
#include "core/globals.hpp"
#include "base/CObject.hpp"
#include "entities/fwEntity.hpp"
#include "rage/netSyncDataNodeBase.hpp"
#include "rage/netSyncTree.hpp"
#include "gta/net_object_mgr.hpp"
#include "datanodes/door/CDoorCreationDataNode.hpp"
#include "datanodes/dynamic_entity/CDynamicEntityGameStateDataNode.hpp"
#include "datanodes/object/CObjectCreationDataNode.hpp"
#include "datanodes/ped/CPedAttachDataNode.hpp"
#include "datanodes/ped/CPedCreationDataNode.hpp"
#include "datanodes/ped/CPedInventoryDataNode.hpp"
#include "datanodes/pickup/CPickupCreationDataNode.hpp"
#include "datanodes/physical/CPhysicalAttachDataNode.hpp"
#include "datanodes/player/CPlayerAppearanceDataNode.hpp"
#include "datanodes/player/CPlayerGameStateDataNode.hpp"
#include "datanodes/proximity_migrateable/CSectorDataNode.hpp"
#include "datanodes/vehicle/CVehicleCreationDataNode.hpp"
#include "datanodes/vehicle/CVehicleGadgetDataNode.hpp"
#include "network/netObject.hpp"
#include "base/CBaseModelInfo.hpp"
#include "vehicle/CVehicleModelInfo.hpp"
#include "util/model_info.hpp"
#include "network/CNetGamePlayer.hpp"
#include "util/notify.hpp"
#define CLASS_TO_MANGLED_NAME(c) "?AV"#c"@@"

namespace big
{
	constexpr uint64_t operator ""_fnv1a(char const* str, std::size_t len)
	{
		auto const fnv_offset_basis = 14695981039346656037ULL;
		auto const fnv_prime = 1099511628211ULL;

		auto value = fnv_offset_basis;
		for (auto i = 0; i < len; i++)
		{
			value ^= static_cast<size_t>(str[i]);
			value *= fnv_prime;
		}
		value ^= value >> 32;

		return value;
	}

	constexpr uint32_t crash_peds[] = { RAGE_JOAAT("slod_human"), RAGE_JOAAT("slod_small_quadped"), RAGE_JOAAT("slod_large_quadped") };

	constexpr uint32_t crash_vehicles[] = { RAGE_JOAAT("arbitergt"), RAGE_JOAAT("astron2"), RAGE_JOAAT("cyclone2"), RAGE_JOAAT("ignus2"), RAGE_JOAAT("s95") };

	constexpr uint32_t crash_objects[] = { RAGE_JOAAT("prop_dummy_01"), RAGE_JOAAT("prop_dummy_car"), RAGE_JOAAT("prop_dummy_light"), RAGE_JOAAT("prop_dummy_plane"),
		RAGE_JOAAT("prop_distantcar_night"), RAGE_JOAAT("prop_distantcar_day"), RAGE_JOAAT("hei_bh1_08_details4_em_night"),
		RAGE_JOAAT("dt1_18_sq_night_slod"), RAGE_JOAAT("ss1_12_night_slod"), -1288391198, RAGE_JOAAT("h4_prop_bush_bgnvla_med_01"), RAGE_JOAAT("h4_prop_bush_bgnvla_lrg_01"),
		RAGE_JOAAT("h4_prop_bush_buddleia_low_01"), RAGE_JOAAT("h4_prop_bush_ear_aa"), RAGE_JOAAT("h4_prop_bush_ear_ab"), RAGE_JOAAT("h4_prop_bush_fern_low_01"),
		RAGE_JOAAT("h4_prop_bush_fern_tall_cc"), RAGE_JOAAT("h4_prop_bush_mang_ad"), RAGE_JOAAT("h4_prop_bush_mang_low_aa"), RAGE_JOAAT("h4_prop_bush_mang_low_ab"),
		RAGE_JOAAT("h4_prop_bush_seagrape_low_01"), RAGE_JOAAT("prop_h4_ground_cover"), RAGE_JOAAT("h4_prop_weed_groundcover_01"), RAGE_JOAAT("h4_prop_grass_med_01"),
		RAGE_JOAAT("h4_prop_grass_tropical_lush_01"), RAGE_JOAAT("h4_prop_grass_wiregrass_01"), RAGE_JOAAT("h4_prop_weed_01_plant"), RAGE_JOAAT("h4_prop_weed_01_row"),
		RAGE_JOAAT("urbanweeds02_l1"), RAGE_JOAAT("proc_forest_grass01"), RAGE_JOAAT("prop_small_bushyba"), RAGE_JOAAT("v_res_d_dildo_a"), RAGE_JOAAT("v_res_d_dildo_b"), RAGE_JOAAT("v_res_d_dildo_c"),
		RAGE_JOAAT("v_res_d_dildo_d"), RAGE_JOAAT("v_res_d_dildo_e"), RAGE_JOAAT("v_res_d_dildo_f"), RAGE_JOAAT("v_res_skateboard"), RAGE_JOAAT("prop_battery_01"), RAGE_JOAAT("prop_barbell_01"),
		RAGE_JOAAT("prop_barbell_02"), RAGE_JOAAT("prop_bandsaw_01"), RAGE_JOAAT("prop_bbq_3"), RAGE_JOAAT("v_med_curtainsnewcloth2"), RAGE_JOAAT("bh1_07_flagpoles"),
		92962485 };

	inline bool is_crash_ped(uint32_t model)
	{
		for (auto iterator : crash_peds)
			if (iterator == model) 
				return true;
		return false;
	}

	inline bool is_crash_vehicle(uint32_t model)
	{
		for (auto iterator : crash_vehicles)
			if (iterator == model)
				return true;
		return false;
	}

	inline bool is_crash_object(uint32_t model)
	{
		for (auto iterator : crash_objects)
			if (iterator == model)
				return true;
		return false;
	}

	template<typename T>
	T* get_node_from_object(rage::netSyncNodeBase* node)
	{
		constexpr uint64_t hash = CLASS_TO_MANGLED_NAME(T)""_fnv1a;
		if (node->IsParentNode())
		{
			for (auto child = node->m_first_child; child; child = child->m_next_sibling)
			{
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

	bool is_sync_fuzzer_crash(rage::netSyncNodeBase* node)
	{
		__try
		{
			// the ptr is neither null nor a node.
			if (node)
			{
				node->IsParentNode();
			}
		}
		__except (EXCEPTION_EXECUTE_HANDLER)
		{
			return true;
		}

		return false;
	}

	bool check_node(rage::netSyncNodeBase* node, CNetGamePlayer* sender, rage::netObject* object)
	{
		if (is_sync_fuzzer_crash(node))
		{
			return true;
		}

		if (node->IsParentNode())
		{
			for (auto child = node->m_first_child; child; child = child->m_next_sibling)
			{
				if (check_node(child, sender, object))
					return true;
			}
		}
		else if (node->IsDataNode())
		{
			switch (typeid(*node).hash_code())
			{
				case "?AVCDoorCreationDataNode@@"_fnv1a:
				{
					const auto creation_node = dynamic_cast<CDoorCreationDataNode*>(node);
					if (is_crash_object(creation_node->m_model))
					{
						notify::crash_blocked(sender, "invalid door model");
						return true;
					}
					break;
				}
				case "?AVCPickupCreationDataNode@@"_fnv1a:
				{
					const auto creation_node = dynamic_cast<CPickupCreationDataNode*>(node);
					if (is_crash_object(creation_node->m_custom_model))
					{
						notify::crash_blocked(sender, "invalid door model");
						return true;
					}
					break;
				}
				case "?AVCPhysicalAttachDataNode@@"_fnv1a:
				{
					const auto attach_node = dynamic_cast<CPhysicalAttachDataNode*>(node);

					// TODO: Find a better method to avoid false positives
					auto model_hash = object->GetGameObject() ? object->GetGameObject()->m_model_info->m_hash : 0;
					if (attach_node->m_attached && attach_node->m_attached_to == object->m_object_id && (model_hash != RAGE_JOAAT("hauler2") && model_hash != RAGE_JOAAT("phantom3")))
					{
						// notify::crash_blocked(sender, "infinite physical attachment");
						return true;
					}
					break;
				}
				case "?AVCPedCreationDataNode@@"_fnv1a:
				{
					const auto creation_node = dynamic_cast<CPedCreationDataNode*>(node);
					if (is_crash_ped(creation_node->m_model))
					{
						notify::crash_blocked(sender, "invalid ped model");
						return true;
					}
					else if (creation_node->m_has_prop && is_crash_object(creation_node->m_prop_model))
					{
						notify::crash_blocked(sender, "invalid ped prop model");
						return true;
					}
					break;
				}
				case "?AVCPedAttachDataNode@@"_fnv1a:
				{
					const auto attach_node = dynamic_cast<CPedAttachDataNode*>(node);
					if (attach_node->m_attached && attach_node->m_attached_to == object->m_object_id)
					{
						notify::crash_blocked(sender, "infinite ped attachment");
						return true;
					}
					break;
				}
				case "?AVCVehicleCreationDataNode@@"_fnv1a:
				{
					const auto vehicle_creation_node = dynamic_cast<CVehicleCreationDataNode*>(node);
					if (is_crash_vehicle(vehicle_creation_node->m_model))
					{
						notify::crash_blocked(sender, "invalid vehicle model");
						return true;
					}
					break;
				}
				case "?AVCObjectCreationDataNode@@"_fnv1a:
				{
					const auto creation_node = dynamic_cast<CObjectCreationDataNode*>(node);
					if (is_crash_object(creation_node->m_model))
					{
						notify::crash_blocked(sender, "invalid object model");
						return true;
					}
					break;
				}
				case "?AVCPlayerAppearanceDataNode@@"_fnv1a:
				{
					const auto player_appearance_node = dynamic_cast<CPlayerAppearanceDataNode*>(node);
					if (is_crash_ped(player_appearance_node->m_model_hash))
					{
						notify::crash_blocked(sender, "invalid player model");
						return true;
					}
					break;
				}
				case "?AVCPlayerGameStateDataNode@@"_fnv1a:
				{
					if(g->notifications.script_event_handler.spectate.notify)
					{
						const auto player_game_state_node = dynamic_cast<CPlayerGameStateDataNode*>(node);
						if (player_game_state_node->m_is_spectating &&
						 sender->m_player_info &&
						 sender->m_player_info->m_ped &&
						 sender->m_player_info->m_ped->m_net_object &&
						 sender->m_player_info->m_ped->m_net_object->m_object_id == object->m_object_id)
						{
							if (g_local_player && g_local_player->m_net_object && g_local_player->m_net_object->m_object_id == player_game_state_node->m_spectating_net_id)
							{
								g_notification_service->push("Spectating", std::format("{} is spectating you", sender->get_name()));
							}
							else
							{
								g_player_service->iterate([&](auto& player) 
								{ 
									if (player.second->get_ped() && player.second->get_ped()->m_net_object && player.second->get_ped()->m_net_object->m_object_id == player_game_state_node->m_spectating_net_id)
									{
										g_notification_service->push("Spectating", std::format("{} is spectating: {}", sender->get_name(), player.first));
									}
								});
							}
						}
					}
					break;
				}
				case "?AVCSectorDataNode@@"_fnv1a:
				{
					const auto sector_node = dynamic_cast<CSectorDataNode*>(node);
					if (sector_node->m_pos_x == 712 || sector_node->m_pos_y == 712 || sector_node->m_pos_z == 712)
					{
						notify::crash_blocked(sender, "invalid sector position");
						return true;
					}
					break;
				}
			}
		}
		return false;
	}

	bool hooks::can_apply_data(rage::netSyncTree* tree, rage::netObject* object)
	{
		if (tree->m_child_node_count && check_node(tree->m_sync_node, g->m_syncing_player, object))
		{
			return false;
		}

		return g_hooking->get_original<hooks::can_apply_data>()(tree, object);
	}
}