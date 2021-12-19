#include "common.hpp"
#include "features.hpp"
#include "logger.hpp"
#include "script.hpp"
#include "natives.hpp"

#include "backend/backend.hpp"

namespace big
{
	void features::run_tick()
	{
		backend::loop();
	}

	bool features::unlimited_ammo_bool = false;

	void features::unlimited_ammo(Ped ped)
	{

		if (features::unlimited_ammo_bool)
		{
			WEAPON::SET_PED_INFINITE_AMMO(ped, true, 0);
		}
		else
		{
			WEAPON::SET_PED_INFINITE_AMMO(ped, false, 0);
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
