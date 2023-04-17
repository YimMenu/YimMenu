#include "backend/looped_command.hpp"
#include "pointers.hpp"
#include "util/vehicle.hpp"

namespace big
{
	class veh_no_collision : looped_command
	{
		using looped_command::looped_command;

		virtual void on_enable() override
		{
			vehicle::disable_collisions::m_patch->apply();
		}

		virtual void on_tick() override
		{

		}

		virtual void on_disable() override
		{
			vehicle::disable_collisions::m_patch->restore();
		}
	};
	veh_no_collision g_veh_no_collision("vehnocollision", "No Collision", "Same as Ped No Collision, except this is global and also affects Ped", g.vehicle.no_collision);
}
