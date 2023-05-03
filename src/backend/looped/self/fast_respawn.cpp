#include "fast_respawn.hpp"

#include "fiber_pool.hpp"
#include "gta/enums.hpp"
#include "natives.hpp"

namespace big
{
	void fast_respawn::on_tick()
	{
		if (PED::IS_PED_DEAD_OR_DYING(self::ped, true))
		{
			PED::RESURRECT_PED(self::ped);
			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(self::ped, self::pos.x, self::pos.y, self::pos.z, 0, 0, 0);
			TASK::CLEAR_PED_TASKS_IMMEDIATELY(self::ped);
			MISC::FORCE_GAME_STATE_PLAYING();
		}
	}
}
