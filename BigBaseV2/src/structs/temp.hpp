#pragma once

namespace big
{
	struct game_time
	{
		int hour = 0;
		int minutes = 0;
	};

	struct temp
	{
		int character_slot = 0;
		int set_level = 0;
		int spoofed_rank = 0;
		game_time time = game_time{};
		bool spectate_player = false;
		int teleport_location = 0;
		int wanted_level = 0;
		int weather_type = 0;
	};
}