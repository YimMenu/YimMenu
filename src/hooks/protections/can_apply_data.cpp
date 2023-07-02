#include "base/CBaseModelInfo.hpp"
#include "base/CObject.hpp"
#include "entities/fwEntity.hpp"
#include "gta/net_object_mgr.hpp"
#include "hooking.hpp"
#include "netsync/netSyncDataNode.hpp"
#include "netsync/netSyncTree.hpp"
#include "netsync/nodes/door/CDoorCreationDataNode.hpp"
#include "netsync/nodes/dynamic_entity/CDynamicEntityGameStateDataNode.hpp"
#include "netsync/nodes/object/CObjectCreationDataNode.hpp"
#include "netsync/nodes/ped/CPedAttachDataNode.hpp"
#include "netsync/nodes/ped/CPedCreationDataNode.hpp"
#include "netsync/nodes/ped/CPedInventoryDataNode.hpp"
#include "netsync/nodes/physical/CPhysicalAttachDataNode.hpp"
#include "netsync/nodes/pickup/CPickupCreationDataNode.hpp"
#include "netsync/nodes/player/CPlayerAppearanceDataNode.hpp"
#include "netsync/nodes/player/CPlayerCreationDataNode.hpp"
#include "netsync/nodes/player/CPlayerGameStateDataNode.hpp"
#include "netsync/nodes/proximity_migrateable/CSectorDataNode.hpp"
#include "netsync/nodes/train/CTrainGameStateDataNode.hpp"
#include "netsync/nodes/vehicle/CVehicleCreationDataNode.hpp"
#include "netsync/nodes/vehicle/CVehicleGadgetDataNode.hpp"
#include "netsync/nodes/vehicle/CVehicleProximityMigrationDataNode.hpp"
#include "network/CNetGamePlayer.hpp"
#include "network/netObject.hpp"
#include "util/model_info.hpp"
#include "util/notify.hpp"
#include "vehicle/CVehicleModelInfo.hpp"

namespace big
{
	struct sync_node_id
	{
		Hash id;

		constexpr sync_node_id()
		{
			id = 0;
		}

		template<size_t N>
		constexpr sync_node_id(char const (&pp)[N])
		{
			id = rage::consteval_joaat(pp);
		}

		// implicit conversion
		constexpr operator Hash() const
		{
			return id;
		}
	};

	using sync_node_vft = uintptr_t;

	// Sync Node Virtual Function Table address to all sync node identifiers that also have that vft address.
	using sync_node_vft_to_ids = std::unordered_map<sync_node_vft, std::vector<sync_node_id>>;

	// Sync Tree node array index to node identifier.
	using sync_tree_node_array_index_to_node_id_t = std::vector<sync_node_id>;

	struct sync_node_finder_t
	{
		static constexpr size_t sync_tree_count = size_t(eNetObjType::NET_OBJ_TYPE_TRAIN) + 1;

		std::array<sync_node_vft_to_ids, sync_tree_count> sync_trees_sync_node_vft_to_ids;

