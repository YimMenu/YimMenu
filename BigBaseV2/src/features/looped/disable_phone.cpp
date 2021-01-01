#include "features.hpp"
#include "script_global.hpp"

namespace big
{
	void features::disable_phone()
	{
		if (g_settings.options["disable_phone"].get<bool>())
			*script_global(19664).as<int*>() = 1;
	}
}