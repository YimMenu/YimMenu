#pragma once
#include "file_manager/file.hpp"
#include "vehicle_item.hpp"
#include "ped_item.hpp"

namespace big
{
	class gta_data_service
	{
		file m_vehicle_file;
		file m_vehicle_file_etag;

		file m_ped_file;
		file m_ped_file_etag;

		std::vector<std::string> m_vehicle_class_arr;
		std::map<Hash, int> m_vehicle_hash_idx_map;
		std::vector<vehicle_item> m_vehicle_item_arr;
		const vehicle_item empty_vehicle_item = vehicle_item();

		std::vector<std::string> m_ped_type_arr;
		std::map<Hash, int> m_ped_hash_idx_map;
		std::vector<ped_item> m_ped_item_arr;
		const ped_item empty_ped_item = ped_item();

	public:
		gta_data_service();
		~gta_data_service();

		const vehicle_item& find_vehicle_by_hash(Hash hash);
		std::vector<std::string>& get_vehicle_class_arr();
		std::vector<vehicle_item>& get_vehicle_arr();

		const ped_item& find_ped_by_hash(Hash hash);
		std::vector<std::string>& get_ped_type_arr();
		std::vector<ped_item>& get_ped_arr();

	private:
		void load_from_file(file file_to_load, file file_etag, std::string url, void(gta_data_service::* load_func)(), std::string data_name);

		void load_vehicles();
		void load_ped();
	};

	inline gta_data_service* g_gta_data_service{};
}