#include "backend/looped/looped.hpp"
#include "script_global.hpp"

namespace big
{
	void looped::tunables_no_idle_kick()
	{
		if (g->tunables.no_idle_kick)
		{
			*script_global(1644218).at(1149).as<int*>() = 0;
			*script_global(1644218).at(1165).as<int*>() = 0;
		}
	}
}