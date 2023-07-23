#include "base/CBaseModelInfo.hpp"
#include "base/CObject.hpp"
#include "core/data/task_types.hpp"
#include "entities/fwEntity.hpp"
#include "gta/net_object_mgr.hpp"
#include "hooking.hpp"
#include "netsync/netSyncDataNode.hpp"
#include "netsync/netSyncTree.hpp"
#include "netsync/nodes/automobile/CAutomobileCreationNode.hpp"
#include "netsync/nodes/door/CDoorCreationDataNode.hpp"
#include "netsync/nodes/door/CDoorMovementDataNode.hpp"
#include "netsync/nodes/door/CDoorScriptGameStateDataNode.hpp"
#include "netsync/nodes/door/CDoorScriptInfoDataNode.hpp"
#include "netsync/nodes/dynamic_entity/CDynamicEntityGameStateDataNode.hpp"
#include "netsync/nodes/entity/CEntityScriptGameStateDataNode.hpp"
#include "netsync/nodes/object/CObjectCreationDataNode.hpp"
#include "netsync/nodes/ped/CPedAIDataNode.hpp"
#include "netsync/nodes/ped/CPedAttachDataNode.hpp"
#include "netsync/nodes/ped/CPedComponentReservationDataNode.hpp"
#include "netsync/nodes/ped/CPedCreationDataNode.hpp"
#include "netsync/nodes/ped/CPedGameStateDataNode.hpp"
#include "netsync/nodes/ped/CPedHealthDataNode.hpp"
#include "netsync/nodes/ped/CPedInventoryDataNode.hpp"
#include "netsync/nodes/ped/CPedMovementDataNode.hpp"
#include "netsync/nodes/ped/CPedOrientationDataNode.hpp"
#include "netsync/nodes/ped/CPedScriptCreationDataNode.hpp"
#include "netsync/nodes/ped/CPedTaskSequenceDataNode.hpp"
#include "netsync/nodes/ped/CPedTaskSpecificDataNode.hpp"
#include "netsync/nodes/ped/CPedTaskTreeDataNode.hpp"
#include "netsync/nodes/physical/CPhysicalAngVelocityDataNode.hpp"
#include "netsync/nodes/physical/CPhysicalAttachDataNode.hpp"
#include "netsync/nodes/physical/CPhysicalGameStateDataNode.hpp"
#include "netsync/nodes/physical/CPhysicalHealthDataNode.hpp"
#include "netsync/nodes/physical/CPhysicalMigrationDataNode.hpp"
#include "netsync/nodes/physical/CPhysicalScriptGameStateDataNode.hpp"
#include "netsync/nodes/physical/CPhysicalScriptMigrationDataNode.hpp"
#include "netsync/nodes/physical/CPhysicalVelocityDataNode.hpp"
#include "netsync/nodes/pickup/CPickupCreationDataNode.hpp"
#include "netsync/nodes/pickup_placement/CPickupPlacementCreationDataNode.hpp"
#include "netsync/nodes/player/CPlayerAppearanceDataNode.hpp"
#include "netsync/nodes/player/CPlayerCameraDataNode.hpp"
#include "netsync/nodes/player/CPlayerCreationDataNode.hpp"
#include "netsync/nodes/player/CPlayerExtendedGameStateNode.hpp"
#include "netsync/nodes/player/CPlayerGameStateDataNode.hpp"
#include "netsync/nodes/player/CPlayerGamerDataNode.hpp"
#include "netsync/nodes/player/CPlayerSectorPosNode.hpp"
#include "netsync/nodes/player/CPlayerWantedAndLOSDataNode.hpp"
#include "netsync/nodes/proximity_migrateable/CGlobalFlagsDataNode.hpp"
#include "netsync/nodes/proximity_migrateable/CMigrationDataNode.hpp"
#include "netsync/nodes/proximity_migrateable/CSectorDataNode.hpp"
#include "netsync/nodes/proximity_migrateable/CSectorPositionDataNode.hpp"
#include "netsync/nodes/train/CTrainGameStateDataNode.hpp"
#include "netsync/nodes/vehicle/CVehicleControlDataNode.hpp"
#include "netsync/nodes/vehicle/CVehicleCreationDataNode.hpp"
#include "netsync/nodes/vehicle/CVehicleGadgetDataNode.hpp"
#include "netsync/nodes/vehicle/CVehicleProximityMigrationDataNode.hpp"
#include "netsync/nodes/vehicle/CVehicleTaskDataNode.hpp"
#include "network/CNetGamePlayer.hpp"
#include "network/netObject.hpp"
#include "ped/CPed.hpp"
#include "util/model_info.hpp"
#include "util/notify.hpp"
#include "util/session.hpp"
#include "vehicle/CVehicleModelInfo.hpp"

namespace big
{
	struct sync_node_id
	{
		Hash id;
		const char* name;

		constexpr sync_node_id()
		{
			id = 0;
		}

		template<size_t N>
		constexpr sync_node_id(char const (&pp)[N])
		{
			id   = rage::consteval_joaat(pp);
			name = pp;
		}

		// implicit conversion
		constexpr operator Hash() const
		{
			return id;
		}
	};

	// Sync Node Virtual Function Table address to all sync node identifiers that also have that vft address.
	using sync_node_vft_to_ids = std::unordered_map<uint64_t, sync_node_id>;

	// Sync Tree node array index to node identifier.
	using sync_tree_node_array_index_to_node_id_t = std::vector<sync_node_id>;

	struct sync_node_finder_t
	{
		static constexpr size_t sync_tree_count = size_t(eNetObjType::NET_OBJ_TYPE_TRAIN) + 1;

