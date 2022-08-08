#pragma once
#include "vehicle_item.hpp"
#include "ped_item.hpp"
#include "weapon_item.hpp"

namespace big
{
	class gta_data_service
	{
        static const std::map<Hash, const char*> m_object_hash_map;

        static const std::vector<const char*> m_vehicle_class_arr;
		static const std::map<const Hash, const int> m_vehicle_hash_idx_map;
		static const std::vector<const vehicle_item> m_vehicle_item_arr;
        static const std::vector<const char*> m_vehicle_manufacturer_arr;

        static const std::vector<const char*> m_ped_type_arr;
		static const std::map<const Hash, const int> m_ped_hash_idx_map;
		static const std::vector<const ped_item> m_ped_item_arr;

		static const std::vector<const char*> m_weapon_type_arr;
		static const std::map<const Hash, const int> m_weapon_hash_idx_map;
		static const std::vector<const weapon_item> m_weapon_item_arr;

	public:
		gta_data_service();
		~gta_data_service();

		const vehicle_item& find_vehicle_by_hash(Hash hash);
		const std::vector<const char*>& get_vehicle_class_arr();
        const std::vector<const char*>& get_vehicle_manufacturer_arr();
		const std::vector<const vehicle_item>& get_vehicle_arr();

		const ped_item& find_ped_by_hash(Hash hash);
		const std::vector<const char*>& get_ped_type_arr();
		const std::vector<const ped_item>& get_ped_arr();

		const weapon_item& find_weapon_by_hash(Hash hash);
		const std::vector<const char*>& get_weapon_type_arr();
		const std::vector<const weapon_item>& get_weapon_arr();
	};

	inline gta_data_service* g_gta_data_service{};
}