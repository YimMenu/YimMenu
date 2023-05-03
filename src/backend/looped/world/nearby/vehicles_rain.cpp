#include "vehicles_rain.hpp"

#include "natives.hpp"
#include "pointers.hpp"
#include "util/entity.hpp"

namespace big
{
	void vehicle_rain::on_tick()
	{
		for (auto vehicles : entity::get_entities(true, false))
		{
			if (!ENTITY::IS_ENTITY_IN_AIR(vehicles))
			{
				if (entity::take_control_of(vehicles))
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
}
