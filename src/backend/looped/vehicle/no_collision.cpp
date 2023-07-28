#include "backend/bool_command.hpp"
#include "pointers.hpp"
#include "util/vehicle.hpp"

namespace big
{
	class veh_no_collision : bool_command
	{
		using bool_command::bool_command;

		virtual void on_enable() override
		{
			vehicle::disable_collisions::m_patch->apply();
		}

		virtual void on_disable() override
		{
			vehicle::disable_collisions::m_patch->restore();
		}
	};
	veh_no_collision g_veh_no_collision("vehnocollision", "NO_COLLISION_VEHICLE", "NO_COLLISION_VEHICLE_DESC", g.vehicle.no_collision);
}
