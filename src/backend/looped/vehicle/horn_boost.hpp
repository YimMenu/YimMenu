#pragma once

#include "backend/looped_command.hpp"

namespace big
{
	class horn_boost : public looped_command
	{
		using looped_command::looped_command;

		static constexpr float horn_boost_speed_default   = 10.f;
		static constexpr float horn_boost_speed_max       = 200.f;
		static constexpr float horn_boost_speed_increment = 0.3f;

		float horn_boost_speed = horn_boost_speed_default;

		virtual void on_tick() override;
	};

	namespace cmd
	{
		inline horn_boost
		    g_horn_boost("hornboost", "Horn Boost", "Boosts your vehicle forward when you sound the horn", g.vehicle.horn_boost);
	}
}
