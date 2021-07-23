#include "backend/looped/looped.hpp"
#include "script_global.hpp"

namespace big
{
	void looped::tunables_disable_phone()
	{
		if (g.tunables.disable_phone)
			*script_global(19984).as<bool*>() = true;
	}
}