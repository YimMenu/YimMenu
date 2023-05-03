#pragma once

#include "backend/looped_command.hpp"

namespace big
{
	class veh_unlimited_weapons : public looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override;
	};

	namespace cmd
	{
		inline veh_unlimited_weapons g_veh_unlimited_weapons("vehallweapons", "Allow Weapons In Vehicle", "Allows you to use all weapons in vehicle",
		    g.vehicle.unlimited_weapons);
	}
}
