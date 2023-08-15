#include "backend/looped_command.hpp"
#include "services/tunables/tunables_service.hpp"
#include "core/scr_globals.hpp"

namespace big
{
	class no_idle_kick : looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override
		{
			for (int i = 0; i < 4; i++)
			{
				*scr_globals::tuneables.at(87).at(i).as<PINT>() = INT_MAX;
			}
		}

        virtual void on_disable() override
        {
			*scr_globals::tuneables.at(87).as<PINT>() = *g_tunables_service->get_tunable<int*>(RAGE_JOAAT("IDLEKICK_WARNING1"));
			*scr_globals::tuneables.at(87).at(1).as<PINT>() = *g_tunables_service->get_tunable<int*>(RAGE_JOAAT("IDLEKICK_WARNING2"));
			*scr_globals::tuneables.at(87).at(2).as<PINT>() = *g_tunables_service->get_tunable<int*>(RAGE_JOAAT("IDLEKICK_WARNING3"));
			*scr_globals::tuneables.at(87).at(3).as<PINT>() = *g_tunables_service->get_tunable<int*>(RAGE_JOAAT("IDLEKICK_KICK"));
        }
	};

	no_idle_kick g_no_idle_kick("noidlekick", "NO_IDLE_KICK", "Prevents you from being kicked while idling.", g.tunables.no_idle_kick);
}
