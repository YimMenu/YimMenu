#include "base/CBaseModelInfo.hpp"
#include "base/CObject.hpp"
#include "core/globals.hpp"
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
#include "netsync/nodes/proximity_migrateable/CSectorDataNode.hpp"
#include "netsync/nodes/train/CTrainGameStateDataNode.hpp"
#include "netsync/nodes/vehicle/CVehicleCreationDataNode.hpp"
#include "netsync/nodes/vehicle/CVehicleGadgetDataNode.hpp"
#include "network/CNetGamePlayer.hpp"
#include "network/netObject.hpp"
#include "util/model_info.hpp"
#include "util/notify.hpp"
#include "vehicle/CVehicleModelInfo.hpp"

namespace big
{
	static std::vector<std::pair<Hash, std::vector<uint64_t>>> trees = {
	    {RAGE_JOAAT("CAutomobileSyncTree"),
	        {
	            RAGE_JOAAT("CVehicleCreationDataNode"),
	            RAGE_JOAAT("CAutomobileCreationDataNode"),
	            RAGE_JOAAT("CGlobalFlagsDataNode"),
	            RAGE_JOAAT("CDynamicEntityGameStateDataNode"),
	            RAGE_JOAAT("CPhysicalGameStateDataNode"),
	            RAGE_JOAAT("CVehicleGameStateDataNode"),
	            RAGE_JOAAT("CEntityScriptGameStateDataNode"),
	            RAGE_JOAAT("CPhysicalScriptGameStateDataNode"),
	            RAGE_JOAAT("CVehicleScriptGameStateDataNode"),
	            RAGE_JOAAT("CEntityScriptInfoDataNode"),
	            RAGE_JOAAT("CPhysicalAttachDataNode"),
	            RAGE_JOAAT("CVehicleAppearanceDataNode"),
	            RAGE_JOAAT("CVehicleDamageStatusDataNode"),
	            RAGE_JOAAT("CVehicleComponentReservationDataNode"),
	            RAGE_JOAAT("CVehicleHealthDataNode"),
	            RAGE_JOAAT("CVehicleTaskDataNode"),
	            RAGE_JOAAT("CSectorDataNode"),
	            RAGE_JOAAT("CSectorPositionDataNode"),
	            RAGE_JOAAT("CEntityOrientationDataNode"),
	            RAGE_JOAAT("CPhysicalVelocityDataNode"),
	            RAGE_JOAAT("CVehicleAngVelocityDataNode"),
	            RAGE_JOAAT("CVehicleSteeringDataNode"),
	            RAGE_JOAAT("CVehicleControlDataNode"),
	            RAGE_JOAAT("CVehicleGadgetDataNode"),
	            RAGE_JOAAT("CMigrationDataNode"),
	            RAGE_JOAAT("CPhysicalMigrationDataNode"),
	            RAGE_JOAAT("CPhysicalScriptMigrationDataNode"),
	            RAGE_JOAAT("CVehicleProximityMigrationDataNode"),
	        }},
	    {RAGE_JOAAT("CBikeSyncTree"),
	        {
	            RAGE_JOAAT("CVehicleCreationDataNode"),
	            RAGE_JOAAT("CGlobalFlagsDataNode"),
	            RAGE_JOAAT("CDynamicEntityGameStateDataNode"),
	            RAGE_JOAAT("CPhysicalGameStateDataNode"),
	            RAGE_JOAAT("CVehicleGameStateDataNode"),
	            RAGE_JOAAT("CBikeGameStateDataNode"),
	            RAGE_JOAAT("CEntityScriptGameStateDataNode"),
	            RAGE_JOAAT("CPhysicalScriptGameStateDataNode"),
	            RAGE_JOAAT("CVehicleScriptGameStateDataNode"),
	            RAGE_JOAAT("CEntityScriptInfoDataNode"),
	            RAGE_JOAAT("CPhysicalAttachDataNode"),
	            RAGE_JOAAT("CVehicleAppearanceDataNode"),
	            RAGE_JOAAT("CVehicleDamageStatusDataNode"),
	            RAGE_JOAAT("CVehicleComponentReservationDataNode"),
	            RAGE_JOAAT("CVehicleHealthDataNode"),
	            RAGE_JOAAT("CVehicleTaskDataNode"),
	            RAGE_JOAAT("CSectorDataNode"),
	            RAGE_JOAAT("CSectorPositionDataNode"),
	            RAGE_JOAAT("CEntityOrientationDataNode"),
	            RAGE_JOAAT("CPhysicalVelocityDataNode"),
	            RAGE_JOAAT("CVehicleAngVelocityDataNode"),
	            RAGE_JOAAT("CVehicleSteeringDataNode"),
	            RAGE_JOAAT("CVehicleControlDataNode"),
	            RAGE_JOAAT("CVehicleGadgetDataNode"),
	            RAGE_JOAAT("CMigrationDataNode"),
	            RAGE_JOAAT("CPhysicalMigrationDataNode"),
	            RAGE_JOAAT("CPhysicalScriptMigrationDataNode"),
	            RAGE_JOAAT("CVehicleProximityMigrationDataNode"),
	        }},
	    {RAGE_JOAAT("CBoatSyncTree"),
	        {
	            RAGE_JOAAT("CVehicleCreationDataNode"),
	            RAGE_JOAAT("CGlobalFlagsDataNode"),
	            RAGE_JOAAT("CDynamicEntityGameStateDataNode"),
	            RAGE_JOAAT("CPhysicalGameStateDataNode"),
	            RAGE_JOAAT("CVehicleGameStateDataNode"),
	            RAGE_JOAAT("CBoatGameStateDataNode"),
	            RAGE_JOAAT("CEntityScriptGameStateDataNode"),
	            RAGE_JOAAT("CPhysicalScriptGameStateDataNode"),
	            RAGE_JOAAT("CVehicleScriptGameStateDataNode"),
	            RAGE_JOAAT("CEntityScriptInfoDataNode"),
	            RAGE_JOAAT("CPhysicalAttachDataNode"),
	            RAGE_JOAAT("CVehicleAppearanceDataNode"),
	            RAGE_JOAAT("CVehicleDamageStatusDataNode"),
	            RAGE_JOAAT("CVehicleComponentReservationDataNode"),
	            RAGE_JOAAT("CVehicleHealthDataNode"),
	            RAGE_JOAAT("CVehicleTaskDataNode"),
	            RAGE_JOAAT("CSectorDataNode"),
	            RAGE_JOAAT("CSectorPositionDataNode"),
	            RAGE_JOAAT("CEntityOrientationDataNode"),
	            RAGE_JOAAT("CPhysicalVelocityDataNode"),
	            RAGE_JOAAT("CVehicleAngVelocityDataNode"),
	            RAGE_JOAAT("CVehicleSteeringDataNode"),
	            RAGE_JOAAT("CVehicleControlDataNode"),
	            RAGE_JOAAT("CVehicleGadgetDataNode"),
	            RAGE_JOAAT("CMigrationDataNode"),
	            RAGE_JOAAT("CPhysicalMigrationDataNode"),
	            RAGE_JOAAT("CPhysicalScriptMigrationDataNode"),
	            RAGE_JOAAT("CVehicleProximityMigrationDataNode"),
	        }},
	    {RAGE_JOAAT("CDoorSyncTree"),
	        {
	            RAGE_JOAAT("CDoorCreationDataNode"),
	            RAGE_JOAAT("CGlobalFlagsDataNode"),
	            RAGE_JOAAT("CDoorScriptInfoDataNode"),
	            RAGE_JOAAT("CDoorScriptGameStateDataNode"),
	            RAGE_JOAAT("CDoorMovementDataNode"),
	            RAGE_JOAAT("CMigrationDataNode"),
	            RAGE_JOAAT("CPhysicalScriptMigrationDataNode"),
	        }},
	    {RAGE_JOAAT("CHeliSyncTree"),
	        {
	            RAGE_JOAAT("CVehicleCreationDataNode"),
	            RAGE_JOAAT("CAutomobileCreationDataNode"),
	            RAGE_JOAAT("CGlobalFlagsDataNode"),
	            RAGE_JOAAT("CDynamicEntityGameStateDataNode"),
	            RAGE_JOAAT("CPhysicalGameStateDataNode"),
	            RAGE_JOAAT("CVehicleGameStateDataNode"),
	            RAGE_JOAAT("CEntityScriptGameStateDataNode"),
	            RAGE_JOAAT("CPhysicalScriptGameStateDataNode"),
	            RAGE_JOAAT("CVehicleScriptGameStateDataNode"),
	            RAGE_JOAAT("CEntityScriptInfoDataNode"),
	            RAGE_JOAAT("CPhysicalAttachDataNode"),
	            RAGE_JOAAT("CVehicleAppearanceDataNode"),
	            RAGE_JOAAT("CVehicleDamageStatusDataNode"),
	            RAGE_JOAAT("CVehicleComponentReservationDataNode"),
	            RAGE_JOAAT("CVehicleHealthDataNode"),
	            RAGE_JOAAT("CVehicleTaskDataNode"),
	            RAGE_JOAAT("CHeliHealthDataNode"),
	            RAGE_JOAAT("CSectorDataNode"),
	            RAGE_JOAAT("CSectorPositionDataNode"),
	            RAGE_JOAAT("CEntityOrientationDataNode"),
	            RAGE_JOAAT("CPhysicalVelocityDataNode"),
	            RAGE_JOAAT("CVehicleAngVelocityDataNode"),
	            RAGE_JOAAT("CVehicleSteeringDataNode"),
	            RAGE_JOAAT("CVehicleControlDataNode"),
	            RAGE_JOAAT("CVehicleGadgetDataNode"),
	            RAGE_JOAAT("CHeliControlDataNode"),
	            RAGE_JOAAT("CMigrationDataNode"),
	            RAGE_JOAAT("CPhysicalMigrationDataNode"),
	            RAGE_JOAAT("CPhysicalScriptMigrationDataNode"),
	            RAGE_JOAAT("CVehicleProximityMigrationDataNode"),
	        }},
	    {RAGE_JOAAT("CObjectSyncTree"),
	        {
	            RAGE_JOAAT("CObjectCreationDataNode"),
	            RAGE_JOAAT("CGlobalFlagsDataNode"),
	            RAGE_JOAAT("CDynamicEntityGameStateDataNode"),
	            RAGE_JOAAT("CPhysicalGameStateDataNode"),
	            RAGE_JOAAT("CObjectGameStateDataNode"),
	            RAGE_JOAAT("CEntityScriptGameStateDataNode"),
	            RAGE_JOAAT("CPhysicalScriptGameStateDataNode"),
	            RAGE_JOAAT("CObjectScriptGameStateDataNode"),
	            RAGE_JOAAT("CEntityScriptInfoDataNode"),
	            RAGE_JOAAT("CPhysicalAttachDataNode"),
	            RAGE_JOAAT("CPhysicalHealthDataNode"),
	            RAGE_JOAAT("CSectorDataNode"),
	            RAGE_JOAAT("CObjectSectorPosNode"),
	            RAGE_JOAAT("CObjectOrientationNode"),
	            RAGE_JOAAT("CPhysicalVelocityDataNode"),
	            RAGE_JOAAT("CPhysicalAngVelocityDataNode"),
	            RAGE_JOAAT("CMigrationDataNode"),
	            RAGE_JOAAT("CPhysicalMigrationDataNode"),
	            RAGE_JOAAT("CPhysicalScriptMigrationDataNode"),
	        }},
	    {RAGE_JOAAT("CPedSyncTree"),
	        {
	            RAGE_JOAAT("CPedCreationDataNode"),
	            RAGE_JOAAT("CPedScriptCreationDataNode"),
	            RAGE_JOAAT("CGlobalFlagsDataNode"),
	            RAGE_JOAAT("CDynamicEntityGameStateDataNode"),
	            RAGE_JOAAT("CPhysicalGameStateDataNode"),
	            RAGE_JOAAT("CPedGameStateDataNode"),
	            RAGE_JOAAT("CPedComponentReservationDataNode"),
	            RAGE_JOAAT("CEntityScriptGameStateDataNode"),
	            RAGE_JOAAT("CPhysicalScriptGameStateDataNode"),
	            RAGE_JOAAT("CPedScriptGameStateDataNode"),
	            RAGE_JOAAT("CEntityScriptInfoDataNode"),
	            RAGE_JOAAT("CPedAttachDataNode"),
	            RAGE_JOAAT("CPedHealthDataNode"),
	            RAGE_JOAAT("CPedMovementGroupDataNode"),
	            RAGE_JOAAT("CPedAIDataNode"),
	            RAGE_JOAAT("CPedAppearanceDataNode"),
	            RAGE_JOAAT("CPedOrientationDataNode"),
	            RAGE_JOAAT("CPedMovementDataNode"),
	            RAGE_JOAAT("CPedTaskTreeDataNode"),
	            RAGE_JOAAT("CPedTaskSpecificDataNode"),
	            RAGE_JOAAT("CPedTaskSpecificDataNode"),
	            RAGE_JOAAT("CPedTaskSpecificDataNode"),
	            RAGE_JOAAT("CPedTaskSpecificDataNode"),
	            RAGE_JOAAT("CPedTaskSpecificDataNode"),
	            RAGE_JOAAT("CPedTaskSpecificDataNode"),
	            RAGE_JOAAT("CPedTaskSpecificDataNode"),
	            RAGE_JOAAT("CPedTaskSpecificDataNode"),
	            RAGE_JOAAT("CSectorDataNode"),
	            RAGE_JOAAT("CPedSectorPosMapNode"),
	            RAGE_JOAAT("CPedSectorPosNavMeshNode"),
	            RAGE_JOAAT("CMigrationDataNode"),
	            RAGE_JOAAT("CPhysicalMigrationDataNode"),
	            RAGE_JOAAT("CPhysicalScriptMigrationDataNode"),
	            RAGE_JOAAT("CPedInventoryDataNode"),
	            RAGE_JOAAT("CPedTaskSequenceDataNode"),
	        }},
	    {RAGE_JOAAT("CPickupSyncTree"),
	        {
	            RAGE_JOAAT("CPickupCreationDataNode"),
	            RAGE_JOAAT("CGlobalFlagsDataNode"),
	            RAGE_JOAAT("CDynamicEntityGameStateDataNode"),
	            RAGE_JOAAT("CPickupScriptGameStateNode"),
	            RAGE_JOAAT("CPhysicalGameStateDataNode"),
	            RAGE_JOAAT("CEntityScriptGameStateDataNode"),
	            RAGE_JOAAT("CPhysicalScriptGameStateDataNode"),
	            RAGE_JOAAT("CEntityScriptInfoDataNode"),
	            RAGE_JOAAT("CPhysicalHealthDataNode"),
	            RAGE_JOAAT("CPhysicalAttachDataNode"),
	            RAGE_JOAAT("CSectorDataNode"),
	            RAGE_JOAAT("CPickupSectorPosNode"),
	            RAGE_JOAAT("CEntityOrientationDataNode"),
	            RAGE_JOAAT("CPhysicalVelocityDataNode"),
	            RAGE_JOAAT("CPhysicalAngVelocityDataNode"),
	            RAGE_JOAAT("CMigrationDataNode"),
	            RAGE_JOAAT("CPhysicalMigrationDataNode"),
	            RAGE_JOAAT("CPhysicalScriptMigrationDataNode"),
	        }},
	    {RAGE_JOAAT("CPickupPlacementSyncTree"),
	        {
	            RAGE_JOAAT("CPickupPlacementCreationDataNode"),
	            RAGE_JOAAT("CMigrationDataNode"),
	            RAGE_JOAAT("CGlobalFlagsDataNode"),
	            RAGE_JOAAT("CPickupPlacementStateDataNode"),
	        }},
	    {RAGE_JOAAT("CPlaneSyncTree"),
	        {
	            RAGE_JOAAT("CVehicleCreationDataNode"),
	            RAGE_JOAAT("CGlobalFlagsDataNode"),
	            RAGE_JOAAT("CDynamicEntityGameStateDataNode"),
	            RAGE_JOAAT("CPhysicalGameStateDataNode"),
	            RAGE_JOAAT("CVehicleGameStateDataNode"),
	            RAGE_JOAAT("CEntityScriptGameStateDataNode"),
	            RAGE_JOAAT("CPhysicalScriptGameStateDataNode"),
	            RAGE_JOAAT("CVehicleScriptGameStateDataNode"),
	            RAGE_JOAAT("CEntityScriptInfoDataNode"),
	            RAGE_JOAAT("CPhysicalAttachDataNode"),
	            RAGE_JOAAT("CVehicleAppearanceDataNode"),
	            RAGE_JOAAT("CVehicleDamageStatusDataNode"),
	            RAGE_JOAAT("CVehicleComponentReservationDataNode"),
	            RAGE_JOAAT("CVehicleHealthDataNode"),
	            RAGE_JOAAT("CVehicleTaskDataNode"),
	            RAGE_JOAAT("CPlaneGameStateDataNode"),
	            RAGE_JOAAT("CSectorDataNode"),
	            RAGE_JOAAT("CSectorPositionDataNode"),
	            RAGE_JOAAT("CEntityOrientationDataNode"),
	            RAGE_JOAAT("CPhysicalVelocityDataNode"),
	            RAGE_JOAAT("CVehicleAngVelocityDataNode"),
	            RAGE_JOAAT("CVehicleSteeringDataNode"),
	            RAGE_JOAAT("CVehicleControlDataNode"),
	            RAGE_JOAAT("CVehicleGadgetDataNode"),
	            RAGE_JOAAT("CPlaneControlDataNode"),
	            RAGE_JOAAT("CMigrationDataNode"),
	            RAGE_JOAAT("CPhysicalMigrationDataNode"),
	            RAGE_JOAAT("CPhysicalScriptMigrationDataNode"),
	            RAGE_JOAAT("CVehicleProximityMigrationDataNode"),
	        }},
	    {RAGE_JOAAT("CSubmarineSyncTree"),
	        {
	            RAGE_JOAAT("CVehicleCreationDataNode"),
	            RAGE_JOAAT("CGlobalFlagsDataNode"),
	            RAGE_JOAAT("CDynamicEntityGameStateDataNode"),
	            RAGE_JOAAT("CPhysicalGameStateDataNode"),
	            RAGE_JOAAT("CVehicleGameStateDataNode"),
	            RAGE_JOAAT("CSubmarineGameStateDataNode"),
	            RAGE_JOAAT("CEntityScriptGameStateDataNode"),
	            RAGE_JOAAT("CPhysicalScriptGameStateDataNode"),
	            RAGE_JOAAT("CVehicleScriptGameStateDataNode"),
	            RAGE_JOAAT("CEntityScriptInfoDataNode"),
	            RAGE_JOAAT("CPhysicalAttachDataNode"),
	            RAGE_JOAAT("CVehicleAppearanceDataNode"),
	            RAGE_JOAAT("CVehicleDamageStatusDataNode"),
	            RAGE_JOAAT("CVehicleComponentReservationDataNode"),
	            RAGE_JOAAT("CVehicleHealthDataNode"),
	            RAGE_JOAAT("CVehicleTaskDataNode"),
	            RAGE_JOAAT("CSectorDataNode"),
	            RAGE_JOAAT("CSectorPositionDataNode"),
	            RAGE_JOAAT("CEntityOrientationDataNode"),
	            RAGE_JOAAT("CPhysicalVelocityDataNode"),
	            RAGE_JOAAT("CVehicleAngVelocityDataNode"),
	            RAGE_JOAAT("CVehicleSteeringDataNode"),
	            RAGE_JOAAT("CVehicleControlDataNode"),
	            RAGE_JOAAT("CVehicleGadgetDataNode"),
	            RAGE_JOAAT("CSubmarineControlDataNode"),
	            RAGE_JOAAT("CMigrationDataNode"),
	            RAGE_JOAAT("CPhysicalMigrationDataNode"),
	            RAGE_JOAAT("CPhysicalScriptMigrationDataNode"),
	            RAGE_JOAAT("CVehicleProximityMigrationDataNode"),
	        }},
	    {RAGE_JOAAT("CPlayerSyncTree"),
	        {
	            RAGE_JOAAT("CPlayerCreationDataNode"),
	            RAGE_JOAAT("CGlobalFlagsDataNode"),
	            RAGE_JOAAT("CDynamicEntityGameStateDataNode"),
	            RAGE_JOAAT("CPhysicalGameStateDataNode"),
	            RAGE_JOAAT("CPedGameStateDataNode"),
	            RAGE_JOAAT("CPedComponentReservationDataNode"),
	            RAGE_JOAAT("CEntityScriptGameStateDataNode"),
	            RAGE_JOAAT("CPlayerGameStateDataNode"),
	            RAGE_JOAAT("CPedAttachDataNode"),
	            RAGE_JOAAT("CPedHealthDataNode"),
	            RAGE_JOAAT("CPedMovementGroupDataNode"),
	            RAGE_JOAAT("CPedAIDataNode"),
	            RAGE_JOAAT("CPlayerAppearanceDataNode"),
	            RAGE_JOAAT("CPlayerPedGroupDataNode"),
	            RAGE_JOAAT("CPlayerAmbientModelStreamingNode"),
	            RAGE_JOAAT("CPlayerGamerDataNode"),
	            RAGE_JOAAT("CPlayerExtendedGameStateNode"),
	            RAGE_JOAAT("CPedOrientationDataNode"),
	            RAGE_JOAAT("CPedMovementDataNode"),
	            RAGE_JOAAT("CPedTaskTreeDataNode"),
	            RAGE_JOAAT("CPedTaskSpecificDataNode"),
	            RAGE_JOAAT("CPedTaskSpecificDataNode"),
	            RAGE_JOAAT("CPedTaskSpecificDataNode"),
	            RAGE_JOAAT("CPedTaskSpecificDataNode"),
	            RAGE_JOAAT("CPedTaskSpecificDataNode"),
	            RAGE_JOAAT("CPedTaskSpecificDataNode"),
	            RAGE_JOAAT("CPedTaskSpecificDataNode"),
	            RAGE_JOAAT("CPedTaskSpecificDataNode"),
	            RAGE_JOAAT("CSectorDataNode"),
	            RAGE_JOAAT("CPlayerSectorPosNode"),
	            RAGE_JOAAT("CPlayerCameraDataNode"),
	            RAGE_JOAAT("CPlayerWantedAndLOSDataNode"),
	            RAGE_JOAAT("CMigrationDataNode"),
	            RAGE_JOAAT("CPhysicalMigrationDataNode"),
	            RAGE_JOAAT("CPhysicalScriptMigrationDataNode"),
	        }},
	    {RAGE_JOAAT("CAutomobileSyncTree"),
	        {
	            RAGE_JOAAT("CVehicleCreationDataNode"),
	            RAGE_JOAAT("CAutomobileCreationDataNode"),
	            RAGE_JOAAT("CGlobalFlagsDataNode"),
	            RAGE_JOAAT("CDynamicEntityGameStateDataNode"),
	            RAGE_JOAAT("CPhysicalGameStateDataNode"),
	            RAGE_JOAAT("CVehicleGameStateDataNode"),
	            RAGE_JOAAT("CEntityScriptGameStateDataNode"),
	            RAGE_JOAAT("CPhysicalScriptGameStateDataNode"),
	            RAGE_JOAAT("CVehicleScriptGameStateDataNode"),
	            RAGE_JOAAT("CEntityScriptInfoDataNode"),
	            RAGE_JOAAT("CPhysicalAttachDataNode"),
	            RAGE_JOAAT("CVehicleAppearanceDataNode"),
	            RAGE_JOAAT("CVehicleDamageStatusDataNode"),
	            RAGE_JOAAT("CVehicleComponentReservationDataNode"),
	            RAGE_JOAAT("CVehicleHealthDataNode"),
	            RAGE_JOAAT("CVehicleTaskDataNode"),
	            RAGE_JOAAT("CSectorDataNode"),
	            RAGE_JOAAT("CSectorPositionDataNode"),
	            RAGE_JOAAT("CEntityOrientationDataNode"),
	            RAGE_JOAAT("CPhysicalVelocityDataNode"),
	            RAGE_JOAAT("CVehicleAngVelocityDataNode"),
	            RAGE_JOAAT("CVehicleSteeringDataNode"),
	            RAGE_JOAAT("CVehicleControlDataNode"),
	            RAGE_JOAAT("CVehicleGadgetDataNode"),
	            RAGE_JOAAT("CMigrationDataNode"),
	            RAGE_JOAAT("CPhysicalMigrationDataNode"),
	            RAGE_JOAAT("CPhysicalScriptMigrationDataNode"),
	            RAGE_JOAAT("CVehicleProximityMigrationDataNode"),
	        }},
	    {RAGE_JOAAT("CTrainSyncTree"),
	        {
	            RAGE_JOAAT("CVehicleCreationDataNode"),
	            RAGE_JOAAT("CGlobalFlagsDataNode"),
	            RAGE_JOAAT("CDynamicEntityGameStateDataNode"),
	            RAGE_JOAAT("CPhysicalGameStateDataNode"),
	            RAGE_JOAAT("CVehicleGameStateDataNode"),
	            RAGE_JOAAT("CTrainGameStateDataNode"),
	            RAGE_JOAAT("CEntityScriptGameStateDataNode"),
	            RAGE_JOAAT("CPhysicalScriptGameStateDataNode"),
	            RAGE_JOAAT("CVehicleScriptGameStateDataNode"),
	            RAGE_JOAAT("CEntityScriptInfoDataNode"),
	            RAGE_JOAAT("CPhysicalAttachDataNode"),
	            RAGE_JOAAT("CVehicleAppearanceDataNode"),
	            RAGE_JOAAT("CVehicleDamageStatusDataNode"),
	            RAGE_JOAAT("CVehicleComponentReservationDataNode"),
	            RAGE_JOAAT("CVehicleHealthDataNode"),
	            RAGE_JOAAT("CVehicleTaskDataNode"),
	            RAGE_JOAAT("CSectorDataNode"),
	            RAGE_JOAAT("CSectorPositionDataNode"),
	            RAGE_JOAAT("CEntityOrientationDataNode"),
	            RAGE_JOAAT("CPhysicalVelocityDataNode"),
	            RAGE_JOAAT("CVehicleAngVelocityDataNode"),
	            RAGE_JOAAT("CVehicleSteeringDataNode"),
	            RAGE_JOAAT("CVehicleControlDataNode"),
	            RAGE_JOAAT("CVehicleGadgetDataNode"),
	            RAGE_JOAAT("CMigrationDataNode"),
	            RAGE_JOAAT("CPhysicalMigrationDataNode"),
	            RAGE_JOAAT("CPhysicalScriptMigrationDataNode"),
	            RAGE_JOAAT("CVehicleProximityMigrationDataNode"),
	        }},
	};

