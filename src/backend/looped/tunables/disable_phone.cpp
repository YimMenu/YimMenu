#include "backend/looped_command.hpp"
#include "core/scr_globals.hpp"
#include "core/data/tunables.hpp"
#include "natives.hpp"

namespace big
{
	class disable_phone : looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override
		{
			*scr_globals::mobile.as<PBOOL>() = TRUE;
		}

		virtual void on_disable() override
		{
			*scr_globals::mobile.as<PBOOL>() = FALSE;
		}
	};

	disable_phone g_disable_phone("nophone", "Disable Phone", "Blocks phone and stops all phone calls", g_tunables.disable_phone);
}
