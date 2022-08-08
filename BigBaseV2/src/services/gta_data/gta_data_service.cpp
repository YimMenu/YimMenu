#include "thread_pool.hpp"
#include "gta_data_service.hpp"

namespace big::gta_data_service
{
	gta_data_service::gta_data_service()
	{
		g_gta_data_service = this;
	}

	gta_data_service::~gta_data_service()
	{
		g_gta_data_service = nullptr;
	}



	const char* gta_data_service::find_object_name(Hash hash)
	{
		if (auto it = object_hash_map.find(hash); it != object_hash_map.end())
		{
			return it->second;
		}
		
		return object_hash_map.begin()->second;
	}



	const std::vector<ped_item>& gta_data_service::get_ped_arr()
	{
		return ped_item_arr;
	}

	const std::vector<const char*>& gta_data_service::get_ped_type_arr()
	{
		return ped_type_arr;
	}

	const ped_item& gta_data_service::find_ped_by_hash(Hash hash)
	{
		int idx = 0;

		if (auto it = ped_hash_idx_map.find(hash); it != ped_hash_idx_map.end())
		{
			idx = it->second;
		}

		return ped_item_arr[idx];
	}



	const std::vector<vehicle_item>& gta_data_service::get_vehicle_arr()
	{
		return vehicle_item_arr;
	}

	const std::vector<const char*>& gta_data_service::get_vehicle_class_arr()
	{
		return vehicle_class_arr;
	}

	const std::vector<const char*>& gta_data_service::get_vehicle_manufacturer_arr()
	{
		return vehicle_manufacturer_arr;
	}

	const vehicle_item& gta_data_service::find_vehicle_by_hash(Hash hash)
	{
		int idx = 0;

		if (auto it = vehicle_hash_idx_map.find(hash); it != vehicle_hash_idx_map.end())
		{
			idx = it->second;
		}

		return vehicle_item_arr[idx];
	}



	const std::vector<weapon_item>& gta_data_service::get_weapon_arr()
	{
		return weapon_item_arr;
	}

	const std::vector<const char*>& gta_data_service::get_weapon_type_arr()
	{
		return weapon_type_arr;
	}

	const weapon_item& gta_data_service::find_weapon_by_hash(Hash hash)
	{
		int idx = 0;

		if (auto it = weapon_hash_idx_map.find(hash); it != weapon_hash_idx_map.end())
		{
			idx = it->second;
		}

		return weapon_item_arr[idx];
	}
}
