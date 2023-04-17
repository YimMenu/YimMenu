#pragma once

namespace big
{
	class matchmaking_service
	{
	public:
		constexpr static int MAX_SESSIONS_TO_FIND = 1054;

		struct session_attributes
		{
			int discriminator;
			int player_count;
			int region;
			int language;
		};

		struct session
		{
			rage::rlSessionInfo info;
			session_attributes attributes;
			bool is_valid;
		};

	private:
		int m_num_sessions_found = 0;
		bool m_active            = false;
		session m_found_sessions[MAX_SESSIONS_TO_FIND];

	public:
		matchmaking_service();
		~matchmaking_service();
		bool matchmake(std::optional<int> constraint = std::nullopt);

		inline int get_num_found_sessions()
		{
			return m_num_sessions_found;
		}

		inline session* get_found_sessions()
		{
			return m_found_sessions;
		}

		inline bool is_active()
		{
			return m_active;
		}
	};

	inline matchmaking_service* g_matchmaking_service;
}