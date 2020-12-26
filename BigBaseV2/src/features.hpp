#pragma once
#include "common.hpp"
#include "fiber_pool.hpp"
#include "structs/player.hpp"
#include "structs/temp.hpp"
#include "features/notify.hpp"
#include "features/teleport.hpp"

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

		void god_mode();
		void never_wanted();
		void no_bike_fall();
		void no_idle_kick();
		void no_ragdoll();
		void off_radar();
		void spoof_rank();
		void super_sprint();

		void update_screen_sizes();
		void update_player_structs();
	}
}
