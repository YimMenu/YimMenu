#pragma once
#include "player.hpp"

namespace big
{
	class player;

	using player_ptr   = std::shared_ptr<player>;
	using player_entry = std::pair<std::string, player_ptr>;
	using players      = std::multimap<std::string, player_ptr>;

	class player_service final
	{
		CNetGamePlayer** m_self;

		player_ptr m_self_ptr;

		players m_players;

		player_ptr m_dummy = std::make_shared<player>(nullptr);
		player_ptr m_selected_player;

		std::unordered_set<std::uint64_t> m_players_sending_modder_beacons;

	public:
		player_service();
		~player_service();

		player_service(const player_service&)                = delete;
		player_service(player_service&&) noexcept            = delete;
		player_service& operator=(const player_service&)     = delete;
		player_service& operator=(player_service&&) noexcept = delete;

		void do_cleanup();

		[[nodiscard]] player_ptr get_self();

		[[nodiscard]] player_ptr get_by_msg_id(uint32_t msg_id) const;
		[[nodiscard]] player_ptr get_by_id(uint32_t id) const;
		[[nodiscard]] player_ptr get_by_host_token(uint64_t token) const;
		[[nodiscard]] player_ptr get_selected() const;
		[[nodiscard]] player_ptr get_by_name(const std::string_view name) const;
		[[nodiscard]] player_ptr get_by_name_closest(const std::string_view name) const;
		[[nodiscard]] player_ptr get_closest(bool exclude_friends = false) const;

		void player_join(CNetGamePlayer* net_game_player);
		void player_leave(CNetGamePlayer* net_game_player);
		void mark_player_as_sending_modder_beacons(std::uint64_t rid);
		bool did_player_send_modder_beacon(std::uint64_t rid);

		players& players()
		{
			return m_players;
		}

		void iterate(const std::function<void(const player_entry& entry)> func)
		{
			for (const auto& iter : m_players)
				func(iter);
		}

		void set_selected(player_ptr plyr);
	};

	inline player_service* g_player_service{};
}