		std::array<sync_tree_node_array_index_to_node_id_t, sync_tree_count> sync_trees_node_array_index_to_node_id = {
		    {
		        // AUTOMOBILE
		        {
		            {"CVehicleCreationDataNode"},
		            {"CAutomobileCreationDataNode"},

		            {"CGlobalFlagsDataNode"},
		            {"CDynamicEntityGameStateDataNode"},
		            {"CPhysicalGameStateDataNode"},
		            {"CVehicleGameStateDataNode"},

		            {"CEntityScriptGameStateDataNode"},
		            {"CPhysicalScriptGameStateDataNode"},
		            {"CVehicleScriptGameStateDataNode"},
		            {"CEntityScriptInfoDataNode"},

		            {"CPhysicalAttachDataNode"},
		            {"CVehicleAppearanceDataNode"},
		            {"CVehicleDamageStatusDataNode"},
		            {"CVehicleComponentReservationDataNode"},
		            {"CVehicleHealthDataNode"},
		            {"CVehicleTaskDataNode"},

		            {"CSectorDataNode"},
		            {"CSectorPositionDataNode"},
		            {"CEntityOrientationDataNode"},
		            {"CPhysicalVelocityDataNode"},
		            {"CVehicleAngVelocityDataNode"},

		            {"CVehicleSteeringDataNode"},
		            {"CVehicleControlDataNode"},
		            {"CVehicleGadgetDataNode"},

		            {"CMigrationDataNode"},
		            {"CPhysicalMigrationDataNode"},
		            {"CPhysicalScriptMigrationDataNode"},
		            {"CVehicleProximityMigrationDataNode"},
		        },
		        // BIKE
		        {
		            {"CVehicleCreationDataNode"},

		            {"CGlobalFlagsDataNode"},
		            {"CDynamicEntityGameStateDataNode"},
		            {"CPhysicalGameStateDataNode"},
		            {"CVehicleGameStateDataNode"},
		            {"CBikeGameStateDataNode"},

		            {"CEntityScriptGameStateDataNode"},
		            {"CPhysicalScriptGameStateDataNode"},
		            {"CVehicleScriptGameStateDataNode"},
		            {"CEntityScriptInfoDataNode"},

		            {"CPhysicalAttachDataNode"},
		            {"CVehicleAppearanceDataNode"},
		            {"CVehicleDamageStatusDataNode"},
		            {"CVehicleComponentReservationDataNode"},
		            {"CVehicleHealthDataNode"},
		            {"CVehicleTaskDataNode"},

		            {"CSectorDataNode"},
		            {"CSectorPositionDataNode"},
		            {"CEntityOrientationDataNode"},
		            {"CPhysicalVelocityDataNode"},
		            {"CVehicleAngVelocityDataNode"},

		            {"CVehicleSteeringDataNode"},
		            {"CVehicleControlDataNode"},
		            {"CVehicleGadgetDataNode"},

		            {"CMigrationDataNode"},
		            {"CPhysicalMigrationDataNode"},
		            {"CPhysicalScriptMigrationDataNode"},
		            {"CVehicleProximityMigrationDataNode"},
		        },
		        // BOAT
		        {
		            {"CVehicleCreationDataNode"},

		            {"CGlobalFlagsDataNode"},
		            {"CDynamicEntityGameStateDataNode"},
		            {"CPhysicalGameStateDataNode"},
		            {"CVehicleGameStateDataNode"},
		            {"CBoatGameStateDataNode"},

		            {"CEntityScriptGameStateDataNode"},
		            {"CPhysicalScriptGameStateDataNode"},
		            {"CVehicleScriptGameStateDataNode"},
		            {"CEntityScriptInfoDataNode"},

		            {"CPhysicalAttachDataNode"},
		            {"CVehicleAppearanceDataNode"},
		            {"CVehicleDamageStatusDataNode"},
		            {"CVehicleComponentReservationDataNode"},
		            {"CVehicleHealthDataNode"},
		            {"CVehicleTaskDataNode"},

		            {"CSectorDataNode"},
		            {"CSectorPositionDataNode"},
		            {"CEntityOrientationDataNode"},
		            {"CPhysicalVelocityDataNode"},
		            {"CVehicleAngVelocityDataNode"},

		            {"CVehicleSteeringDataNode"},
		            {"CVehicleControlDataNode"},
		            {"CVehicleGadgetDataNode"},

		            {"CMigrationDataNode"},
		            {"CPhysicalMigrationDataNode"},
		            {"CPhysicalScriptMigrationDataNode"},
		            {"CVehicleProximityMigrationDataNode"},
		        },
		        // DOOR
		        {
		            {"CDoorCreationDataNode"},

		            {"CGlobalFlagsDataNode"},
		            {"CDoorScriptInfoDataNode"},
		            {"CDoorScriptGameStateDataNode"},

		            {"CDoorMovementDataNode"},

		            {"CMigrationDataNode"},
		            {"CPhysicalScriptMigrationDataNode"},
		        },
		        // HELI
		        {
		            {"CVehicleCreationDataNode"},
		            {"CAutomobileCreationDataNode"},

		            {"CGlobalFlagsDataNode"},
		            {"CDynamicEntityGameStateDataNode"},
		            {"CPhysicalGameStateDataNode"},
		            {"CVehicleGameStateDataNode"},

		            {"CEntityScriptGameStateDataNode"},
		            {"CPhysicalScriptGameStateDataNode"},
		            {"CVehicleScriptGameStateDataNode"},
		            {"CEntityScriptInfoDataNode"},

		            {"CPhysicalAttachDataNode"},
		            {"CVehicleAppearanceDataNode"},
		            {"CVehicleDamageStatusDataNode"},
		            {"CVehicleComponentReservationDataNode"},
		            {"CVehicleHealthDataNode"},
		            {"CVehicleTaskDataNode"},
		            {"CHeliHealthDataNode"},

		            {"CSectorDataNode"},
		            {"CSectorPositionDataNode"},
		            {"CEntityOrientationDataNode"},
		            {"CPhysicalVelocityDataNode"},
		            {"CVehicleAngVelocityDataNode"},

		            {"CVehicleSteeringDataNode"},
		            {"CVehicleControlDataNode"},
		            {"CVehicleGadgetDataNode"},
		            {"CHeliControlDataNode"},

		            {"CMigrationDataNode"},
		            {"CPhysicalMigrationDataNode"},
		            {"CPhysicalScriptMigrationDataNode"},
		            {"CVehicleProximityMigrationDataNode"},
		        },
		        // OBJECT
		        {
		            {"CObjectCreationDataNode"},

		            {"CGlobalFlagsDataNode"},
		            {"CDynamicEntityGameStateDataNode"},
		            {"CPhysicalGameStateDataNode"},
		            {"CObjectGameStateDataNode"},

		            {"CEntityScriptGameStateDataNode"},
		            {"CPhysicalScriptGameStateDataNode"},
		            {"CObjectScriptGameStateDataNode"},
		            {"CEntityScriptInfoDataNode"},

		            {"CPhysicalAttachDataNode"},
		            {"CPhysicalHealthDataNode"},

		            {"CSectorDataNode"},
		            {"CObjectSectorPosNode"},
		            {"CObjectOrientationNode"},
		            {"CPhysicalVelocityDataNode"},
		            {"CPhysicalAngVelocityDataNode"},

		            {"CMigrationDataNode"},
		            {"CPhysicalMigrationDataNode"},
		            {"CPhysicalScriptMigrationDataNode"},
		        },
		        // PED
		        {
		            {"CPedCreationDataNode"},
		            {"CPedScriptCreationDataNode"},

		            {"CGlobalFlagsDataNode"},
		            {"CDynamicEntityGameStateDataNode"},
		            {"CPhysicalGameStateDataNode"},
		            {"CPedGameStateDataNode"},
		            {"CPedComponentReservationDataNode"},

		            {"CEntityScriptGameStateDataNode"},
		            {"CPhysicalScriptGameStateDataNode"},
		            {"CPedScriptGameStateDataNode"},
		            {"CEntityScriptInfoDataNode"},

		            {"CPedAttachDataNode"},
		            {"CPedHealthDataNode"},
		            {"CPedMovementGroupDataNode"},
		            {"CPedAIDataNode"},
		            {"CPedAppearanceDataNode"},

		            {"CPedOrientationDataNode"},
		            {"CPedMovementDataNode"},

		            {"CPedTaskTreeDataNode"},
		            {"CPedTaskSpecificDataNode"},
		            {"CPedTaskSpecificDataNode"},
		            {"CPedTaskSpecificDataNode"},
		            {"CPedTaskSpecificDataNode"},
		            {"CPedTaskSpecificDataNode"},
		            {"CPedTaskSpecificDataNode"},
		            {"CPedTaskSpecificDataNode"},
		            {"CPedTaskSpecificDataNode"},

		            {"CSectorDataNode"},
		            {"CPedSectorPosMapNode"},
		            {"CPedSectorPosNavMeshNode"},

		            {"CMigrationDataNode"},
		            {"CPhysicalMigrationDataNode"},
		            {"CPhysicalScriptMigrationDataNode"},
		            {"CPedInventoryDataNode"},
		            {"CPedTaskSequenceDataNode"},
		        },
		        // PICKUP
		        {
		            {"CPickupCreationDataNode"},

		            {"CGlobalFlagsDataNode"},
		            {"CDynamicEntityGameStateDataNode"},

		            {"CPickupScriptGameStateNode"},
		            {"CPhysicalGameStateDataNode"},
		            {"CEntityScriptGameStateDataNode"},
		            {"CPhysicalScriptGameStateDataNode"},
		            {"CEntityScriptInfoDataNode"},
		            {"CPhysicalHealthDataNode"},

		            {"CPhysicalAttachDataNode"},

		            {"CSectorDataNode"},
		            {"CPickupSectorPosNode"},
		            {"CEntityOrientationDataNode"},
		            {"CPhysicalVelocityDataNode"},
		            {"CPhysicalAngVelocityDataNode"},

		            {"CMigrationDataNode"},
		            {"CPhysicalMigrationDataNode"},
		            {"CPhysicalScriptMigrationDataNode"},
		        },
		        // PICKUP_PLACEMENT
		        {
		            {"CPickupPlacementCreationDataNode"},
		            {"CMigrationDataNode"},
		            {"CGlobalFlagsDataNode"},
		            {"CPickupPlacementStateDataNode"},
		        },
		        // PLANE
		        {
		            {"CVehicleCreationDataNode"},

		            {"CGlobalFlagsDataNode"},
		            {"CDynamicEntityGameStateDataNode"},
		            {"CPhysicalGameStateDataNode"},
		            {"CVehicleGameStateDataNode"},

		            {"CEntityScriptGameStateDataNode"},
		            {"CPhysicalScriptGameStateDataNode"},
		            {"CVehicleScriptGameStateDataNode"},
		            {"CEntityScriptInfoDataNode"},

		            {"CPhysicalAttachDataNode"},
		            {"CVehicleAppearanceDataNode"},
		            {"CVehicleDamageStatusDataNode"},
		            {"CVehicleComponentReservationDataNode"},
		            {"CVehicleHealthDataNode"},
		            {"CVehicleTaskDataNode"},
		            {"CPlaneGameStateDataNode"},

		            {"CSectorDataNode"},
		            {"CSectorPositionDataNode"},
		            {"CEntityOrientationDataNode"},
		            {"CPhysicalVelocityDataNode"},
		            {"CVehicleAngVelocityDataNode"},

		            {"CVehicleSteeringDataNode"},
		            {"CVehicleControlDataNode"},
		            {"CVehicleGadgetDataNode"},
		            {"CPlaneControlDataNode"},

		            {"CMigrationDataNode"},
		            {"CPhysicalMigrationDataNode"},
		            {"CPhysicalScriptMigrationDataNode"},
		            {"CVehicleProximityMigrationDataNode"},
		        },
		        // SUBMARINE
		        {
		            {"CVehicleCreationDataNode"},

		            {"CGlobalFlagsDataNode"},
		            {"CDynamicEntityGameStateDataNode"},
		            {"CPhysicalGameStateDataNode"},
		            {"CVehicleGameStateDataNode"},
		            {"CSubmarineGameStateDataNode"},

		            {"CEntityScriptGameStateDataNode"},
		            {"CPhysicalScriptGameStateDataNode"},
		            {"CVehicleScriptGameStateDataNode"},
		            {"CEntityScriptInfoDataNode"},

		            {"CPhysicalAttachDataNode"},
		            {"CVehicleAppearanceDataNode"},
		            {"CVehicleDamageStatusDataNode"},
		            {"CVehicleComponentReservationDataNode"},
		            {"CVehicleHealthDataNode"},
		            {"CVehicleTaskDataNode"},

		            {"CSectorDataNode"},
		            {"CSectorPositionDataNode"},
		            {"CEntityOrientationDataNode"},
		            {"CPhysicalVelocityDataNode"},
		            {"CVehicleAngVelocityDataNode"},

		            {"CVehicleSteeringDataNode"},
		            {"CVehicleControlDataNode"},
		            {"CVehicleGadgetDataNode"},
		            {"CSubmarineControlDataNode"},

		            {"CMigrationDataNode"},
		            {"CPhysicalMigrationDataNode"},
		            {"CPhysicalScriptMigrationDataNode"},
		            {"CVehicleProximityMigrationDataNode"},
		        },
		        // PLAYER
		        {
		            {"CPlayerCreationDataNode"},

		            {"CGlobalFlagsDataNode"},
		            {"CDynamicEntityGameStateDataNode"},
		            {"CPhysicalGameStateDataNode"},
		            {"CPedGameStateDataNode"},
		            {"CPedComponentReservationDataNode"},

		            {"CEntityScriptGameStateDataNode"},
		            {"CPlayerGameStateDataNode"},

		            {"CPedAttachDataNode"},
		            {"CPedHealthDataNode"},
		            {"CPedMovementGroupDataNode"},
		            {"CPedAIDataNode"},
		            {"CPlayerAppearanceDataNode"},
		            {"CPlayerPedGroupDataNode"},
		            {"CPlayerAmbientModelStreamingNode"},
		            {"CPlayerGamerDataNode"},
		            {"CPlayerExtendedGameStateNode"},

		            {"CPedOrientationDataNode"},
		            {"CPedMovementDataNode"},

		            {"CPedTaskTreeDataNode"},
		            {"CPedTaskSpecificDataNode"},
		            {"CPedTaskSpecificDataNode"},
		            {"CPedTaskSpecificDataNode"},
		            {"CPedTaskSpecificDataNode"},
		            {"CPedTaskSpecificDataNode"},
		            {"CPedTaskSpecificDataNode"},
		            {"CPedTaskSpecificDataNode"},
		            {"CPedTaskSpecificDataNode"},

		            {"CSectorDataNode"},
		            {"CPlayerSectorPosNode"},
		            {"CPlayerCameraDataNode"},
		            {"CPlayerWantedAndLOSDataNode"},

		            {"CMigrationDataNode"},
		            {"CPhysicalMigrationDataNode"},
		            {"CPhysicalScriptMigrationDataNode"},
		        },
		        // TRAILER
		        {

		        },
		        // TRAIN
		        {
		            {"CVehicleCreationDataNode"},

		            {"CGlobalFlagsDataNode"},
		            {"CDynamicEntityGameStateDataNode"},
		            {"CPhysicalGameStateDataNode"},
		            {"CVehicleGameStateDataNode"},
		            {"CTrainGameStateDataNode"},

		            {"CEntityScriptGameStateDataNode"},
		            {"CPhysicalScriptGameStateDataNode"},
		            {"CVehicleScriptGameStateDataNode"},
		            {"CEntityScriptInfoDataNode"},

		            {"CPhysicalAttachDataNode"},
		            {"CVehicleAppearanceDataNode"},
		            {"CVehicleDamageStatusDataNode"},
		            {"CVehicleComponentReservationDataNode"},
		            {"CVehicleHealthDataNode"},
		            {"CVehicleTaskDataNode"},

		            {"CSectorDataNode"},
		            {"CSectorPositionDataNode"},
		            {"CEntityOrientationDataNode"},
		            {"CPhysicalVelocityDataNode"},
		            {"CVehicleAngVelocityDataNode"},

		            {"CVehicleSteeringDataNode"},
		            {"CVehicleControlDataNode"},
		            {"CVehicleGadgetDataNode"},

		            {"CMigrationDataNode"},
		            {"CPhysicalMigrationDataNode"},
		            {"CPhysicalScriptMigrationDataNode"},
		            {"CVehicleProximityMigrationDataNode"},
		        },
		    },
		};
	};

