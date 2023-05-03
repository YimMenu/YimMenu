#include "horn_boost.hpp"

#include "gta/enums.hpp"
#include "natives.hpp"

namespace big
{
	void horn_boost::on_tick()
	{
		Vehicle vehicle = self::veh;

		if (vehicle == 0)
		{
			horn_boost_speed = horn_boost_speed_default;
			return;
		}

		if (PAD::IS_CONTROL_JUST_PRESSED(0, (int)ControllerInputs::INPUT_VEH_HORN))
			horn_boost_speed = ENTITY::GET_ENTITY_SPEED(vehicle);

		if (PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_VEH_HORN))
		{
			if (horn_boost_speed < horn_boost_speed_max)
				horn_boost_speed += horn_boost_speed_increment;

			const auto velocity = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(vehicle, 0.f, horn_boost_speed, 0.f) - ENTITY::GET_ENTITY_COORDS(vehicle, true);
			ENTITY::SET_ENTITY_VELOCITY(vehicle, velocity.x, velocity.y, velocity.z);
		}
		else if (PAD::IS_CONTROL_JUST_RELEASED(0, (int)ControllerInputs::INPUT_VEH_HORN))
			horn_boost_speed = horn_boost_speed_default;
	}
}
