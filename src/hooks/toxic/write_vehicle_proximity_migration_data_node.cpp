#include "gta/net_array.hpp"
#include "hooking.hpp"
#include "script_global.hpp"
#include "script_local.hpp"

namespace big
{
	void hooks::write_vehicle_proximity_migration_data_node(rage::netObject* veh, __int64 node)
	{
		CVehicle* vehicle = *(CVehicle**)(((__int64)veh) - 432);

		g_hooking->get_original<hooks::write_vehicle_proximity_migration_data_node>()(veh, node);

		if (vehicle->m_model_info->m_hash == RAGE_JOAAT("ninef"))
		{
			// TODO: use GTAV-Classes CVehicleProximityMigrationDataNode
			*(bool*)(node + 196)    = true;
			*(__int16*)(node + 212) = g.m_tp_player_net_id;
			*(bool*)(node + 0x104)  = true;
			*(float*)(node + 0x110) = g.m_tp_position.x;
			*(float*)(node + 0x114) = g.m_tp_position.y;
			*(float*)(node + 0x118) = g.m_tp_position.z;
		}
	}
}