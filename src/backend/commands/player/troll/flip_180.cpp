#include "backend/player_command.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "util/teleport.hpp"

namespace big
{
	class flip_180 : player_command
	{
		using player_command::player_command;

		virtual void execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx)
		{
			Entity ent               = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player->id());
			float Heading            = ENTITY::GET_ENTITY_HEADING(ent);
			Vector3 flipCar180Coords = ENTITY::GET_ENTITY_COORDS(ent, 1);
			if (!PED::IS_PED_IN_ANY_VEHICLE(ent, true))
			{
				g_notification_service->push_warning("Toxic", "Target player is not in any vehicle.");
			}
			else
			{
				if (entity::take_control_of(ent))
				{
					if (Heading > 180.0)
					{
						Heading -= 180.0;
					}
					else
					{
						Heading += 180.0;
						ENTITY::SET_ENTITY_COORDS(ent, flipCar180Coords.x, flipCar180Coords.y, flipCar180Coords.z, 0, 0, 0, 1);
						ENTITY::SET_ENTITY_HEADING(ent, Heading);
						VEHICLE::SET_VEHICLE_FORWARD_SPEED(ent, ENTITY::GET_ENTITY_SPEED(ent));
					}
				}
			}
		}
	};

	flip_180
		g_flip_180("flip180", "Rotate 180", "Rotates their car around", 0)
			;
}