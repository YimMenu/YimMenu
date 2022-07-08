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

	std::map<Hash, vehicle_preview_item>& vehicle_preview_service::get_vehicle_map()
	{
		return m_hash_veh_map;
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
				auto location = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(self::ped, 0.f, 5.f, .5f);
				if (m_current_veh == -1)
				{
					m_new_model = false;
					location.z = -10.f;
					m_current_veh = vehicle::spawn(m_model, "", location, 0.f, false);
					ENTITY::FREEZE_ENTITY_POSITION(m_current_veh, true);
					ENTITY::SET_ENTITY_ALPHA(m_current_veh, 0, 0);
					ENTITY::SET_ENTITY_COLLISION(m_current_veh, false, false);
					ENTITY::SET_CAN_CLIMB_ON_ENTITY(m_current_veh, false);
					OBJECT::SET_OBJECT_ALLOW_LOW_LOD_BUOYANCY(m_current_veh, false);
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


	void vehicle_preview_service::set_preview_vehicle(const vehicle_preview_item& item)
	{
		if (item.name != "") {
			if (m_model != item.name) {
				m_model = item.name;
				m_new_model = true;
			}

			if (!m_running) {
				g_thread_pool->push([this] { preview_loop(); });
			}
		}
	}

	const vehicle_preview_item& vehicle_preview_service::find_vehicle_item_by_hash(int hash)
	{
		if (m_hash_veh_map.count(hash)) {
			return m_hash_veh_map[hash];
		}

		return empty_item;
	}

	void vehicle_preview_service::stop_preview()
	{
		m_running = false;
	}

	void vehicle_preview_service::load()
	{
		std::ifstream file(m_vehicle_file.get_path());
		nlohmann::json m_all_vehicles;

		try
		{
			file >> m_all_vehicles;
		}
		catch (const std::exception& ex)
		{
			LOG(WARNING) << "Failed to load vehicles.json:\n" << ex.what();
		}

		for (auto& item_json : m_all_vehicles)
		{
			if (item_json["SignedHash"].is_null() || item_json["Name"].is_null())
				continue;

			Hash signed_hash = item_json["SignedHash"];
			std::string name = item_json["Name"];
			vehicle_preview_item item = { name, name, "", signed_hash };

			if (!item_json["DisplayName"].is_null()) {
				item.dispaly_name = item_json["DisplayName"];
			}

			if (!item_json["ManufacturerDisplayName"].is_null()) {
				item.display_manufacturer = item_json["ManufacturerDisplayName"];
			} else if (!item_json["Manufacturer"].is_null()) {
				item.display_manufacturer = item_json["Manufacturer"];
			}

			m_hash_veh_map[signed_hash] = item;
		}
	}
}
