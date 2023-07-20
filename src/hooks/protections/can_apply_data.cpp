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
#include "netsync/nodes/player/CPlayerGamerDataNode.hpp"
#include "netsync/nodes/proximity_migrateable/CSectorDataNode.hpp"
#include "netsync/nodes/train/CTrainGameStateDataNode.hpp"
#include "netsync/nodes/vehicle/CVehicleCreationDataNode.hpp"
#include "netsync/nodes/vehicle/CVehicleGadgetDataNode.hpp"
#include "netsync/nodes/vehicle/CVehicleProximityMigrationDataNode.hpp"
#include "network/CNetGamePlayer.hpp"
#include "network/netObject.hpp"
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

	void log_node(sync_node_id node_id, player_ptr sender, CProjectBaseSyncDataNode* node)
	{
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
			const auto vft   = *(uintptr_t*)node;
			auto sender_plyr = g_player_service->get_by_id(sender->m_player_id);

			for (const sync_node_id node_id : sync_node_finder::find((eNetObjType)object->m_object_type, vft))
			{
				if ((((CProjectBaseSyncDataNode*)node)->flags & 1) == 0)
					continue;

				if (sender_plyr && sender_plyr->log_clones)
					log_node(node_id, sender_plyr, (CProjectBaseSyncDataNode*)node);

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
						notify::crash_blocked(sender, "infinite ped attachment");
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

							auto net_obj = g_pointers->m_gta.m_get_net_object(*g_pointers->m_gta.m_network_object_mgr,
							    game_state_node->m_spectating_net_id,
							    false);

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
						if (gamer_node->m_clan_data.m_clan_id > 0 && gamer_node->m_clan_data.m_clan_id_2 > 0)
						{
							auto len = strlen(gamer_node->m_clan_data.m_clan_tag);

							if (len <= 2)
							{
								session::add_infraction(sender_plyr, Infraction::SPOOFED_DATA);
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