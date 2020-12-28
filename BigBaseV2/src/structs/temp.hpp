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
		int spoofed_rank = 0;
		game_time time = game_time{};
		int wanted_level = 0;
		int teleport_location = 0;
		int weather_type = 0;
	};
}