	class sync_node_finder
	{
	private:
		static inline sync_node_finder_t finder;

	public:
		static const std::vector<sync_node_id>& find(eNetObjType obj_type, uintptr_t vft)
		{
			return finder.sync_trees_sync_node_vft_to_ids[(int)obj_type][vft];
		}

		static void init()
		{
			for (int i = (int)eNetObjType::NET_OBJ_TYPE_AUTOMOBILE; i <= (int)eNetObjType::NET_OBJ_TYPE_TRAIN; i++)
			{
				if (i == (int)eNetObjType::NET_OBJ_TYPE_TRAILER)
					continue;

				rage::netSyncTree* tree = g_pointers->m_gta.m_get_sync_tree_for_type(*g_pointers->m_gta.m_network_object_mgr, i);

				if (tree->m_child_node_count != finder.sync_trees_node_array_index_to_node_id[i].size())
				{
					LOG(FATAL) << "Cache nodes failed " << i << " " << tree->m_child_node_count << " "
					           << finder.sync_trees_node_array_index_to_node_id[i].size();

					throw std::runtime_error("Failed to cache nodes");
				}

				for (int j = 0; j < tree->m_child_node_count; j++)
				{
					const uintptr_t vft = *(uintptr_t*)tree->m_child_nodes[j];

					const sync_node_id node_id = finder.sync_trees_node_array_index_to_node_id[i][j];

					finder.sync_trees_sync_node_vft_to_ids[i][vft].push_back(node_id);
				}
			}
		}
	};

