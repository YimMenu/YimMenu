#pragma once
#include "natives.hpp"

namespace lua::stats
{
	// Lua API: Table
	// Name: stats
	// Table for manipulating GTA stats.
	// For stats that get prefixed by either `MP0` or `MP1`, you can use `MPX` instead and the menu will resolve to the correct number automatically.

	// Lua API: Function
	// Table: stats
	// Name: get_character_index
	// Returns: integer: The current multiplayer character index (0 or 1).
	static int get_character_index()
	{
		return self::char_index;
	}

	static Hash stat_text_to_hash(std::string& text)
	{
		if (text[0] == '$')
		{
			text = text.substr(1);
		}

		std::transform(text.begin(), text.end(), text.begin(), ::toupper);

		if (text.substr(0, 3) == "MPX")
			text[2] = get_character_index() + '0';

		return rage::joaat(text);
	}

	// Lua API: Function
	// Table: stats
	// Name: get_bool
	// Param: stat_hash: integer: the stat hash.
	// Returns: boolean: The value of the given stat.
	static bool get_bool_hash(Hash stat_hash)
	{
		BOOL out_value;
		STATS::STAT_GET_BOOL(stat_hash, &out_value, -1);

		return out_value;
	}

	// Lua API: Function
	// Table: stats
	// Name: get_bool
	// Param: stat_name: string: the stat name.
	// Returns: boolean: The value of the given stat.
	static bool get_bool_name(std::string stat_name)
	{
		return get_bool_hash(stat_text_to_hash(stat_name));
	}

	// Lua API: Function
	// Table: stats
	// Name: get_bool_masked
	// Param: stat_hash: integer: the stat hash.
	// Param: bit_index: integer: bit index.
	// Returns: boolean: The value of the given stat.
	static bool get_bool_masked_hash(Hash stat_hash, int bit_index)
	{
		int out_value;
		constexpr int bit_count = 1;
		STATS::STAT_GET_MASKED_INT(stat_hash, &out_value, bit_index, bit_count, -1);

		return out_value;
	}

	// Lua API: Function
	// Table: stats
	// Name: get_bool_masked
	// Param: stat_name: string: the stat name.
	// Param: bit_index: integer: bit index.
	// Returns: boolean: The value of the given stat.
	static bool get_bool_masked_name(std::string stat_name, int bit_index)
	{
		return get_bool_masked_hash(stat_text_to_hash(stat_name), bit_index);
	}

	// Lua API: Function
	// Table: stats
	// Name: get_float
	// Param: stat_hash: integer: the stat hash.
	// Returns: float: The value of the given stat.
	static float get_float_hash(Hash stat_hash)
	{
		float out_value;
		STATS::STAT_GET_FLOAT(stat_hash, &out_value, -1);

		return out_value;
	}

	// Lua API: Function
	// Table: stats
	// Name: get_float
	// Param: stat_name: string: the stat name.
	// Returns: float: The value of the given stat.
	static float get_float_name(std::string stat_name)
	{
		return get_float_hash(stat_text_to_hash(stat_name));
	}

	// Lua API: Function
	// Table: stats
	// Name: get_int
	// Param: stat_hash: integer: the stat hash.
	// Returns: integer: The value of the given stat.
	static int get_int_hash(Hash stat_hash)
	{
		int out_value;
		STATS::STAT_GET_INT(stat_hash, &out_value, -1);

		return out_value;
	}

	// Lua API: Function
	// Table: stats
	// Name: get_int
	// Param: stat_name: string: the stat name.
	// Returns: integer: The value of the given stat.
	static int get_int_name(std::string stat_name)
	{
		return get_int_hash(stat_text_to_hash(stat_name));
	}

