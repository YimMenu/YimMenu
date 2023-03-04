#include "backend/looped_command.hpp"
#include "core/scr_globals.hpp"
#include "natives.hpp"

namespace big
{
	class disable_phone : looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override
		{
			*script_global(20366).as<bool*>() = true;
		}

		virtual void on_disable() override
		{
			*script_global(20366).as<bool*>() = false;
		}
	};

	disable_phone g_disable_phone("nophone", "Disable Phone", "Blocks phone and stops all phone calls", g.tunables.disable_phone);
}
