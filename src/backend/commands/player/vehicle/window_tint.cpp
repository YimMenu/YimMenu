#include "backend/player_command.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "util/teleport.hpp"
#include "util/vehicle.hpp"

namespace big
{
	class black_tint : player_command
	{
		using player_command::player_command;

		virtual void execute(player_ptr player, const command_arguments& _args, const std::shared_ptr<command_context> ctx)
		{
			Ped ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player->id());

			if (PED::IS_PED_IN_ANY_VEHICLE(ped, false))
			{
				Vehicle vehicle = PED::GET_VEHICLE_PED_IS_IN(ped, false);

				if (entity::take_control_of(vehicle))
					VEHICLE::SET_VEHICLE_WINDOW_TINT(vehicle, WINDOWTINT_BLACK);
			}
		}
	};

	black_tint g_black_tint("blacktint", "Black Window Tint", "Makes their windows black.", 0);
}