#include "backend/command.hpp"
#include "natives.hpp"
#include "util/teleport.hpp"

namespace big
{
	class teleport_to_last_vehicle : command
	{
		using command::command;

		virtual void execute(const command_arguments&, const std::shared_ptr<command_context> ctx) override
		{
			if (g_local_player && g_local_player->m_vehicle)
			{
				const Vehicle veh = g_pointers->m_gta.m_ptr_to_handle(g_local_player->m_vehicle);
				teleport::into_vehicle(veh);
			}
		}
	};

	teleport_to_last_vehicle g_teleport_to_last_vehicle("lastvehtp", "BACKEND_TELEPORT_TO_LAST_VEHICLE", "BACKEND_TELEPORT_TO_LAST_VEHICLE_DESC", 0);
}