#include "backend/looped/looped.hpp"
#include "natives.hpp"
#include "script_global.hpp"

namespace big
{
	void looped::self_off_radar()
	{
		if (g.self.off_radar)
		{
			*script_global(2426097).at(PLAYER::PLAYER_ID(), 443).at(204).as<int*>() = 1;
			*script_global(2440277).at(70).as<int*>() = NETWORK::GET_NETWORK_TIME();
		}
	}
}