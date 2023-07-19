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
	// Lua API: Table
	// Name: network
	// Table containing helper functions for network related features.

	// Lua API: Function
	// Table: network
	// Name: trigger_script_event
	// Param: bitset: integer
	// Param: _args: table
	// Call trigger_script_event (TSE)
	void trigger_script_event(int bitset, sol::table _args);

	// Lua API: Function
	// Table: network
	// Name: give_pickup_rewards
	// Param: player: integer: Index of the player.
	// Param: reward: integer: Index of the reward pickup.
	// Give the given pickup reward to the given player.
	void give_pickup_rewards(int player, int reward);

	// Lua API: Function
	// Table: network
	// Name: set_player_coords
	// Param: player_idx: integer: Index of the player.
	// Param: x: float: New x position.
	// Param: y: float: New y position.
	// Param: z: float: New z position.
	// Teleport the given player to the given position.
	void set_player_coords(int player_idx, float x, float y, float z);

	// Lua API: Function
	// Table: network
	// Name: set_all_player_coords
	// Param: x: float: New x position.
	// Param: y: float: New y position.
	// Param: z: float: New z position.
	// Teleport all players to the given position.
	void set_all_player_coords(float x, float y, float z);

	// Lua API: Function
	// Table: network
	// Name: get_selected_player
	// Returns: integer: Returns the index of the currently selected player in the GUI.
	int get_selected_player();

	// Lua API: Function
	// Table: network
	// Name: get_selected_database_player_rockstar_id
	// Returns: integer: Returns the rockstar id of the currently selected player in the GUI.
	int get_selected_database_player_rockstar_id();

	// Lua API: Function
	// Table: network
	// Name: flag_player_as_modder
	// Param: player_idx: integer: Index of the player.
	// Flags the given player as a modder in our local database.
	void flag_player_as_modder(int player_idx);

	// Lua API: Function
	// Table: network
	// Name: is_player_flagged_as_modder
	// Param: player_idx: integer: Index of the player.
	// Returns: boolean: Returns true if the given player is flagged as a modder.
	bool is_player_flagged_as_modder(int player_idx);

	// Lua API: Function
	// Table: network
	// Name: force_script_host
	// Param: script_name: string: Name of the script
	// Try to force ourself to be host for the given GTA Script.
	void force_script_host(const std::string& script_name);

	// Lua API: Function
	// Table: network
	// Name: send_chat_message
	// Param: msg: string: Message to be sent.
	// Param: team_only: boolean: Should be true if the msg should only be sent to our team.
	// Sends a message to the in game chat.
	void send_chat_message(const std::string& msg, bool team_only);

	static void bind(sol::state& state)
	{
		auto ns                                        = state["network"].get_or_create<sol::table>();
		ns["trigger_script_event"]                     = trigger_script_event;
		ns["give_pickup_rewards"]                      = give_pickup_rewards;
		ns["set_player_coords"]                        = set_player_coords;
		ns["set_all_player_coords"]                    = set_all_player_coords;
		ns["get_selected_player"]                      = get_selected_player;
		ns["get_selected_database_player_rockstar_id"] = get_selected_database_player_rockstar_id;
		ns["flag_player_as_modder"]                    = flag_player_as_modder;
		ns["is_player_flagged_as_modder"]              = is_player_flagged_as_modder;
		ns["force_script_host"]                        = force_script_host;
		ns["send_chat_message"]                        = send_chat_message;
	}
}