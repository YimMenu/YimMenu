#include "api/remote.hpp"
#include "file_manager.hpp"
#include "thread_pool.hpp"
#include "gta_data_service.hpp"

#define EXIST_IN_ARRAY(arr, val) (std::find(std::begin(arr), std::end(arr), val) != std::end(arr))

namespace big
{
	gta_data_service::gta_data_service()
	{
		const std::string url_prefix = "http://github-proxy.damon.sh/DurtyFree/gta-v-data-dumps/master/";

		load_from_file(
			"./lib/vehicles.json",
			"./lib/vehicles_etag.txt",
			url_prefix + "vehicles.json",
			&gta_data_service::load_vehicles,
			"Vehicle"
		);

		load_from_file(
			"./lib/peds.json",
			"./lib/peds_etag.txt",
			url_prefix + "peds.json",
			&gta_data_service::load_peds,
			"Ped"
		);

		load_from_file(
			"./lib/weapons.json",
			"./lib/weapons_etag.txt",
			url_prefix + "weapons.json",
			&gta_data_service::load_weapons,
			"Weapon"
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
		
		return m_vehicle_item_arr[idx];
	}

	const std::vector<std::string>& gta_data_service::get_vehicle_class_arr()
	{
		return m_vehicle_class_arr;
	}

	const std::vector<vehicle_item>& gta_data_service::get_vehicle_arr()
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
		
		return m_ped_item_arr[idx];
	}

	const std::vector<std::string>& gta_data_service::get_ped_type_arr()
	{
		return m_ped_type_arr;
	}

	const std::vector<ped_item>& gta_data_service::get_ped_arr()
	{
		return m_ped_item_arr;
	}


	const weapon_item& gta_data_service::find_weapon_by_hash(Hash hash)
	{
		int idx = -1;

		if (m_weapon_hash_idx_map.count(hash))
		{
			idx = m_weapon_hash_idx_map[hash];
		}

		if (idx == -1)
		{
			return empty_weapon_item;
		}
		
		return m_weapon_item_arr[idx];
	}

	const std::vector<std::string>& gta_data_service::get_weapon_type_arr()
	{
		return m_weapon_type_arr;
	}

	const std::vector<weapon_item>& gta_data_service::get_weapon_arr()
	{
		return m_weapon_item_arr;
	}


	void gta_data_service::load_from_file(std::string file_path, std::string etag_path, std::string url, void(gta_data_service::* load_func)(file), std::string data_name)
	{
		file file_to_load(g_file_manager->get_project_file(file_path));

		if (file_to_load.exists())
		{
			(this->*load_func)(file_to_load);
			LOG(INFO) << "Data loaded: " + data_name;
		}

		g_thread_pool->push([this, file_path, etag_path, url, load_func, data_name]() {
			file file_to_load(g_file_manager->get_project_file(file_path));
			file file_etag(g_file_manager->get_project_file(etag_path));

			for (int retry = 0; retry < 2; retry++)
			{
				bool ret = remote::update_binary(
					url,
					file_to_load.get_path(),
					file_etag.get_path()
				);

				if (ret)
				{
					(this->*load_func)(file_to_load);
					LOG(INFO) << "Data updated: " + data_name;
					break;
				}
				else if (!file_to_load.exists())
				{
					LOG(WARNING) << "Failed to download data: " + data_name;
				}
			}
		});
	}

	void gta_data_service::load_vehicles(file file_to_load)
	{
		m_vehicle_class_arr.clear();
		m_vehicle_hash_idx_map.clear();
		m_vehicle_item_arr.clear();

		std::ifstream file(file_to_load.get_path());
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
			) {
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


	void gta_data_service::load_peds(file file_to_load)
	{
		m_ped_type_arr.clear();
		m_ped_hash_idx_map.clear();
		m_ped_item_arr.clear();

		std::ifstream file(file_to_load.get_path());
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
			) {
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


	void gta_data_service::load_weapons(file file_to_load)
	{
		m_weapon_type_arr.clear();
		m_weapon_hash_idx_map.clear();
		m_weapon_item_arr.clear();

		std::ifstream file(file_to_load.get_path());
		nlohmann::json all_weapons;

		try
		{
			file >> all_weapons;
		}
		catch (const std::exception& ex)
		{
			LOG(WARNING) << "Failed to load weapons.json:\n" << ex.what();
		}

		constexpr Hash hash_blacklist_arr[] = {
			RAGE_JOAAT("WEAPON_BIRD_CRAP"),
			RAGE_JOAAT("WEAPON_DIGISCANNER"),
			RAGE_JOAAT("WEAPON_GARBAGEBAG"),
			RAGE_JOAAT("WEAPON_GRENADELAUNCHER_SMOKE"),
			RAGE_JOAAT("WEAPON_HANDCUFFS"),
			RAGE_JOAAT("WEAPON_METALDETECTOR"),
			RAGE_JOAAT("GADGET_NIGHTVISION"),
			RAGE_JOAAT("GADGET_PARACHUTE"),
			RAGE_JOAAT("WEAPON_TRANQUILIZER"),
			RAGE_JOAAT("WEAPON_STINGER")
		};

		for (auto& item_json : all_weapons)
		{
			if (
				item_json["Hash"].is_null() ||
				item_json["Name"].is_null() ||
				item_json["IsVehicleWeapon"]
			) {
				continue;
			}

			if (EXIST_IN_ARRAY(hash_blacklist_arr, item_json["Hash"]))
			{
				continue;
			}

			auto item = weapon_item(item_json);

			if (item.name == "Invalid" || item.name == "Unarmed" || item.weapon_type == "NULL")
			{
				continue;
			}

			m_weapon_hash_idx_map[item_json["Hash"]] = (int)m_weapon_item_arr.size();

			m_weapon_item_arr.push_back(item);

			if (std::find(m_weapon_type_arr.begin(), m_weapon_type_arr.end(), item.weapon_type) == m_weapon_type_arr.end())
			{
				m_weapon_type_arr.push_back(item.weapon_type);
			}

			std::sort(m_weapon_type_arr.begin(), m_weapon_type_arr.end());
		}
	}
}
