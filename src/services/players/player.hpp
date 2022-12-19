#pragma once
#include "player_service.hpp"
#include "rate_limiter.hpp"

class CVehicle;

namespace rage
{
	class snPlayer;
	class snPeer;
}

namespace big
{
	class player final
	{
		friend class player_service;

		CNetGamePlayer* m_net_game_player = nullptr;
		std::string m_identifier;
		bool m_is_friend;

	public:
		explicit player(CNetGamePlayer* net_game_player);
		~player() = default;

		player(const player&) = default;
		player(player&&) noexcept = default;
		player& operator=(const player&) = default;
		player& operator=(player&&) noexcept = default;

		float screen_position_x = -1.f;
		float screen_position_y = -1.f;

		[[nodiscard]] CVehicle* get_current_vehicle() const;
		[[nodiscard]] const char* get_name() const;
		[[nodiscard]] rage::rlGamerInfo* get_net_data() const;
		[[nodiscard]] CNetGamePlayer* get_net_game_player() const;
		[[nodiscard]] CPed* get_ped() const;
		[[nodiscard]] CPlayerInfo* get_player_info() const;
		[[nodiscard]] class rage::snPlayer* get_session_player();
		[[nodiscard]] class rage::snPeer* get_session_peer();
 
		[[nodiscard]] uint8_t id() const;

		[[nodiscard]] bool is_friend() const;
		[[nodiscard]] bool is_host() const;
		[[nodiscard]] bool is_valid() const;

		bool off_radar = false;
		bool never_wanted = false;
		bool semi_godmode = false;

		rate_limiter m_host_migration_rate_limit{ 1s, 20 };
		rate_limiter m_play_sound_rate_limit{ 1s, 10 };

		bool exposed_desync_protection = false;
		bool is_modder = false;
		bool block_join = false;
		int block_join_reason = 0;
		bool is_spammer = false;

		std::optional<std::uint32_t> player_time_value;
		std::optional<std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds>> player_time_value_received_time;
		std::optional<std::uint32_t> time_difference;
		std::uint32_t num_time_syncs_sent = 9999;

	protected:
		bool equals(const CNetGamePlayer* net_game_player) const;

		[[nodiscard]] std::string to_lowercase_identifier() const;

	};
}