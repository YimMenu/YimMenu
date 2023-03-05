#include "backend/player_command.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "util/teleport.hpp"
namespace big
{
	class unlock_vehicle : player_command
	{
		using player_command::player_command;

		virtual void execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx)
		{
			if (PED::IS_PED_IN_ANY_VEHICLE((player->id()), false))
			{
				entity::take_control_of(PED::GET_VEHICLE_PED_IS_USING(player->id()));
				VEHICLE::SET_VEHICLE_DOORS_LOCKED(PED::GET_VEHICLE_PED_IS_USING(player->id()), 0);
			}
		}
	};

	unlock_vehicle g_unlock_vehicle("unlockveh", "Unlock Vehicle Doors", "Unlocks Vehicle Doors", 0);
}