#include "gta_data_service.hpp"

#include "fiber_pool.hpp"
#include "file_manager.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "pugixml.hpp"
#include "script.hpp"
#include "thread_pool.hpp"
#include "util/session.hpp"
#include "yim_fipackfile.hpp"

namespace big
{
	bool add_if_not_exists(string_vec& vec, std::string str)
	{
		if (std::find(vec.begin(), vec.end(), str) != vec.end())
			return true;

		vec.emplace_back(std::move(str));
		return false;
	}

	gta_data_service::gta_data_service() :
	    m_peds_cache(g_file_manager->get_project_file("./cache/peds.bin"), 1),
	    m_vehicles_cache(g_file_manager->get_project_file("./cache/vehicles.bin"), 1),
	    m_weapons_cache(g_file_manager->get_project_file("./cache/weapons.bin"), 2),
	    m_update_state(eGtaDataUpdateState::IDLE)
	{
		if (!is_cache_up_to_date())
			m_update_state = eGtaDataUpdateState::NEEDS_UPDATE;
		else
			load_data();

		g_gta_data_service = this;
	}

	gta_data_service::~gta_data_service()
	{
		g_gta_data_service = nullptr;
	}

	bool gta_data_service::cache_needs_update() const
	{
		return m_update_state == eGtaDataUpdateState::NEEDS_UPDATE;
	}

	eGtaDataUpdateState gta_data_service::state() const
	{
		return m_update_state;
	}

	void gta_data_service::update_in_online()
	{
		m_update_state = eGtaDataUpdateState::WAITING_FOR_SINGLE_PLAYER;
		g_fiber_pool->queue_job([this] {
			while (*g_pointers->m_game_state != eGameState::Playing)
			{
				script::get_current()->yield(100ms);
			}
			m_update_state = eGtaDataUpdateState::WAITING_FOR_ONLINE;

			session::join_type(eSessionType::SOLO);

			while (!*g_pointers->m_is_session_started)
			{
				script::get_current()->yield(100ms);
			}

			rebuild_cache();
		});
	}

	void gta_data_service::update_now()
	{
		m_update_state = eGtaDataUpdateState::WAITING_FOR_SINGLE_PLAYER;
		g_fiber_pool->queue_job([this] {
			rebuild_cache();
		});
	}

	// innefficient getters, don't care to fix right now
	const ped_item& gta_data_service::ped_by_hash(std::uint32_t hash)
	{
		for (const auto& [name, ped] : m_peds)
			if (rage::joaat(name) == hash)
				return ped;
		return gta_data_service::empty_ped;
	}

	const vehicle_item& gta_data_service::vehicle_by_hash(std::uint32_t hash)
	{
		for (const auto& [name, veh] : m_vehicles)
			if (rage::joaat(name) == hash)
				return veh;
		return gta_data_service::empty_vehicle;
	}

	const weapon_item& gta_data_service::weapon_by_hash(std::uint32_t hash)
	{
		for (const auto& [name, weapon] : m_weapons)
			if (rage::joaat(name) == hash)
				return weapon;
		return gta_data_service::empty_weapon;
	}

	string_vec& gta_data_service::ped_types()
	{
		return m_ped_types;
	}

	string_vec& gta_data_service::vehicle_classes()
	{
		return m_vehicle_classes;
	}

	string_vec& gta_data_service::weapon_types()
	{
		return m_weapon_types;
	}

	bool gta_data_service::is_cache_up_to_date()
	{
		m_peds_cache.load();
		m_vehicles_cache.load();
		m_weapons_cache.load();

		const auto game_version   = std::strtoul(g_pointers->m_game_version, nullptr, 10);
		const auto online_version = std::strtof(g_pointers->m_online_version, nullptr);

		return m_peds_cache.up_to_date(game_version, online_version) && m_vehicles_cache.up_to_date(game_version, online_version)
		    && m_weapons_cache.up_to_date(game_version, online_version);
	}

	void gta_data_service::load_data()
	{
		LOG(VERBOSE) << "Loading data from cache.";

		load_peds();
		load_vehicles();
		load_weapons();

		LOG(VERBOSE) << "Loaded all data from cache.";
	}

	void gta_data_service::load_peds()
	{
		const auto ped_count = m_peds_cache.data_size() / sizeof(ped_item);
		LOG(INFO) << "Loading " << ped_count << " peds from cache.";

		auto cached_peds = reinterpret_cast<const ped_item*>(m_peds_cache.data());
		for (size_t i = 0; i < ped_count; i++)
		{
			const auto ped = cached_peds[i];

			add_if_not_exists(m_ped_types, ped.m_ped_type);
			m_peds.insert({ped.m_name, ped});
		}

		std::sort(m_ped_types.begin(), m_ped_types.end());
		m_peds_cache.free();
	}