	// Lua API: Function
	// Table: stats
	// Name: get_masked_int
	// Param: stat_hash: integer: the stat hash.
	// Param: bit_start: integer: bit start.
	// Param: bit_size: integer: bit size.
	// Returns: integer: The value of the given stat.
	static int get_masked_int_hash(Hash stat_hash, int bit_index, int bit_size)
	{
		int out_value;
		STATS::STAT_GET_MASKED_INT(stat_hash, &out_value, bit_index, bit_size, -1);

		return out_value;
	}

	// Lua API: Function
	// Table: stats
	// Name: get_masked_int
	// Param: stat_name: string: the stat name.
	// Param: bit_index: integer: bit index.
	// Param: bit_size: integer: bit size.
	// Returns: integer: The value of the given stat.
	static int get_masked_int_name(std::string stat_name, int bit_index, int bit_size)
	{
		return get_masked_int_hash(stat_text_to_hash(stat_name), bit_index, bit_size);
	}

	// Lua API: Function
	// Table: stats
	// Name: set_bool
	// Param: stat_hash: integer: the stat hash.
	// Param: new_value: boolean: the new value for the stat.
	// Returns: boolean: True if succeeded.
	static bool set_bool_hash(Hash stat_hash, bool new_value)
	{
		return STATS::STAT_SET_BOOL(stat_hash, new_value, true);
	}

	// Lua API: Function
	// Table: stats
	// Name: set_bool
	// Param: stat_name: string: the stat name.
	// Param: new_value: boolean: the new value for the stat.
	// Returns: boolean: True if succeeded.
	static bool set_bool_name(std::string stat_name, bool new_value)
	{
		return set_bool_hash(stat_text_to_hash(stat_name), new_value);
	}

	// Lua API: Function
	// Table: stats
	// Name: set_bool_masked
	// Param: stat_hash: integer: the stat hash.
	// Param: new_value: boolean: the new value for the stat.
	// Param: bit_index: integer: bit_index.
	// Returns: boolean: True if succeeded.
	static bool set_bool_masked_hash(Hash stat_hash, bool new_value, int bit_index)
	{
		constexpr int bit_count = 1;
		return STATS::STAT_SET_MASKED_INT(stat_hash, new_value, bit_index, bit_count, true);
	}

	// Lua API: Function
	// Table: stats
	// Name: set_bool_masked
	// Param: stat_name: string: the stat name.
	// Param: new_value: boolean: the new value for the stat.
	// Param: bit_index: integer: bit_index.
	// Returns: boolean: True if succeeded.
	static bool set_bool_masked_name(std::string stat_name, bool new_value, int bit_index)
	{
		return set_bool_masked_hash(stat_text_to_hash(stat_name), new_value, bit_index);
	}

	// Lua API: Function
	// Table: stats
	// Name: set_float
	// Param: stat_hash: integer: the stat hash.
	// Param: new_value: float: the new value for the stat.
	// Returns: boolean: True if succeeded.
	static bool set_float_hash(Hash stat_hash, float new_value)
	{
		return STATS::STAT_SET_FLOAT(stat_hash, new_value, true);
	}

	// Lua API: Function
	// Table: stats
	// Name: set_float
	// Param: stat_name: string: the stat name.
	// Param: new_value: float: the new value for the stat.
	// Returns: boolean: True if succeeded.
	static bool set_float_name(std::string stat_name, float new_value)
	{
		return set_float_hash(stat_text_to_hash(stat_name), new_value);
	}

	// Lua API: Function
	// Table: stats
	// Name: set_int
	// Param: stat_hash: integer: the stat hash.
	// Param: new_value: integer: the new value for the stat.
	// Returns: boolean: True if succeeded.
	static bool set_int_hash(Hash stat_hash, int new_value)
	{
		return STATS::STAT_SET_INT(stat_hash, new_value, true);
	}

	// Lua API: Function
	// Table: stats
	// Name: set_int
	// Param: stat_name: string: the stat name.
	// Param: new_value: integer: the new value for the stat.
	// Returns: boolean: True if succeeded.
	static bool set_int_name(std::string stat_name, int new_value)
	{
		return set_int_hash(stat_text_to_hash(stat_name), new_value);
	}

