#pragma once
#include "object_data.hpp"
#include "ped_data.hpp"
#include "vehicle_data.hpp"
#include "weapon_data.hpp"

namespace big
{
	namespace gta_data_service
	{
		class gta_data_service
		{

		public:
			gta_data_service();
			~gta_data_service();

			const char* find_object_name(Hash hash);

			const std::vector<ped_item>& get_ped_arr();
			const std::vector<const char*>& get_ped_type_arr();
			const ped_item& find_ped_by_hash(Hash hash);

			const std::vector<vehicle_item>& get_vehicle_arr();
			const std::vector<const char*>& get_vehicle_class_arr();
			const std::vector<const char*>& get_vehicle_manufacturer_arr();
			const vehicle_item& find_vehicle_by_hash(Hash hash);

			const std::vector<weapon_item>& get_weapon_arr();
			const std::vector<const char*>& get_weapon_type_arr();
			const weapon_item& find_weapon_by_hash(Hash hash);
		};
	}

	inline gta_data_service::gta_data_service* g_gta_data_service{};
}
