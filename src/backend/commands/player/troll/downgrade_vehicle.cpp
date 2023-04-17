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
			Ped ped         = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player->id());
			Vehicle vehicle = PED::GET_VEHICLE_PED_IS_IN(ped, false);
			if (!PED::IS_PED_IN_ANY_VEHICLE(vehicle, true))
			{
				g_notification_service->push_warning("Toxic", "Target player is not in a vehicle.");
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

	downgrade_vehicle g_downgrade_vehicle("downgradeveh", "Downgrade Vehicle", "Removes all upgrades", 0);
}