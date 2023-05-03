#pragma once

#include "backend/looped_command.hpp"

namespace big
{
	class super_run : public looped_command
	{
		using looped_command::looped_command;

		const float run_cap = 100.f;
		float run_speed     = 10.f;

		virtual void on_tick() override;

		virtual void on_disable() override;
	};

	namespace cmd
	{
		inline super_run g_super_run("fastrun", "Super Run", "Makes you run much faster", g.self.super_run);
	}
}
