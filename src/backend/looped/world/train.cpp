#include "backend/looped/looped.hpp"
#include "gta/enums.hpp"
#include "natives.hpp"
#include "util/blip.hpp"
#include "util/entity.hpp"
#include "util/train.hpp"

namespace big
{
	void looped::drive_train()
	{
		if (g.train.drive_train)
		{

		}
	}

	void looped::derail_train()
	{
		if (g.train.derail_train)
		{
			int train = train::get_closest_train();
			if (train != 0 && g.train.derail_train)
				VEHICLE::SET_RENDER_TRAIN_AS_DERAILED(train, true);
		}
	}

}