	constexpr uint32_t crash_peds[] = {RAGE_JOAAT("slod_human"), RAGE_JOAAT("slod_small_quadped"), RAGE_JOAAT("slod_large_quadped")};

	constexpr uint32_t crash_vehicles[] = {RAGE_JOAAT("arbitergt"), RAGE_JOAAT("astron2"), RAGE_JOAAT("cyclone2"), RAGE_JOAAT("ignus2"), RAGE_JOAAT("s95")};

	constexpr uint32_t crash_objects[] = {RAGE_JOAAT("prop_dummy_01"), RAGE_JOAAT("prop_dummy_car"), RAGE_JOAAT("prop_dummy_light"), RAGE_JOAAT("prop_dummy_plane"), RAGE_JOAAT("prop_distantcar_night"), RAGE_JOAAT("prop_distantcar_day"), RAGE_JOAAT("hei_bh1_08_details4_em_night"), RAGE_JOAAT("dt1_18_sq_night_slod"), RAGE_JOAAT("ss1_12_night_slod"), -1288391198, RAGE_JOAAT("h4_prop_bush_bgnvla_med_01"), RAGE_JOAAT("h4_prop_bush_bgnvla_lrg_01"), RAGE_JOAAT("h4_prop_bush_buddleia_low_01"), RAGE_JOAAT("h4_prop_bush_ear_aa"), RAGE_JOAAT("h4_prop_bush_ear_ab"), RAGE_JOAAT("h4_prop_bush_fern_low_01"), RAGE_JOAAT("h4_prop_bush_fern_tall_cc"), RAGE_JOAAT("h4_prop_bush_mang_ad"), RAGE_JOAAT("h4_prop_bush_mang_low_aa"), RAGE_JOAAT("h4_prop_bush_mang_low_ab"), RAGE_JOAAT("h4_prop_bush_seagrape_low_01"), RAGE_JOAAT("prop_h4_ground_cover"), RAGE_JOAAT("h4_prop_weed_groundcover_01"), RAGE_JOAAT("h4_prop_grass_med_01"), RAGE_JOAAT("h4_prop_grass_tropical_lush_01"), RAGE_JOAAT("h4_prop_grass_wiregrass_01"), RAGE_JOAAT("h4_prop_weed_01_plant"), RAGE_JOAAT("h4_prop_weed_01_row"), RAGE_JOAAT("urbanweeds02_l1"), RAGE_JOAAT("proc_forest_grass01"), RAGE_JOAAT("prop_small_bushyba"), RAGE_JOAAT("v_res_d_dildo_a"), RAGE_JOAAT("v_res_d_dildo_b"), RAGE_JOAAT("v_res_d_dildo_c"), RAGE_JOAAT("v_res_d_dildo_d"), RAGE_JOAAT("v_res_d_dildo_e"), RAGE_JOAAT("v_res_d_dildo_f"), RAGE_JOAAT("v_res_skateboard"), RAGE_JOAAT("prop_battery_01"), RAGE_JOAAT("prop_barbell_01"), RAGE_JOAAT("prop_barbell_02"), RAGE_JOAAT("prop_bandsaw_01"), RAGE_JOAAT("prop_bbq_3"), RAGE_JOAAT("v_med_curtainsnewcloth2"), RAGE_JOAAT("bh1_07_flagpoles"), 92962485};

