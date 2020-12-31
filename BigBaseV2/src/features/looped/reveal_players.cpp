#include "features.hpp"
#include "script_global.hpp"

namespace big
{
	void features::reveal_players()
	{
		if (g_settings.options["reveal_players"].get<bool>())
		{
			*script_global(2425869).at(1 + (g_playerId * 443)).at(207).as<int*>() = 1;
			*script_global(2440049).at(71).as<int*>() = NETWORK::GET_NETWORK_TIME() + 999;
		}
	}
}