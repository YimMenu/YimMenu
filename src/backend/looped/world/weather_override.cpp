#include "backend/looped_command.hpp"
#include "core/data/weathers.hpp"
#include "fiber_pool.hpp"
#include "gta_util.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "script.hpp"
#include "services/tunables/tunables_service.hpp"

namespace big
{
	class weather_override : looped_command
	{
		int current_weather_idx = -1;
		bool* turn_snow_on_off  = nullptr;

		using looped_command::looped_command;

		virtual void on_tick() override
		{
			if (!turn_snow_on_off)
				turn_snow_on_off = g_tunables_service->get_tunable<bool*>("TURN_SNOW_ON_OFF"_J);

			if (current_weather_idx != g.world.local_weather)
			{
				MISC::SET_OVERRIDE_WEATHER(weathers[g.world.local_weather]);
				current_weather_idx = g.world.local_weather;
			}

			if (turn_snow_on_off)
				*turn_snow_on_off = g.world.local_weather == 13;
		}

		virtual void on_disable() override
		{
			MISC::CLEAR_OVERRIDE_WEATHER();
		}
	};

	weather_override g_weather_override("weatheroverride", "BACKEND_LOOPED_WORLD_OVERRIDE_WEATHER", "BACKEND_LOOPED_WORLD_OVERRIDE_WEATHER_DESC", g.world.override_weather);
}
