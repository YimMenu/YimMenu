#pragma once
#include "core/scr_globals.hpp"

namespace big::outfit
{
	struct outfit_t
	{
		int id;
		std::string label;
		int drawable_id     = 0;
		int drawable_id_max = 0;
		int texture_id      = 0;
		int texture_id_max  = 0;
	};

	struct components_t
	{
		std::vector<outfit_t> items = {{0, "OUTFIT_HEAD"_T.data()},
		    {1, "OUTFIT_BERD"_T.data()},
		    {2, "OUTFIT_HAIR"_T.data()},
		    {3, "OUTFIT_UPPR"_T.data()},
		    {4, "OUTFIT_LOWR"_T.data()},
		    {5, "OUTFIT_HAND"_T.data()},
		    {6, "OUTFIT_FEET"_T.data()},
		    {7, "OUTFIT_TEEF"_T.data()},
		    {8, "OUTFIT_ACCS"_T.data()},
		    {9, "OUTFIT_TASK"_T.data()},
		    {10, "OUTFIT_DECL"_T.data()},
		    {11, "OUTFIT_JBIB"_T.data()}};
	};

	struct props_t
	{
		std::vector<outfit_t> items = {{0, "OUTFIT_HEAD"_T.data()},
		    {1, "OUTFIT_GLASSES"_T.data()},
		    {2, "OUTFIT_EARS"_T.data()},
		    {6, "OUTFIT_WATCH"_T.data()},
		    {7, "OUTFIT_WRIST"_T.data()}};
	};

	inline void check_bounds_drawable(outfit_t* item)
	{
		if(item->drawable_id > item->drawable_id_max)
			item->drawable_id = item->drawable_id_max;
		if(item->drawable_id < -1)
			item->drawable_id = -1;
	}

	inline void check_bounds_texture(outfit_t* item)
	{
		if(item->texture_id > item->texture_id_max)
			item->texture_id = item->texture_id_max;
		if(item->texture_id < -1)
			item->texture_id = -1;
	}

	inline char* get_slot_name_address(int slot)
	{
		return scr_globals::stats.at(0, 5568).at(681).at(2460).at(slot, 8).as<char*>();
	}

	inline int* get_component_drawable_id_address(int slot, int id)
	{
		return scr_globals::stats.at(0, 5568).at(681).at(1336).at(slot, 13).at(id, 1).as<int*>();
	}

	inline int* get_component_texture_id_address(int slot, int id)
	{
		return scr_globals::stats.at(0, 5568).at(681).at(1610).at(slot, 13).at(id, 1).as<int*>();
	}

	inline int* get_prop_drawable_id_address(int slot, int id)
	{
		return scr_globals::stats.at(0, 5568).at(681).at(1884).at(slot, 10).at(id, 1).as<int*>();
	}

	inline int* get_prop_texture_id_address(int slot, int id)
	{
		return scr_globals::stats.at(0, 5568).at(681).at(2095).at(slot, 10).at(id, 1).as<int*>();
	}
}