#include "backend/looped_command.hpp"
#include "natives.hpp"
#include "script_global.hpp"
#include "core/scr_globals.hpp"

namespace big
{
	class toggle_passive : looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override
		{
			*scr_globals::tuneables.at(27371).as<int*>() = 0; // End Passive Time = 0s
			*script_global(1574582).as<bool*>() = true;
		}

		virtual void on_disable() override
		{
			//NETWORK::SET_LOCAL_PLAYER_AS_GHOST(false, false);
			*script_global(1574582+2).as<bool*>()          = true;
			*script_global(1574582).as<bool*>() = false;
			*scr_globals::tuneables.at(27371).as<int*>() = 30000;
			
		}
	};

	toggle_passive g_toggle_passive("passive", "PASSIVE", "PASSIVE_DESC", g.self.passive);
}