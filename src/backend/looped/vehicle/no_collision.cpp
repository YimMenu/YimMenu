#include "no_collision.hpp"

#include "pointers.hpp"
#include "util/vehicle.hpp"

namespace big
{
	void veh_no_collision::on_enable()
	{
		vehicle::disable_collisions::m_patch->apply();
	}

	void veh_no_collision::on_tick()
	{
	}

	void veh_no_collision::on_disable()
	{
		vehicle::disable_collisions::m_patch->restore();
	}
}