	static auto nodes = std::to_array<std::pair<Hash, uint64_t>>({{RAGE_JOAAT("CAutomobileCreationDataNode"), 0}, {RAGE_JOAAT("CBikeGameStateDataNode"), 0}, {RAGE_JOAAT("CBoatGameStateDataNode"), 0}, {RAGE_JOAAT("CDoorCreationDataNode"), 0}, {RAGE_JOAAT("CDoorMovementDataNode"), 0}, {RAGE_JOAAT("CDoorScriptGameStateDataNode"), 0}, {RAGE_JOAAT("CDoorScriptInfoDataNode"), 0}, {RAGE_JOAAT("CDynamicEntityGameStateDataNode"), 0}, {RAGE_JOAAT("CEntityOrientationDataNode"), 0}, {RAGE_JOAAT("CEntityScriptGameStateDataNode"), 0}, {RAGE_JOAAT("CEntityScriptInfoDataNode"), 0}, {RAGE_JOAAT("CGlobalFlagsDataNode"), 0}, {RAGE_JOAAT("CHeliControlDataNode"), 0}, {RAGE_JOAAT("CHeliHealthDataNode"), 0}, {RAGE_JOAAT("CMigrationDataNode"), 0}, {RAGE_JOAAT("CObjectCreationDataNode"), 0}, {RAGE_JOAAT("CObjectGameStateDataNode"), 0}, {RAGE_JOAAT("CObjectOrientationNode"), 0}, {RAGE_JOAAT("CObjectScriptGameStateDataNode"), 0}, {RAGE_JOAAT("CObjectSectorPosNode"), 0}, {RAGE_JOAAT("CPedAIDataNode"), 0}, {RAGE_JOAAT("CPedAppearanceDataNode"), 0}, {RAGE_JOAAT("CPedAttachDataNode"), 0}, {RAGE_JOAAT("CPedComponentReservationDataNode"), 0}, {RAGE_JOAAT("CPedCreationDataNode"), 0}, {RAGE_JOAAT("CPedGameStateDataNode"), 0}, {RAGE_JOAAT("CPedHealthDataNode"), 0}, {RAGE_JOAAT("CPedInventoryDataNode"), 0}, {RAGE_JOAAT("CPedMovementDataNode"), 0}, {RAGE_JOAAT("CPedMovementGroupDataNode"), 0}, {RAGE_JOAAT("CPedOrientationDataNode"), 0}, {RAGE_JOAAT("CPedScriptCreationDataNode"), 0}, {RAGE_JOAAT("CPedScriptGameStateDataNode"), 0}, {RAGE_JOAAT("CPedSectorPosMapNode"), 0}, {RAGE_JOAAT("CPedSectorPosNavMeshNode"), 0}, {RAGE_JOAAT("CPedTaskSequenceDataNode"), 0}, {RAGE_JOAAT("CPedTaskSpecificDataNode"), 0}, {RAGE_JOAAT("CPedTaskTreeDataNode"), 0}, {RAGE_JOAAT("CPhysicalAngVelocityDataNode"), 0}, {RAGE_JOAAT("CPhysicalAttachDataNode"), 0}, {RAGE_JOAAT("CPhysicalGameStateDataNode"), 0}, {RAGE_JOAAT("CPhysicalHealthDataNode"), 0}, {RAGE_JOAAT("CPhysicalMigrationDataNode"), 0}, {RAGE_JOAAT("CPhysicalScriptGameStateDataNode"), 0}, {RAGE_JOAAT("CPhysicalScriptMigrationDataNode"), 0}, {RAGE_JOAAT("CPhysicalVelocityDataNode"), 0}, {RAGE_JOAAT("CPickupCreationDataNode"), 0}, {RAGE_JOAAT("CPickupPlacementCreationDataNode"), 0}, {RAGE_JOAAT("CPickupPlacementStateDataNode"), 0}, {RAGE_JOAAT("CPickupScriptGameStateNode"), 0}, {RAGE_JOAAT("CPickupSectorPosNode"), 0}, {RAGE_JOAAT("CPlaneControlDataNode"), 0}, {RAGE_JOAAT("CPlaneGameStateDataNode"), 0}, {RAGE_JOAAT("CPlayerAmbientModelStreamingNode"), 0}, {RAGE_JOAAT("CPlayerAppearanceDataNode"), 0}, {RAGE_JOAAT("CPlayerCameraDataNode"), 0}, {RAGE_JOAAT("CPlayerCreationDataNode"), 0}, {RAGE_JOAAT("CPlayerExtendedGameStateNode"), 0}, {RAGE_JOAAT("CPlayerGameStateDataNode"), 0}, {RAGE_JOAAT("CPlayerGamerDataNode"), 0}, {RAGE_JOAAT("CPlayerPedGroupDataNode"), 0}, {RAGE_JOAAT("CPlayerSectorPosNode"), 0}, {RAGE_JOAAT("CPlayerWantedAndLOSDataNode"), 0}, {RAGE_JOAAT("CSectorDataNode"), 0}, {RAGE_JOAAT("CSectorPositionDataNode"), 0}, {RAGE_JOAAT("CSubmarineControlDataNode"), 0}, {RAGE_JOAAT("CSubmarineGameStateDataNode"), 0}, {RAGE_JOAAT("CTrainGameStateDataNode"), 0}, {RAGE_JOAAT("CVehicleAngVelocityDataNode"), 0}, {RAGE_JOAAT("CVehicleAppearanceDataNode"), 0}, {RAGE_JOAAT("CVehicleComponentReservationDataNode"), 0}, {RAGE_JOAAT("CVehicleControlDataNode"), 0}, {RAGE_JOAAT("CVehicleCreationDataNode"), 0}, {RAGE_JOAAT("CVehicleDamageStatusDataNode"), 0}, {RAGE_JOAAT("CVehicleGadgetDataNode"), 0}, {RAGE_JOAAT("CVehicleGameStateDataNode"), 0}, {RAGE_JOAAT("CVehicleHealthDataNode"), 0}, {RAGE_JOAAT("CVehicleProximityMigrationDataNode"), 0}, {RAGE_JOAAT("CVehicleScriptGameStateDataNode"), 0}, {RAGE_JOAAT("CVehicleSteeringDataNode"), 0}, {RAGE_JOAAT("CVehicleTaskDataNode"), 0}});

