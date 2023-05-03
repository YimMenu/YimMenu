#include "upgrade_vehicle.hpp"

#include "natives.hpp"
#include "pointers.hpp"
#include "util/teleport.hpp"
#include "util/vehicle.hpp"

namespace big
{
	void upgrade_vehicle::execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx)
	{
		Vehicle vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player->id()), false);
		vehicle::max_vehicle(vehicle);
	}
}
