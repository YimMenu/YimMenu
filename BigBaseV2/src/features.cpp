#include "common.hpp"
#include "features.hpp"
#include "logger.hpp"
#include "script.hpp"
#include "natives.hpp"
#include "backend/backend.hpp"
#include "util/entity.hpp"
#include "util/vehicle.hpp"
#include "gta/VehicleValues.h"

namespace big
{
	void features::run_tick()
	{
		backend::loop();
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
