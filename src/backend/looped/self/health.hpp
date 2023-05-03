#pragma once

#include "backend/looped_command.hpp"

namespace big
{
	class health_regen_looped : public looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override;
		virtual void on_disable() override;
	};

	namespace cmd
	{
		health_regen_looped g_health_regen_looped("healthregen", "Override Health Regen", "Turn on the regen multiplier you have set.",
		    g.self.healthregen);
	}
}
