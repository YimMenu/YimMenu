#include "backend/player_command.hpp"
#include "natives.hpp"
#include "util/entity.hpp"

namespace big
{
	class smash_windows : player_command
	{
		using player_command::player_command;

		virtual void execute(player_ptr player, const command_arguments& _args, const std::shared_ptr<command_context> ctx) override
		{
			Ped ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player->id());
			if (PED::IS_PED_IN_ANY_VEHICLE(ped, false))
			{
				Vehicle vehicle = PED::GET_VEHICLE_PED_IS_IN(ped, false);

				if (entity::take_control_of(vehicle))
				{
					int window = 0;

					for (window = 0; window < 8; window++)
					{
						VEHICLE::SMASH_VEHICLE_WINDOW(vehicle, window);
					}
				}
			}
		}
	};

	smash_windows g_smash_windows("smashwindows", "BACKEND_SMASH_VEHICLE_WINDOWS", "BACKEND_SMASH_VEHICLE_WINDOWS_DESC", 0);
}