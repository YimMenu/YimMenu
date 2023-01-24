#include "backend/player_command.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "util/teleport.hpp"

namespace big
{
	class downgrade_vehicle : player_command
	{
		using player_command::player_command;

		virtual void execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx)
		{
		    Vehicle vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player->id()), false);
		    VEHICLE::SET_VEHICLE_MOD_KIT(vehicle, 0);
		    for (int i = 0; i < 50; i++)
		    {
		    	VEHICLE::REMOVE_VEHICLE_MOD(vehicle, i);
		    }
		    VEHICLE::REMOVE_VEHICLE_MOD(vehicle, 18); //Remove turbo on vehicle
		    VEHICLE::REMOVE_VEHICLE_MOD(vehicle, 22); //Remove xeon headlights
        }
	};

	downgrade_vehicle g_downgrade_vehicle("downgradeveh", "Downgrade Vehicle", "Removes all upgrades", 0);
}