	// Lua API: Function
	// Table: stats
	// Name: set_masked_int
	// Param: stat_hash: integer: the stat hash.
	// Param: new_value: integer: the new value for the stat.
	// Param: bit_start: integer: bit_start.
	// Param: bit_size: integer: bit_size.
	// Returns: boolean: True if succeeded.
	static bool set_masked_int_hash(Hash stat_hash, int new_value, int bit_start, int bit_size)
	{
		return STATS::STAT_SET_MASKED_INT(stat_hash, new_value, bit_start, bit_size, true);
	}

	// Lua API: Function
	// Table: stats
	// Name: set_masked_int
	// Param: stat_name: string: the stat name.
	// Param: new_value: integer: the new value for the stat.
	// Param: bit_start: integer: bit_start.
	// Param: bit_size: integer: bit_size.
	// Returns: boolean: True if succeeded.
	static bool set_masked_int_name(std::string stat_name, int new_value, int bit_start, int bit_size)
	{
		return set_masked_int_hash(stat_text_to_hash(stat_name), new_value, bit_start, bit_size);
	}

	// Lua API: Function
	// Table: stats
	// Name: get_packed_stat_bool
	// Param: index: int: packed stat's index
	// Returns: boolean: Value of the stat.
	static bool get_packed_stat_bool(int index)
	{
		return STATS::GET_PACKED_STAT_BOOL_CODE(index, get_character_index());
	}

	// Lua API: Function
	// Table: stats
	// Name: set_packed_stat_bool
	// Param: index: int: packed stat's index.
	// Param: value: bool: value to set the packed stat to.
	static void set_packed_stat_bool(int index, bool value)
	{
		STATS::SET_PACKED_STAT_BOOL_CODE(index, value, get_character_index());
	}

	// Lua API: Function
	// Table: stats
	// Name: get_packed_stat_int
	// Param: index: int: packed stat's index.
	// Returns: int: Value of the stat.
	static int get_packed_stat_int(int index)
	{
		return STATS::GET_PACKED_STAT_INT_CODE(index, get_character_index());
	}

	// Lua API: Function
	// Table: stats
	// Name: set_packed_stat_int
	// Param: index: int: packed stat's index.
	// Param: value: int: value to set the packed stat to.
	static void set_packed_stat_int(int index, int value)
	{
		STATS::SET_PACKED_STAT_INT_CODE(index, value, get_character_index());
	}

	void bind(sol::state& state)
	{
		auto ns = state["stats"].get_or_create<sol::table>();

		ns["get_character_index"]  = get_character_index;

		ns["get_bool"]             = sol::overload(get_bool_hash, get_bool_name);
		ns["get_bool_masked"]      = sol::overload(get_bool_masked_hash, get_bool_masked_name);
		ns["get_float"]            = sol::overload(get_float_hash, get_float_name);
		ns["get_int"]              = sol::overload(get_int_hash, get_int_name);
		ns["get_masked_int"]       = sol::overload(get_masked_int_hash, get_masked_int_name);
		ns["get_packed_stat_bool"] = get_packed_stat_bool;
		ns["get_packed_stat_int"]  = get_packed_stat_int;

		ns["set_bool"]             = sol::overload(set_bool_hash, set_bool_name);
		ns["set_bool_masked"]      = sol::overload(set_bool_masked_hash, set_bool_masked_name);
		ns["set_float"]            = sol::overload(set_float_hash, set_float_name);
		ns["set_int"]              = sol::overload(set_int_hash, set_int_name);
		ns["set_masked_int"]       = sol::overload(set_masked_int_hash, set_masked_int_name);
		ns["set_packed_stat_bool"] = set_packed_stat_bool;
		ns["set_packed_stat_int"]  = set_packed_stat_int;
	}
}