		std::array<sync_node_vft_to_ids, sync_tree_count> sync_trees_sync_node_addr_to_ids;

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
		static const sync_node_id& find(eNetObjType obj_type, uintptr_t addr)
		{
			return finder.sync_trees_sync_node_addr_to_ids[(int)obj_type][addr];
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
					const uintptr_t addr = (uintptr_t)tree->m_child_nodes[j];

					const sync_node_id node_id = finder.sync_trees_node_array_index_to_node_id[i][j];

					finder.sync_trees_sync_node_addr_to_ids[i][addr] = node_id;
				}
			}
		}
	};


	constexpr uint32_t crash_peds[] = {RAGE_JOAAT("slod_human"), RAGE_JOAAT("slod_small_quadped"), RAGE_JOAAT("slod_large_quadped")};

	constexpr uint32_t crash_vehicles[] = {RAGE_JOAAT("arbitergt"), RAGE_JOAAT("astron2"), RAGE_JOAAT("cyclone2"), RAGE_JOAAT("ignus2"), RAGE_JOAAT("s95")};

	constexpr uint32_t crash_objects[] = {RAGE_JOAAT("prop_dummy_01"), RAGE_JOAAT("prop_dummy_car"), RAGE_JOAAT("prop_dummy_light"), RAGE_JOAAT("prop_dummy_plane"), RAGE_JOAAT("prop_distantcar_night"), RAGE_JOAAT("prop_distantcar_day"), RAGE_JOAAT("hei_bh1_08_details4_em_night"), RAGE_JOAAT("dt1_18_sq_night_slod"), RAGE_JOAAT("ss1_12_night_slod"), -1288391198, RAGE_JOAAT("h4_prop_bush_bgnvla_med_01"), RAGE_JOAAT("h4_prop_bush_bgnvla_lrg_01"), RAGE_JOAAT("h4_prop_bush_buddleia_low_01"), RAGE_JOAAT("h4_prop_bush_ear_aa"), RAGE_JOAAT("h4_prop_bush_ear_ab"), RAGE_JOAAT("h4_prop_bush_fern_low_01"), RAGE_JOAAT("h4_prop_bush_fern_tall_cc"), RAGE_JOAAT("h4_prop_bush_mang_ad"), RAGE_JOAAT("h4_prop_bush_mang_low_aa"), RAGE_JOAAT("h4_prop_bush_mang_low_ab"), RAGE_JOAAT("h4_prop_bush_seagrape_low_01"), RAGE_JOAAT("prop_h4_ground_cover"), RAGE_JOAAT("h4_prop_weed_groundcover_01"), RAGE_JOAAT("h4_prop_grass_med_01"), RAGE_JOAAT("h4_prop_grass_tropical_lush_01"), RAGE_JOAAT("h4_prop_grass_wiregrass_01"), RAGE_JOAAT("h4_prop_weed_01_plant"), RAGE_JOAAT("h4_prop_weed_01_row"), RAGE_JOAAT("urbanweeds02_l1"), RAGE_JOAAT("proc_forest_grass01"), RAGE_JOAAT("prop_small_bushyba"), RAGE_JOAAT("v_res_d_dildo_a"), RAGE_JOAAT("v_res_d_dildo_b"), RAGE_JOAAT("v_res_d_dildo_c"), RAGE_JOAAT("v_res_d_dildo_d"), RAGE_JOAAT("v_res_d_dildo_e"), RAGE_JOAAT("v_res_d_dildo_f"), RAGE_JOAAT("v_res_skateboard"), RAGE_JOAAT("prop_battery_01"), RAGE_JOAAT("prop_barbell_01"), RAGE_JOAAT("prop_barbell_02"), RAGE_JOAAT("prop_bandsaw_01"), RAGE_JOAAT("prop_bbq_3"), RAGE_JOAAT("v_med_curtainsnewcloth2"), RAGE_JOAAT("bh1_07_flagpoles"), 92962485, RAGE_JOAAT("proc_dry_plants_01"), RAGE_JOAAT("proc_leafyplant_01"), RAGE_JOAAT("proc_grassplantmix_02"), RAGE_JOAAT("proc_dryplantsgrass_01"), RAGE_JOAAT("proc_dryplantsgrass_02"), RAGE_JOAAT("proc_dryplantsgrass_02"), RAGE_JOAAT("proc_grasses01"), RAGE_JOAAT("prop_dryweed_002_a"), RAGE_JOAAT("prop_fernba"), RAGE_JOAAT("prop_weed_001_aa"), RAGE_JOAAT("urbangrnfrnds_01"), RAGE_JOAAT("urbanweeds01"), RAGE_JOAAT("prop_dandy_b"), RAGE_JOAAT("v_proc2_temp"), RAGE_JOAAT("prop_fernbb"), RAGE_JOAAT("proc_drygrassfronds01"), RAGE_JOAAT("prop_log_ae"), RAGE_JOAAT("prop_grass_da")};

	constexpr uint32_t valid_player_models[] = {
	    RAGE_JOAAT("mp_m_freemode_01"),
	    RAGE_JOAAT("mp_f_freemode_01"),
	    RAGE_JOAAT("u_m_m_filmdirector"),
	    RAGE_JOAAT("player_zero"),
	    RAGE_JOAAT("player_one"),
	    RAGE_JOAAT("player_two"),
	    // peyote
	    RAGE_JOAAT("A_C_Boar"),
	    RAGE_JOAAT("A_C_Cat_01"),
	    RAGE_JOAAT("A_C_Cow"),
	    RAGE_JOAAT("A_C_Coyote"),
	    RAGE_JOAAT("A_C_Deer"),
	    RAGE_JOAAT("A_C_Husky"),
	    RAGE_JOAAT("A_C_MtLion"),
	    RAGE_JOAAT("A_C_Pig"),
	    RAGE_JOAAT("A_C_Poodle"),
	    RAGE_JOAAT("A_C_Pug"),
	    RAGE_JOAAT("A_C_Rabbit_01"),
	    RAGE_JOAAT("A_C_Retriever"),
	    RAGE_JOAAT("A_C_Rottweiler"),
	    RAGE_JOAAT("A_C_shepherd"),
	    RAGE_JOAAT("A_C_Westy"),
	    RAGE_JOAAT("A_C_Chickenhawk"),
	    RAGE_JOAAT("A_C_Cormorant"),
	    RAGE_JOAAT("A_C_Crow"),
	    RAGE_JOAAT("A_C_Hen"),
	    RAGE_JOAAT("A_C_Pigeon"),
	    RAGE_JOAAT("A_C_Seagull"),
	    RAGE_JOAAT("A_C_Dolphin"),
	    RAGE_JOAAT("A_C_Fish"),
	    RAGE_JOAAT("A_C_KillerWhale"),
	    RAGE_JOAAT("A_C_SharkHammer"),
	    RAGE_JOAAT("A_C_SharkTiger"),
	    RAGE_JOAAT("A_C_Stingray"),
	    RAGE_JOAAT("IG_Orleans"),
	    RAGE_JOAAT("A_C_Chop"),
	    RAGE_JOAAT("A_C_HumpBack"),
	};

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

	inline bool is_valid_player_model(uint32_t model)
	{
		for (auto iterator : valid_player_models)
			if (iterator == model)
				return true;
		return false;
	}

	inline void check_player_model(player_ptr player, uint32_t model)
	{
		if (!player)
			return;

		if (NETWORK::NETWORK_IS_ACTIVITY_SESSION())
			return;

		if (!is_valid_player_model(model))
		{
			session::add_infraction(player, Infraction::INVALID_PLAYER_MODEL);
		}
	}

	// the game function does weird stuff that we don't want
	inline CObject* get_entity_attached_to(CObject* entity)
	{
		if (!entity)
			return nullptr;

		if (!entity->gap50)
			return nullptr;

		__int64 component = *(__int64*)((__int64)(entity->gap50) + 0x48);

		if (!component)
			return nullptr;

		int unk_count = *(int*)(component + 0x5C) & 0xF;

		if (unk_count < 2)
			return nullptr;

		return *(CObject**)(component);
	}

	inline bool is_attachment_infinite(rage::netObject* object, uint16_t attached_to_net_id, int from_bone, int to_bone)
	{
		if (object == nullptr)
			return false;

		auto target = g_pointers->m_gta.m_get_net_object(*g_pointers->m_gta.m_network_object_mgr, attached_to_net_id, false);

		while (target)
		{
			if (target == object)
				return true;

			auto next = get_entity_attached_to(target->GetGameObject());

			if (!next)
				return false;

			if (!next->m_net_object)
				return false;

			target = next->m_net_object;
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

	inline bool is_sane_override_pos(float x, float y, float z)
	{
		bool crash = (char)(fmaxf(0.0, (x + 149.0) - -8192.0) / 75.0) == 255 || (char)(fmaxf(0.0, (y + 149.0) - -8192.0) / 75.0) == 255;

		return !crash;
	}

	inline std::string get_task_type_string(int type)
	{
		std::string buffer = "";

		for (auto& value : task_type_names)
		{
			if (value.first == type)
			{
				buffer += value.second;
				buffer += '|';
			}

			if (value.first > type)
				break; // a minor optimization
		}

		if (buffer.length() > 1)
			buffer.pop_back();
		else
			buffer = "Unknown";

		buffer += " (" + std::to_string(type) + ")";

		return buffer;
	}

	inline bool is_valid_clan_tag(char* data, bool system_clan)
	{
		int length = strlen(data);

		if (length <= (system_clan ? 2 : 3))
			return false;

		for (int i = 0; i < length; i++)
		{
			if (data[i] >= '0' && data[i] <= '9')
				continue;

			if (data[i] >= 'A' && data[i] <= 'Z')
				continue;

			if (data[i] >= 'a' && data[i] <= 'z')
				continue;

			return false;
		}

		return true;
	}

#define LOG_FIELD_H(type, field) LOG(INFO) << "\t" << #field << ": " << HEX_TO_UPPER((((type*)(node))->field));
#define LOG_FIELD(type, field) LOG(INFO) << "\t" << #field << ": " << ((((type*)(node))->field));
#define LOG_FIELD_C(type, field) LOG(INFO) << "\t" << #field << ": " << (int)((((type*)(node))->field));
#define LOG_FIELD_B(type, field) LOG(INFO) << "\t" << #field << ": " << ((((type*)(node))->field) ? "YES" : "NO");
#define LOG_FIELD_V3(type, field)                                                                                    \
	LOG(INFO) << "\t" << #field << ": X: " << ((((type*)(node))->field)).x << " Y: " << ((((type*)(node))->field)).y \
	          << " Z: " << ((((type*)(node))->field)).z;
#define LOG_FIELD_V4(type, field)                                                                                    \
	LOG(INFO) << "\t" << #field << ": X: " << ((((type*)(node))->field)).x << " Y: " << ((((type*)(node))->field)).y \
	          << " Z: " << ((((type*)(node))->field)).z << " W: " << ((((type*)(node))->field)).w;
#define LOG_FIELD_APPLY(type, field, func) LOG(INFO) << "\t" << #field << ": " << func((((type*)(node))->field));

	void log_node(const sync_node_id& node_id, player_ptr sender, CProjectBaseSyncDataNode* node, rage::netObject* object)
	{
		if (object)
			LOG(INFO) << sender->get_name() << ": " << node_id.name << ", " << object->m_object_id;
		else
			LOG(INFO) << sender->get_name() << ": " << node_id.name;

		switch (node_id)
		{
		case sync_node_id("CVehicleCreationDataNode"):
			LOG_FIELD(CVehicleCreationDataNode, m_pop_type);
			LOG_FIELD(CVehicleCreationDataNode, m_random_seed);
			LOG_FIELD_H(CVehicleCreationDataNode, m_model);
			LOG_FIELD(CVehicleCreationDataNode, m_vehicle_status);
			LOG_FIELD(CVehicleCreationDataNode, m_max_health);
			LOG_FIELD(CVehicleCreationDataNode, m_creation_token);
			LOG_FIELD_B(CVehicleCreationDataNode, m_needs_to_be_hotwired);
			LOG_FIELD_B(CVehicleCreationDataNode, m_tires_dont_burst);
			break;
		case sync_node_id("CPedCreationDataNode"):
			LOG_FIELD(CPedCreationDataNode, m_pop_type);
			LOG_FIELD_H(CPedCreationDataNode, m_model);
			LOG_FIELD(CPedCreationDataNode, m_random_seed);
			LOG_FIELD(CPedCreationDataNode, m_max_health);
			LOG_FIELD_B(CPedCreationDataNode, m_in_vehicle);
			LOG_FIELD(CPedCreationDataNode, pad_0xD1[0]);
			LOG_FIELD(CPedCreationDataNode, m_vehicle_id);
			LOG_FIELD(CPedCreationDataNode, m_vehicle_seat);
			LOG_FIELD_B(CPedCreationDataNode, m_has_prop);
			LOG_FIELD(CPedCreationDataNode, m_prop_model);
			LOG_FIELD_B(CPedCreationDataNode, m_is_standing);
			LOG_FIELD_B(CPedCreationDataNode, m_is_respawn_object_id);
			LOG_FIELD_B(CPedCreationDataNode, m_is_respawn_flagged_for_removal);
			LOG_FIELD_B(CPedCreationDataNode, m_has_attr_damage_to_player);
			LOG_FIELD_C(CPedCreationDataNode, m_attribute_damage_to_player);
			LOG_FIELD_H(CPedCreationDataNode, m_voice_hash);
			break;
		case sync_node_id("CObjectCreationDataNode"):
			LOG_FIELD(CObjectCreationDataNode, unk_00C0);
			LOG_FIELD_V4(CObjectCreationDataNode, m_object_orientation);
			LOG_FIELD_V3(CObjectCreationDataNode, m_object_position);
			LOG_FIELD_V3(CObjectCreationDataNode, m_dummy_position);
			LOG_FIELD_V3(CObjectCreationDataNode, m_script_grab_position);
			LOG_FIELD(CObjectCreationDataNode, m_script_grab_radius);
			LOG_FIELD(CObjectCreationDataNode, m_created_by);
			LOG_FIELD_H(CObjectCreationDataNode, m_model);
			LOG_FIELD(CObjectCreationDataNode, m_frag_group_index);
			LOG_FIELD(CObjectCreationDataNode, m_ownership_token);
			LOG_FIELD(CObjectCreationDataNode, unk_015C);
			LOG_FIELD_B(CObjectCreationDataNode, m_no_reassign);
			LOG_FIELD_B(CObjectCreationDataNode, unk_0161);
			LOG_FIELD_B(CObjectCreationDataNode, m_player_wants_control);
			LOG_FIELD_B(CObjectCreationDataNode, m_has_init_physics);
			LOG_FIELD_B(CObjectCreationDataNode, m_script_grabbed_from_world);
			LOG_FIELD_B(CObjectCreationDataNode, m_has_frag_group);
			LOG_FIELD_B(CObjectCreationDataNode, m_is_broken);
			LOG_FIELD_B(CObjectCreationDataNode, m_has_exploded);
			LOG_FIELD_B(CObjectCreationDataNode, m_keep_registered);
			LOG_FIELD_B(CObjectCreationDataNode, m_has_frag_group);
			LOG_FIELD_B(CObjectCreationDataNode, unk_0169);
			LOG_FIELD_B(CObjectCreationDataNode, unk_016A);
			LOG_FIELD_B(CObjectCreationDataNode, unk_016B);
			break;
		case sync_node_id("CTrainGameStateDataNode"):
			LOG_FIELD_B(CTrainGameStateDataNode, m_is_engine);
			LOG_FIELD_B(CTrainGameStateDataNode, m_is_caboose);
			LOG_FIELD_B(CTrainGameStateDataNode, m_is_mission_train);
			LOG_FIELD_B(CTrainGameStateDataNode, m_direction);
			LOG_FIELD_B(CTrainGameStateDataNode, m_has_passenger_carriages);
			LOG_FIELD_B(CTrainGameStateDataNode, m_render_derailed);
			LOG_FIELD_B(CTrainGameStateDataNode, unk_00C6);
			LOG_FIELD_B(CTrainGameStateDataNode, unk_00C7);
			LOG_FIELD(CTrainGameStateDataNode, m_engine_id);
			LOG_FIELD_C(CTrainGameStateDataNode, m_train_config_index);
			LOG_FIELD_C(CTrainGameStateDataNode, m_carriage_config_index);
			LOG_FIELD_C(CTrainGameStateDataNode, m_track_id);
			LOG_FIELD(CTrainGameStateDataNode, m_distance_from_engine);
			LOG_FIELD(CTrainGameStateDataNode, m_cruise_speed);
			LOG_FIELD(CTrainGameStateDataNode, m_linked_to_backward_id);
			LOG_FIELD(CTrainGameStateDataNode, m_linked_to_forward_id);
			LOG_FIELD(CTrainGameStateDataNode, m_train_state);
			LOG_FIELD_B(CTrainGameStateDataNode, unk_00E0);
			LOG_FIELD_B(CTrainGameStateDataNode, m_force_doors_open);
			break;
		case sync_node_id("CDynamicEntityGameStateDataNode"):
			LOG_FIELD(CDynamicEntityGameStateDataNode, m_interior_index);
			LOG_FIELD_B(CDynamicEntityGameStateDataNode, unk_00C4);
			LOG_FIELD_B(CDynamicEntityGameStateDataNode, unk_00C5);
			LOG_FIELD(CDynamicEntityGameStateDataNode, m_decor_count);
			for (int i = 0; i < ((CDynamicEntityGameStateDataNode*)node)->m_decor_count; i++)
			{
				LOG_FIELD(CDynamicEntityGameStateDataNode, m_decors[i].m_type);
				LOG_FIELD_H(CDynamicEntityGameStateDataNode, m_decors[i].m_name_hash);
				LOG_FIELD(CDynamicEntityGameStateDataNode, m_decors[i].m_value);
			}
			break;
		case sync_node_id("CAutomobileCreationDataNode"):
			LOG_FIELD_B(CAutomobileCreationDataNode, m_all_doors_closed);
			break;
		case sync_node_id("CDoorCreationDataNode"):
			LOG_FIELD_H(CDoorCreationDataNode, m_model);
			LOG_FIELD_V3(CDoorCreationDataNode, m_pos);
			LOG_FIELD_B(CDoorCreationDataNode, m_is_script_door);
			LOG_FIELD_B(CDoorCreationDataNode, m_player_wants_control);
			break;
		case sync_node_id("CDoorMovementDataNode"):
			LOG_FIELD_B(CDoorMovementDataNode, m_is_manual_door);
			LOG_FIELD(CDoorMovementDataNode, m_open_ratio);
			LOG_FIELD_B(CDoorMovementDataNode, m_opening);
			LOG_FIELD_B(CDoorMovementDataNode, m_fully_open);
			LOG_FIELD_B(CDoorMovementDataNode, m_closed);
			break;
		case sync_node_id("CDoorScriptGameStateDataNode"):
			LOG_FIELD(CDoorScriptGameStateDataNode, m_door_system_state);
			LOG_FIELD(CDoorScriptGameStateDataNode, m_automatic_distance);
			LOG_FIELD(CDoorScriptGameStateDataNode, m_slide_rate);
			LOG_FIELD_B(CDoorScriptGameStateDataNode, m_has_broken_flags);
			LOG_FIELD(CDoorScriptGameStateDataNode, m_broken_flags);
			LOG_FIELD_B(CDoorScriptGameStateDataNode, m_has_damaged_flags);
			LOG_FIELD(CDoorScriptGameStateDataNode, m_damaged_flags);
			LOG_FIELD_B(CDoorScriptGameStateDataNode, m_hold_open);
			break;
		case sync_node_id("CDoorScriptInfoDataNode"):
			LOG_FIELD_B(CDoorScriptInfoDataNode, m_has_script_info);
			LOG_FIELD(CDoorScriptInfoDataNode, m_door_system_hash);
			LOG_FIELD_B(CDoorScriptInfoDataNode, m_existing_door_system_entry);
			break;
		case sync_node_id("CEntityScriptGameStateDataNode"):
			LOG_FIELD_B(CEntityScriptGameStateDataNode, m_fixed);
			LOG_FIELD_B(CEntityScriptGameStateDataNode, m_uses_collision);
			LOG_FIELD_B(CEntityScriptGameStateDataNode, m_completely_disabled_collision);
			break;
		case sync_node_id("CPedAIDataNode"):
			LOG_FIELD_H(CPedAIDataNode, m_relationship_group);
			LOG_FIELD_H(CPedAIDataNode, m_decision_maker_type);
			break;
		case sync_node_id("CPedAttachDataNode"):
			LOG_FIELD_V3(CPedAttachDataNode, m_offset);
			LOG_FIELD_V4(CPedAttachDataNode, m_orientation);
			LOG_FIELD(CPedAttachDataNode, m_attached_to);
			LOG_FIELD(CPedAttachDataNode, m_attachment_bone);
			LOG_FIELD(CPedAttachDataNode, m_attachment_flags);
			LOG_FIELD(CPedAttachDataNode, m_heading_1);
			LOG_FIELD(CPedAttachDataNode, m_heading_2);
			LOG_FIELD_B(CPedAttachDataNode, m_attached);
			LOG_FIELD_B(CPedAttachDataNode, unk_00F1);
			break;
		case sync_node_id("CPedComponentReservationDataNode"):
			LOG_FIELD(CPedComponentReservationDataNode, m_num_peds_using_component);
			break;
		case sync_node_id("CPedGameStateDataNode"):
			LOG_FIELD(CPedGameStateDataNode, unk_0104);
			LOG_FIELD(CPedGameStateDataNode, unk_0108);
			LOG_FIELD(CPedGameStateDataNode, unk_010C);
			LOG_FIELD(CPedGameStateDataNode, unk_0110);
			LOG_FIELD(CPedGameStateDataNode, unk_0114);
			LOG_FIELD(CPedGameStateDataNode, unk_0118);
			LOG_FIELD_B(CPedGameStateDataNode, unk_011C);
			LOG_FIELD(CPedGameStateDataNode, m_arrest_state);
			LOG_FIELD(CPedGameStateDataNode, m_death_state);
			LOG_FIELD_H(CPedGameStateDataNode, m_weapon_hash);
			LOG_FIELD(CPedGameStateDataNode, m_num_weapon_components);
			if (((CPedGameStateDataNode*)node)->m_num_weapon_components <= 12)
			{
				for (int i = 0; i < ((CPedGameStateDataNode*)node)->m_num_weapon_components; i++)
				{
					LOG_FIELD_B(CPedGameStateDataNode, m_weapon_component_something[i]);
					LOG_FIELD_H(CPedGameStateDataNode, m_weapon_component_hash[i]);
				}
			}
			LOG_FIELD(CPedGameStateDataNode, m_num_equiped_gadgets);
			if (((CPedGameStateDataNode*)node)->m_num_equiped_gadgets <= 3)
			{
				for (int i = 0; i < ((CPedGameStateDataNode*)node)->m_num_equiped_gadgets; i++)
				{
					LOG_FIELD_B(CPedGameStateDataNode, m_gadget_hash[i]);
				}
			}
			LOG_FIELD(CPedGameStateDataNode, m_seat);
			LOG_FIELD(CPedGameStateDataNode, m_action_mode_override);
			LOG_FIELD(CPedGameStateDataNode, unk_013C);
			LOG_FIELD(CPedGameStateDataNode, m_vehicle);
			LOG_FIELD(CPedGameStateDataNode, m_mount_id);
			LOG_FIELD(CPedGameStateDataNode, m_custodian_id);
			LOG_FIELD(CPedGameStateDataNode, unk_0146);
			LOG_FIELD_B(CPedGameStateDataNode, m_tint_index);
			LOG_FIELD_C(CPedGameStateDataNode, pad_0149);
			LOG_FIELD_C(CPedGameStateDataNode, unk_014A);
			LOG_FIELD_B(CPedGameStateDataNode, m_is_handcuffed);
			LOG_FIELD_B(CPedGameStateDataNode, m_can_preform_arrest);
			LOG_FIELD_B(CPedGameStateDataNode, m_can_preform_uncuff);
			LOG_FIELD_B(CPedGameStateDataNode, m_can_be_arrested);
			LOG_FIELD_B(CPedGameStateDataNode, m_is_in_custody);
			LOG_FIELD_C(CPedGameStateDataNode, pad_0150);
			LOG_FIELD_B(CPedGameStateDataNode, m_weapon_exists);
			LOG_FIELD_B(CPedGameStateDataNode, m_weapon_visible);
			LOG_FIELD_B(CPedGameStateDataNode, m_weapon_has_ammo);
			LOG_FIELD_B(CPedGameStateDataNode, m_weapon_attach_left);
			LOG_FIELD_C(CPedGameStateDataNode, pad_0155);
			LOG_FIELD_B(CPedGameStateDataNode, m_in_seat);
			LOG_FIELD_B(CPedGameStateDataNode, m_in_vehicle);
			LOG_FIELD_B(CPedGameStateDataNode, m_on_mount);
			LOG_FIELD_B(CPedGameStateDataNode, m_has_custodian_or_arrest_flags);
			LOG_FIELD_C(CPedGameStateDataNode, pad_015A);
			LOG_FIELD_B(CPedGameStateDataNode, m_action_mode_enabled);
			LOG_FIELD_B(CPedGameStateDataNode, m_stealth_mode_enabled);
			LOG_FIELD_B(CPedGameStateDataNode, unk_015D);
			LOG_FIELD_B(CPedGameStateDataNode, unk_015E);
			LOG_FIELD_B(CPedGameStateDataNode, unk_015F);
			LOG_FIELD_B(CPedGameStateDataNode, unk_0160);
			LOG_FIELD_B(CPedGameStateDataNode, unk_0161);
			LOG_FIELD_B(CPedGameStateDataNode, unk_0162);
			LOG_FIELD_B(CPedGameStateDataNode, unk_0163);
			LOG_FIELD_B(CPedGameStateDataNode, unk_0164);
			LOG_FIELD_B(CPedGameStateDataNode, unk_0165);
			LOG_FIELD_B(CPedGameStateDataNode, unk_0166);
			LOG_FIELD_B(CPedGameStateDataNode, unk_0167);
			LOG_FIELD_B(CPedGameStateDataNode, unk_0168);
			LOG_FIELD_B(CPedGameStateDataNode, unk_0169);
			LOG_FIELD_B(CPedGameStateDataNode, unk_016A);
			LOG_FIELD_B(CPedGameStateDataNode, unk_016B);
			LOG_FIELD_B(CPedGameStateDataNode, unk_016C);
			LOG_FIELD_B(CPedGameStateDataNode, unk_016D);
			LOG_FIELD_B(CPedGameStateDataNode, unk_016E);
			LOG_FIELD_B(CPedGameStateDataNode, unk_016F);
			LOG_FIELD_B(CPedGameStateDataNode, unk_0170);
			LOG_FIELD_B(CPedGameStateDataNode, unk_0171);
			LOG_FIELD_B(CPedGameStateDataNode, unk_0172);
			break;
		case sync_node_id("CPedHealthDataNode"):
			LOG_FIELD(CPedHealthDataNode, unk_00C0);
			LOG_FIELD(CPedHealthDataNode, m_health);
			LOG_FIELD(CPedHealthDataNode, m_armor);
			LOG_FIELD(CPedHealthDataNode, unk_00CC);
			LOG_FIELD(CPedHealthDataNode, unk_00D0);
			LOG_FIELD_H(CPedHealthDataNode, m_weapon_damage_hash);
			LOG_FIELD(CPedHealthDataNode, m_hurt_end_time);
			LOG_FIELD_H(CPedHealthDataNode, m_weapon_damage_component);
			LOG_FIELD(CPedHealthDataNode, m_weapon_damage_entity);
			LOG_FIELD_B(CPedHealthDataNode, m_has_max_health);
			LOG_FIELD_B(CPedHealthDataNode, m_has_default_armor);
			LOG_FIELD_B(CPedHealthDataNode, unk_00E4);
			LOG_FIELD_B(CPedHealthDataNode, m_killed_with_headshot);
			LOG_FIELD_B(CPedHealthDataNode, m_killed_with_melee);
			LOG_FIELD_B(CPedHealthDataNode, m_hurt_started);
			LOG_FIELD_B(CPedHealthDataNode, unk_00E8);
			LOG_FIELD_B(CPedHealthDataNode, unk_00E9);
			break;
		case sync_node_id("CPedMovementDataNode"):
			LOG_FIELD_B(CPedMovementDataNode, m_has_desired_move_blend_ratio_x);
			LOG_FIELD_B(CPedMovementDataNode, m_has_desired_move_blend_ratio_y);
			LOG_FIELD_B(CPedMovementDataNode, unk_00C2);
			LOG_FIELD(CPedMovementDataNode, m_desired_move_blend_ratio_x);
			LOG_FIELD(CPedMovementDataNode, m_desired_move_blend_ratio_y);
			LOG_FIELD(CPedMovementDataNode, unk_00CC);
			LOG_FIELD(CPedMovementDataNode, m_desired_pitch);
			break;
		case sync_node_id("CPedOrientationDataNode"):
			LOG_FIELD_B(CPedOrientationDataNode, m_has_desired_heading_x);
			LOG_FIELD_B(CPedOrientationDataNode, m_has_desired_heading_y);
			LOG_FIELD(CPedOrientationDataNode, m_desired_heading_x);
			LOG_FIELD(CPedOrientationDataNode, m_desired_heading_y);
			break;
		case sync_node_id("CPedScriptCreationDataNode"):
			LOG_FIELD_B(CPedScriptCreationDataNode, m_stay_in_car_when_jacked);
			break;
		case sync_node_id("CPedTaskSpecificDataNode"):
			LOG_FIELD(CPedTaskSpecificDataNode, m_task_index);
			LOG_FIELD_APPLY(CPedTaskSpecificDataNode, m_task_type, get_task_type_string);
			LOG_FIELD(CPedTaskSpecificDataNode, m_buffer_size);
			break;
		case sync_node_id("CPhysicalAngVelocityDataNode"):
			LOG_FIELD(CPhysicalAngVelocityDataNode, m_ang_velocity_x);
			LOG_FIELD(CPhysicalAngVelocityDataNode, m_ang_velocity_y);
			LOG_FIELD(CPhysicalAngVelocityDataNode, m_ang_velocity_z);
			break;
		case sync_node_id("CPhysicalAttachDataNode"):
			LOG_FIELD_B(CPhysicalAttachDataNode, m_attached);
			LOG_FIELD_B(CPhysicalAttachDataNode, unk_00C1);
			LOG_FIELD(CPhysicalAttachDataNode, m_attached_to);
			LOG_FIELD_V3(CPhysicalAttachDataNode, m_offset);
			LOG_FIELD_V4(CPhysicalAttachDataNode, m_orientation);
			LOG_FIELD_V3(CPhysicalAttachDataNode, m_parent_offset);
			LOG_FIELD(CPhysicalAttachDataNode, m_other_attach_bone);
			LOG_FIELD(CPhysicalAttachDataNode, m_attach_bone);
			LOG_FIELD(CPhysicalAttachDataNode, m_attach_flags);
			LOG_FIELD_B(CPhysicalAttachDataNode, m_allow_initial_separation);
			LOG_FIELD(CPhysicalAttachDataNode, unk_010C);
			LOG_FIELD(CPhysicalAttachDataNode, unk_0110);
			LOG_FIELD_B(CPhysicalAttachDataNode, unk_0114);
			LOG_FIELD_B(CPhysicalAttachDataNode, unk_0115);
			LOG_FIELD_B(CPhysicalAttachDataNode, m_is_cargo_vehicle);
			break;
		case sync_node_id("CPhysicalHealthDataNode"):
			LOG_FIELD_B(CPhysicalHealthDataNode, unk_00C0);
			LOG_FIELD_B(CPhysicalHealthDataNode, m_has_max_health_changed);
			LOG_FIELD(CPhysicalHealthDataNode, m_max_health);
			LOG_FIELD(CPhysicalHealthDataNode, m_current_health);
			LOG_FIELD(CPhysicalHealthDataNode, m_weapon_damage_entity);
			LOG_FIELD_H(CPhysicalHealthDataNode, m_weapon_damage_hash);
			LOG_FIELD(CPhysicalHealthDataNode, unk_00D8);
			break;
		case sync_node_id("CPhysicalMigrationDataNode"):
			LOG_FIELD_B(CPhysicalMigrationDataNode, m_unk);
			//
			break;
		case sync_node_id("CPhysicalScriptMigrationDataNode"):
			LOG_FIELD_B(CPhysicalScriptMigrationDataNode, m_has_data);
			LOG_FIELD(CPhysicalScriptMigrationDataNode, m_script_participants);
			LOG_FIELD(CPhysicalScriptMigrationDataNode, m_host_token);
			break;
		case sync_node_id("CPhysicalVelocityDataNode"):
			LOG_FIELD(CPhysicalVelocityDataNode, m_velocity_x);
			LOG_FIELD(CPhysicalVelocityDataNode, m_velocity_y);
			LOG_FIELD(CPhysicalVelocityDataNode, m_velocity_z);
			break;
		case sync_node_id("CPickupCreationDataNode"):
			LOG_FIELD_B(CPickupCreationDataNode, m_has_placement);
			LOG_FIELD_H(CPickupCreationDataNode, m_pickup_hash);
			LOG_FIELD(CPickupCreationDataNode, m_amount);
			LOG_FIELD_H(CPickupCreationDataNode, m_custom_model);
			LOG_FIELD(CPickupCreationDataNode, m_life_time);
			LOG_FIELD(CPickupCreationDataNode, m_num_weapon_components);
			if (((CPickupCreationDataNode*)node)->m_num_weapon_components <= 12)
			{
				for (int i = 0; i < ((CPickupCreationDataNode*)node)->m_num_weapon_components; i++)
				{
					LOG_FIELD_H(CPickupCreationDataNode, m_weapon_component[i]);
				}
			}
			LOG_FIELD(CPickupCreationDataNode, m_tint_index);
			LOG_FIELD_B(CPickupCreationDataNode, m_player_gift);
			LOG_FIELD_B(CPickupCreationDataNode, unk_015D);
			LOG_FIELD(CPickupCreationDataNode, unk_0164);
			LOG_FIELD_B(CPickupCreationDataNode, unk_0168);
			break;
		case sync_node_id("CPickupPlacementCreationDataNode"):
			LOG_FIELD_B(CPickupPlacementCreationDataNode, m_has_pickup_data);
			LOG_FIELD_V3(CPickupPlacementCreationDataNode, m_pickup_pos);
			LOG_FIELD_V4(CPickupPlacementCreationDataNode, m_pickup_orientation);
			LOG_FIELD_H(CPickupPlacementCreationDataNode, m_pickup_type);
			LOG_FIELD(CPickupPlacementCreationDataNode, m_pickup_flags);
			LOG_FIELD(CPickupPlacementCreationDataNode, m_amount);
			LOG_FIELD_H(CPickupPlacementCreationDataNode, m_custom_model);
			LOG_FIELD(CPickupPlacementCreationDataNode, m_custom_regeneration_time);
			LOG_FIELD(CPickupPlacementCreationDataNode, m_team_permits);
			break;
		case sync_node_id("CPlayerCameraDataNode"):
			LOG_FIELD(CPlayerCameraDataNode, m_free_cam_pos_x);
			LOG_FIELD(CPlayerCameraDataNode, m_free_cam_pos_y);
			LOG_FIELD(CPlayerCameraDataNode, m_free_cam_pos_z);
			LOG_FIELD(CPlayerCameraDataNode, m_lock_on_target_offset_x);
			LOG_FIELD(CPlayerCameraDataNode, m_lock_on_target_offset_y);
			LOG_FIELD(CPlayerCameraDataNode, m_camera_x);
			LOG_FIELD(CPlayerCameraDataNode, m_camera_z);
			LOG_FIELD(CPlayerCameraDataNode, m_free_aim_locked_on_target);
			LOG_FIELD_B(CPlayerCameraDataNode, m_free_cam);
			LOG_FIELD_B(CPlayerCameraDataNode, m_has_position_offset);
			LOG_FIELD_B(CPlayerCameraDataNode, m_is_long_range_target);
			break;
		case sync_node_id("CPlayerCreationDataNode"):
			LOG_FIELD_H(CPlayerCreationDataNode, m_model);
			LOG_FIELD(CPlayerCreationDataNode, m_num_scars);
			LOG_FIELD(CPlayerCreationDataNode, unk_0188);
			LOG_FIELD_B(CPlayerCreationDataNode, unk_0240);
			break;
		case sync_node_id("CPlayerExtendedGameStateNode"):
			LOG_FIELD(CPlayerExtendedGameStateNode, waypoint_x);
			LOG_FIELD(CPlayerExtendedGameStateNode, waypoint_y);
			LOG_FIELD_B(CPlayerExtendedGameStateNode, unk1);
			LOG_FIELD_B(CPlayerExtendedGameStateNode, unk2);
			LOG_FIELD_B(CPlayerExtendedGameStateNode, unk3);
			LOG_FIELD_B(CPlayerExtendedGameStateNode, unk4);
			LOG_FIELD_B(CPlayerExtendedGameStateNode, unk5);
			LOG_FIELD_B(CPlayerExtendedGameStateNode, has_waypoint_data);
			LOG_FIELD_B(CPlayerExtendedGameStateNode, is_waypoint_set);
			break;
		case sync_node_id("CPlayerGameStateDataNode"):
			LOG_FIELD(CPlayerGameStateDataNode, m_player_state);
			LOG_FIELD_B(CPlayerGameStateDataNode, m_controls_disabled_by_script);
			LOG_FIELD_B(CPlayerGameStateDataNode, m_is_max_armor_and_health_default);
			LOG_FIELD_B(CPlayerGameStateDataNode, unk_000C6);
			LOG_FIELD_B(CPlayerGameStateDataNode, m_is_spectating);
			LOG_FIELD_B(CPlayerGameStateDataNode, m_is_antagonistic_to_another_player);
			LOG_FIELD_B(CPlayerGameStateDataNode, m_never_target);
			LOG_FIELD_B(CPlayerGameStateDataNode, m_use_kinematic_physics);
			LOG_FIELD_B(CPlayerGameStateDataNode, m_has_tutorial_data);
			LOG_FIELD_B(CPlayerGameStateDataNode, m_pending_tutorial_change);
			LOG_FIELD_B(CPlayerGameStateDataNode, unk_00CD);
			LOG_FIELD_B(CPlayerGameStateDataNode, m_respawning);
			LOG_FIELD_B(CPlayerGameStateDataNode, m_will_jack_any_player);
			LOG_FIELD_B(CPlayerGameStateDataNode, m_will_jack_wanted_players);
			LOG_FIELD_B(CPlayerGameStateDataNode, m_dont_drag_from_car);
			LOG_FIELD_B(CPlayerGameStateDataNode, m_random_peds_flee);
			LOG_FIELD_B(CPlayerGameStateDataNode, m_every_ped_back_away);
			LOG_FIELD_B(CPlayerGameStateDataNode, m_has_microphone);
			LOG_FIELD_B(CPlayerGameStateDataNode, m_is_invincible);
			LOG_FIELD_B(CPlayerGameStateDataNode, unk_00D6);
			LOG_FIELD_B(CPlayerGameStateDataNode, unk_00D7);
			LOG_FIELD_B(CPlayerGameStateDataNode, m_seatbelt);
			LOG_FIELD_B(CPlayerGameStateDataNode, unk_00D9);
			LOG_FIELD_B(CPlayerGameStateDataNode, m_bullet_proof);
			LOG_FIELD_B(CPlayerGameStateDataNode, m_fire_proof);
			LOG_FIELD_B(CPlayerGameStateDataNode, m_explosion_proof);
			LOG_FIELD_B(CPlayerGameStateDataNode, m_collision_proof);
			LOG_FIELD_B(CPlayerGameStateDataNode, m_melee_proof);
			LOG_FIELD_B(CPlayerGameStateDataNode, m_water_proof);
			LOG_FIELD_B(CPlayerGameStateDataNode, m_steam_proof);
			LOG_FIELD_B(CPlayerGameStateDataNode, unk_00E1);
			LOG_FIELD_B(CPlayerGameStateDataNode, unk_00E2);
			LOG_FIELD_B(CPlayerGameStateDataNode, unk_00E3);
			LOG_FIELD_B(CPlayerGameStateDataNode, unk_00E4);
			LOG_FIELD_B(CPlayerGameStateDataNode, unk_00E5);
			LOG_FIELD_B(CPlayerGameStateDataNode, unk_00E6);
			LOG_FIELD_B(CPlayerGameStateDataNode, unk_00E7);
			LOG_FIELD_B(CPlayerGameStateDataNode, unk_00E8);
			LOG_FIELD_B(CPlayerGameStateDataNode, unk_00E9);
			LOG_FIELD_B(CPlayerGameStateDataNode, unk_00EA);
			LOG_FIELD_B(CPlayerGameStateDataNode, unk_00EB);
			LOG_FIELD_B(CPlayerGameStateDataNode, unk_00EC);
			LOG_FIELD_B(CPlayerGameStateDataNode, unk_00ED);
			LOG_FIELD_B(CPlayerGameStateDataNode, unk_00EE);
			LOG_FIELD_B(CPlayerGameStateDataNode, unk_00EF);
			LOG_FIELD_B(CPlayerGameStateDataNode, unk_00F0);
			LOG_FIELD_B(CPlayerGameStateDataNode, unk_00F1);
			LOG_FIELD_B(CPlayerGameStateDataNode, unk_00F2);
			LOG_FIELD_B(CPlayerGameStateDataNode, unk_00F3);
			LOG_FIELD_B(CPlayerGameStateDataNode, unk_00F4);
			LOG_FIELD_B(CPlayerGameStateDataNode, unk_00F5);
			LOG_FIELD_B(CPlayerGameStateDataNode, unk_00F6);
			LOG_FIELD_B(CPlayerGameStateDataNode, unk_00F7);
			LOG_FIELD_B(CPlayerGameStateDataNode, unk_00F8);
			LOG_FIELD_B(CPlayerGameStateDataNode, unk_00F9);
			LOG_FIELD_B(CPlayerGameStateDataNode, unk_00FA);
			LOG_FIELD_B(CPlayerGameStateDataNode, unk_00FB);
			LOG_FIELD(CPlayerGameStateDataNode, unk_00FC);
			LOG_FIELD(CPlayerGameStateDataNode, m_mobile_ring_state);
			LOG_FIELD(CPlayerGameStateDataNode, m_player_team);
			LOG_FIELD(CPlayerGameStateDataNode, m_air_drag_multiplier);
			LOG_FIELD(CPlayerGameStateDataNode, m_max_health);
			LOG_FIELD(CPlayerGameStateDataNode, m_max_armor);
			LOG_FIELD(CPlayerGameStateDataNode, m_jack_speed);
			LOG_FIELD(CPlayerGameStateDataNode, m_player_is_targetable_by_team);
			LOG_FIELD(CPlayerGameStateDataNode, m_override_receive_chat);
			LOG_FIELD(CPlayerGameStateDataNode, m_override_send_chat);
			LOG_FIELD_B(CPlayerGameStateDataNode, unk_0124);
			LOG_FIELD_B(CPlayerGameStateDataNode, unk_0125);
			LOG_FIELD_B(CPlayerGameStateDataNode, unk_0126);
			LOG_FIELD_B(CPlayerGameStateDataNode, unk_0127);
			LOG_FIELD(CPlayerGameStateDataNode, m_spectating_net_id);
			LOG_FIELD_C(CPlayerGameStateDataNode, m_antagonistic_to_player_id);
			LOG_FIELD_C(CPlayerGameStateDataNode, m_tutorial_index);
			LOG_FIELD_C(CPlayerGameStateDataNode, m_tutorial_instance_id);
			LOG_FIELD(CPlayerGameStateDataNode, m_microphone_volume);
			LOG_FIELD(CPlayerGameStateDataNode, m_voice_channel);
			LOG_FIELD_B(CPlayerGameStateDataNode, m_is_overriding_voice_proximity);
			LOG_FIELD(CPlayerGameStateDataNode, m_voice_proximity_x);
			LOG_FIELD(CPlayerGameStateDataNode, m_voice_proximity_x);
			LOG_FIELD(CPlayerGameStateDataNode, m_voice_proximity_x);
			LOG_FIELD(CPlayerGameStateDataNode, m_voice_proximity_radius_maybe);
			LOG_FIELD(CPlayerGameStateDataNode, unk_0150);
			LOG_FIELD(CPlayerGameStateDataNode, m_vehicle_weapon_index);
			LOG_FIELD_B(CPlayerGameStateDataNode, m_has_vehicle_weapon_index);
			LOG_FIELD(CPlayerGameStateDataNode, m_decor_count);
			LOG_FIELD_B(CPlayerGameStateDataNode, m_friendly_fire_allowed);
			LOG_FIELD_B(CPlayerGameStateDataNode, unk_0185);
			LOG_FIELD_C(CPlayerGameStateDataNode, m_current_garage_instance_index);
			LOG_FIELD_C(CPlayerGameStateDataNode, m_current_property_id);
			LOG_FIELD_C(CPlayerGameStateDataNode, unk_0188);
			LOG_FIELD_C(CPlayerGameStateDataNode, unk_0189);
			LOG_FIELD_B(CPlayerGameStateDataNode, m_battle_aware);
			LOG_FIELD_B(CPlayerGameStateDataNode, m_vehicle_jump_down);
			LOG_FIELD(CPlayerGameStateDataNode, m_weapon_defence_modifier);
			LOG_FIELD(CPlayerGameStateDataNode, m_weapon_defence_modifier_2);
			LOG_FIELD_B(CPlayerGameStateDataNode, m_is_overriding_population_control_sphere);
			LOG_FIELD(CPlayerGameStateDataNode, m_population_control_sphere_x);
			LOG_FIELD(CPlayerGameStateDataNode, m_population_control_sphere_y);
			LOG_FIELD(CPlayerGameStateDataNode, m_population_control_sphere_z);
			LOG_FIELD(CPlayerGameStateDataNode, unk_01AC);
			LOG_FIELD(CPlayerGameStateDataNode, unk_01AE);
			LOG_FIELD(CPlayerGameStateDataNode, unk_01B0);
			LOG_FIELD_B(CPlayerGameStateDataNode, pad_01B2);
			LOG_FIELD_B(CPlayerGameStateDataNode, unk_01B3);
			LOG_FIELD_B(CPlayerGameStateDataNode, m_no_collision);
			LOG_FIELD_B(CPlayerGameStateDataNode, unk_01B5);
			LOG_FIELD_B(CPlayerGameStateDataNode, unk_01B6);
			LOG_FIELD_B(CPlayerGameStateDataNode, m_super_jump);
			LOG_FIELD_B(CPlayerGameStateDataNode, unk_01B8);
			LOG_FIELD_B(CPlayerGameStateDataNode, unk_01B9);
			LOG_FIELD(CPlayerGameStateDataNode, unk_01BA);
			LOG_FIELD(CPlayerGameStateDataNode, unk_01BC);
			LOG_FIELD(CPlayerGameStateDataNode, unk_01C0);
			LOG_FIELD(CPlayerGameStateDataNode, m_weapon_damage_modifier);
			LOG_FIELD(CPlayerGameStateDataNode, m_melee_weapon_damage_modifier);
			LOG_FIELD(CPlayerGameStateDataNode, unk_01CC);
			LOG_FIELD_B(CPlayerGameStateDataNode, unk_01D0);
			LOG_FIELD(CPlayerGameStateDataNode, unk_01E0);
			LOG_FIELD(CPlayerGameStateDataNode, unk_01E4);
			LOG_FIELD(CPlayerGameStateDataNode, unk_01E8);
			LOG_FIELD(CPlayerGameStateDataNode, unk_01EC);
			LOG_FIELD_C(CPlayerGameStateDataNode, unk_01F0);
			LOG_FIELD_C(CPlayerGameStateDataNode, unk_01F1);
			LOG_FIELD_B(CPlayerGameStateDataNode, unk_01F2);
			LOG_FIELD_C(CPlayerGameStateDataNode, unk_01F3);
			LOG_FIELD_B(CPlayerGameStateDataNode, unk_01F4);
			LOG_FIELD_B(CPlayerGameStateDataNode, unk_01F5);
			break;
		case sync_node_id("CPlayerSectorPosNode"):
			LOG_FIELD_V3(CPlayerSectorPosNode, m_sector_pos);
			LOG_FIELD_B(CPlayerSectorPosNode, m_is_standing_on_entity);
			LOG_FIELD_B(CPlayerSectorPosNode, unk_00CD);
			LOG_FIELD_B(CPlayerSectorPosNode, unk_00CE);
			LOG_FIELD(CPlayerSectorPosNode, m_entity_standing_on);
			LOG_FIELD_V3(CPlayerSectorPosNode, m_standing_on_entity_offset);
			LOG_FIELD(CPlayerSectorPosNode, m_stealth_noise);
			break;
		case sync_node_id("CGlobalFlagsDataNode"):
			LOG_FIELD(CGlobalFlagsDataNode, m_global_flags);
			LOG_FIELD(CGlobalFlagsDataNode, m_ownership_token);
			break;
		case sync_node_id("CMigrationDataNode"):
			LOG_FIELD(CMigrationDataNode, m_cloned_state);
			LOG_FIELD(CMigrationDataNode, m_cloned_players_that_left);
			LOG_FIELD(CMigrationDataNode, m_unsynced_nodes);
			break;
		case sync_node_id("CSectorDataNode"):
			LOG_FIELD(CSectorDataNode, m_pos_x);
			LOG_FIELD(CSectorDataNode, m_pos_y);
			LOG_FIELD(CSectorDataNode, m_pos_z);
			break;
		case sync_node_id("CSectorPositionDataNode"):
			LOG_FIELD(CSectorPositionDataNode, m_sector_pos_x);
			LOG_FIELD(CSectorPositionDataNode, m_sector_pos_y);
			LOG_FIELD(CSectorPositionDataNode, m_sector_pos_z);
			break;
		case sync_node_id("CVehicleGadgetDataNode"):
			LOG_FIELD_B(CVehicleGadgetDataNode, m_has_parent_offset);
			LOG_FIELD(CVehicleGadgetDataNode, m_parent_offset_x);
			LOG_FIELD(CVehicleGadgetDataNode, m_parent_offset_y);
			LOG_FIELD(CVehicleGadgetDataNode, m_parent_offset_z);
			LOG_FIELD(CVehicleGadgetDataNode, m_parent_offset_w);
			LOG_FIELD(CVehicleGadgetDataNode, m_gadget_count);
			if (((CVehicleGadgetDataNode*)node)->m_gadget_count <= 2)
			{
				for (int i = 0; i < ((CVehicleGadgetDataNode*)node)->m_gadget_count; i++)
				{
					LOG_FIELD(CVehicleGadgetDataNode, m_gadget_data[i].m_gadget_type);
				}
			}
			break;
		case sync_node_id("CVehicleProximityMigrationDataNode"):
			LOG_FIELD(CVehicleProximityMigrationDataNode, m_max_occupants);
			LOG_FIELD_B(CVehicleProximityMigrationDataNode, m_override_position);
			LOG_FIELD_V3(CVehicleProximityMigrationDataNode, m_position);
			LOG_FIELD_V3(CVehicleProximityMigrationDataNode, m_velocity);
			break;
		case sync_node_id("CPlayerGamerDataNode"):
			LOG_FIELD(CPlayerGamerDataNode, m_clan_data.m_clan_member_id);
			LOG_FIELD(CPlayerGamerDataNode, m_clan_data.m_clan_id);
			LOG_FIELD(CPlayerGamerDataNode, m_clan_data.m_clan_color);
			LOG_FIELD(CPlayerGamerDataNode, m_clan_data.m_clan_member_count);
			LOG_FIELD(CPlayerGamerDataNode, m_clan_data.m_clan_created_time);
			LOG_FIELD_B(CPlayerGamerDataNode, m_clan_data.m_is_system_clan);
			LOG_FIELD_B(CPlayerGamerDataNode, m_clan_data.m_is_clan_open);
			LOG_FIELD(CPlayerGamerDataNode, m_clan_data.m_clan_name);
			LOG_FIELD(CPlayerGamerDataNode, m_clan_data.m_clan_tag);
			LOG_FIELD(CPlayerGamerDataNode, m_clan_data.m_clan_motto);
			LOG_FIELD(CPlayerGamerDataNode, m_clan_data.m_clan_id_2);
			LOG_FIELD(CPlayerGamerDataNode, m_clan_data.m_clan_rank_name);
			LOG_FIELD(CPlayerGamerDataNode, m_clan_data.m_clan_rank_order);
			LOG_FIELD(CPlayerGamerDataNode, m_clan_data.m_clan_rank_flags);
			LOG_FIELD_B(CPlayerGamerDataNode, m_need_crew_rank_sysflags);
			LOG_FIELD_B(CPlayerGamerDataNode, m_need_crew_rank_title);
			LOG_FIELD(CPlayerGamerDataNode, m_crew_rank_title);
			LOG_FIELD_B(CPlayerGamerDataNode, m_has_started_transition);
			LOG_FIELD_B(CPlayerGamerDataNode, m_has_transition_info);
			LOG_FIELD(CPlayerGamerDataNode, m_transition_info_buffer);
			LOG_FIELD(CPlayerGamerDataNode, m_player_privilege_flags);
			LOG_FIELD(CPlayerGamerDataNode, m_matchmaking_group);
			LOG_FIELD_B(CPlayerGamerDataNode, m_need_mute_data);
			LOG_FIELD(CPlayerGamerDataNode, m_mute_count);
			LOG_FIELD(CPlayerGamerDataNode, m_mute_talkers_count);
			LOG_FIELD(CPlayerGamerDataNode, m_unk);
			LOG_FIELD(CPlayerGamerDataNode, m_account_id);
			break;
		case sync_node_id("CPhysicalGameStateDataNode"):
			LOG_FIELD_B(CPhysicalGameStateDataNode, m_is_visible);
			LOG_FIELD_B(CPhysicalGameStateDataNode, m_flag2);
			LOG_FIELD_B(CPhysicalGameStateDataNode, m_flag3);
			LOG_FIELD_B(CPhysicalGameStateDataNode, m_flag4);
			LOG_FIELD(CPhysicalGameStateDataNode, m_val1);
			LOG_FIELD(CPhysicalGameStateDataNode, m_unk204);
			LOG_FIELD_B(CPhysicalGameStateDataNode, m_unk5);
			break;
		case sync_node_id("CPhysicalScriptGameStateDataNode"):
			LOG_FIELD_B(CPhysicalScriptGameStateDataNode, m_godmode);
			LOG_FIELD_B(CPhysicalScriptGameStateDataNode, m_dont_load_collision);
			LOG_FIELD_B(CPhysicalScriptGameStateDataNode, m_freeze_on_collision_load);
			LOG_FIELD_B(CPhysicalScriptGameStateDataNode, m_only_damaged_by_player);
			LOG_FIELD_B(CPhysicalScriptGameStateDataNode, m_bullet_proof);
			LOG_FIELD_B(CPhysicalScriptGameStateDataNode, m_fire_proof);
			LOG_FIELD_B(CPhysicalScriptGameStateDataNode, m_explosion_proof);
			LOG_FIELD_B(CPhysicalScriptGameStateDataNode, m_collision_proof);
			LOG_FIELD_B(CPhysicalScriptGameStateDataNode, m_melee_proof);
			LOG_FIELD_B(CPhysicalScriptGameStateDataNode, m_cannot_be_damaged_by_relationship_group);
			LOG_FIELD_B(CPhysicalScriptGameStateDataNode, m_can_only_be_damaged_by_relationship_group);
			LOG_FIELD_B(CPhysicalScriptGameStateDataNode, m_smoke_proof);
			LOG_FIELD_B(CPhysicalScriptGameStateDataNode, m_steam_proof);
			LOG_FIELD_B(CPhysicalScriptGameStateDataNode, m_can_only_be_damaged_by_participants);
			LOG_FIELD_B(CPhysicalScriptGameStateDataNode, m_dont_reset_proofs_on_cleanup_mission);
			LOG_FIELD_B(CPhysicalScriptGameStateDataNode, m_no_reassign);
			LOG_FIELD_B(CPhysicalScriptGameStateDataNode, m_pass_control_in_tutorial);
			LOG_FIELD_B(CPhysicalScriptGameStateDataNode, m_visible_in_cutscene);
			LOG_FIELD_B(CPhysicalScriptGameStateDataNode, m_visible_in_cutscene_remain_hack);
			LOG_FIELD_B(CPhysicalScriptGameStateDataNode, m_pickup_by_cargobob_disabled);
			LOG_FIELD_B(CPhysicalScriptGameStateDataNode, m_godmode);
			LOG_FIELD(CPhysicalScriptGameStateDataNode, m_relationship_group);
			LOG_FIELD(CPhysicalScriptGameStateDataNode, m_always_cloned_for_players);
			LOG_FIELD_B(CPhysicalScriptGameStateDataNode, m_trigger_damage_event_for_zero_damage);
			LOG_FIELD(CPhysicalScriptGameStateDataNode, m_max_speed);
			break;
		case sync_node_id("CPedTaskTreeDataNode"):
			LOG_FIELD(CPedTaskTreeDataNode, m_task_bitset);
			for (int i = 0; i < 8; i++)
			{
				if (((CPedTaskTreeDataNode*)node)->m_task_bitset & (1 << i))
				{
					LOG_FIELD_APPLY(CPedTaskTreeDataNode, m_tasks[i].m_task_type, get_task_type_string);
					LOG_FIELD(CPedTaskTreeDataNode, m_tasks[i].m_priority);
					LOG_FIELD(CPedTaskTreeDataNode, m_tasks[i].m_tree_depth);
					LOG_FIELD(CPedTaskTreeDataNode, m_tasks[i].m_sequence_id);
					LOG_FIELD_B(CPedTaskTreeDataNode, m_tasks[i].m_active);
				}
			}
			LOG_FIELD(CPedTaskTreeDataNode, m_script_command);
			LOG_FIELD(CPedTaskTreeDataNode, m_script_command_stage);
			break;
		case sync_node_id("CPedTaskSequenceDataNode"):
			LOG_FIELD_B(CPedTaskSequenceDataNode, m_has_sequence);
			LOG_FIELD(CPedTaskSequenceDataNode, m_sequence_resource_id);
			LOG_FIELD(CPedTaskSequenceDataNode, m_num_tasks_in_sequence);
			for (int i = 0; i < ((CPedTaskSequenceDataNode*)node)->m_num_tasks_in_sequence; i++)
			{
				LOG_FIELD_APPLY(CPedTaskSequenceDataNode, m_task_data[i].m_task_type, get_task_type_string);
				LOG_FIELD(CPedTaskSequenceDataNode, m_task_data[i].m_task_data_size);
			}
			LOG_FIELD(CPedTaskSequenceDataNode, m_unk);
			break;
		case sync_node_id("CVehicleTaskDataNode"):
			LOG_FIELD_APPLY(CVehicleTaskDataNode, m_task_type, get_task_type_string);
			LOG_FIELD(CVehicleTaskDataNode, m_task_data_size);
			break;
		case sync_node_id("CPlayerWantedAndLOSDataNode"):
			LOG_FIELD_V3(CPlayerWantedAndLOSDataNode, m_wanted_position);
			LOG_FIELD(CPlayerWantedAndLOSDataNode, m_time_in_prev_pursuit);
			LOG_FIELD_V3(CPlayerWantedAndLOSDataNode, m_unk_position);
			LOG_FIELD(CPlayerWantedAndLOSDataNode, m_time_in_pursuit);
			LOG_FIELD(CPlayerWantedAndLOSDataNode, m_wanted_level);
			LOG_FIELD(CPlayerWantedAndLOSDataNode, m_unk_wanted_level);
			LOG_FIELD(CPlayerWantedAndLOSDataNode, m_current_time);
			LOG_FIELD(CPlayerWantedAndLOSDataNode, m_unk_player_bitset);
			LOG_FIELD(CPlayerWantedAndLOSDataNode, m_pursuit_start_time);
			LOG_FIELD_C(CPlayerWantedAndLOSDataNode, m_fake_wanted_level);
			LOG_FIELD_B(CPlayerWantedAndLOSDataNode, m_cops_cant_see_player);
			LOG_FIELD_B(CPlayerWantedAndLOSDataNode, m_is_evading);
			LOG_FIELD_B(CPlayerWantedAndLOSDataNode, m_pending_wanted_level);
			LOG_FIELD_B(CPlayerWantedAndLOSDataNode, m_unk3);
			LOG_FIELD_C(CPlayerWantedAndLOSDataNode, m_unk_player_index);
			break;
		}
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
			const auto addr     = (uintptr_t)node;
			auto sender_plyr    = g_player_service->get_by_id(sender->m_player_id);
			const auto& node_id = sync_node_finder::find((eNetObjType)object->m_object_type, addr);

			if ((((CProjectBaseSyncDataNode*)node)->flags & 1) == 0)
				return false;

			if (sender_plyr && sender_plyr->log_clones)
				log_node(node_id, sender_plyr, (CProjectBaseSyncDataNode*)node, object);

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

				if (attach_node->m_attached
				    && is_attachment_infinite(object,
				        attach_node->m_attached_to,
				        attach_node->m_attach_bone,
				        attach_node->m_other_attach_bone))
				{
					notify::crash_blocked(sender, "infinite physical attachment");
					return true;
				}

				if (attach_node->m_attached && object && object->m_object_type == (int16_t)eNetObjType::NET_OBJ_TYPE_TRAILER)
				{
					if (auto net_obj =
					        g_pointers->m_gta.m_get_net_object(*g_pointers->m_gta.m_network_object_mgr, attach_node->m_attached_to, false))
					{
						if (auto entity = net_obj->GetGameObject())
						{
							if (entity->m_entity_type != 3)
							{
								notify::crash_blocked(sender, "invalid attachment");
								return true;
							}
						}
					}
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
				if (attach_node->m_attached
				    && is_attachment_infinite(object,
				        attach_node->m_attached_to,
				        attach_node->m_attachment_bone,
				        attach_node->m_attachment_bone))
				{
					if (auto game_object = (CPed*)object->GetGameObject())
						if (!game_object->m_player_info)
							notify::crash_blocked(sender, "infinite ped attachment"); // parachute false positives

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
				check_player_model(sender_plyr, player_appearance_node->m_model_hash);
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
				check_player_model(sender_plyr, player_creation_node->m_model);
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
				if (game_state_node->m_is_overriding_population_control_sphere
				    && !is_sane_override_pos(game_state_node->m_population_control_sphere_x,
				        game_state_node->m_population_control_sphere_y,
				        game_state_node->m_population_control_sphere_z)
				    && gta_util::get_network()->m_game_session_ptr->is_host())
				{
					notify::crash_blocked(sender, "invalid sector position (player game state node)");
					return true;
				}

				if (sender_plyr)
				{
					if (game_state_node->m_is_spectating)
					{
						if (!sender_plyr->get_ped())
							break;

						if (sender_plyr->get_ped()->m_health <= 0.0f) // you spectate the player that killed you
							break;

						auto net_obj =
						    g_pointers->m_gta.m_get_net_object(*g_pointers->m_gta.m_network_object_mgr, game_state_node->m_spectating_net_id, false);

						if (!net_obj)
							break;

						auto entity = net_obj->GetGameObject();

						if (!entity || entity->m_entity_type != 4)
							break;

						auto player_info = ((CPed*)entity)->m_player_info;

						if (!player_info)
							break;

						player_ptr target = nullptr;

						if (g_local_player && (CPed*)entity == g_local_player)
						{
							target = g_player_service->get_self();
						}
						else
						{
							for (auto p : g_player_service->players())
								if (p.second->get_player_info() == player_info)
									target = p.second;
						}

						if (!target || !target->is_valid())
							break;

						if (target->id() != sender_plyr->spectating_player)
						{
							if (target->id() == self::id)
								g.reactions.spectate.process(sender_plyr);
							else
								g.reactions.spectate_others.process(sender_plyr, target);

							sender_plyr->spectating_player = target->id();
						}
					}
					else
					{
						sender_plyr->spectating_player = -1;
					}
				}

				break;
			}
			case sync_node_id("CTrainGameStateDataNode"):
			{
				const auto train_node = (CTrainGameStateDataNode*)(node);
				if (train_node->m_track_id < 0 || train_node->m_track_id >= 27)
				{
					//notify::crash_blocked(sender, "out of bounds train track index");
					//LOG(INFO) << train_node->m_track_id;
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
			case sync_node_id("CPlayerGamerDataNode"):
			{
				const auto gamer_node = (CPlayerGamerDataNode*)(node);

				if (sender_plyr)
				{
					if (gamer_node->m_clan_data.m_clan_id == 123456 && gamer_node->m_clan_data.m_clan_id_2 == 123456)
					{
						session::add_infraction(sender_plyr, Infraction::SPOOFED_DATA);
					}
					else if (gamer_node->m_clan_data.m_clan_id > 0 && gamer_node->m_clan_data.m_clan_id_2 > 0)
					{
						if (!is_valid_clan_tag(gamer_node->m_clan_data.m_clan_tag, gamer_node->m_clan_data.m_is_system_clan))
						{
							session::add_infraction(sender_plyr, Infraction::SPOOFED_DATA);
						}

						if (gamer_node->m_clan_data.m_is_system_clan
						    && (!gamer_node->m_clan_data.m_is_clan_open || gamer_node->m_clan_data.m_clan_member_count == 0))
						{
							session::add_infraction(sender_plyr, Infraction::SPOOFED_DATA);
						}
					}
				}
				break;
			}
			case sync_node_id("CPedGameStateDataNode"):
			{
				const auto game_state_node = (CPedGameStateDataNode*)(node);
				if (game_state_node->m_on_mount)
				{
					notify::crash_blocked(sender, "mount flag");
					return true;
				}
				for (int i = 0; i < game_state_node->m_num_equiped_gadgets; i++)
				{
					if (game_state_node->m_gadget_hash[i] != RAGE_JOAAT("gadget_parachute") && game_state_node->m_gadget_hash[i] != RAGE_JOAAT("gadget_nightvision"))
					{
						notify::crash_blocked(sender, "invalid gadget");
						return true;
					}
				}
				break;
			}
			case sync_node_id("CVehicleControlDataNode"):
			{
				const auto control_node = (CVehicleControlDataNode*)(node);
				if (control_node->m_is_submarine_car)
				{
					if (auto vehicle = (CVehicle*)object->GetGameObject())
					{
						if (auto model_info = vehicle->m_model_info)
						{
							if (model_info->m_hash != RAGE_JOAAT("stromberg") && model_info->m_hash != RAGE_JOAAT("toreador"))
							{
								notify::crash_blocked(sender, "submarine car");
								return true;
							}
						}
					}
				}

				break;
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