#pragma once

#include "backend/looped/looped.hpp"
#include "backend/looped_command.hpp"

namespace big
{
	class no_collision : public looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override;

		virtual void on_disable() override;
	};

	namespace cmd
	{
		inline no_collision g_no_collision("nocollision", "No Collision", "Allows you to walk through vehicles and most obstacles",
		    g.self.no_collision);
	}
}
