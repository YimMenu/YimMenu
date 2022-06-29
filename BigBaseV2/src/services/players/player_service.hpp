#pragma once

namespace big
{
	class player_service;
	class player final
	{
		friend player_service;

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

		[[nodiscard]] CAutomobile* get_current_vehicle() const;
		[[nodiscard]] const char* get_name() const;
		[[nodiscard]] rage::netPlayerData* get_net_data() const;
		[[nodiscard]] CNetGamePlayer* get_net_game_player() const;
		[[nodiscard]] CPed* get_ped() const;
		[[nodiscard]] CPlayerInfo* get_player_info() const;

		[[nodiscard]] uint8_t id() const;

		[[nodiscard]] bool is_friend() const;
		[[nodiscard]] bool is_host() const;
		[[nodiscard]] bool is_valid() const;

	protected:
		bool equals(const CNetGamePlayer* net_game_player) const;

		[[nodiscard]] std::string to_lowercase_identifier() const;

	};

	using player_ptr = std::shared_ptr<player>;
	using players = std::map<std::string, player_ptr>;

	class player_service final
	{
		CNetGamePlayer** m_self;

		player_ptr m_self_ptr;

		players m_players;

		player_ptr m_dummy = std::make_shared<player>(nullptr);
		player_ptr m_selected_player;
	public:

		player_service();
		~player_service();

		player_service(const player_service&) = delete;
		player_service(player_service&&) noexcept = delete;
		player_service& operator=(const player_service&) = delete;
		player_service& operator=(player_service&&) noexcept = delete;

		void do_cleanup();

		[[nodiscard]] player_ptr get_self();

		[[nodiscard]] player_ptr get_by_name(std::string name);
		[[nodiscard]] player_ptr get_by_msg_id(uint32_t msg_id) const;
		[[nodiscard]] player_ptr get_by_host_token(uint64_t token) const;
		[[nodiscard]] player_ptr get_selected() const;

		void player_join(CNetGamePlayer* net_game_player);
		void player_leave(CNetGamePlayer* net_game_player);

		players& players()
		{ return m_players; }

		void set_selected(player_ptr plyr);

	};

	inline player_service* g_player_service{};
}
