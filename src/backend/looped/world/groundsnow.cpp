#include "backend/looped_command.hpp"
#include "fiber_pool.hpp"
#include "gta_util.hpp"
#include "script.hpp"
#include "services/tunables/tunables_service.hpp"

namespace big
{
	class ground_snow : looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override
		{
			g_tunables_service->set_tunable<bool>(RAGE_JOAAT("TURN_SNOW_ON_OFF"), true);
		}

		virtual void on_disable() override
		{
			g_tunables_service->set_tunable<bool>(RAGE_JOAAT("TURN_SNOW_ON_OFF"), false);
		}
	};

	ground_snow g_ground_snow("groundsnow", "BACKEND_LOOPED_WORLD_GROUND_SNOW", "BACKEND_LOOPED_WORLD_GROUND_SNOW_DESC", g.world.ground_snow);
}