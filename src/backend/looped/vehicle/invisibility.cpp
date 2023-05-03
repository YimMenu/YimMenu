#include "invisibility.hpp"

#include "fiber_pool.hpp"
#include "natives.hpp"

namespace big
{
	void vehinvisibility::on_tick()
	{
		if (!PED::GET_PED_CONFIG_FLAG(self::ped, 62, false))
		{
			if (last_driving)
			{
				ENTITY::SET_ENTITY_VISIBLE(self::veh, true, 0);
			}

			last_driving = false;
			return;
		}

		last_driving = true;

		ENTITY::SET_ENTITY_VISIBLE(self::veh, false, 0);

		if (g.vehicle.localveh_visibility)
			NETWORK::SET_ENTITY_LOCALLY_VISIBLE(self::veh);
	}

	void vehinvisibility::on_disable()
	{
		ENTITY::SET_ENTITY_VISIBLE(self::veh, true, 0);
	}
}
