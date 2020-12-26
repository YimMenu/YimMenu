#pragma once
#include "common.hpp"
#include "structs/player.hpp"
#include "structs/temp.hpp"

namespace big
{
	inline Player g_playerId;
	inline Player g_selectedPlayer = -1;
	inline player g_players[32];

	// Temporary Variable struct
	inline temp g_temp = temp{};

	// Screen Width & Height
	inline int x, y;

	namespace features
	{
		void run_tick();
		void script_func();
	}
}
