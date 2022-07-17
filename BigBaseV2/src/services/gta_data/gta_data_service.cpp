#include "api/remote.hpp"
#include "file_manager.hpp"
#include "thread_pool.hpp"
#include "gta_data_service.hpp"

namespace big
{
	gta_data_service::gta_data_service() :
		m_vehicle_file(g_file_manager->get_project_file("./lib/vehicles.json")),
		m_vehicle_file_etag(g_file_manager->get_project_file("./lib/vehicles_etag.txt")),
		m_ped_file(g_file_manager->get_project_file("./lib/peds.json")),
		m_ped_file_etag(g_file_manager->get_project_file("./lib/peds_etag.txt"))
	{
		load_from_file(
			m_vehicle_file,
			m_vehicle_file_etag,
			"http://github-proxy.damon.sh/DurtyFree/gta-v-data-dumps/master/vehicles.json",
			&gta_data_service::load_vehicles,
			"Vehicle"
		);

		load_from_file(
			m_ped_file,
			m_ped_file_etag,
			"http://github-proxy.damon.sh/DurtyFree/gta-v-data-dumps/master/peds.json",
			&gta_data_service::load_ped,
			"Ped"
		);

		g_gta_data_service = this;
	}

	gta_data_service::~gta_data_service()
	{
		g_gta_data_service = nullptr;
	}


	const vehicle_item& gta_data_service::find_vehicle_by_hash(Hash hash)
	{
		int idx = -1;

		if (m_vehicle_hash_idx_map.count(hash))
		{
			idx = m_vehicle_hash_idx_map[hash];
		}

		if (idx == -1)
		{
			return empty_vehicle_item;
		}
		else
		{
			return m_vehicle_item_arr[idx];
		}
	}

	std::vector<std::string>& gta_data_service::get_vehicle_class_arr()
	{
		return m_vehicle_class_arr;
	}

	std::vector<vehicle_item>& gta_data_service::get_vehicle_arr()
	{
		return m_vehicle_item_arr;
	}


	const ped_item& gta_data_service::find_ped_by_hash(Hash hash)
	{
		int idx = -1;

		if (m_ped_hash_idx_map.count(hash))
		{
			idx = m_ped_hash_idx_map[hash];
		}

		if (idx == -1)
		{
			return empty_ped_item;
		}
		else
		{
			return m_ped_item_arr[idx];
		}
	}

	std::vector<std::string>& gta_data_service::get_ped_type_arr()
	{
		return m_ped_type_arr;
	}

	std::vector<ped_item>& gta_data_service::get_ped_arr()
	{
		return m_ped_item_arr;
	}



	void gta_data_service::load_from_file(file file_to_load, file file_etag, std::string url, void(gta_data_service::* load_func)(), std::string data_name)
	{
		if (file_to_load.exists())
		{
			(this->*load_func)();
			LOG(INFO) << "Data loaded: " + data_name;
		}

		g_thread_pool->push([this, file_to_load, file_etag, url, load_func, data_name]() {
			for (int retry = 0; retry < 2; retry++)
			{
				bool ret = remote::update_binary(
					url,
					file_to_load.get_path(),
					file_etag.get_path()
				);

				if (ret)
				{
					(this->*load_func)();
					LOG(INFO) << "Data updated: " + data_name;
					break;
				}
				else if (!m_vehicle_file.exists())
				{
					LOG(WARNING) << "Failed to download data: " + data_name;
				}
			}
		});
	}

	void gta_data_service::load_vehicles()
	{
		m_vehicle_class_arr.clear();
		m_vehicle_hash_idx_map.clear();
		m_vehicle_item_arr.clear();

		std::ifstream file(m_vehicle_file.get_path());
		nlohmann::json all_vehicles;

		try
		{
			file >> all_vehicles;
		}
		catch (const std::exception& ex)
		{
			LOG(WARNING) << "Failed to load vehicles.json:\n" << ex.what();
		}


		for (auto& item_json : all_vehicles)
		{
			if (
				item_json["Hash"].is_null() ||
				item_json["Name"].is_null() ||
				!item_json["Bones"].is_array() ||
				item_json["Bones"][0] == "stub"
				)
			{
				continue;
			}

			auto item = vehicle_item(item_json);

			m_vehicle_hash_idx_map[item_json["Hash"]] = (int)m_vehicle_item_arr.size();

			m_vehicle_item_arr.push_back(item);

			if (std::find(m_vehicle_class_arr.begin(), m_vehicle_class_arr.end(), item.clazz) == m_vehicle_class_arr.end())
			{
				m_vehicle_class_arr.push_back(item.clazz);
			}

			std::sort(m_vehicle_class_arr.begin(), m_vehicle_class_arr.end());
		}
	}


	void gta_data_service::load_ped()
	{
		m_ped_type_arr.clear();
		m_ped_hash_idx_map.clear();
		m_ped_item_arr.clear();

		std::ifstream file(m_ped_file.get_path());
		nlohmann::json all_peds;

		try
		{
			file >> all_peds;
		}
		catch (const std::exception& ex)
		{
			LOG(WARNING) << "Failed to load peds.json:\n" << ex.what();
		}

		for (auto& item_json : all_peds)
		{
			if (
				item_json["Hash"].is_null() ||
				item_json["Name"].is_null()
			)
			{
				continue;
			}

			auto item = ped_item(item_json);

			m_ped_hash_idx_map[item_json["Hash"]] = (int)m_ped_item_arr.size();

			m_ped_item_arr.push_back(item);

			if (std::find(m_ped_type_arr.begin(), m_ped_type_arr.end(), item.ped_type) == m_ped_type_arr.end())
			{
				m_ped_type_arr.push_back(item.ped_type);
			}

			std::sort(m_ped_type_arr.begin(), m_ped_type_arr.end());
		}
	}
}
