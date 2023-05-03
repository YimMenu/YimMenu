#pragma once

#include "backend/looped_command.hpp"

namespace big
{
	class rapid_fire : public looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override;
	};

	namespace cmd
	{
		inline rapid_fire g_rapid_fire("rapidfire", "Rapid Fire", "Makes your weapon fire insanely fast", g.weapons.rapid_fire);
	}
}