	inline CObject* get_game_object(rage::netObject* object)
	{
		return *(CObject**)((__int64)object + 0x50);
	}

	inline bool is_crash_ped(uint32_t model)
	{
		if (!model_info::is_model_of_type(model, eModelType::Ped, eModelType::OnlineOnlyPed))
			return true;
		for (auto iterator : crash_peds)
			if (iterator == model)
				return true;
		return false;
	}

	inline bool is_crash_vehicle(uint32_t model)
	{
		if (!model_info::is_model_of_type(model, eModelType::Vehicle, eModelType::Unk133))
			return true;
		for (auto iterator : crash_vehicles)
			if (iterator == model)
				return true;
		return false;
	}

	inline bool is_crash_object(uint32_t model)
	{
		if (!model_info::get_model(model))
			return false;
		if (!model_info::is_model_of_type(model, eModelType::Object, eModelType::Time, eModelType::Weapon, eModelType::Destructable, eModelType::WorldObject, eModelType::Sprinkler, eModelType::Unk65, eModelType::Plant, eModelType::LOD, eModelType::Unk132, eModelType::Building))
			return true;
		for (auto iterator : crash_objects)
			if (iterator == model)
				return true;
		return false;
	}

	inline bool is_attachment_infinite(rage::CDynamicEntity* object, uint16_t attached_to_net_id)
	{
		if (object == nullptr)
			return false;

		constexpr size_t reasonable_limit = 150;
		size_t i                          = 0;
		while (object && i < reasonable_limit)
		{
			if (object->m_net_object && object->m_net_object->m_object_id == attached_to_net_id)
				return true;

			object = g_pointers->m_gta.m_get_entity_attached_to(object);
			i++;
		}

		return false;
	}

