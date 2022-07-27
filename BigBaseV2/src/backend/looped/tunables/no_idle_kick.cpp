#include "backend/looped/looped.hpp"
#include "script_global.hpp"

namespace big
{
	void looped::tunables_no_idle_kick()
	{
		if (g->tunables.no_idle_kick)
		{
			*script_global(1648034).at(1156).as<int*>() = 0;
			*script_global(1648034).at(1172).as<int*>() = 0;
		}
	}
}