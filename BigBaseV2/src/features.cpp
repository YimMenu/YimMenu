#include "features.hpp"
#include "features/custom_guns.hpp"
#include "features/protections.hpp"
#include "features/self.hpp"
#include "features/sys.hpp"
#include "features/tunables.hpp"
#include "features/util.hpp"
#include "features/vehicle.hpp"
#include "features/world.hpp"
#include "pointers.hpp"
#include "script.hpp"

namespace big
{
	void features::run_tick()
	{
		// System
		sys::loop();

		// Protections
		protections::loop();

		if (*g_pointers->m_game_state == eGameState::Playing)
		{
			// Custom Guns
			custom_guns::loop();

			// Self
			self::loop();

			// Tunable
			tunables::loop();

			// Util
			util::loop();

			// Vehicle
			vehicle::loop();

			// World
			world::loop();
		}
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
