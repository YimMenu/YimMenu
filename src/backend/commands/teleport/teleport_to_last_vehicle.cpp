#include "teleport_to_last_vehicle.hpp"

#include "natives.hpp"
#include "util/teleport.hpp"

namespace big
{
	void teleport_to_last_vehicle::execute(const std::vector<std::uint64_t>&, const std::shared_ptr<command_context> ctx)
	{
		if (g_local_player && g_local_player->m_vehicle)
		{
			const Vehicle veh = g_pointers->m_gta.m_ptr_to_handle(g_local_player->m_vehicle);
			teleport::into_vehicle(veh);
		}
	}
}
