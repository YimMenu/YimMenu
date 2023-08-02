#include "gta_data_service.hpp"

#include "fiber_pool.hpp"
#include "file_manager.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "pugixml.hpp"
#include "script.hpp"
#include "thread_pool.hpp"
#include "util/misc.hpp"
#include "util/model_info.hpp"
#include "util/session.hpp"
#include "util/vehicle.hpp"
#include "yim_fipackfile.hpp"

namespace big
{
	inline bool is_crash_ped(rage::joaat_t hash)
	{
		return hash == RAGE_JOAAT("slod_human") || hash == RAGE_JOAAT("slod_small_quadped") || hash == RAGE_JOAAT("slod_large_quadped");
	}

	bool add_if_not_exists(string_vec& vec, std::string str)
	{
		if (std::find(vec.begin(), vec.end(), str) != vec.end())
			return true;

		vec.emplace_back(std::move(str));
		return false;
	}

	gta_data_service::gta_data_service() :
	    m_peds_cache(g_file_manager.get_project_file("./cache/peds.bin"), 5),
	    m_vehicles_cache(g_file_manager.get_project_file("./cache/vehicles.bin"), 4),
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

	void gta_data_service::set_state(eGtaDataUpdateState state)
	{
		m_update_state = state;
	}

	void gta_data_service::update_now()
	{
		m_update_state = eGtaDataUpdateState::WAITING_FOR_SINGLE_PLAYER;
		g_fiber_pool->queue_job([this] {
			m_update_state = eGtaDataUpdateState::UPDATING;
			rebuild_cache();
		});
	}

	// innefficient getters, don't care to fix right now
	const ped_item& gta_data_service::ped_by_hash(uint32_t hash)
	{
		for (const auto& [name, ped] : m_peds)
			if (rage::joaat(name) == hash)
				return ped;
		return gta_data_service::empty_ped;
	}

	const vehicle_item& gta_data_service::vehicle_by_hash(uint32_t hash)
	{
		for (const auto& [name, veh] : m_vehicles)
			if (rage::joaat(name) == hash)
				return veh;
		return gta_data_service::empty_vehicle;
	}

	const weapon_item& gta_data_service::weapon_by_hash(uint32_t hash)
	{
		for (const auto& [name, weapon] : m_weapons_cache.weapon_map)
			if (rage::joaat(name) == hash)
				return weapon;
		return gta_data_service::empty_weapon;
	}

	const weapon_component& gta_data_service::weapon_component_by_hash(uint32_t hash)
	{
		for (const auto& [name, component] : m_weapons_cache.weapon_components)
			if (component.m_hash == hash)
				return component;
		return gta_data_service::empty_component;
	}

	const weapon_component& gta_data_service::weapon_component_by_name(std::string name)
	{
		for (const auto& [name_key, component] : m_weapons_cache.weapon_components)
			if (name_key == name)
				return component;
		return gta_data_service::empty_component;
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

		auto weapons_file = g_file_manager.get_project_file("./cache/weapons.json");
		if (weapons_file.exists())
		{
			std::ifstream file(weapons_file.get_path());
			file.open(weapons_file.get_path());

			try
			{
				nlohmann::json weapons_file_json;
				file >> weapons_file_json;
				m_weapons_cache = weapons_file_json["weapons_cache"];
				file.close();
			}
			catch (const std::exception& exception)
			{
				file.close();
				LOG(WARNING) << "Detected corrupt weapons: " << exception.what();
			}
		}

		const auto file_version = memory::module("GTA5.exe").size();

		return m_peds_cache.up_to_date(file_version) && m_vehicles_cache.up_to_date(file_version) && m_weapons_cache.up_to_date(file_version);
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
		LOG(INFO) << "Loading " << m_weapons_cache.weapon_map.size() << " weapons from cache.";
		LOG(INFO) << "Loading " << m_weapons_cache.weapon_components.size() << " weapon components from cache.";

		for (const auto& [_, weapon] : m_weapons_cache.weapon_map)
		{
			add_if_not_exists(m_weapon_types, weapon.m_weapon_type);
		}

		std::sort(m_weapon_types.begin(), m_weapon_types.end());
	}

