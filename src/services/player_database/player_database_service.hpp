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
		std::unordered_map<std::uint64_t, std::shared_ptr<persistent_player>> m_players;
		std::map<std::string, std::shared_ptr<persistent_player>> m_sorted_players;
		std::shared_ptr<persistent_player> m_selected = nullptr;

		void handle_session_type_change(persistent_player& player, GSType new_session_type);

	public:
		std::filesystem::path m_file_path;
		player_database_service();
		~player_database_service();

		void save();
		void load();

		std::shared_ptr<persistent_player> add_player(std::int64_t rid, const std::string_view name);
		std::unordered_map<std::uint64_t, std::shared_ptr<persistent_player>>& get_players();
		std::map<std::string, std::shared_ptr<persistent_player>>& get_sorted_players();
		std::shared_ptr<persistent_player> get_player_by_rockstar_id(std::uint64_t rockstar_id);
		std::shared_ptr<persistent_player> get_or_create_player(player_ptr player);
		void update_rockstar_id(std::uint64_t old, std::uint64_t _new);
		void remove_rockstar_id(std::uint64_t rockstar_id);

		void set_selected(std::shared_ptr<persistent_player> selected);
		std::shared_ptr<persistent_player> get_selected();

		void start_update_loop();
		void update_player_states(bool tracked_only = false);

		static bool is_joinable_session(GSType type);
		static const char* get_session_type_str(GSType type);
	};

	inline player_database_service* g_player_database_service;
}