#include "backend/player_command.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "util/teleport.hpp"

namespace big
{
	class lock_vehicle : player_command
	{
		using player_command::player_command;

		virtual void execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx)
		{
			int lockStatus = VEHICLE::GET_VEHICLE_DOOR_LOCK_STATUS(player->id());
			Entity ent     = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player->id());
			if (!PED::IS_PED_IN_ANY_VEHICLE(ent, true))
			{
				g_notification_service->push_warning("Toxic", "Target player is not in a vehicle.");
			}
			else
			{
				if (entity::take_control_of(ent))
				{
					entity::take_control_of(PED::GET_VEHICLE_PED_IS_USING(player->id()));
					VEHICLE::SET_VEHICLE_DOORS_LOCKED(PED::GET_VEHICLE_PED_IS_USING(player->id()), 4);
				}
			}
		}
	};

	lock_vehicle g_lock_vehicle("lockveh", "Lock Vehicle", "Locks vehicle doors", 0);
}