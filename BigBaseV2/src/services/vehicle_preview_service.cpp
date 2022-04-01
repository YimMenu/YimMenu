#include "api/remote.hpp"
#include "fiber_pool.hpp"
#include "file_manager.hpp"
#include "gui.hpp"
#include "thread_pool.hpp"
#include "util/entity.hpp"
#include "util/vehicle.hpp"
#include "vehicle_preview_service.hpp"

namespace big
{
	vehicle_preview_service::vehicle_preview_service() :
		m_vehicle_file(g_file_manager->get_project_file("./lib/vehicles.json"))
	{
		if (m_vehicle_file.exists())
			this->load();
		else
		{
			g_thread_pool->push([this]()
			{
				if (remote::download_binary("http://github-proxy.damon.sh/DurtyFree/gta-v-data-dumps/master/vehicles.json", m_vehicle_file.get_path()))
					this->load();
				else
					LOG(WARNING) << "Failed to download vehicles.json data...";
			});
		}

		g_vehicle_preview_service = this;
	}

	vehicle_preview_service::~vehicle_preview_service()
	{
		g_vehicle_preview_service = nullptr;
	}

	nlohmann::json& vehicle_preview_service::get_vehicle_list()
	{
		return m_all_vehicles;
	}

	void vehicle_preview_service::preview_loop()
	{
		if (m_running)
			return;
		m_running = true;
		
		g_fiber_pool->queue_job([this]
		{
			while (g_running && m_running && g->spawn.preview_vehicle && g_gui.m_opened)
			{
				auto location = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 2.5f, 2.5f, .5f);
				if (m_current_veh == -1)
				{
					location.z = -10.f;
					m_current_veh = vehicle::spawn(m_model, location, 0.f, false);
					ENTITY::FREEZE_ENTITY_POSITION(m_current_veh, true);
					ENTITY::SET_ENTITY_ALPHA(m_current_veh, 0, 0);
					ENTITY::SET_ENTITY_COLLISION(m_current_veh, false, false);

					m_new_model = false;
				}
				else if (m_new_model)
				{
					entity::delete_entity(m_current_veh);

					m_current_veh = -1;
				}
				else
				{
					if (const int alpha = ENTITY::GET_ENTITY_ALPHA(m_current_veh); alpha < 250)
						ENTITY::SET_ENTITY_ALPHA(m_current_veh, std::min<int>(255, alpha + 10), 0);

					ENTITY::SET_ENTITY_HEADING(m_current_veh, m_heading);
					ENTITY::SET_ENTITY_COORDS(m_current_veh, location.x, location.y, location.z, 0, 0, 0, 0);
				}

				if (m_heading += 0.5f; m_heading > 359) m_heading = 0;

				script::get_current()->yield();
			}

			entity::delete_entity(m_current_veh);
			m_current_veh = -1;
			m_running = false;
		});
	}


	void vehicle_preview_service::set_preview_vehicle(const nlohmann::json& item)
	{
		if (m_model != item["Name"])
		{
			m_model = item["Name"];

			m_new_model = true;
		}

		if (!m_running)
			g_thread_pool->push([this] { preview_loop(); });
	}

	void vehicle_preview_service::stop_preview()
	{
		m_running = false;
	}

	void vehicle_preview_service::load()
	{
		std::ifstream file(m_vehicle_file.get_path());

		try
		{
			file >> m_all_vehicles;
		}
		catch (const std::exception& ex)
		{
			LOG(WARNING) << "Failed to load vehicles.json:\n" << ex.what();
		}
	}
}