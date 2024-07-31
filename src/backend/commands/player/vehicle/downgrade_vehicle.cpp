#include "backend/player_command.hpp"
#include "natives.hpp"
#include "util/entity.hpp"

namespace big
{
	class downgrade_vehicle : player_command
	{
		using player_command::player_command;

		virtual void execute(player_ptr player, const command_arguments& _args, const std::shared_ptr<command_context> ctx) override
		{
			Ped ped         = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player->id());
			Vehicle vehicle = PED::GET_VEHICLE_PED_IS_IN(ped, false);

			if (!PED::IS_PED_IN_ANY_VEHICLE(ped, true))
			{
				g_notification_service.push_warning("TOXIC"_T.data(), "ERROR_PLAYER_IS_NOT_IN_VEHICLE"_T.data());
			}
			else
			{
				Vehicle vehicle = PED::GET_VEHICLE_PED_IS_USING(ped);
				if (entity::take_control_of(vehicle))
				{
					VEHICLE::SET_VEHICLE_MOD_KIT(vehicle, 0);
					for (int i = 0; i < 50; i++)
					{
						VEHICLE::REMOVE_VEHICLE_MOD(vehicle, i);
					}
				}
			}
		}
	};

	downgrade_vehicle g_downgrade_vehicle("downgradeveh", "BACKEND_DOWNGRADE_VEHICLE", "BACKEND_DOWNGRADE_VEHICLE_DESC", 0);
}
