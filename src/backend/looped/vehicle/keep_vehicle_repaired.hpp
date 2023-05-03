#pragma once

#include "backend/looped_command.hpp"

namespace big
{
	class keep_vehicle_repaired : public looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override;
	};

	namespace cmd
	{
		inline keep_vehicle_repaired g_keep_vehicle_repaired("keepfixed", "Keep Vehicle Repaired", "Keeps your vehicle free of wear and tear",
		    g.vehicle.keep_vehicle_repaired);
	}
}
