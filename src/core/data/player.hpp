#pragma once
#include "services/players/player_service.hpp"

namespace big
{
	inline struct g_player
	{
		bool spectating        = false;
	} g_player{};
}