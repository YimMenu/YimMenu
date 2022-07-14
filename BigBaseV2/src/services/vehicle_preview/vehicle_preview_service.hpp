#pragma once
#include "file_manager/file.hpp"

namespace big
{
	class vehicle_preview_item {

	public:
		vehicle_preview_item();
		vehicle_preview_item(nlohmann::json& item_json);

		std::string name;
		std::string display_name;
		std::string display_manufacturer;
		std::string clazz;
		Hash hash;
	};

	class vehicle_preview_service
	{
		file m_vehicle_file;
		file m_vehicle_file_etag;

		std::condition_variable m_cond;
		std::mutex m_mutex;

		std::map<Hash, int> m_hash_idx_map;
		std::vector<std::string> m_vehicle_class_arr;
		std::vector<vehicle_preview_item> m_vehicle_preview_item_arr;
		const vehicle_preview_item empty_item = vehicle_preview_item();

		Vehicle m_current_veh = -1;
		Hash m_model_hash;
		bool m_new_model = false;
		float m_heading = 0.f;
		bool m_running = false;
	public:
		vehicle_preview_service();
		~vehicle_preview_service();

		const vehicle_preview_item& find_vehicle_item_by_hash(Hash hash);
		std::vector<std::string>& get_vehicle_class_arr();
		std::vector<vehicle_preview_item>& get_vehicle_preview_item_arr();
		void set_preview_vehicle(const vehicle_preview_item& item);

		void preview_loop();
		void stop_preview();

	private:
		void load();

	};

	inline vehicle_preview_service* g_vehicle_preview_service{};
}