	inline bool is_in_vehicle(CPed* ped, CVehicle* vehicle)
	{
		if (!ped || !vehicle)
			return false;

		if (ped == vehicle->m_driver)
			return true;

		for (int i = 0; i < 15; i++)
			if (vehicle->m_passengers[i] == ped)
				return true;

		return false;
	}

	inline bool is_local_player_an_occupant(CVehicleProximityMigrationDataNode* node)
	{
		for (int i = 0; i < 16; i++)
		{
			if (node->m_has_occupants[i] && node->m_occupants[i] == g_local_player->m_net_object->m_object_id)
				return true;
		}

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
			const auto vft = *(uintptr_t*)node;

			for (const sync_node_id node_id : sync_node_finder::find((eNetObjType)object->m_object_type, vft))
			{
				switch (node_id)
				{
				case sync_node_id("CVehicleCreationDataNode"):
				{
					const auto creation_node = (CVehicleCreationDataNode*)(node);
					if (is_crash_vehicle(creation_node->m_model))
					{
						notify::crash_blocked(sender, "invalid vehicle model");
						return true;
					}
					break;
				}
				case sync_node_id("CDoorCreationDataNode"):
				{
					const auto creation_node = (CDoorCreationDataNode*)(node);
					if (is_crash_object(creation_node->m_model))
					{
						notify::crash_blocked(sender, "invalid door model");
						return true;
					}
					break;
				}
				case sync_node_id("CPickupCreationDataNode"):
				{
					const auto creation_node = (CPickupCreationDataNode*)(node);
					if (creation_node->m_custom_model && is_crash_object(creation_node->m_custom_model))
					{
						notify::crash_blocked(sender, "invalid pickup model");
						return true;
					}
					break;
				}
				case sync_node_id("CPhysicalAttachDataNode"):
				{
					const auto attach_node = (CPhysicalAttachDataNode*)(node);

					// TODO: Find a better method to avoid false positives
					auto model_hash = get_game_object(object) ? get_game_object(object)->m_model_info->m_hash : 0;
					if (attach_node->m_attached && attach_node->m_attached_to == object->m_object_id && (model_hash != RAGE_JOAAT("hauler2") && model_hash != RAGE_JOAAT("phantom3")))
					{
						// notify::crash_blocked(sender, "infinite physical attachment");
						return true;
					}
					else if (attach_node->m_attached
					    && is_attachment_infinite((rage::CDynamicEntity*)get_game_object(object), attach_node->m_attached_to))
					{
						// notify::crash_blocked(sender, "recursive infinite physical attachment");
						return true;
					}

					break;
				}
				case sync_node_id("CPedCreationDataNode"):
				{
					const auto creation_node = (CPedCreationDataNode*)(node);
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
				case sync_node_id("CPedAttachDataNode"):
				{
					const auto attach_node = (CPedAttachDataNode*)(node);
					if (attach_node->m_attached && attach_node->m_attached_to == object->m_object_id)
					{
						notify::crash_blocked(sender, "infinite ped attachment");
						return true;
					}
					else if (attach_node->m_attached && is_attachment_infinite(get_game_object(object), attach_node->m_attached_to))
					{
						// notify::crash_blocked(sender, "recursive infinite ped attachment");
						return true;
					}

					break;
				}
				case sync_node_id("CObjectCreationDataNode"):
				{
					const auto creation_node = (CObjectCreationDataNode*)(node);
					if (is_crash_object(creation_node->m_model))
					{
						notify::crash_blocked(sender, "invalid object model");
						return true;
					}
					break;
				}
				case sync_node_id("CPlayerAppearanceDataNode"):
				{
					const auto player_appearance_node = (CPlayerAppearanceDataNode*)(node);
					if (is_crash_ped(player_appearance_node->m_model_hash))
					{
						notify::crash_blocked(sender, "invalid player model (appearance node)");
						return true;
					}
					break;
				}
				case sync_node_id("CPlayerCreationDataNode"):
				{
					const auto player_creation_node = (CPlayerCreationDataNode*)(node);
					if (is_crash_ped(player_creation_node->m_model))
					{
						notify::crash_blocked(sender, "invalid player model (creation node)");
						return true;
					}
					break;
				}
				case sync_node_id("CSectorDataNode"):
				{
					const auto sector_node = (CSectorDataNode*)(node);
					if (sector_node->m_pos_x == 712 || sector_node->m_pos_y == 712 || sector_node->m_pos_z == 712)
					{
						notify::crash_blocked(sender, "invalid sector position (sector node)");
						return true;
					}
					break;
				}
				case sync_node_id("CPlayerGameStateDataNode"):
				{
					const auto game_state_node = (CPlayerGameStateDataNode*)(node);
					if (game_state_node->m_population_control_sphere_x == 712 || game_state_node->m_population_control_sphere_y == 712
					    || game_state_node->m_population_control_sphere_z == 712)
					{
						notify::crash_blocked(sender, "invalid sector position (player game state node)");
						return true;
					}
					break;
				}
				case sync_node_id("CTrainGameStateDataNode"):
				{
					const auto train_node = (CTrainGameStateDataNode*)(node);
					if (train_node->m_track_id < 0 || train_node->m_track_id >= 27)
					{
						notify::crash_blocked(sender, "out of bound train track index");
						return true;
					}
					break;
				}
				case sync_node_id("CVehicleProximityMigrationDataNode"):
				{
					if (object && g_local_player && g_local_player->m_net_object)
					{
						const auto migration_node = (CVehicleProximityMigrationDataNode*)(node);

						if (!g_local_player->m_vehicle || !g_local_player->m_vehicle->m_net_object
						    || g_local_player->m_vehicle->m_net_object->m_object_id != object->m_object_id
						    || !is_in_vehicle(g_local_player, g_local_player->m_vehicle))
						{
							if (is_local_player_an_occupant(migration_node))
							{
								return true; // remote teleport
							}
						}
					}

					break;
				}
				}
			}
		}
		return false;
	}

	bool hooks::can_apply_data(rage::netSyncTree* tree, rage::netObject* object)
	{
		static bool init = ([] { sync_node_finder::init(); }(), true);

		if (tree->m_child_node_count && tree->m_next_sync_node && check_node(tree->m_next_sync_node, g.m_syncing_player, object))
		{
			return false;
		}

		return g_hooking->get_original<hooks::can_apply_data>()(tree, object);
	}
}