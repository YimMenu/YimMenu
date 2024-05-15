#include "backend/looped_command.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "util/entity.hpp"

namespace big
{
	class ped_rain : looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override
		{
			for (auto ped : entity::get_entities(false, true))
			{
				if (!ENTITY::IS_ENTITY_IN_AIR(ped) && entity::take_control_of(ped, 0) && !PED::IS_PED_A_PLAYER(ped) && ped != self::ped)
				{
					Vector3 my_location = ENTITY::GET_ENTITY_COORDS(self::ped, 1);
					my_location.x       = my_location.x + (rand() % 100 + (-50));
					my_location.y       = my_location.y + (rand() % 100 + (-50));
					my_location.z       = my_location.z + (rand() % 50 + 50);
					ENTITY::SET_ENTITY_COORDS(ped, my_location.x, my_location.y, my_location.z, 0, 0, 0, 0);
					ENTITY::SET_ENTITY_VELOCITY(ped, 0.0, 0.0, -1.0);
				}
			}
		}
	};

	ped_rain g_ped_rain("pedrain", "BACKEND_LOOPED_WORLD_RAIN_PEDS", "BACKEND_LOOPED_WORLD_RAIN_PEDS_DESC", g.world.nearby.ped_rain);
}