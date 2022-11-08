#include "backend/looped/looped.hpp"
#include "script_global.hpp"

namespace big
{
	// allows for spawning unreleased vehicles in online and online vehicles in single player
	void looped::vehicle_despawn_bypass()
	{
		*script_global(4539659).as<bool*>() = true;
	}
}