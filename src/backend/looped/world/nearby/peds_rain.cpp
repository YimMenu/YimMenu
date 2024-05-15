#include "backend/looped_command.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "util/entity.hpp"

namespace big
{
	class ped_rain : looped_command
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
				// Mitigate thread-unsafe behavior of get_entities by not calling it every tick (should be minimal impact to in-game ped behavior)
				entity_list    = entity::get_entities(false, true);
				last_call_time = current_time;
			}

			for (auto ped : entity_list)
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