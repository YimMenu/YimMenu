#include "backend/looped/looped.hpp"
#include "natives.hpp"
#include "pointers.hpp"

#include <network/CNetworkPlayerMgr.hpp>

namespace big
{
	void looped::system_self_globals()
	{
		if (!*g_pointers->m_gta.m_network_player_mgr || !(*g_pointers->m_gta.m_network_player_mgr)->m_local_net_player
		    || (*g_pointers->m_gta.m_network_player_mgr)->m_local_net_player->m_player_id == -1) [[unlikely]]
			self::id = 0;
		else [[likely]]
		{
			self::id = (*g_pointers->m_gta.m_network_player_mgr)->m_local_net_player->m_player_id;

			if (self::id == 255)
				LOG(VERBOSE) << "how? " << (int)(*g_pointers->m_gta.m_network_player_mgr)->m_local_net_player->m_player_id;
		}

		self::ped = PLAYER::PLAYER_PED_ID();

		STATS::STAT_GET_INT("MPPLY_LAST_MP_CHAR"_J, &self::char_index, true);

		self::pos = ENTITY::GET_ENTITY_COORDS(self::ped, false /*Unused*/);

		self::rot = ENTITY::GET_ENTITY_ROTATION(self::ped, 2);

		if (PED::IS_PED_IN_ANY_VEHICLE(self::ped, 0))
		{
			self::veh = PED::GET_VEHICLE_PED_IS_IN(self::ped, false);
		}
		else
		{
			self::veh = 0;
		}
	}
}
