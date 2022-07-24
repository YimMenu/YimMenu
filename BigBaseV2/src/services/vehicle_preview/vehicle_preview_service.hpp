#pragma once
#include "file_manager/file.hpp"
#include "services/gta_data/gta_data_service.hpp"

namespace big
{
	class vehicle_preview_service
	{
		std::condition_variable m_cond;
		std::mutex m_mutex;

		Vehicle m_current_veh = -1;
		Hash m_model_hash;
		bool m_new_model = false;
		float m_heading = 0.f;
		bool m_running = false;
	public:
		vehicle_preview_service();
		~vehicle_preview_service();

		void set_preview_vehicle(const vehicle_item& item);

		void preview_loop();
		void stop_preview();
	};

	inline vehicle_preview_service* g_vehicle_preview_service{};
}