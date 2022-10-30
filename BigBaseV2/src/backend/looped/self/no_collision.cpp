#include "backend/looped/looped.hpp"

namespace big
{
	static bool bLastNoCollsion = false;

	void looped::self_no_collision()
	{
		if (g_local_player == nullptr) return;

		bool bNoCollsion = g->self.no_collision;

		auto set_collison = [](float value) 
		{
			static int offsets[] = { 0x30, 0x10, 0x20, 0x70, 0x00, 0x2C };
			uintptr_t address = (uintptr_t)&g_local_player;
			for (auto item : offsets)
			{
				address = *(uintptr_t*)(address);
				address += item;
			}
			*(float*)address = value;
		};

		if (bNoCollsion)
		{
			set_collison(-1);
			bLastNoCollsion = bNoCollsion;
		}
		else if (bNoCollsion != bLastNoCollsion)
		{
			set_collison(0.25);
			bLastNoCollsion = bNoCollsion;
		}
	}
}
