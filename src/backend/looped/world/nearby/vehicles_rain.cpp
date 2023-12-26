#include "backend/looped_command.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "util/entity.hpp"

namespace big
{

	class vehicle_rain : looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override
		{
			for (auto vehicles : entity::get_entities(true, false))
			{
				if (!ENTITY::IS_ENTITY_IN_AIR(vehicles) && vehicles != self::veh)
				{
					if (entity::take_control_of(vehicles, 0))
					{
						Vector3 my_location = ENTITY::GET_ENTITY_COORDS(self::ped, 1);
						my_location.x       = my_location.x + (rand() % 100 + (-50));
						my_location.y       = my_location.y + (rand() % 100 + (-50));
						my_location.z       = my_location.z + (rand() % 20 + 100);
						ENTITY::SET_ENTITY_COORDS(vehicles, my_location.x, my_location.y, my_location.z, 0, 0, 0, 0);
						ENTITY::SET_ENTITY_VELOCITY(vehicles, 0.0, 0.0, -1.0);
					}
				}
			}
		}
	};

	vehicle_rain g_vehicle_rain("vehiclerain", "BACKEND_LOOPED_WORLD_RAIN_VEHICLES", "BACKEND_LOOPED_WORLD_RAIN_VEHICLES_DESC",g.world.nearby.veh_rain);
}