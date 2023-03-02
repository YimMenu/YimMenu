#include "backend/looped_command.hpp"
#include "gta/enums.hpp"
#include "natives.hpp"

namespace big
{

	class beast_jump_looped : looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override
		{
			if (PAD::IS_CONTROL_JUST_PRESSED(0, (int)ControllerInputs::INPUT_JUMP) && !PED::IS_PED_IN_ANY_VEHICLE(self::ped, NULL) && !ENTITY::IS_ENTITY_IN_AIR(self::ped))
			{
				TASK::TASK_JUMP(self::ped, true, true, true);
			}
		}
	};

	beast_jump_looped g_beast_jump_looped("beastjump", "Beast Jump", "Allows you to jump as if you were the beast like in the Hunt the Beast event",
	    g.self.beast_jump);
}
