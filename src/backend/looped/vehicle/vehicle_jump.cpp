#include "backend/looped/looped.hpp"
#include "gta/enums.hpp"
#include "natives.hpp"

namespace big
{
	void looped::vehicle_jump()
	{
		if (!g->vehicle.vehicle_jump) return;

		const auto vehicle = self::veh;

		if (!vehicle || !ENTITY::IS_ENTITY_A_VEHICLE(vehicle))
		{
			return;
		}

		if (PAD::IS_CONTROL_JUST_PRESSED(0, (int)ControllerInputs::INPUT_VEH_HANDBRAKE))
		{
			ENTITY::APPLY_FORCE_TO_ENTITY(vehicle, 1, 0.0, 0.0, 20, 0.0, 0.0, 0.0, 0, 0, 1, 1, 0, 1);
		}
	}
}
