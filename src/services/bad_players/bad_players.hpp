#pragma once
#include "thread_pool.hpp"

using json = nlohmann::json;

namespace bad_players_nm
{
	struct bad_player
	{
		std::string name;
		uint64_t rockstar_id;
		bool block_join = true;
		bool is_spammer;
	};

	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(bad_player, name, rockstar_id, is_spammer);

	extern std::map<uint64_t, bad_player> bad_players_list;

	inline std::filesystem::path getSavedFilePath()
	{
		return big::g_file_manager.get_project_file("blocked_players.json").get_path();
	}

	void load_blocked_list();
	void save_blocked_list();

	inline void add_player(bad_player player)
	{
		bad_players_list[player.rockstar_id] = player;
		if (player.block_join)
			big::g_thread_pool->push([] {
				save_blocked_list();
			});
	}
	inline void toggle_block(uint64_t rockstar_id, bool v)
	{
		bad_players_list[rockstar_id].block_join = v;
		save_blocked_list();
	}
	inline void set_spammer(uint64_t rockstar_id, bool v)
	{
		bad_players_list[rockstar_id].is_spammer = v;
		save_blocked_list();
	}
	inline bool is_blocked(uint64_t rockstar_id)
	{
		auto bad_player = bad_players_list.find(rockstar_id);
		return bad_player != bad_players_list.end() && bad_player->second.block_join;
	}
	inline bool does_exist(uint64_t rockstar_id)
	{
		auto bad_player = bad_players_list.find(rockstar_id);
		return bad_player != bad_players_list.end();
	}
}