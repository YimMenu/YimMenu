#include "backend/player_command.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "util/teleport.hpp"

namespace big
{
	class burst_tyres : player_command
	{
		using player_command::player_command;

		virtual void execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx)
		{
			Ped ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player->id());
			if (!PED::IS_PED_IN_ANY_VEHICLE(ped, true))
			{
				g_notification_service->push_warning("Toxic", "Target player is not in a vehicle.");
			}

			else
			{
				Vehicle vehicle = PED::GET_VEHICLE_PED_IS_USING(ped);
				if (entity::take_control_of(vehicle))
				{
					Vehicle vehicle = PED::GET_VEHICLE_PED_IS_USING(ped);
					entity::take_control_of(vehicle);
					VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(vehicle, true);
					static int tireID = 0;
					for (tireID = 0; tireID < 8; tireID++)
					{
						VEHICLE::SET_VEHICLE_TYRE_BURST(vehicle, tireID, true, 1000.0);
					}
				}
			}
		}
	};

	burst_tyres g_burst_tyres("burstwheels", "Burst Vehicle Tyres", "Removes their tyres.", 0);
}
