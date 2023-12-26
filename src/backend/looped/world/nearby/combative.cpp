#include "backend/bool_command.hpp"
#include "natives.hpp"

namespace big
{
	class combative : bool_command
	{
		using bool_command::bool_command;

		virtual void on_enable() override
		{
			MISC::SET_RIOT_MODE_ENABLED(true);
		}

		virtual void on_disable() override
		{
			MISC::SET_RIOT_MODE_ENABLED(false);
		}
	};

	combative g_combative("riotmode", "BACKEND_LOOPED_WORLD_NEARBY_RIOT_MODE", "BACKEND_LOOPED_WORLD_NEARBY_RIOT_MODE_DESC", g.world.nearby.combative);
}
