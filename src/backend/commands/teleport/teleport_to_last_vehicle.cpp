#include "backend/command.hpp"
#include "natives.hpp"
#include "util/mobile.hpp"
#include "util/vehicle.hpp"

namespace big
{
	class teleport_to_last_vehicle : command
	{
		using command::command;

		virtual void execute(const std::vector<std::uint64_t>&, const std::shared_ptr<command_context> ctx)
		{
			if (g_local_player && g_local_player->m_vehicle)
			{
				const Vehicle veh = g_pointers->m_ptr_to_handle(g_local_player->m_vehicle);
				teleport::into_vehicle(veh);
			}
		}
	};

	teleport_to_last_vehicle g_teleport_to_last_vehicle("lastvehtp", "Teleport To Last Vehicle", "Teleports you into your last driven vehicle", 0);
}