#pragma once
#include "services/mobile/mobile_service.hpp"

namespace big
{
	class vehicle_preview
	{
		Cam camera = -1;
		Vehicle last_spawned;
		Hash last_veh_hash;
		std::string last_veh_file_name;

		bool busy;

		void preview(std::function<void()> func, bool should_run_fun);

	public:
		bool is_camera_prepared;

		void preview_veh(Hash hash);
		void preview_persisted_veh(std::string file_name, std::string folder_name);
		void preview_personal_veh(const std::unique_ptr<big::personal_vehicle>& personal_veh);
		void clear();
		void reset();
	};

	inline vehicle_preview g_vehicle_preview;
}