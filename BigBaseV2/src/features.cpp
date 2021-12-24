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
	float features::max_vehicle_torque = 5.f;
	float features::max_vehicle_engine = 5.f;

	bool features::unlimited_ammo_bool = false;
	bool features::always_jackpot = false;

	void features::unlimited_ammo(Ped ped)
	{

		if (features::unlimited_ammo_bool)
		{
			WEAPON::SET_PED_INFINITE_AMMO_CLIP(ped, true);
		}
		else
		{
			WEAPON::SET_PED_INFINITE_AMMO_CLIP(ped, false);
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
