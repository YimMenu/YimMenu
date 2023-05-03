#pragma once

#include "backend/looped_command.hpp"

namespace big
{
	class blackhole : public looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override;
	};

	namespace cmd
	{
		inline blackhole g_blackhole("blackhole", "Blackhole", "Spawns a black hole that picks up all the peds and vehicles in your area.",
		    g.world.blackhole.enable);

		inline bool_command g_blackhole_peds("blackholeincpeds", "Peds", "Includes all nearby peds in the blackholes path of destruction",
		    g.world.blackhole.include_peds);

		inline bool_command g_blackhole_vehicles("blackholeincvehs", "Vehicles", "Includes all nearby vehicles in the blackholes path of destruction",
		    g.world.blackhole.include_vehicles);
	}
}
