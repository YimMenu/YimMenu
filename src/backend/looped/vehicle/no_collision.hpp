#pragma once

#include "backend/looped_command.hpp"

namespace big
{
	class veh_no_collision : public looped_command
	{
		using looped_command::looped_command;

		virtual void on_enable() override;

		virtual void on_tick() override;

		virtual void on_disable() override;
	};

	namespace cmd
	{
		inline veh_no_collision g_veh_no_collision("vehnocollision", "No Collision", "Same as Ped No Collision, except this is global and also affects Ped",
		    g.vehicle.no_collision);
	}
}
