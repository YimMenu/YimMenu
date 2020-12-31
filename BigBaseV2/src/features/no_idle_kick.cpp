#include "features.hpp"
#include "script_global.hpp"

namespace big
{
	void features::no_idle_kick()
	{
		bool bNoIdleKick = g_settings.options["no_idle_kick"].get<bool>();

		if (bNoIdleKick)
		{
			*script_global(1377236).at(1165).as<int*>() = -1;
			*script_global(1377236).at(1149).as<int*>() = -1;
		}
	}
}