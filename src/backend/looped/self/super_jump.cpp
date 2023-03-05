#include "backend/looped_command.hpp"
#include "gta/enums.hpp"
#include "natives.hpp"

namespace big
{

	class super_jump_looped : looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override
		{
			if (PAD::IS_CONTROL_JUST_PRESSED(0, (int)ControllerInputs::INPUT_JUMP) && !PED::IS_PED_IN_ANY_VEHICLE(self::ped, NULL) && !ENTITY::IS_ENTITY_IN_AIR(self::ped))
			{
				ENTITY::APPLY_FORCE_TO_ENTITY_CENTER_OF_MASS(self::ped, 0, 0, 10000, 5000, true, true, true, false);
			}
		}
	};

	super_jump_looped g_super_jump_looped("superjump", "Super Jump", "Allows you to jump really high", g.self.super_jump);
}