	inline void parse_ped(std::vector<ped_item>& peds, std::vector<uint32_t>& mapped_peds, pugi::xml_document& doc)
	{
		const auto& items = doc.select_nodes("/CPedModelInfo__InitDataList/InitDatas/Item");
		for (const auto& item_node : items)
		{
			const auto& item = item_node.node();
			const auto name  = item.child("Name").text().as_string();
			const auto hash  = rage::joaat(name);

			if (is_crash_ped(hash))
				continue;

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
		using hash_array = std::vector<uint32_t>;
		hash_array mapped_peds;
		hash_array mapped_vehicles;
		hash_array mapped_weapons;
		hash_array mapped_components;

		std::vector<ped_item> peds;
		std::vector<vehicle_item> vehicles;
		std::vector<weapon_item> weapons;
		std::vector<weapon_component> weapon_components;

		constexpr auto exists = [](const hash_array& arr, uint32_t val) -> bool {
			return std::find(arr.begin(), arr.end(), val) != arr.end();
		};

		LOG(INFO) << "Rebuilding cache started...";

		yim_fipackfile::add_wrapper_call_back([&](yim_fipackfile& rpf_wrapper, std::filesystem::path path) -> void {
			if (path.filename() == "setup2.xml")
			{
				std::string dlc_name;
				rpf_wrapper.read_xml_file(path, [&dlc_name](pugi::xml_document& doc) {
					const auto item = doc.select_node("/SSetupData/nameHash");
					dlc_name        = item.node().text().as_string();
				});

				if (dlc_name == "mpG9EC")
				{
					LOG(VERBOSE) << "Bad DLC, skipping...";
				}
			}
			else if (path.filename() == "vehicles.meta")
			{
				rpf_wrapper.read_xml_file(path, [&exists, &vehicles, &mapped_vehicles](pugi::xml_document& doc) {
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
						std::strncpy(veh.m_display_manufacturer, manufacturer_display, sizeof(veh.m_display_manufacturer));

						const auto game_name = item.child("gameName").text().as_string();
						std::strncpy(veh.m_display_name, game_name, sizeof(veh.m_display_name));

						const auto vehicle_class       = item.child("vehicleClass").text().as_string();
						constexpr auto enum_prefix_len = 3;
						if (std::strlen(vehicle_class) > enum_prefix_len)
							std::strncpy(veh.m_vehicle_class, vehicle_class + enum_prefix_len, sizeof(veh.m_vehicle_class));

						veh.m_hash = hash;

						vehicles.emplace_back(std::move(veh));
					}
				});
			}
			else if (const auto file_str = path.string(); file_str.find("weaponcomponents") != std::string::npos && path.extension() == ".meta")
			{
				rpf_wrapper.read_xml_file(path, [&exists, &weapon_components, &mapped_components](pugi::xml_document& doc) {
					const auto& items = doc.select_nodes("/CWeaponComponentInfoBlob/Infos/*[self::Item[@type='CWeaponComponentInfo'] or self::Item[@type='CWeaponComponentFlashLightInfo'] or self::Item[@type='CWeaponComponentScopeInfo'] or self::Item[@type='CWeaponComponentSuppressorInfo'] or self::Item[@type='CWeaponComponentVariantModelInfo'] or self::Item[@type='CWeaponComponentClipInfo']]");
					for (const auto& item_node : items)
					{
						const auto item        = item_node.node();
						const std::string name = item.child("Name").text().as_string();
						const auto hash        = rage::joaat(name);

						if (!name.starts_with("COMPONENT"))
						{
							continue;
						}

						if (exists(mapped_components, hash))
						{
							continue;
						}
						mapped_components.emplace_back(hash);

						std::string LocName = item.child("LocName").text().as_string();
						std::string LocDesc = item.child("LocDesc").text().as_string();

						if (LocName.ends_with("INVALID") || LocName.ends_with("RAIL"))
						{
							continue;
						}

						weapon_component component;

						component.m_name         = name;
						component.m_hash         = hash;
						component.m_display_name = LocName;
						component.m_display_desc = LocDesc;

						weapon_components.push_back(component);
					}
				});
			}
			else if (const auto file_str = path.string(); file_str.find("weapon") != std::string::npos && path.extension() == ".meta")
			{
				rpf_wrapper.read_xml_file(path, [&exists, &weapons, &mapped_weapons](pugi::xml_document& doc) {
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

						weapon.m_name = name;

						weapon.m_display_name = human_name_hash;

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
							weapon.m_weapon_type = category + 6;
						}

						if (is_gun || weapon.m_weapon_type == "MELEE" || weapon.m_weapon_type == "UNARMED")
						{
							const std::string reward_prefix = "REWARD_";
							weapon.m_reward_hash            = rage::joaat(reward_prefix + name);

							if (is_gun && !is_rechargable)
							{
								std::string weapon_id     = name + 7;
								weapon.m_reward_ammo_hash = rage::joaat(reward_prefix + "AMMO_" + weapon_id);
							}
						}

						for (pugi::xml_node attach_point : item.child("AttachPoints").children("Item"))
						{
							for (pugi::xml_node component : attach_point.child("Components").children("Item"))
							{
								weapon.m_attachments.push_back(component.child_value("Name"));
							}
						}

						weapon.m_hash = hash;

						weapons.emplace_back(std::move(weapon));
					skip:
						continue;
					}
				});
			}
			else if (path.filename() == "peds.meta")
			{
				rpf_wrapper.read_xml_file(path, [&exists, &peds, &mapped_peds](pugi::xml_document& doc) {
					parse_ped(peds, mapped_peds, doc);
				});
			}
			else if (std::string str = rpf_wrapper.get_name(); (str.find("componentpeds") != std::string::npos || str.find("streamedpeds") != std::string::npos || str.find("mppatches") != std::string::npos || str.find("cutspeds") != std::string::npos) && path.extension() == ".yft")
			{
				const auto name = path.stem().string();
				const auto hash = rage::joaat(name);

				if (is_crash_ped(hash))
					return;

				if (std::find(mapped_peds.begin(), mapped_peds.end(), hash) != mapped_peds.end())
					return;

				mapped_peds.emplace_back(hash);

				auto ped = ped_item{};

				std::strncpy(ped.m_name, name.c_str(), sizeof(ped.m_name));

				ped.m_hash = hash;

				peds.emplace_back(std::move(ped));
			}
		});

		if (state() == eGtaDataUpdateState::UPDATING)
		{
			yim_fipackfile::for_each_fipackfile();
		}

		static bool translate_lebel = false;

		g_fiber_pool->queue_job([&] {
			for (auto& item : vehicles)
			{
				std::strncpy(item.m_display_manufacturer, HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(item.m_display_manufacturer), sizeof(item.m_display_manufacturer));
				std::strncpy(item.m_display_name, HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(item.m_display_name), sizeof(item.m_display_name));
				char vehicle_class[32];
				std::sprintf(vehicle_class, "VEH_CLASS_%i", VEHICLE::GET_VEHICLE_CLASS_FROM_NAME(item.m_hash));
				std::strncpy(item.m_vehicle_class, HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(vehicle_class), sizeof(item.m_vehicle_class));
			}
			for (auto& item : weapons)
			{
				item.m_display_name = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(item.m_display_name.c_str());
			}
			for (auto& item : weapon_components)
			{
				item.m_display_name = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(item.m_display_name.c_str());
				item.m_display_desc = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(item.m_display_desc.c_str());
			}
			for (auto it = peds.begin(); it != peds.end();)
			{
				if (CPedModelInfo* info = model_info::get_model<CPedModelInfo*>(it->m_hash))
				{
					static std::array<std::string, 30> ped_types = {"PLAYER_0", "PLAYER_1", "NETWORK_PLAYER", "PLAYER_2", "CIVMALE", "CIVFEMALE", "COP", "GANG_ALBANIAN", "GANG_BIKER_1", "GANG_BIKER_2", "GANG_BIKER_2", "GANG_RUSSIAN", "GANG_RUSSIAN_2", "GANG_RUSSIAN_2", "GANG_JAMAICAN", "GANG_AFRICAN_AMERICAN", "GANG_KOREAN", "GANG_CHINESE_JAPANESE", "GANG_PUERTO_RICAN", "DEALER", "MEDIC", "FIREMAN", "CRIMINAL", "BUM", "PROSTITUTE", "SPECIAL", "MISSION", "SWAT", "ANIMAL", "ARMY"};
					std::strncpy(it->m_ped_type, ped_types[info->ped_type].c_str(), sizeof(it->m_ped_type));
					++it;
				}
				else
				{
					peds.erase(it);
				}
			}
			translate_lebel = true;
		});

		while (!translate_lebel)
		{
			if (state() == eGtaDataUpdateState::UPDATING)
				script::get_current()->yield();
			else
				std::this_thread::sleep_for(100ms);
		}

		m_update_state = eGtaDataUpdateState::IDLE;
		LOG(INFO) << "Cache has been rebuilt.\n\tPeds: " << peds.size() << "\n\tVehicles: " << vehicles.size()
		          << "\n\tWeapons: " << weapons.size() << "\n\tWeaponComponents: " << weapon_components.size();

		LOG(VERBOSE) << "Starting cache saving procedure...";
		g_thread_pool->push([this, peds = std::move(peds), vehicles = std::move(vehicles), weapons = std::move(weapons), weapon_components = std::move(weapon_components)] {
			const auto file_version = memory::module("GTA5.exe").size();

			{
				const auto data_size = sizeof(ped_item) * peds.size();
				m_peds_cache.set_data(std::make_unique<uint8_t[]>(data_size), data_size);
				std::memcpy(m_peds_cache.data(), peds.data(), data_size);

				m_peds_cache.set_header_version(file_version);
				m_peds_cache.write();
			}

			{
				const auto data_size = sizeof(vehicle_item) * vehicles.size();
				m_vehicles_cache.set_data(std::make_unique<uint8_t[]>(data_size), data_size);
				std::memcpy(m_vehicles_cache.data(), vehicles.data(), data_size);

				m_vehicles_cache.set_header_version(file_version);
				m_vehicles_cache.write();
			}

			{
				m_weapons_cache.version_info.m_game_build     = g_pointers->m_gta.m_game_version;
				m_weapons_cache.version_info.m_online_version = g_pointers->m_gta.m_online_version;
				m_weapons_cache.version_info.m_file_version   = file_version;

				for (auto weapon : weapons)
				{
					add_if_not_exists(m_weapon_types, weapon.m_weapon_type);
					m_weapons_cache.weapon_map.insert({weapon.m_name, weapon});
				}

				for (auto weapon_component : weapon_components)
				{
					m_weapons_cache.weapon_components.insert({weapon_component.m_name, weapon_component});
				}

				auto weapons_file = g_file_manager.get_project_file("./cache/weapons.json");
				std::ofstream file(weapons_file.get_path());
				try
				{
					nlohmann::json weapons_file_json;
					weapons_file_json["weapons_cache"] = m_weapons_cache;
					file << weapons_file_json;
					file.flush();
				}
				catch (const std::exception& exception)
				{
					LOG(WARNING) << "Failed to write weapons JSON: " << exception.what();
				}
			}

			LOG(INFO) << "Finished writing cache to disk.";

			load_data();
		});
	}
}