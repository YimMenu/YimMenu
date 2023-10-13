#pragma once

namespace big
{
	inline struct g_session_browser_t
	{
		bool region_filter_enabled = true;
		int region_filter          = 0;

		bool language_filter_enabled = false;
		int language_filter          = 0;

		bool pool_filter_enabled = false;
		int pool_filter          = 0;

		bool player_count_filter_enabled = false;
		int player_count_filter_minimum  = 0;
		int player_count_filter_maximum  = 32;

		int sort_method    = 0;
		int sort_direction = 0;

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(g_session_browser_t, region_filter_enabled, region_filter, language_filter_enabled, language_filter, player_count_filter_enabled, player_count_filter_minimum, player_count_filter_maximum, sort_method, sort_direction, pool_filter_enabled, pool_filter)
	} g_session_browser{};
}