	void gta_data_service::load_vehicles()
	{
		const auto vehicle_count = m_vehicles_cache.data_size() / sizeof(vehicle_item);
		LOG(INFO) << "Loading " << vehicle_count << " vehicles from cache.";

		auto cached_vehicles = reinterpret_cast<const vehicle_item*>(m_vehicles_cache.data());
		for (size_t i = 0; i < vehicle_count; i++)
		{
			const auto vehicle = cached_vehicles[i];

			add_if_not_exists(m_vehicle_classes, vehicle.m_vehicle_class);
			m_vehicles.insert({vehicle.m_name, vehicle});
		}

		std::sort(m_vehicle_classes.begin(), m_vehicle_classes.end());
		m_vehicles_cache.free();
	}

	void gta_data_service::load_weapons()
	{
		const auto weapon_count = m_weapons_cache.data_size() / sizeof(weapon_item);
		LOG(INFO) << "Loading " << weapon_count << " weapons from cache.";

		auto cached_weapons = reinterpret_cast<const weapon_item*>(m_weapons_cache.data());
		for (size_t i = 0; i < weapon_count; i++)
		{
			const auto weapon = cached_weapons[i];

			add_if_not_exists(m_weapon_types, weapon.m_weapon_type);
			m_weapons.insert({weapon.m_name, weapon});
		}

		std::sort(m_weapon_types.begin(), m_weapon_types.end());
		m_weapons_cache.free();
	}

	inline void parse_ped(std::vector<ped_item>& peds, std::vector<std::uint32_t>& mapped_peds, pugi::xml_document& doc)
	{
		const auto& items = doc.select_nodes("/CPedModelInfo__InitDataList/InitDatas/Item");
		for (const auto& item_node : items)
		{
			const auto& item = item_node.node();
			const auto name  = item.child("Name").text().as_string();
			const auto hash  = rage::joaat(name);

			if (std::find(mapped_peds.begin(), mapped_peds.end(), hash) != mapped_peds.end())
				continue;

			mapped_peds.emplace_back(hash);

			auto ped = ped_item{};

			std::strncpy(ped.m_name, name, sizeof(ped.m_name));

			const auto ped_type = item.child("Pedtype").text().as_string();
			std::strncpy(ped.m_ped_type, ped_type, sizeof(ped.m_ped_type));

			ped.m_hash = hash;

			peds.emplace_back(std::move(ped));
		}
	}

