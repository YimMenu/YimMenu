#include "teleport_to_personal_vehicle.hpp"

#include "natives.hpp"
#include "util/mobile.hpp"
#include "util/teleport.hpp"

namespace big
{
	void teleport_to_personal_vehicle::execute(const std::vector<std::uint64_t>&, const std::shared_ptr<command_context> ctx)
	{
		if (g_local_player && g_local_player->m_vehicle)
		{
			Vehicle veh = mobile::mechanic::get_personal_vehicle();
			teleport::into_vehicle(veh);
		}
	}
}
