#pragma once

namespace big
{
	inline struct g_notifications_t
	{
		struct pair
		{
			bool log    = false;
			bool notify = false;

			NLOHMANN_DEFINE_TYPE_INTRUSIVE(pair, log, notify)
		};

		pair gta_thread_kill{}, gta_thread_start{};

		pair player_join, player_leave{};

		pair transaction_rate_limit{};

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(g_notifications_t, player_join, player_leave, transaction_rate_limit)
	} g_notifications{};
}