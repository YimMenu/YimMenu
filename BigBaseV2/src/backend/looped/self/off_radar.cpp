#include "backend/looped/looped.hpp"
#include "pointers.hpp"
#include "natives.hpp"
#include "script_global.hpp"

namespace big
{
	void looped::self_off_radar()
	{
		if (g.self.off_radar)
		{
			*script_global(2689156).at(PLAYER::GET_PLAYER_INDEX(), 453).at(209).as<int*>() = 1;
			*script_global(2703656).at(70).as<int*>() = NETWORK::GET_NETWORK_TIME() + 1;
		}
	}
}