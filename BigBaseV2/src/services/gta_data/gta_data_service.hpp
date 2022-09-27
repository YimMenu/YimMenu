#pragma once
#include "file_manager/file.hpp"
#include "vehicle_item.hpp"
#include "ped_item.hpp"
#include "weapon_item.hpp"
#include "gta/joaat.hpp"

namespace big
{
	class gta_data_service
	{
		static constexpr auto cache_version_file_path = "./lib/cache_version.txt";
		static constexpr auto vehicles_json_file_path = "./lib/vehicles.json";
		static constexpr auto peds_json_file_path = "./lib/peds.json";
		static constexpr auto weapons_json_file_path = "./lib/weapons.json";

		std::vector<std::string> m_vehicle_class_arr;
		std::map<Hash, int> m_vehicle_hash_idx_map;
		std::vector<vehicle_item> m_vehicle_item_arr;
		const vehicle_item empty_vehicle_item = vehicle_item();

		std::vector<std::string> m_ped_type_arr;
		std::map<Hash, int> m_ped_hash_idx_map;
		std::vector<ped_item> m_ped_item_arr;
		const ped_item empty_ped_item = ped_item();

		std::vector<std::string> m_weapon_type_arr;
		std::map<Hash, int> m_weapon_hash_idx_map;
		std::vector<weapon_item> m_weapon_item_arr;
		const weapon_item empty_weapon_item = weapon_item();

	public:
		gta_data_service();
		~gta_data_service();

		const vehicle_item& find_vehicle_by_hash(Hash hash);
		const std::vector<std::string>& get_vehicle_class_arr();
		const std::vector<vehicle_item>& get_vehicle_arr();

		const ped_item& find_ped_by_hash(Hash hash);
		const std::vector<std::string>& get_ped_type_arr();
		const std::vector<ped_item>& get_ped_arr();

		const weapon_item& find_weapon_by_hash(Hash hash);
		const std::vector<std::string>& get_weapon_type_arr();
		const std::vector<weapon_item>& get_weapon_arr();

	private:
		bool is_cache_updated();
		void save_cache_version();
		void update_cache_and_load_data();

		void load_data();

		void save_data_to_file(const std::string& file_path, const nlohmann::json& j);

		bool load_vehicles(std::filesystem::path path);
		bool load_peds(std::filesystem::path path);
		bool load_weapons(std::filesystem::path path);

	};

	inline gta_data_service* g_gta_data_service{};
}
