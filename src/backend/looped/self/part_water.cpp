#include "backend/looped/looped.hpp"
#include "backend/looped_command.hpp"
#include "natives.hpp"

namespace big
{
	class partwater : looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override
		{
			WATER::RESET_DEEP_OCEAN_SCALER();

			Vector3 coords = self::pos;
			float offset[] = {-4, 4};

			for (int i = 0; i < 5; i++)
			{
				if (i < 2)
				{
					coords.x += offset[(i % 2 == 0)];
				}
				else if (i < 4)
				{
					coords.y += offset[(i % 2 == 0)];
				}
				WATER::MODIFY_WATER(coords.x, coords.y, 0.0f, 300.0f);
			}
		}
	};

	partwater g_partwater("partwater", "Part Water", "Makes you like Moses", g.world.water.part_water);
}
