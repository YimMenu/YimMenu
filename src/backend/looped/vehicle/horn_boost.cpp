#include "backend/looped_command.hpp"
#include "gta/enums.hpp"
#include "natives.hpp"

namespace big
{
	class horn_boost : looped_command
	{
		using looped_command::looped_command;
		static constexpr float horn_boost_speed_default   = 10.f;
		static constexpr float horn_boost_speed_max       = 200.f;
		static constexpr float horn_boost_speed_increment = 0.3f;

		float horn_boost_speed = horn_boost_speed_default;

		virtual void on_tick() override
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
	};

	horn_boost g_horn_boost("hornboost", "Horn Boost", "Boosts your vehicle forward when you sound the horn", g.vehicle.horn_boost);
}
