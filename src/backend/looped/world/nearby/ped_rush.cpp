#include "backend/looped_command.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "util/entity.hpp"

namespace big
{

	class ped_rush : looped_command
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
				PED::SET_PED_MOVE_RATE_OVERRIDE(ped, 10.0f);
			}
		}

		virtual void on_disable() override //Set the peds back to their normal speed
		{
			for (auto ped : entity::get_entities(false, true))
			{
				PED::SET_PED_MOVE_RATE_OVERRIDE(ped, 1.0f);
			}
		}
	};

	ped_rush g_ped_rush("pedrush", "BACKEND_LOOPED_WORLD_PED_RUSH", "BACKEND_LOOPED_WORLD_PED_RUSH_DESC", g.world.nearby.ped_rush);
}