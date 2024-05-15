#include "backend/looped_command.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "util/entity.hpp"

namespace big
{
	class high_alert : looped_command
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
				entity_list = entity::get_entities(false, true);
				last_call_time = current_time;
			}

			for (auto ped : entity_list)
			{
				PED::SET_PED_HIGHLY_PERCEPTIVE(ped, true);
				PED::SET_PED_HEARING_RANGE(ped, 1000.0);
				PED::SET_PED_SEEING_RANGE(ped, 1000.0);
				PED::SET_PED_VISUAL_FIELD_MIN_ANGLE(ped, 1000.0);
			}
		}
	};

	high_alert g_high_alert("highalert", "BACKEND_LOOPED_WORLD_NEARBY_HIGH_ALERT", "BACKEND_LOOPED_WORLD_NEARBY_HIGH_ALERT_DESC", g.world.nearby.high_alert);
}