#pragma once

#include "backend/looped/looped.hpp"
#include "backend/looped_command.hpp"

namespace big
{
	class no_water_collision : public looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override;

		virtual void on_disable() override;
	};

	namespace cmd
	{
		inline no_water_collision
		    g_no_water_collision("walkunder", "Walk Underwater", "Allows you to walk and shoot underwater", g.self.no_water_collision);
	}
}
