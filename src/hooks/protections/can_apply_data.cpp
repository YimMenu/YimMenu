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
#include "datanodes/proximity_migrateable/CSectorDataNode.hpp"
#include "datanodes/vehicle/CVehicleCreationDataNode.hpp"
#include "datanodes/vehicle/CVehicleGadgetDataNode.hpp"
#include "network/netObject.hpp"
#include "base/CBaseModelInfo.hpp"
#include "vehicle/CVehicleModelInfo.hpp"
#include "util/model_info.hpp"
#include "network/CNetGamePlayer.hpp"
#include "util/notify.hpp"
// TODO: remove as it's unused
#define CLASS_TO_MANGLED_NAME(c) "?AV"#c"@@"

namespace big
{
	constexpr auto nodes = std::to_array<std::pair<Hash, uint64_t>>({
		{RAGE_JOAAT("CAutomobileCreationDataNode"), 0x1b088e0},
		{RAGE_JOAAT("CBikeGameStateDataNode"), 0x1b08a40},
		{RAGE_JOAAT("CBoatGameStateDataNode"), 0x1b08a80},
		{RAGE_JOAAT("CDoorCreationDataNode"), 0x1b08be0},
		{RAGE_JOAAT("CDoorMovementDataNode"), 0x1b09000},
		{RAGE_JOAAT("CDoorScriptGameStateDataNode"), 0x1b08ea0},
		{RAGE_JOAAT("CDoorScriptInfoDataNode"), 0x1b08d40},
		{RAGE_JOAAT("CDynamicEntityGameStateDataNode"), 0x1b06450},
		{RAGE_JOAAT("CEntityOrientationDataNode"), 0x1b05df0},
		{RAGE_JOAAT("CEntityScriptGameStateDataNode"), 0x1b05c90},
		{RAGE_JOAAT("CEntityScriptInfoDataNode"), 0x1b05b30},
		{RAGE_JOAAT("CGlobalFlagsDataNode"), 0x1b057f0},
		{RAGE_JOAAT("CHeliControlDataNode"), 0x1b08180},
		{RAGE_JOAAT("CHeliHealthDataNode"), 0x1b06f60},
		{RAGE_JOAAT("CMigrationDataNode"), 0x1b05af0},
		{RAGE_JOAAT("CObjectCreationDataNode"), 0x1b096e0},
		{RAGE_JOAAT("CObjectGameStateDataNode"), 0x1b09840},
		{RAGE_JOAAT("CObjectOrientationNode"), 0x1b09c60},
		{RAGE_JOAAT("CObjectScriptGameStateDataNode"), 0x1b099a0},
		{RAGE_JOAAT("CObjectSectorPosNode"), 0x1b09b00},
		{RAGE_JOAAT("CPedAIDataNode"), 0x1b0ae80},
		{RAGE_JOAAT("CPedAppearanceDataNode"), 0x1b0ad20},
		{RAGE_JOAAT("CPedAttachDataNode"), 0x1b0a900},
		{RAGE_JOAAT("CPedComponentReservationDataNode"), 0x1b0a380},
		{RAGE_JOAAT("CPedCreationDataNode"), 0x1b09ca0},
		{RAGE_JOAAT("CPedGameStateDataNode"), 0x1b09f60},
		{RAGE_JOAAT("CPedHealthDataNode"), 0x1b0a7a0},
		{RAGE_JOAAT("CPedInventoryDataNode"), 0x1b0b2a0},
		{RAGE_JOAAT("CPedMovementDataNode"), 0x1b0abc0},
		{RAGE_JOAAT("CPedMovementGroupDataNode"), 0x1b0aa60},
		{RAGE_JOAAT("CPedOrientationDataNode"), 0x1b0a640},
		{RAGE_JOAAT("CPedScriptCreationDataNode"), 0x1b09e00},
		{RAGE_JOAAT("CPedScriptGameStateDataNode"), 0x1b0a4e0},
		{RAGE_JOAAT("CPedSectorPosMapNode"), 0x1b05ab0},
		{RAGE_JOAAT("CPedSectorPosNavMeshNode"), 0x1b0a220},
		{RAGE_JOAAT("CPedTaskSequenceDataNode"), 0x1b0b400},
		{RAGE_JOAAT("CPedTaskSpecificDataNode"), 0x1b0b140},
		{RAGE_JOAAT("CPedTaskTreeDataNode"), 0x1b0afe0},
		{RAGE_JOAAT("CPhysicalAngVelocityDataNode"), 0x1b06f20},
		{RAGE_JOAAT("CPhysicalAttachDataNode"), 0x1b06fa0},
		{RAGE_JOAAT("CPhysicalGameStateDataNode"), 0x1b06b00},
		{RAGE_JOAAT("CPhysicalHealthDataNode"), 0x1b06f60},
		{RAGE_JOAAT("CPhysicalMigrationDataNode"), 0x1b07100},
		{RAGE_JOAAT("CPhysicalScriptGameStateDataNode"), 0x1b06c60},
		{RAGE_JOAAT("CPhysicalScriptMigrationDataNode"), 0x1b07140},
		{RAGE_JOAAT("CPhysicalVelocityDataNode"), 0x1b06dc0},
		{RAGE_JOAAT("CPickupCreationDataNode"), 0x1b0b560},
		{RAGE_JOAAT("CPickupPlacementCreationDataNode"), 0x1b0b860},
		{RAGE_JOAAT("CPickupPlacementStateDataNode"), 0x1b0b9c0},
		{RAGE_JOAAT("CPickupScriptGameStateNode"), 0x1b0b820},
		{RAGE_JOAAT("CPickupSectorPosNode"), 0x1b0b6c0},
		{RAGE_JOAAT("CPlaneControlDataNode"), 0x1b08180},
		{RAGE_JOAAT("CPlaneGameStateDataNode"), 0x1b0c380},
		{RAGE_JOAAT("CPlayerAmbientModelStreamingNode"), 0x1b0c040},
		{RAGE_JOAAT("CPlayerAppearanceDataNode"), 0x1b0bc20},
		{RAGE_JOAAT("CPlayerCameraDataNode"), 0x1b0bba0},
		{RAGE_JOAAT("CPlayerCreationDataNode"), 0x1b0ba00},
		{RAGE_JOAAT("CPlayerExtendedGameStateNode"), 0x1b0c300},
		{RAGE_JOAAT("CPlayerGameStateDataNode"), 0x1b0bbe0},
		{RAGE_JOAAT("CPlayerGamerDataNode"), 0x1b0c1a0},
		{RAGE_JOAAT("CPlayerPedGroupDataNode"), 0x1b0bd80},
		{RAGE_JOAAT("CPlayerSectorPosNode"), 0x1b0bb60},
		{RAGE_JOAAT("CPlayerWantedAndLOSDataNode"), 0x1b0bee0},
		{RAGE_JOAAT("CSectorDataNode"), 0x1b05950},
		{RAGE_JOAAT("CSectorPositionDataNode"), 0x1b05ab0},
		{RAGE_JOAAT("CSubmarineControlDataNode"), 0x1b08180},
		{RAGE_JOAAT("CSubmarineGameStateDataNode"), 0x1b092c0},
		{RAGE_JOAAT("CTrainGameStateDataNode"), 0x1b0c340},
		{RAGE_JOAAT("CVehicleAngVelocityDataNode"), 0x1b06f20},
		{RAGE_JOAAT("CVehicleAppearanceDataNode"), 0x1b082e0},
		{RAGE_JOAAT("CVehicleComponentReservationDataNode"), 0x1b085e0},
		{RAGE_JOAAT("CVehicleControlDataNode"), 0x1b08180},
		{RAGE_JOAAT("CVehicleCreationDataNode"), 0x1b07940},
		{RAGE_JOAAT("CVehicleDamageStatusDataNode"), 0x1b08440},
		{RAGE_JOAAT("CVehicleGadgetDataNode"), 0x1b08780},
		{RAGE_JOAAT("CVehicleGameStateDataNode"), 0x1b07c00},
		{RAGE_JOAAT("CVehicleHealthDataNode"), 0x1b07ec0},
		{RAGE_JOAAT("CVehicleProximityMigrationDataNode"), 0x1b08740},
		{RAGE_JOAAT("CVehicleScriptGameStateDataNode"), 0x1b07d60},
		{RAGE_JOAAT("CVehicleSteeringDataNode"), 0x1b08020},
		{RAGE_JOAAT("CVehicleTaskDataNode"), 0x1b085a0}});

