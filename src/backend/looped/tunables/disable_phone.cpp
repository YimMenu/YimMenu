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
			*script_global(20483).as<bool*>() = true;
		}

		virtual void on_disable() override
		{
			*script_global(20483).as<bool*>() = false;
		}
	};

	disable_phone g_disable_phone("nophone", "DISABLE_PHONE", "DISABLE_PHONE_DESC", g.tunables.disable_phone);
}
