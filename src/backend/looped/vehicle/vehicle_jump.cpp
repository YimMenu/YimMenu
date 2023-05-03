#include "vehicle_jump.hpp"

#include "gta/enums.hpp"
#include "natives.hpp"

namespace big
{
	void vehicle_jump::on_tick()
	{
		if (self::veh && PAD::IS_CONTROL_JUST_PRESSED(0, (int)ControllerInputs::INPUT_VEH_HANDBRAKE))
		{
			ENTITY::APPLY_FORCE_TO_ENTITY(self::veh, 1, 0.0, 0.0, 20, 0.0, 0.0, 0.0, 0, 0, 1, 1, 0, 1);
		}
	}
}
