#include "backend/player_command.hpp"
#include "natives.hpp"
#include "util/entity.hpp"

namespace big
{
	class burst_tyres : player_command
	{
		using player_command::player_command;

		virtual void execute(player_ptr player, const command_arguments& _args, const std::shared_ptr<command_context> ctx) override
		{
			Ped ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player->id());

			if (!PED::IS_PED_IN_ANY_VEHICLE(ped, true))
			{
				g_notification_service.push_warning("TOXIC"_T.data(), "ERROR_PLAYER_IS_NOT_IN_VEHICLE"_T.data());
			}
			else
			{
				Vehicle vehicle = PED::GET_VEHICLE_PED_IS_IN(ped, false);
				if (entity::take_control_of(vehicle))
				{
					VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(vehicle, true);

					for (int tire = 0; tire < 8; tire++)
					{
						VEHICLE::SET_VEHICLE_TYRE_BURST(vehicle, tire, true, 1000.0f);
					}
				}
			}
		}
	};

	burst_tyres g_burst_tyres("burstwheels", "BACKEND_BURST_VEHICLE_TIRES", "BACKEND_BURST_VEHICLE_TIRES_DESC", 0);
}
