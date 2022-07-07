#pragma once
#include "file_manager/file.hpp"

namespace big
{
	struct vehicle_preview_item {
		std::string name;
		std::string dispaly_name;
		std::string display_manufacturer;
		Hash hash;
	};

	class vehicle_preview_service
	{
		file m_vehicle_file;

		std::condition_variable m_cond;
		std::mutex m_mutex;

		std::map<Hash, vehicle_preview_item> m_hash_veh_map;
		const vehicle_preview_item empty_item = {"", "", "", 0};

		Vehicle m_current_veh = -1;
		std::string m_model;
		bool m_new_model = false;
		float m_heading = 0.f;
		bool m_running = false;
	public:
		vehicle_preview_service();
		~vehicle_preview_service();

		std::map<Hash, vehicle_preview_item>& get_vehicle_map();

		void preview_loop();

		void set_preview_vehicle(const vehicle_preview_item& item);
		const vehicle_preview_item& find_vehicle_item_by_hash(int hash);

		void stop_preview();

	private:
		void load();

	};

	inline vehicle_preview_service* g_vehicle_preview_service{};
}