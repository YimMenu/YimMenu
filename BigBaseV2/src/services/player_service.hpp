#pragma once

namespace big
{
	class player_service;
	class player final
	{
		friend player_service;

		CNetGamePlayer* m_net_game_player = nullptr;
		std::string m_identifier;

	public:
		player(CNetGamePlayer* net_game_player);
		virtual ~player() = default;

		CAutomobile* get_current_vehicle();
		const char* get_name();
		rage::netPlayerData* get_net_data();
		CNetGamePlayer* get_net_game_player();
		CPed* get_ped();
		CPlayerInfo* get_player_info();

		uint8_t id();

		bool is_host();
		bool is_valid();

	protected:
		std::string to_lowercase_identifier();

	};

	typedef std::map<std::string, std::unique_ptr<player>> player_list;
	class player_service final
	{
	public:
		player_list m_players;
		player* m_selected_player = nullptr;

		player_service();
		virtual ~player_service();

		void do_cleanup();

		std::unique_ptr<player>& get_by_name(std::string name);

		void player_join(CNetGamePlayer* net_game_player);
		void player_leave(CNetGamePlayer* net_game_player);

	};

	inline player_service* g_player_service{};
}