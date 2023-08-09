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

	combative g_combative("riotmode", "Riot Mode", "Make nearby peds attack each other", g.world.nearby.combative);
}
