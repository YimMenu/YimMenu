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
		int trainSpeed = ENTITY::GET_ENTITY_SPEED(train::get_closest_train());

		if (g.world.train.drive_train)
		{
			if (PAD::IS_CONTROL_PRESSED(0, 71))
				trainSpeed++;
			if (PAD::IS_CONTROL_PRESSED(0, 72))
				trainSpeed--;

			train::set_train_speed(trainSpeed);
		}
	}

	void looped::derail_train()
	{
		int train = train::get_closest_train();

		if (train != 0)
			VEHICLE::SET_RENDER_TRAIN_AS_DERAILED(train, g.world.train.derail_train);
	}
}