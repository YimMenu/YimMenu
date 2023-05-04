#pragma once

#include "backend/looped_command.hpp"

namespace big
{
	class partwater : public looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override;
	};

	namespace cmd
	{
		inline partwater g_partwater("partwater", "Part Water", "Makes you like Moses", g.world.water.part_water);
	}
}
