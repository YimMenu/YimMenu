#pragma once

#include "backend/looped_command.hpp"

namespace big
{
	class instant_brake : public looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override;
	};

	namespace cmd
	{
		inline instant_brake g_instant_brake("instantbrake", "Instant Brake", "Makes your vehicle stop instantly when you press the brake",
		    g.vehicle.instant_brake);
	}
}
