#include "backend/player_command.hpp"
#include "natives.hpp"
#include "util/entity.hpp"
#include "gta/enums.hpp"

namespace big
{
	class unlock_vehicle : player_command
	{
		using player_command::player_command;

		virtual void execute(player_ptr player, const command_arguments& _args, const std::shared_ptr<command_context> ctx) override
		{
			Ped ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player->id());
			if (!PED::IS_PED_IN_ANY_VEHICLE(ped, true))
			{
				g_notification_service.push_warning("VEHICLE"_T.data(), "ERROR_PLAYER_IS_NOT_IN_VEHICLE"_T.data());
			}
			else
			{
				Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(ped, false);

				if (entity::take_control_of(veh))
					VEHICLE::SET_VEHICLE_DOORS_LOCKED(veh, (int)eVehicleLockState::VEHICLELOCK_UNLOCKED);
			}
		}
	};

	unlock_vehicle g_unlock_vehicle("unlockveh", "BACKEND_UNLOCK_DOORS", "BACKEND_UNLOCK_DOORS_DESC", 0);
}
