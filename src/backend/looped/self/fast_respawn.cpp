#include "backend/looped/looped.hpp"
#include "backend/looped_command.hpp"
#include "fiber_pool.hpp"
#include "gta/enums.hpp"
#include "natives.hpp"

namespace big
{
	class fast_respawn : looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override
		{
			if (PED::IS_PED_DEAD_OR_DYING(self::ped, true))
			{
				PED::RESURRECT_PED(self::ped);
				ENTITY::SET_ENTITY_COORDS_NO_OFFSET(self::ped, self::pos.x, self::pos.y, self::pos.z, 0, 0, 0);
				TASK::CLEAR_PED_TASKS_IMMEDIATELY(self::ped);
				MISC::FORCE_GAME_STATE_PLAYING();
			}
		}
	};

	fast_respawn g_fast_respawn("fastrespawn", "Instant Respawn", "Makes you respawn instantly when you die", g.self.fast_respawn);
}
