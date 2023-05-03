#pragma once

#include "backend/looped_command.hpp"

namespace big
{
	class no_vehicle_water_collision : public looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override;

		virtual void on_disable() override;
	};

	namespace cmd
	{
		inline no_vehicle_water_collision
		    g_no_vehicle_water_collision("driveunder", "Drive Underwater", "Allows you to drive underwater", g.vehicle.no_water_collision);
	}
}
