#include "backend/looped/looped.hpp"
#include "natives.hpp"
#include "backend/looped_command.hpp"

namespace big
{
	class partwater : looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override
		{
			float offset[] = { -4, 4 };
			for (int i = 0; i < 5; i++)
			{
				if (i < 2)
				{
					self::pos.x += offset[(i % 2 == 0)];
				}
				else if (i < 4)
				{
					self::pos.y += offset[(i % 2 == 0)];
					WATER::MODIFY_WATER(self::pos.x, self::pos.y, -500000.0f, 0.2f);
				}
			}
		}
	};

	partwater g_invisibility("partwater", "Part Water", "Makes you like Moses", g.world.water.part_water);
}
