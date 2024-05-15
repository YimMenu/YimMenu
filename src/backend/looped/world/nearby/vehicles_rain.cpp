#include "backend/looped_command.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "util/entity.hpp"

namespace big
{

	class vehicle_rain : looped_command
	{
		using looped_command::looped_command;

		std::vector<Entity> entity_list;
		std::chrono::steady_clock::time_point last_call_time;

		virtual void on_tick() override
		{
			auto current_time = std::chrono::steady_clock::now();
			auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - last_call_time).count();

			if (elapsed_time >= 100)
			{
				// Mitigate thread-unsafe behavior of get_entities by not calling it every tick (should be minimal impact to in-game vehicle behavior)
				entity_list    = entity::get_entities(true, false);
				last_call_time = current_time;
			}

			for (auto vehicles : entity_list)
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