	// TODO: remove as it's unused
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

	bool check_node(rage::netSyncNodeBase* node, CNetGamePlayer* sender, rage::netObject* object)
	{
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
			auto offset_to_address = [](uint64_t off)
			{
				static auto base_addr = reinterpret_cast<uint64_t>(GetModuleHandle(nullptr));
				return base_addr + off;
			};

			auto vtable = *(void**)node;
			Hash node_hash;
			for (const auto& n : nodes)
			{
				if ((void*)offset_to_address(n.second) == vtable)
				{
					node_hash = n.first;
				}
			}
			switch (node_hash)
			{
				case "CDoorCreationDataNode"_j:
				{
					const auto creation_node = dynamic_cast<CDoorCreationDataNode*>(node);
					if (is_crash_object(creation_node->m_model))
					{
						notify::crash_blocked(sender, "invalid door model");
						return true;
					}
					break;
				}
				case "CPickupCreationDataNode"_j:
				{
					const auto creation_node = dynamic_cast<CPickupCreationDataNode*>(node);
					if (is_crash_object(creation_node->m_custom_model))
					{
						notify::crash_blocked(sender, "invalid pickup model");
						return true;
					}
					break;
				}
				case "CPhysicalAttachDataNode"_j:
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
				case "CPedCreationDataNode"_j:
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
				case "CPedAttachDataNode"_j:
				{
					const auto attach_node = dynamic_cast<CPedAttachDataNode*>(node);
					if (attach_node->m_attached && attach_node->m_attached_to == object->m_object_id)
					{
						notify::crash_blocked(sender, "infinite ped attachment");
						return true;
					}
					break;
				}
				case "CVehicleCreationDataNode"_j:
				{
					const auto vehicle_creation_node = dynamic_cast<CVehicleCreationDataNode*>(node);
					if (is_crash_vehicle(vehicle_creation_node->m_model))
					{
						notify::crash_blocked(sender, "invalid vehicle model");
						return true;
					}
					break;
				}
				case "CObjectCreationDataNode"_j:
				{
					const auto creation_node = dynamic_cast<CObjectCreationDataNode*>(node);
					if (is_crash_object(creation_node->m_model))
					{
						notify::crash_blocked(sender, "invalid object model");
						return true;
					}
					break;
				}
				case "CPlayerAppearanceDataNode"_j:
				{
					const auto player_appearance_node = dynamic_cast<CPlayerAppearanceDataNode*>(node);
					if (is_crash_ped(player_appearance_node->m_model_hash))
					{
						notify::crash_blocked(sender, "invalid player model");
						return true;
					}
					break;
				}
				case "CSectorDataNode"_j:
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
		if (tree->m_child_node_count && check_node(tree->m_sync_node, g.m_syncing_player, object))
		{
			return false;
		}

		return g_hooking->get_original<hooks::can_apply_data>()(tree, object);
	}
}