#pragma once
#include "file_manager/file.hpp"

namespace big
{
	class model_preview_service
	{
		Entity m_current_ent = 0;

		Hash m_veh_model_hash = 0;
		std::map<int, int32_t> m_veh_owned_mods;
		bool m_veh_spawn_max = false;

		Hash m_ped_model_hash = 0;
		Ped m_ped_clone       = 0;

		bool m_new_model    = false;
		float m_heading     = 0.f;
		bool m_loop_running = false;
		bool m_running      = false;

		std::string m_current_persisted_vehicle_name;

		std::chrono::time_point<std::chrono::steady_clock> start_time;

	public:
		model_preview_service();
		~model_preview_service();

		void show_ped(Hash hash);
		void show_ped(Hash hash, Ped clone);

		void show_vehicle(Hash hash, bool spawn_max);
		void show_vehicle(const std::map<int, int32_t>& owned_mods, bool spawn_max);
		void show_vehicle_persisted(std::string vehicle_name);
		void show_vehicle(Vehicle veh);

	private:
		void preview_loop();

	public:
		void stop_preview();
	};

	inline model_preview_service* g_model_preview_service{};
}