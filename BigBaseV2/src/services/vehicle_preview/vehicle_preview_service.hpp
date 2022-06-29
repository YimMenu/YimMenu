#pragma once
#include "file_manager/file.hpp"

namespace big
{
	class vehicle_preview_service
	{
		file m_vehicle_file;

		std::condition_variable m_cond;
		std::mutex m_mutex;

		nlohmann::json m_all_vehicles;

		Vehicle m_current_veh = -1;
		std::string m_model;
		bool m_new_model = false;
		float m_heading = 0.f;
		bool m_running = false;
	public:
		vehicle_preview_service();
		~vehicle_preview_service();

		nlohmann::json& get_vehicle_list();

		void preview_loop();

		void set_preview_vehicle(const nlohmann::json& item);
		void stop_preview();

	private:
		void load();

	};

	inline vehicle_preview_service* g_vehicle_preview_service{};
}