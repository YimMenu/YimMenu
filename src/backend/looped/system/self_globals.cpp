#include "backend/looped/looped.hpp"
#include "natives.hpp"
#include "pointers.hpp"

#include <network/CNetworkPlayerMgr.hpp>

namespace big
{
	void looped::system_self_globals()
	{
		if (!*g_pointers->m_gta.m_network_player_mgr || !(*g_pointers->m_gta.m_network_player_mgr)->m_local_net_player
		    || (*g_pointers->m_gta.m_network_player_mgr)->m_local_net_player->m_player_id == -1)
			self::id = 0;
		else
			self::id = (*g_pointers->m_gta.m_network_player_mgr)->m_local_net_player->m_player_id;

		self::ped = PLAYER::PLAYER_PED_ID();

		self::pos = ENTITY::GET_ENTITY_COORDS(self::ped, false /*Unused*/);

		if (PED::IS_PED_IN_ANY_VEHICLE(self::ped, 0))
			self::veh = PED::GET_VEHICLE_PED_IS_IN(self::ped, false);
		else
			self::veh = 0;

		if (g_local_player && g_local_player->m_vehicle)
		{
			Vehicle veh = g_pointers->m_gta.m_ptr_to_handle(g_local_player->m_vehicle);
			if (ENTITY::DOES_ENTITY_EXIST(veh) && !ENTITY::IS_ENTITY_DEAD(veh, 0))
				self::last_veh = veh;
		}
		else
			self::last_veh = 0;
	}
}
