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
			if (self::veh && PAD::IS_CONTROL_JUST_PRESSED(0, (int)ControllerInputs::INPUT_VEH_HANDBRAKE))
			{
				ENTITY::APPLY_FORCE_TO_ENTITY(self::veh, 1, 0.0, 0.0, 20, 0.0, 0.0, 0.0, 0, 0, 1, 1, 0, 1);
			}
		}
	};

	vehicle_jump
	    g_vehicle_jump("vehjump", "Vehicle Jump", "Makes the vehicle jump when you press the handbrake", g.vehicle.vehicle_jump);
}
