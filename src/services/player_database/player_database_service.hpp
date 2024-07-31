#pragma once
#include "persistent_player.hpp"
#include "services/players/player.hpp"

namespace nlohmann
{
	template<typename T>
	struct adl_serializer<std::shared_ptr<T>>
	{
		static void to_json(json& j, const std::shared_ptr<T>& value)
		{
			j = *value;
		}

		static void from_json(const json& j, std::shared_ptr<T>& value)
		{
			value  = std::make_shared<T>();
			*value = j.get<T>();
		}
	};
}

namespace big
{
	class player_database_service
	{
		std::unordered_map<uint64_t, std::shared_ptr<persistent_player>> m_players;
		std::map<std::string, std::shared_ptr<persistent_player>> m_sorted_players;
		std::shared_ptr<persistent_player> m_selected = nullptr;

		void handle_session_type_change(persistent_player& player, GSType new_session_type);
		static void handle_game_mode_change(uint64_t rid, GameMode old_game_mode, GameMode new_game_mode, std::string mission_id, std::string mission_name); // run in fiber pool
		bool join_being_redirected = false;
		void handle_join_redirect();
		std::atomic_bool updating = false;

	public:
		std::filesystem::path m_file_path;
		player_database_service();
		~player_database_service();

		void save();
		void load();

		std::shared_ptr<persistent_player> add_player(std::int64_t rid, const std::string_view name);
		std::unordered_map<uint64_t, std::shared_ptr<persistent_player>>& get_players();
		std::map<std::string, std::shared_ptr<persistent_player>>& get_sorted_players();
		std::shared_ptr<persistent_player> get_player_by_rockstar_id(uint64_t rockstar_id);
		std::shared_ptr<persistent_player> get_or_create_player(player_ptr player);
		void remove_filtered_players(bool filter_modder, bool filter_trust, bool filter_block_join, bool filter_track_player);
		void update_rockstar_id(uint64_t old, uint64_t _new);
		void remove_rockstar_id(uint64_t rockstar_id);

		void set_selected(std::shared_ptr<persistent_player> selected);
		std::shared_ptr<persistent_player> get_selected();

		void start_update_loop();
		void update_player_states(bool tracked_only = false);

		static bool is_joinable_session(GSType type, GameMode mode);
		static const char* get_session_type_str(GSType type);
		static const char* get_game_mode_str(GameMode mode);
		static bool can_fetch_name(GameMode mode);
		static const char* get_name_by_content_id(const std::string& content_id);
		inline bool is_redirect_join_active()
		{
			return join_being_redirected;
		}
	};

	inline player_database_service* g_player_database_service;
}