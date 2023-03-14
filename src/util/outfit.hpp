#pragma once
#include "script_global.hpp"

namespace big::outfit
{
	inline char* get_slot_name_address(int slot)
	{
		return script_global(2359296).at(0, 5568).at(681).at(2460).at(slot, 8).as<char*>();
	}

	inline int* get_component_drawable_id_address(int slot, int id)
	{
		return script_global(2359296).at(0, 5568).at(681).at(1336).at(slot, 13).at(id, 1).as<int*>();
	}

	inline int* get_component_texture_id_address(int slot, int id)
	{
		return script_global(2359296).at(0, 5568).at(681).at(1610).at(slot, 13).at(id, 1).as<int*>();
	}

	inline int* get_prop_drawable_id_address(int slot, int id)
	{
		return script_global(2359296).at(0, 5568).at(681).at(1884).at(slot, 10).at(id, 1).as<int*>();
	}

	inline int* get_prop_texture_id_address(int slot, int id)
	{
		return script_global(2359296).at(0, 5568).at(681).at(2095).at(slot, 10).at(id, 1).as<int*>();
	}
}