#include "backend/looped/looped.hpp"
#include "natives.hpp"
#include "script_global.hpp"

namespace big
{
	void looped::self_off_radar()
	{
		if (g.self.off_radar)
		{
			*script_global(2426865).at(PLAYER::PLAYER_ID(), 449).at(209).as<bool*>() = true;
			*script_global(2441237).at(70).as<int*>() = NETWORK::GET_NETWORK_TIME() + 1;
		}
	}
}