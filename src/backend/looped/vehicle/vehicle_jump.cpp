#include "backend/looped_command.hpp"
#include "gta/enums.hpp"
#include "natives.hpp"

namespace big
{
	class vehicle_jump : looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override
		{
			PAD::DISABLE_CONTROL_ACTION(0, (int)ControllerInputs::INPUT_VEH_HANDBRAKE, false);
			if (self::veh && PAD::IS_DISABLED_CONTROL_JUST_PRESSED(0, (int)ControllerInputs::INPUT_VEH_HANDBRAKE))
			{
				ENTITY::APPLY_FORCE_TO_ENTITY(self::veh, 1, 0.0, 0.0, 20, 0.0, 0.0, 0.0, 0, 0, 1, 1, 0, 1);
			}
		}
	};

	vehicle_jump
	    g_vehicle_jump("vehjump", "VEHICLE_JUMP", "VEHICLE_JUMP_DESC", g.vehicle.vehicle_jump);
}
