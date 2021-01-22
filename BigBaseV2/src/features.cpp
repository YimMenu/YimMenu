#include "features.hpp"
#include "logger.hpp"
#include "natives.hpp"
#include "script.hpp"

namespace big
{
	void features::run_tick()
	{
		g_playerId = PLAYER::PLAYER_ID();

		// System
		update_player_structs();
		update_screen_sizes();

		// Custom Guns
		cage_gun();
		delete_gun();
		gravity_gun();
		money_gun();
		vehicle_gun();

		// Tunable
		disable_phone();
		no_idle_kick();

		// Self
		god_mode();
		never_wanted();
		noclip();
		no_ragdoll();
		off_radar();
		super_sprint();
		spoof_rank();

		// Vehicle
		handling();
		no_bike_fall();
		speedo_meter();
		sticky_tyres();

		// World
		population_modifiers();

		// Util
		spectate_player();

		// Protections
		replay_interface();
		//version_mismatch();
	}

	void features::script_func()
	{
		while (true)
		{
			TRY_CLAUSE
			{
				run_tick();
			}
			EXCEPT_CLAUSE
			script::get_current()->yield();
		}
	}
}
