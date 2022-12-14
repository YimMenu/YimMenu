#include "backend/looped/looped.hpp"
#include "script_global.hpp"

namespace big
{
	void looped::tunables_disable_phone()
	{
		*script_global(20366).as<bool*>() = g->tunables.disable_phone; // Who even uses that...
	}
}