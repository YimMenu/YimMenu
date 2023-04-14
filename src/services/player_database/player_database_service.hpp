#pragma once
#include "persistent_player.hpp"
#include "services/players/player.hpp"

namespace big
{
	class player_database_service
	{
		std::unordered_map<std::uint64_t, persistent_player> m_players;
		persistent_player* m_selected = nullptr;

	public:
		std::filesystem::path m_file_path;
		player_database_service();
		~player_database_service();

		void save();
		void load();

		std::unordered_map<std::uint64_t, persistent_player>& get_players();
		persistent_player* get_player_by_rockstar_id(std::uint64_t rockstar_id);
		persistent_player* get_or_create_player(player_ptr player);
		void update_rockstar_id(std::uint64_t old, std::uint64_t _new);
		void remove_rockstar_id(std::uint64_t rockstar_id);

		void set_selected(persistent_player* selected);
		persistent_player* get_selected();

		void update_player_states();
		void invalidate_player_states();
	};

	inline player_database_service* g_player_database_service;
}