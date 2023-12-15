#include "backend/looped/looped.hpp"
#include "backend/looped_command.hpp"
#include "util/misc.hpp"
#include "core/scr_globals.hpp"

namespace big
{
	class fast_respawn : looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override
		{
			// disable wasted sound cause it's annoying
			*scr_globals::disable_wasted_sound.as<bool*>() = true;

			// triggers respawn instantly upon death, has no effect if not respawning so no need to check if the player's dead
			misc::set_bit(&(*scr_globals::freemode_properties.at(1689).at(756).as<int*>()), 1); // Update: freemode -> KILL_STRIP_H -> Above that = "!IS_BIT_SET(global, 2)"
		}

		virtual void on_disable() override
		{
			*scr_globals::disable_wasted_sound.as<bool*>() = false;

			misc::clear_bit(&(*scr_globals::freemode_properties.at(1689).at(756).as<int*>()), 1); 
		}
	};

	fast_respawn g_fast_respawn("fastrespawn", "INSTANT_RESPAWN", "INSTANT_RESPAWN_DESC", g.self.fast_respawn);
}
