#include "backend/looped_command.hpp"
#include "script_global.hpp"

namespace big
{
	class toggle_passive : looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override
		{
			*script_global(1574582+1).as<bool*>() = true;
			*script_global(1574582).as<bool*>() = true;
		}

		virtual void on_disable() override
		{
			*script_global(1574582+1).as<bool*>() = false;
			*script_global(1574582).as<bool*>() = false;
		}
	};

	toggle_passive g_toggle_passive("passive", "PASSIVE", "PASSIVE_DESC", g.self.passive);
}