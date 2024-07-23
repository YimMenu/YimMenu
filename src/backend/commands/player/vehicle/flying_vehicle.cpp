#include "backend/player_command.hpp"
#include "natives.hpp"
#include "util/entity.hpp"

namespace big
{
	class flying_vehicle : player_command
	{
		using player_command::player_command;

		virtual void execute(player_ptr player, const command_arguments& _args, const std::shared_ptr<command_context> ctx) override
		{
			Entity ent = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player->id());

			if (!PED::IS_PED_IN_ANY_VEHICLE(ent, true))
			{
				g_notification_service.push_warning("TOXIC"_T.data(), "ERROR_PLAYER_IS_NOT_IN_VEHICLE"_T.data());
			}
			else
			{
				ent = PED::GET_VEHICLE_PED_IS_IN(ent, false);

				if (entity::take_control_of(ent))
				{
					ENTITY::APPLY_FORCE_TO_ENTITY(ent, 1, 0.f, 0.f, 50000.f, 0.f, 0.f, 0.f, 0, 0, 1, 1, 0, 1);
				}
			}
		}
	};

	flying_vehicle g_flying_vehicle("flyingveh", "BACKEND_FLYING_VEHICLE", "BACKEND_FLYING_VEHICLE_DESC", 0);
}
