#pragma once

#include "backend/looped_command.hpp"

namespace big
{
	class vehicle_rain : public looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override;
	};

	namespace cmd
	{
		inline vehicle_rain g_vehicle_rain("vehiclerain", "Rain Vehicles", "Drops surround vehicles, vehicles can hit and kill you!",
		    g.world.nearby.veh_rain);
	}
}
