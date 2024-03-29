#pragma once
#include "file_manager/file.hpp"

namespace big
{
	class model_preview_service
	{
		Entity m_current_ent{};
		float m_heading{};

		Hash m_ped_model_hash{};
		Hash m_veh_model_hash{};
		Ped m_ped_clone{};
		std::string m_current_persisted_vehicle_name;

		std::map<int, int32_t> m_veh_owned_mods;
		bool m_veh_spawn_max = false;

		bool m_running = false;
		bool m_shutdown_preview = false;

		std::chrono::time_point<std::chrono::steady_clock> m_rotation_start_time;
	public:
		model_preview_service();
		~model_preview_service();

		void show_ped(Hash hash);
		void show_ped(Hash hash, Ped clone);

		void show_vehicle(Hash hash, bool spawn_max);
		void show_vehicle(const std::map<int, int32_t>& owned_mods, bool spawn_max);
		void show_vehicle_persisted(std::string vehicle_name);
		void show_vehicle(Vehicle veh);
		void stop_preview();

	private:
		void clear_data();
		void preview_loop();
	};

	inline model_preview_service* g_model_preview_service{};
}