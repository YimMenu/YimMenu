#pragma once

namespace big
{
	inline struct g_world
	{
		struct custom_time
		{
			bool override_time = {};
			int hour{}, minute{}, second{};
		} custom_time;

		struct nearby
		{
			bool ignore = false;

			struct auto_disarm
			{
				bool enable = false;
			} auto_disarm{};
		} nearby{};

		int local_weather = 0;
	} g_world{};
}