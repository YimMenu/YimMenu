#include "backend/player_command.hpp"
#include "natives.hpp"
#include "util/entity.hpp"
#include "gta/vehicle_values.hpp"

namespace big
{
	class black_tint : player_command
	{
		using player_command::player_command;

		virtual void execute(player_ptr player, const command_arguments& _args, const std::shared_ptr<command_context> ctx) override
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

	black_tint g_black_tint("blacktint", "WINDOW_TINT", "BACKEND_WINDOW_TINT_DESC", 0);
}