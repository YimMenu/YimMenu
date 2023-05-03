#pragma once

#include "backend/looped_command.hpp"

namespace big
{
	class high_alert : public looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override;
	};

	namespace cmd
	{
		inline high_alert g_high_alert("highalert", "High Alert", "Not the CoD perk.", g.world.nearby.high_alert);
	}
}
