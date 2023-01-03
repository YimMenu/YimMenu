#include "natives.hpp"
#include "backend/looped_command.hpp"
#include "util/entity.hpp"
#include "gta/enums.hpp"

namespace big
{
	class super_jump_looped : looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override
		{
			if (PAD::IS_CONTROL_JUST_PRESSED(0, INPUT_JUMP) && !PED::IS_PED_IN_ANY_VEHICLE(self::ped, NULL) && !ENTITY::IS_ENTITY_IN_AIR(self::ped))
			{
				TASK::TASK_JUMP(self::ped, true, true, true);
			}
		}
	};
	
	super_jump_looped g_super_jump_looped("superjump", "Super Jump", "Allows You To Jump Really High", g.self.super_jump);
}
