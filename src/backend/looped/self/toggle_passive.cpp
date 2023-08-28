#include "backend/looped_command.hpp"
#include "core/scr_globals.hpp"
#include "natives.hpp"
#include "script_global.hpp"

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
			NETWORK::SET_LOCAL_PLAYER_AS_GHOST(false, false);
			*script_global(1574582).as<bool*>() = false;
			*scr_globals::tuneables.at(27371).as<int*>() = 30000;
			PED::SET_PED_CONFIG_FLAG(self::ped, 342, false); // Disable NotAllowedToJackAnyPlayers
			PED::SET_PED_CONFIG_FLAG(self::ped, 122, false); // Disable DisableMelee
			PLAYER::SET_PLAYER_VEHICLE_DEFENSE_MODIFIER(self::ped, 1.f);
		}
	};

	toggle_passive g_toggle_passive("passive", "PASSIVE", "PASSIVE_DESC", g.self.passive);
}