	static void cache_nodes()
	{
		for (int i = (int)eNetObjType::NET_OBJ_TYPE_AUTOMOBILE; i <= (int)eNetObjType::NET_OBJ_TYPE_TRAIN; i++)
		{
			if (i == (int)eNetObjType::NET_OBJ_TYPE_TRAILER)
				continue;
			rage::netSyncTree* tree = g_pointers->m_get_sync_tree_for_type(*g_pointers->m_network_object_mgr, i);
			if (tree->m_child_node_count > trees[i].second.size())
			{
				LOG(FATAL) << "Cache nodes failed " << i << tree->m_child_node_count << " " << trees[i].second.size();
				throw std::runtime_error("Failed to cache nodes");
			}
			for (int j = 0; j < tree->m_child_node_count; j++)
			{
				PVOID vft = *(PVOID*)tree->m_child_nodes[j];
				for (auto& n : nodes)
				{
					if (n.first == trees[i].second[j])
					{
						n.second = (uint64_t)vft;
						break;
					}
				}
			}
		}
	}

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

		while (object = g_pointers->m_get_entity_attached_to(object))
		{
			if (object->m_net_object && object->m_net_object->m_object_id == attached_to_net_id)
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
			auto vtable    = *(void**)node;
			Hash node_hash = 0;

			for (const auto& n : nodes)
			{
				if ((void*)n.second == vtable)
				{
					node_hash = n.first;
					break;
				}
			}

			switch (node_hash)
			{
			case (RAGE_JOAAT("CVehicleCreationDataNode")):
			{
				const auto creation_node = (CVehicleCreationDataNode*)(node);
				if (is_crash_vehicle(creation_node->m_model))
				{
					notify::crash_blocked(sender, "invalid vehicle model");
					return true;
				}
				break;
			}
			case RAGE_JOAAT("CDoorCreationDataNode"):
			{
				const auto creation_node = (CDoorCreationDataNode*)(node);
				if (is_crash_object(creation_node->m_model))
				{
					notify::crash_blocked(sender, "invalid door model");
					return true;
				}
				break;
			}
			case RAGE_JOAAT("CPickupCreationDataNode"):
			{
				const auto creation_node = (CPickupCreationDataNode*)(node);
				if (creation_node->m_custom_model && is_crash_object(creation_node->m_custom_model))
				{
					notify::crash_blocked(sender, "invalid pickup model");
					return true;
				}
				break;
			}
			case RAGE_JOAAT("CPhysicalAttachDataNode"):
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
			case RAGE_JOAAT("CPedCreationDataNode"):
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
			case RAGE_JOAAT("CPedAttachDataNode"):
			{
				const auto attach_node = (CPedAttachDataNode*)(node);
				if (attach_node->m_attached && attach_node->m_attached_to == object->m_object_id)
				{
					notify::crash_blocked(sender, "infinite ped attachment");
					return true;
				}
				else if (attach_node->m_attached && is_attachment_infinite(get_game_object(object), attach_node->m_attached_to))
				{
					notify::crash_blocked(sender, "recursive infinite ped attachment");
					return true;
				}

				break;
			}
			case RAGE_JOAAT("CObjectCreationDataNode"):
			{
				const auto creation_node = (CObjectCreationDataNode*)(node);
				if (is_crash_object(creation_node->m_model))
				{
					notify::crash_blocked(sender, "invalid object model");
					return true;
				}
				break;
			}
			case RAGE_JOAAT("CPlayerAppearanceDataNode"):
			{
				const auto player_appearance_node = (CPlayerAppearanceDataNode*)(node);
				if (is_crash_ped(player_appearance_node->m_model_hash))
				{
					notify::crash_blocked(sender, "invalid player model (appearance node)");
					return true;
				}
				break;
			}
			case RAGE_JOAAT("CPlayerCreationDataNode"):
			{
				const auto player_creation_node = (CPlayerCreationDataNode*)(node);
				if (is_crash_ped(player_creation_node->m_model))
				{
					notify::crash_blocked(sender, "invalid player model (creation node)");
					return true;
				}
				break;
			}
			case RAGE_JOAAT("CSectorDataNode"):
			{
				const auto sector_node = (CSectorDataNode*)(node);
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
		static bool init = ([] { cache_nodes(); }(), true);

		if (tree->m_child_node_count && check_node(tree->m_next_sync_node, g.m_syncing_player, object))
		{
			return false;
		}

		return g_hooking->get_original<hooks::can_apply_data>()(tree, object);
	}
}