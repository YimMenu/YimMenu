#pragma once

#include "backend/looped_command.hpp"

namespace big
{
	class off_radar : public looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override;

		virtual void on_disable() override;
	};

	namespace cmd
	{
		inline off_radar g_off_radar("otr", "Off Radar", "Hides your blip from other players", g.self.off_radar);
	}
}
