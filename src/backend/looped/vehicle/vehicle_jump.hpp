#pragma once

#include "backend/looped_command.hpp"

namespace big
{
	class vehicle_jump : public looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override;
	};

	namespace cmd
	{
		inline vehicle_jump
		    g_vehicle_jump("vehjump", "Vehicle Jump", "Makes the vehicle jump when you press the handbrake", g.vehicle.vehicle_jump);
	}
}
