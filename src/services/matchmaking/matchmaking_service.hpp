#pragma once

#include <network/MatchmakingId.hpp>
#include <rage/rlTaskStatus.hpp>

namespace rage
{
	class rlSessionInfo;
	class rlSessionDetailMsg;
}

class MatchmakingAttributes;

namespace big
{
	class matchmaking_service
	{
	public:
		constexpr static int MAX_SESSIONS_TO_FIND = 1000;

		struct session_attributes
		{
			int discriminator;
			int player_count;
			int region;
			int language;
			int multiplex_count = 1;
		};

		struct session
		{
			rage::rlSessionInfo info;
			session_attributes attributes;
			bool is_valid;
		};

	private:
		int m_num_sessions_found = 0;
		int m_num_valid_sessions = 0;
		bool m_active            = false;
		session m_found_sessions[MAX_SESSIONS_TO_FIND];
		std::unordered_map<std::uint32_t, std::vector<MatchmakingId>> m_multiplexed_sessions;

		void patch_matchmaking_attributes(MatchmakingAttributes* attributes);

	public:
		matchmaking_service();
		~matchmaking_service();
		bool matchmake(std::optional<int> constraint = std::nullopt, std::optional<bool> enforce_player_limit = std::nullopt);

		bool handle_advertise(int num_slots, int available_slots, rage::rlSessionInfo* info, MatchmakingAttributes* attributes, MatchmakingId* out_id, rage::rlTaskStatus* status);
		void handle_update(int num_slots, int available_slots, rage::rlSessionInfo* info, MatchmakingAttributes* attributes, MatchmakingId* id);
		bool handle_unadvertise(MatchmakingId* id);
		void handle_session_detail_send_response(rage::rlSessionDetailMsg* msg);

		inline int get_num_found_sessions()
		{
			return m_num_sessions_found;
		}

		inline int get_num_valid_sessions()
		{
			return m_num_valid_sessions;
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