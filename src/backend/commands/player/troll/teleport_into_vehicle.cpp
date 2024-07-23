#include "backend/player_command.hpp"
#include "natives.hpp"
#include "util/teleport.hpp"

namespace big
{
	class teleport_into_vehicle : player_command
	{
		using player_command::player_command;

		virtual void execute(player_ptr player, const command_arguments& _args, const std::shared_ptr<command_context> ctx) override
		{
			Vehicle veh =
			    PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player_service->get_selected()->id()), false);

			teleport::into_vehicle(veh);
		}
	};

	teleport_into_vehicle g_teleport_into_vehicle("playervehtp", "TELEPORT_INTO_VEHICLE", "TELEPORT_INTO_VEHICLE_DESC", 0, false);
}