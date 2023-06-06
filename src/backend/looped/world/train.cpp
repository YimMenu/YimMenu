#include "util/train.hpp"

#include "backend/looped/looped.hpp"
#include "gta/enums.hpp"
#include "natives.hpp"
#include "util/blip.hpp"
#include "util/entity.hpp"

namespace big
{
	void looped::drive_train()
	{
		if (self::veh && VEHICLE::IS_THIS_MODEL_A_TRAIN(ENTITY::GET_ENTITY_MODEL(self::veh)))
		{
			int trainSpeed = ENTITY::GET_ENTITY_SPEED(self::veh);

			if (g.world.train.drive_train)
			{
				if (PAD::IS_CONTROL_PRESSED(0, 71))
					trainSpeed++;

				if (PAD::IS_CONTROL_PRESSED(0, 72))
					trainSpeed--;

				VEHICLE::SET_TRAIN_CRUISE_SPEED(self::veh, trainSpeed);
			}
		}
	}

	void looped::derail_train()
	{
		if (self::veh && VEHICLE::IS_THIS_MODEL_A_TRAIN(ENTITY::GET_ENTITY_MODEL(self::veh)))
			VEHICLE::SET_RENDER_TRAIN_AS_DERAILED(self::veh, g.world.train.derail_train);
	}
}