#pragma once

#include "natives.hpp"
#include "core/data/model_attachment.hpp"


namespace big
{
	struct player_l {
		std::string player_name;
		uint64_t rid;
		std::string relationship;
		int tmp_player_id;
	};
	using player_list = std::vector<player_l>;

	using player_database_callback = std::function<const char* (const char*)>;
	class player_database_service
	{
	public:

		player_database_service();
		~player_database_service();

		player_list& player_list_()
		{
			return m_player_list;
		}

		static void save_players();
		static void load_players();

		static void create_dummy_player();
		static void add_player_to_db(uint64_t rid, std::string name, std::string relationship);
		static void add_player_to_db(uint64_t rid, std::string name, std::string relationship, Player player);

		static bool is_player_in_db(uint64_t rid);
		static player_l get_player_from_db(uint64_t rid);

		
	private:
		player_list m_player_list;

		static constexpr auto name_key = "name";
		static constexpr auto rid_key = "rid";
		static constexpr auto relationship_key = "relationship";

		static constexpr auto players_key = "players";

		static void load_players_from_json(nlohmann::json player_json);

		static std::vector<nlohmann::json> get_players_json();

		static nlohmann::json get_player_json_full(uint64_t rid, Player player, std::string relationship);
		static nlohmann::json get_player_json_small(uint64_t rid, std::string name, std::string relationship);

		static big::folder get_players_folder();
	};

	inline player_database_service* g_player_database_service;
}
