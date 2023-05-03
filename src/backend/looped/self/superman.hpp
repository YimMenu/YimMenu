#pragma once

#include "backend/looped_command.hpp"

namespace big
{
	class superman : public looped_command
	{
		using looped_command::looped_command;

		void apply_force(float x, float y, float z);

		virtual void on_tick() override;

		virtual void on_enable() override;
	};

	namespace cmd
	{
		inline superman g_superman("superman", "Superman", "Fly like a superman", g.self.superman);
	}
}
