#include "hooking/hooking.hpp"

#include <netsync/nodes/vehicle/CVehicleProximityMigrationDataNode.hpp>

namespace big
{
	void hooks::write_vehicle_proximity_migration_data_node(rage::netObject* veh, CVehicleProximityMigrationDataNode* node)
	{
		CVehicle* vehicle = *(CVehicle**)(((__int64)veh) - 432);

		g_hooking->get_original<hooks::write_vehicle_proximity_migration_data_node>()(veh, node);

		if (auto it = g.m_remote_player_teleports.find(vehicle->m_net_object->m_object_id);
		    it != g.m_remote_player_teleports.end())
		{
			node->m_has_occupants[0]  = true;
			node->m_occupants[0]      = it->second.m_player_net_id;
			node->m_override_position = true;
			node->m_position          = it->second.m_position;
			node->m_velocity.x        = 1;
			node->m_velocity.y        = 1;
			node->m_velocity.z        = 1;
		}
	}
}