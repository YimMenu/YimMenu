#include "keep_on_ground.hpp"

#include "natives.hpp"

namespace big
{
	void keep_on_ground::on_tick()
	{
		auto model = ENTITY::GET_ENTITY_MODEL(self::veh);

		if (ENTITY::IS_ENTITY_IN_AIR(self::veh) && (VEHICLE::IS_THIS_MODEL_A_CAR(model) || VEHICLE::IS_THIS_MODEL_A_BIKE(model)))
			VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(self::veh, 5.0);
	}
}
