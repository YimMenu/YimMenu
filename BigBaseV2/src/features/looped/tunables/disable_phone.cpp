#include "features/tunables.hpp"
#include "script_global.hpp"

namespace big
{
	void tunables::disable_phone()
	{
		if (g_settings.options["disable_phone"])
			*script_global(19664).as<int*>() = 1;
	}
}