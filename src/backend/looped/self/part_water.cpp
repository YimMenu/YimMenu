#include "backend/looped/looped.hpp"
#include "natives.hpp"

namespace big
{
	void looped::self_part_water()
	{
		if (g.self.part_water)
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
	}
}