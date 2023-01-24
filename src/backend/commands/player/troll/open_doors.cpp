#include "backend/player_command.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "util/teleport.hpp"

namespace big
{
    	class open_doors : player_command
	{
		using player_command::player_command;

		virtual void execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx)
		{
		    Ped ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player->id());
		    if (!PED::IS_PED_IN_ANY_VEHICLE(ped, true))
		    	g_notification_service->push_warning("Toxic", "Target player is not in a vehicle.");
		    else {
		    	Vehicle vehicle = PED::GET_VEHICLE_PED_IS_USING(ped);

		    	if (entity::take_control_of(vehicle))
		    	{
		    		VEHICLE::SET_VEHICLE_DOOR_OPEN(vehicle, 0, true, false);
		    		VEHICLE::SET_VEHICLE_DOOR_OPEN(vehicle, 1, true, false);
		      		VEHICLE::SET_VEHICLE_DOOR_OPEN(vehicle, 2, true, false);
		       		VEHICLE::SET_VEHICLE_DOOR_OPEN(vehicle, 3, true, false);
		    		VEHICLE::SET_VEHICLE_DOOR_OPEN(vehicle, 4, true, false);
		    		VEHICLE::SET_VEHICLE_DOOR_OPEN(vehicle, 5, true, false);
		    		VEHICLE::SET_VEHICLE_DOOR_OPEN(vehicle, 6, true, false);
		    		VEHICLE::SET_VEHICLE_DOOR_OPEN(vehicle, 7, true, false);
			    }
		    	else {
			    	g_notification_service->push_warning("Toxic", "Failed to take control of player vehicle.");
                }
            }
        }
	};

	open_doors g_open_doors("opendoors", "Opens Vehicle Doors", "Opens all vehicle doors", 0);
}