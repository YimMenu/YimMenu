#pragma once
#include "lua/sol.hpp"

// https://stackoverflow.com/a/40777268
/**
	* Convert a Lua sequence into a C++ vector
	* Throw exception on errors or wrong types
	*/
template<typename elementType>
inline std::vector<elementType> convert_sequence(sol::table t)
{
	std::size_t sz = t.size();
	std::vector<elementType> res(sz);
	for (int i = 1; i <= sz; i++)
	{
		res[i - 1] = t[i];
	}
	return res;
}

namespace lua::network
{
	void trigger_script_event(int bitset, sol::table _args);
	void give_pickup_rewards(int player, int reward);
	void set_player_coords(int player_idx, float x, float y, float z);
	int get_selected_player();
	int get_selected_database_player_rockstar_id();
	void flag_player_as_modder(int player_idx);
	bool is_player_flagged_as_modder(int player_idx);

	static void bind(sol::state& state)
	{
		auto ns                                        = state["network"].get_or_create<sol::table>();
		ns["trigger_script_event"]                     = trigger_script_event;
		ns["give_pickup_rewards"]                      = give_pickup_rewards;
		ns["set_player_coords"]                        = set_player_coords;
		ns["get_selected_player"]                      = get_selected_player;
		ns["get_selected_database_player_rockstar_id"] = get_selected_database_player_rockstar_id;
		ns["flag_player_as_modder"]                    = flag_player_as_modder;
		ns["is_player_flagged_as_modder"]              = is_player_flagged_as_modder;
	}
}