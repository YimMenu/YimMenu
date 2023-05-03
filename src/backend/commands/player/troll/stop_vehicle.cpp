#include "stop_vehicle.hpp"

#include "natives.hpp"
#include "pointers.hpp"
#include "util/teleport.hpp"

namespace big
{
	void stop_vehicle::execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx)
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
				VEHICLE::SET_VEHICLE_FORWARD_SPEED(vehicle, 0);
			}
			else
			{
				g_notification_service->push_warning("Toxic", "Failed to take control of player vehicle.");
			}
		}
	}
}
