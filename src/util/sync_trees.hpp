#pragma once
#include "gta/enums.hpp"
#include "pointers.hpp"

namespace big
{
	struct sync_node_id
	{
		Hash id;
		const char* name;

		constexpr sync_node_id()
		{
			id   = 0;
			name = "INVALID NODE ID!";
		}

		template<size_t N>
		constexpr sync_node_id(char const (&pp)[N])
		{
			id   = rage::constexpr_joaat(pp);
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
		sync_node_vft_to_ids global_node_identifier;

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
		static inline bool inited = false;

	public:
		static const sync_node_id& find(eNetObjType obj_type, uintptr_t addr)
		{
			if (!is_initialized()) [[unlikely]]
				init();

			return finder.sync_trees_sync_node_addr_to_ids[(int)obj_type][addr];
		}

		static const sync_node_id& find(uintptr_t addr)
		{
			if (!is_initialized()) [[unlikely]]
				init();

			return finder.global_node_identifier[addr];
		}

		static sync_node_vft_to_ids& get_object_nodes(eNetObjType obj_type)
		{
			return finder.sync_trees_sync_node_addr_to_ids[(int)obj_type];
		}

		static bool is_initialized()
		{
			return inited;
		}

		static void init()
		{
			for (int i = (int)eNetObjType::NET_OBJ_TYPE_AUTOMOBILE; i <= (int)eNetObjType::NET_OBJ_TYPE_TRAIN; i++)
			{
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
					finder.global_node_identifier.emplace(addr, node_id);
				}
			}

			inited = true;
		}
	};
}
