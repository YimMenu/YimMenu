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
	class blackout : looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override
		{
			GRAPHICS::SET_ARTIFICIAL_LIGHTS_STATE(true);
		}

		virtual void on_disable() override
		{
			GRAPHICS::SET_ARTIFICIAL_LIGHTS_STATE(false);
		}
	};

	blackout g_blackout("blackout", "BACKEND_LOOPED_WORLD_BLACKOUT", "BACKEND_LOOPED_WORLD_BLACKOUT_DESC", g.world.blackout);
}