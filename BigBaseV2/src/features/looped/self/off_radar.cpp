#include "features/self.hpp"
#include "natives.hpp"
#include "script_global.hpp"

namespace big
{
	void self::off_radar()
	{
		if (g_settings.options["off_radar"].get<bool>())
		{
			if (PLAYER::IS_PLAYER_ONLINE())
			{
				*script_global(2425869).at(g_player.id, 443).at(204).as<int*>() = 1;
				*script_global(2440049).at(70).as<int*>() = NETWORK::GET_NETWORK_TIME() + 999;
			}
		}
	}
}