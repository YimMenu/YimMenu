#include "common.hpp"
#include "features.hpp"
#include "logger.hpp"
#include "script.hpp"

#include "backend/backend.hpp"

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
