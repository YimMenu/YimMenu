#include "features.hpp"
#include "features/custom_guns.hpp"
#include "features/protections.hpp"
#include "features/self.hpp"
#include "features/sys.hpp"
#include "features/tunables.hpp"
#include "features/util.hpp"
#include "features/vehicle.hpp"
#include "features/world.hpp"
#include "script.hpp"

namespace big
{
	void features::run_tick()
	{
		// System
		sys::loop();

		// Custom Guns
		custom_guns::loop();

		// Protections
		protections::loop();

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