	void gta_data_service::rebuild_cache()
	{
		m_update_state = eGtaDataUpdateState::UPDATING;

		using hash_array = std::vector<std::uint32_t>;
		hash_array mapped_peds;
		hash_array mapped_vehicles;
		hash_array mapped_weapons;

		std::vector<ped_item> peds;
		std::vector<vehicle_item> vehicles;
		std::vector<weapon_item> weapons;

		constexpr auto exists = [](const hash_array& arr, std::uint32_t val) -> bool {
			return std::find(arr.begin(), arr.end(), val) != arr.end();
		};

		LOG(INFO) << "Rebuilding cache started...";

		yim_fipackfile::for_each_fipackfile([&](yim_fipackfile& rpf_wrapper) {
			const auto files = rpf_wrapper.get_file_paths();
			for (const auto& file : files)
			{
				if (file.filename() == "setup2.xml")
				{
					std::string dlc_name;
					rpf_wrapper.read_xml_file(file, [&dlc_name](pugi::xml_document& doc) {
						const auto item = doc.select_node("/SSetupData/nameHash");
						dlc_name        = item.node().text().as_string();
					});

					if (dlc_name == "mpG9EC")
					{
						LOG(VERBOSE) << "Bad DLC, skipping...";

						return std::size_t(0);
					}
				}
				else if (file.filename() == "vehicles.meta")
				{
					rpf_wrapper.read_xml_file(file, [&exists, &vehicles, &mapped_vehicles](pugi::xml_document& doc) {
						const auto& items = doc.select_nodes("/CVehicleModelInfo__InitDataList/InitDatas/Item");
						for (const auto& item_node : items)
						{
							const auto item = item_node.node();

							const auto name = item.child("modelName").text().as_string();
							const auto hash = rage::joaat(name);

							if (exists(mapped_vehicles, hash))
								continue;
							mapped_vehicles.emplace_back(hash);

							auto veh = vehicle_item{};
							std::strncpy(veh.m_name, name, sizeof(veh.m_name));

							const auto manufacturer_display = item.child("vehicleMakeName").text().as_string();
							std::strncpy(veh.m_display_manufacturer, HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(manufacturer_display), sizeof(veh.m_display_manufacturer));

							const auto game_name = item.child("gameName").text().as_string();
							std::strncpy(veh.m_display_name, HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(game_name), sizeof(veh.m_display_name));

							char vehicle_class[32];
							std::sprintf(vehicle_class, "VEH_CLASS_%i", VEHICLE::GET_VEHICLE_CLASS_FROM_NAME(hash));
							std::strncpy(veh.m_vehicle_class, HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(vehicle_class), sizeof(veh.m_vehicle_class));

							veh.m_hash = hash;

							vehicles.emplace_back(std::move(veh));
						}
					});
				}
				else if (const auto file_str = file.string(); file_str.find("weapon") != std::string::npos && file.extension() == ".meta")
				{
					rpf_wrapper.read_xml_file(file, [&exists, &weapons, &mapped_weapons](pugi::xml_document& doc) {
						const auto& items = doc.select_nodes("/CWeaponInfoBlob/Infos/Item/Infos/Item[@type='CWeaponInfo']");
						for (const auto& item_node : items)
						{
							const auto item = item_node.node();
							const auto name = item.child("Name").text().as_string();
							const auto hash = rage::joaat(name);

							if (hash == RAGE_JOAAT("WEAPON_BIRD_CRAP"))
								continue;

							if (exists(mapped_weapons, hash))
								continue;
							mapped_weapons.emplace_back(hash);

							const auto human_name_hash = item.child("HumanNameHash").text().as_string();
							if (std::strcmp(human_name_hash, "WT_INVALID") == 0 || std::strcmp(human_name_hash, "WT_VEHMINE") == 0)
								continue;

							auto weapon = weapon_item{};

							std::strncpy(weapon.m_name, name, sizeof(weapon.m_name));

							const auto display_name = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(human_name_hash);
							std::strncpy(weapon.m_display_name, display_name, sizeof(weapon.m_name));

							auto weapon_flags = std::string(item.child("WeaponFlags").text().as_string());

							bool is_gun         = false;
							bool is_rechargable = false;

							const char* category = "";

							std::size_t pos;
							while ((pos = weapon_flags.find(' ')) != std::string::npos)
							{
								const auto flag = weapon_flags.substr(0, pos);
								if (flag == "Thrown")
								{
									weapon.m_throwable = true;
								}
								else if (flag == "Gun")
								{
									is_gun = true;
								}
								else if (flag == "DisplayRechargeTimeHUD")
								{
									is_rechargable = true;
								}
								else if (flag == "Vehicle" || flag == "HiddenFromWeaponWheel" || flag == "NotAWeapon")
								{
									goto skip;
								}

								weapon_flags.erase(0, pos + 1);
							}

							category = item.child("Group").text().as_string();

							if (std::strlen(category) == 0 || std::strcmp(category, "GROUP_DIGISCANNER") == 0)
								continue;

							if (std::strlen(category) > 6)
							{
								std::strncpy(weapon.m_weapon_type, category + 6, sizeof(weapon.m_weapon_type));
							}

							if (is_gun || !std::strcmp(weapon.m_weapon_type, "MELEE") || !std::strcmp(weapon.m_weapon_type, "UNARMED"))
							{
								const std::string reward_prefix = "REWARD_";
								weapon.m_reward_hash            = rage::joaat(reward_prefix + name);

								if (is_gun && !is_rechargable)
								{
									std::string weapon_id     = name + 7;
									weapon.m_reward_ammo_hash = rage::joaat(reward_prefix + "AMMO_" + weapon_id);
								}
							}

							weapon.m_hash = hash;

							weapons.emplace_back(std::move(weapon));
						skip:
							continue;
						}
					});
				}
				else if (file.filename() == "peds.meta")
				{
					rpf_wrapper.read_xml_file(file, [&exists, &peds, &mapped_peds](pugi::xml_document& doc) {
						parse_ped(peds, mapped_peds, doc);
					});
				}
			}

			return files.size();
		});

		m_update_state = eGtaDataUpdateState::IDLE;
		LOG(INFO) << "Cache has been rebuilt.\n\tPeds: " << peds.size() << "\n\tVehicles: " << vehicles.size()
		          << "\n\tWeapons: " << weapons.size();

		LOG(VERBOSE) << "Starting cache saving procedure...";
		g_thread_pool->push([this, peds = std::move(peds), vehicles = std::move(vehicles), weapons = std::move(weapons)] {
			const auto game_version   = std::strtoul(g_pointers->m_game_version, nullptr, 10);
			const auto online_version = std::strtof(g_pointers->m_online_version, nullptr);

			{
				const auto data_size = sizeof(ped_item) * peds.size();
				m_peds_cache.set_data(std::make_unique<std::uint8_t[]>(data_size), data_size);
				std::memcpy(m_peds_cache.data(), peds.data(), data_size);

				m_peds_cache.set_header_version(game_version, online_version);
				m_peds_cache.write();
			}

			{
				const auto data_size = sizeof(vehicle_item) * vehicles.size();
				m_vehicles_cache.set_data(std::make_unique<std::uint8_t[]>(data_size), data_size);
				std::memcpy(m_vehicles_cache.data(), vehicles.data(), data_size);

				m_vehicles_cache.set_header_version(game_version, online_version);
				m_vehicles_cache.write();
			}

			{
				const auto data_size = sizeof(weapon_item) * weapons.size();
				m_weapons_cache.set_data(std::make_unique<std::uint8_t[]>(data_size), data_size);
				std::memcpy(m_weapons_cache.data(), weapons.data(), data_size);

				m_weapons_cache.set_header_version(game_version, online_version);
				m_weapons_cache.write();
			}

			LOG(INFO) << "Finished writing cache to disk.";

			load_data();
		});
	}
}
