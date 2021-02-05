#pragma once

namespace big
{
	struct temp
	{
		struct game_time
		{
			int hour = 0;
			int minutes = 0;
		};

		struct window
		{
			bool handling = false;
			bool player = false;
		};

		bool in_vehicle = false;
		bool is_spectating = false;

		int character_slot = 0;

		int set_level = 0;
		int spoofed_rank = 0;
		int teleport_location = 0;
		int wanted_level = 0;
		int weather_type = 0;

		game_time time = game_time{};
		window windows = window{};
	};
}