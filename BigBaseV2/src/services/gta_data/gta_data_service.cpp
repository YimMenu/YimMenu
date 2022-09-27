#include "api/remote.hpp"
#include "file_manager.hpp"
#include "gta_data_service.hpp"
#include "gta/gxt2.hpp"
#include "pointers.hpp"
#include "gta/fidevice.hpp"
#include "pugixml.hpp"
#include "yim_fipackfile.hpp"
#include "natives.hpp"
#include "fiber_pool.hpp"
#include "script.hpp"
#include "thread_pool.hpp"
#include "util/notify.hpp"

#define EXIST_IN_ARRAY(arr, val) (std::find(std::begin(arr), std::end(arr), val) != std::end(arr))

namespace big
{
	gta_data_service::gta_data_service()
	{
		// this has to happen in a gta thread because of the required tls context when iterating through rpf files
		g_fiber_pool->queue_job([this]()
		{
			while (*g_pointers->m_game_state != eGameState::Playing)
			{
				script::get_current()->yield(1s);
			}

			if (!is_cache_updated())
			{
				script::get_current()->yield(1s);
				notify::above_map("Updating vehicles, peds and weapons cache. This may take a bit.");
				script::get_current()->yield(1s);

				update_cache_and_load_data();
			}
			else
			{
				load_data();
			}
		});

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

	bool gta_data_service::is_cache_updated()
	{
		std::ifstream cache_version_file(g_file_manager->get_project_file(cache_version_file_path).get_path());
		std::stringstream cache_version_file_content;
		cache_version_file_content << cache_version_file.rdbuf();

		return cache_version_file_content.str() == (std::string(g_pointers->m_game_version) + std::string(g_pointers->m_online_version));
	}

	void gta_data_service::save_cache_version()
	{
		std::ofstream cache_version_file(g_file_manager->get_project_file(cache_version_file_path).get_path());
		cache_version_file << g_pointers->m_game_version << g_pointers->m_online_version;
	}

	static nlohmann::json split_str_into_json_array(const std::string& s, const std::string& delimiter)
	{
		size_t pos_start = 0, pos_end, delim_len = delimiter.length();
		std::string token;
		auto res = nlohmann::json::array();

		while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos)
		{
			token = s.substr(pos_start, pos_end - pos_start);
			pos_start = pos_end + delim_len;
			res.push_back(token);
		}

		res.push_back(s.substr(pos_start));
		return res;
	}

	// todo: find a way to keep it fast but also
	void gta_data_service::update_cache_and_load_data()
	{
		// wrap around shared ptr because we'll share it with a worker thread below

		std::shared_ptr<std::vector<GXT2_entry>> gxt2_entries = std::make_shared<std::vector<GXT2_entry>>();

		// we may encounter the same vehicle xml entry while iterating rpfs.
		std::unordered_map<rage::joaat_t, const void*> veh_hashes;
		// we always add a vehicle entry to the veh json through the vehicles.meta parser
		// then we add info to them later on through that vector
		std::shared_ptr<std::vector<nlohmann::json>> scheduled_vehs = std::make_shared<std::vector<nlohmann::json>>();
		std::shared_ptr<nlohmann::json> vehs = std::make_shared<nlohmann::json>(nlohmann::json::array());

		// we may encounter the same ped xml entry while iterating rpfs.
		std::unordered_map<rage::joaat_t, const void*> peds_hashes;
		std::shared_ptr<nlohmann::json> peds = std::make_shared<nlohmann::json>(nlohmann::json::array());

		// we may encounter the same weapon xml entry while iterating rpfs.
		std::unordered_map<rage::joaat_t, const void*> weapons_hashes;
		std::shared_ptr<nlohmann::json> weapons = std::make_shared<nlohmann::json>(nlohmann::json::array());

		yim_fipackfile::for_each_fipackfile([&](yim_fipackfile& rpf_wrapper)
		{
			const auto file_paths = rpf_wrapper.get_file_paths();
			for (const auto& file_path : file_paths)
			{
				if (file_path.find("/vehicles.meta") != std::string::npos)
				{
					rpf_wrapper.read_xml_file(file_path, [&](pugi::xml_document& doc)
					{
						pugi::xpath_node_set items = doc.select_nodes("/CVehicleModelInfo__InitDataList/InitDatas/Item");
						for (pugi::xpath_node item_node : items)
						{
							pugi::xml_node item = item_node.node();

							nlohmann::json veh;

							veh["Name"] = item.child("modelName").text().as_string();
							veh["HandlingId"] = item.child("handlingId").text().as_string();

							rage::joaat_t model_hash = rage::joaat(veh["Name"]);

							if (veh_hashes.find(model_hash) != veh_hashes.end())
							{
								continue;
							}
							veh_hashes[model_hash] = {};

							veh["Hash"] = model_hash;
							veh["SignedHash"] = (int32_t)model_hash;
							std::stringstream s;
							s << HEX_TO_UPPER(model_hash);
							veh["HexHash"] = s.str();

							veh["DlcName"] = "TODO"; // todo: how DurtyFree generate it?

							veh["HandlingId"] = item.child("handlingId").text().as_string();

							veh["LayoutId"] = item.child("layout").text().as_string();

							const std::string manufacturer = item.child("vehicleMakeName").text().as_string();
							if (manufacturer.size())
							{
								veh["Manufacturer"] = manufacturer;
								veh["ManufacturerHash"] = rage::joaat(manufacturer);
								veh["ManufacturerDisplayName"] = nullptr;
							}
							else
							{
								veh["Manufacturer"] = "";
								veh["ManufacturerHash"] = -1;
								veh["ManufacturerDisplayName"] = nullptr;
							}

							const auto vehicle_class = std::string(item.child("vehicleClass").text().as_string());
							if (vehicle_class.size() > 3)
								veh["Class"] = vehicle_class.substr(3);
							else
								veh["Class"] = nullptr;

							veh["ClassId"] = 0; // todo: how DurtyFree generate it?

							const auto vehicle_type = std::string(item.child("type").text().as_string());
							if (vehicle_type.size() > 13)
								veh["Type"] = vehicle_type.substr(13);
							else
								veh["Type"] = nullptr;

							const auto plate_type = std::string(item.child("plateType").text().as_string());
							if (plate_type.size() > 4)
								veh["PlateType"] = plate_type.substr(4);
							else
								veh["PlateType"] = nullptr;

							const auto dashboard_type = std::string(item.child("dashboardType").text().as_string());
							if (dashboard_type.size() > 4)
								veh["DashboardType"] = dashboard_type.substr(4);
							else
								veh["DashboardType"] = nullptr;

							const auto wheel_type = std::string(item.child("wheelType").text().as_string());
							if (wheel_type.size() > 4)
								veh["WheelType"] = wheel_type.substr(4);
							else
								veh["WheelType"] = nullptr;

							const std::string flags_str = item.child("flags").text().as_string();
							veh["Flags"] = split_str_into_json_array(flags_str, " ");

							veh["Seats"] = VEHICLE::GET_VEHICLE_MODEL_NUMBER_OF_SEATS(model_hash);

							veh["Price"] = -1; // todo: how DurtyFree generate it?
							veh["MonetaryValue"] = VEHICLE::GET_VEHICLE_MODEL_VALUE(model_hash);

							veh["HasConvertibleRoof"] = flags_str.find("CONVERTIBLE") != std::string::npos;

							const auto rewards = item.child("rewards").select_nodes("Item");
							if (rewards.size())
							{
								veh["Rewards"] = nlohmann::json::array();
								for (const auto& reward : rewards)
								{
									veh["Rewards"].push_back(reward.node().text().as_string());
								}
							}
							else
							{
								veh["Rewards"] = nullptr;
							}

							vehs->push_back(veh);
						}
					});
				}
				else if (file_path.find("global.gxt2") != std::string::npos)
				{
					rpf_wrapper.read_file<std::vector<uint8_t>>(file_path, [&](const std::vector<uint8_t>& file_content)
					{
						std::string gxt2_header;
						gxt2_header.resize(4);
						memcpy(gxt2_header.data(), file_content.data(), 4);

						if (gxt2_header == GXT2_metadata::header)
						{
							uint32_t gxt_key_entries_count = 0;
							memcpy(&gxt_key_entries_count, file_content.data() + 0x04, 4);

							std::vector<GXT2_key> key_entries;
							key_entries.resize(gxt_key_entries_count * sizeof(GXT2_key));
							memcpy(key_entries.data(), file_content.data() + 0x08, gxt_key_entries_count * sizeof(GXT2_key));

							uint32_t end_offset = 0;
							memcpy(&end_offset, file_content.data() + 0x08 + gxt_key_entries_count * sizeof(GXT2_key), 4);

							for (const auto& key_entry : key_entries)
							{
								std::string text;
								uint32_t offset = key_entry.file_offset_to_text;
								if (offset >= end_offset)
								{
									break;
								}
								while (file_content[offset] != 0 && offset < end_offset)
								{
									text.push_back(file_content[offset++]);
								}

								GXT2_entry gxt2_entry;
								gxt2_entry.hash = key_entry.key_hash;
								gxt2_entry.text = text;
								gxt2_entries->push_back(gxt2_entry);
							}
						}
					});
				}
				else if ((file_path.find("weapon") != std::string::npos && file_path.find(".meta") != std::string::npos))
				{
					rpf_wrapper.read_xml_file(file_path, [&](pugi::xml_document& doc)
					{
						pugi::xpath_node_set items = doc.select_nodes("/CWeaponInfoBlob/Infos/Item/Infos/Item[@type='CWeaponInfo']");
						for (const auto& item_node : items)
						{
							pugi::xml_node item = item_node.node();

							nlohmann::json weapon;

							weapon["Name"] = item.child("Name").text().as_string();

							std::string human_name_hash = item.child("HumanNameHash").text().as_string();
							if (human_name_hash == "WT_INVALID")
							{
								continue;
							}

							weapon["HumanNameHash"] = rage::joaat(human_name_hash);

							uint32_t model_hash = rage::joaat(weapon["Name"]);

							if (weapons_hashes.find(model_hash) != weapons_hashes.end())
							{
								continue;
							}
							weapons_hashes[model_hash] = {};

							weapon["Hash"] = model_hash;
							weapon["IntHash"] = (int32_t)model_hash;

							const std::string flags_str = item.child("WeaponFlags").text().as_string();
							weapon["Flags"] = split_str_into_json_array(flags_str, " ");

							weapon["Category"] = item.child("Group").text().as_string();

							weapon["IsVehicleWeapon"] = std::string(item.child("VehicleWeaponHash").text().as_string()).size() > 0 || weapon["Flags"].contains("Vehicle");

							weapons->push_back(weapon);
						}
					});
				}
				else if (file_path.find("weaponcomponents.meta") != std::string::npos)
				{

				}
				else if (file_path.find("/peds.meta") != std::string::npos ||
						file_path.find("/peds.ymt") != std::string::npos)
				{
					rpf_wrapper.read_xml_file(file_path, [&](pugi::xml_document& doc)
					{
						pugi::xpath_node_set items = doc.select_nodes("/CPedModelInfo__InitDataList/InitDatas/Item");
						for (const auto& item_node : items)
						{
							pugi::xml_node item = item_node.node();

							nlohmann::json ped;

							ped["Name"] = item.child("Name").text().as_string();

							uint32_t model_hash = rage::joaat(ped["Name"]);

							if (peds_hashes.find(model_hash) != peds_hashes.end())
							{
								continue;
							}
							peds_hashes[model_hash] = {};

							ped["Hash"] = model_hash;
							ped["SignedHash"] = (int32_t)model_hash;
							std::stringstream s;
							s << HEX_TO_UPPER(model_hash);
							ped["HexHash"] = s.str();
							ped["DlcName"] = "Unk";

							ped["PropsName"] = item.child("PropsName").text().as_string();

							ped["ClipDictionaryName"] = item.child("ClipDictionaryName").text().as_string();
							ped["BlendShapeFileName"] = item.child("BlendShapeFileName").text().as_string();
							ped["ExpressionSetName"] = item.child("ExpressionSetName").text().as_string();
							ped["ExpressionDictionaryName"] = item.child("ExpressionDictionaryName").text().as_string();
							ped["ExpressionName"] = item.child("ExpressionName").text().as_string();

							ped["Pedtype"] = item.child("Pedtype").text().as_string();

							ped["MovementClipSet"] = item.child("MovementClipSet").text().as_string();
							ped["MovementClipSets"] = nullptr; // todo

							ped["StrafeClipSet"] = item.child("StrafeClipSet").text().as_string();

							peds->push_back(ped);
						}
					});
				}
				else if (file_path.find("/carvariations.ymt") != std::string::npos ||
					file_path.find("/carvariations.meta") != std::string::npos)
				{
					rpf_wrapper.read_xml_file(file_path, [&](pugi::xml_document& doc)
					{
						pugi::xpath_node_set items = doc.select_nodes("/CVehicleModelInfoVariation/variationData/Item");
						for (const auto& item_node : items)
						{
							pugi::xml_node item = item_node.node();

							nlohmann::json veh;

							veh["Name"] = item.child("modelName").text().as_string();

							auto kits = item.child("kits").select_nodes("Item");
							veh["ModKits"] = nlohmann::json::array();
							for (const auto& kit : kits)
							{
								veh["ModKits"].push_back(kit.node().text().as_string());
							}

							veh["HasSirens"] = item.child("sirenSettings").attribute("value") != 0 ? true : false;

							scheduled_vehs->push_back(veh);
						}
					});
				}
				else if (file_path.find("/handling.meta") != std::string::npos)
				{
					rpf_wrapper.read_xml_file(file_path, [&](pugi::xml_document& doc)
					{
						pugi::xpath_node_set items = doc.select_nodes("/CHandlingDataMgr/HandlingData/Item");
						for (const auto& item_node : items)
						{
							pugi::xml_node item = item_node.node();

							nlohmann::json veh;

							veh["HandlingId"] = item.child("handlingName").text().as_string();

							auto veh_weapon_hashes = item.select_nodes("SubHandlingData/Item/uWeaponHash/Item");
							veh["Weapons"] = nlohmann::json::array();
							for (const auto& veh_weapon_hash : veh_weapon_hashes)
							{
								veh["Weapons"].push_back(veh_weapon_hash.node().text().as_string());
							}

							scheduled_vehs->push_back(veh);
						}
					});
				}
			}

			return file_paths.size();
		});

		LOG(INFO) << "Vehicle Count: " << vehs->size();
		if (!vehs->size())
			return;

		g_thread_pool->push([=]() {

			for (const auto& scheduled_veh : *scheduled_vehs)
			{
				std::string scheduled_veh_name = scheduled_veh.contains("Name") ? scheduled_veh["Name"] : "";
				std::string scheduled_veh_handling_id = scheduled_veh.contains("HandlingId") ? scheduled_veh["HandlingId"] : "";

				for (auto& veh : *vehs)
				{
					if (veh["Name"] == scheduled_veh_name || veh["HandlingId"] == scheduled_veh_handling_id)
					{
						for (const auto& [scheduled_key, scheduled_val] : scheduled_veh.items())
						{
							if (veh.contains(scheduled_key))
							{
								if ((scheduled_val.is_array() && scheduled_val.size()) ||
									!scheduled_val.is_null())
								{
									veh[scheduled_key] = scheduled_val;
								}
							}
							else
							{
								veh[scheduled_key] = scheduled_val;
							}
						}
					}
				}
			}

			for (const auto& gxt2_entry : *gxt2_entries)
			{
				if (gxt2_entry.hash != -1)
				{
					for (auto& veh : *vehs)
					{
						if (gxt2_entry.hash == veh["Hash"])
						{
							veh["DisplayName"] = gxt2_entry.text;
						}
						else if (gxt2_entry.hash == veh["ManufacturerHash"])
						{
							veh["ManufacturerDisplayName"] = gxt2_entry.text;
						}
					}

					for (auto& weapon : *weapons)
					{
						if (gxt2_entry.hash == weapon["HumanNameHash"])
						{
							weapon["DisplayName"] = gxt2_entry.text;
						}
					}
				}
			}

			LOG(INFO) << "Saving gta data to files";

			save_data_to_file(vehicles_json_file_path, *vehs);
			save_data_to_file(peds_json_file_path, *peds);
			save_data_to_file(weapons_json_file_path, *weapons);

			save_cache_version();

			load_data();
		});
	}

	void gta_data_service::load_data()
	{
		load_vehicles(g_file_manager->get_project_file(vehicles_json_file_path).get_path());
		load_peds(g_file_manager->get_project_file(peds_json_file_path).get_path());
		load_weapons(g_file_manager->get_project_file(weapons_json_file_path).get_path());

		g_fiber_pool->queue_job([]()
		{
			notify::above_map("Vehicles, peds and weapons cache loaded.");
		});
	}

	void gta_data_service::save_data_to_file(const std::string& file_path, const nlohmann::json& j)
	{
		file f(g_file_manager->get_project_file(file_path));
		std::ofstream ofstream(f.get_path());
		ofstream << std::setw(4) << j << std::endl;
	}

	bool gta_data_service::load_vehicles(std::filesystem::path path)
	{
		std::ifstream file(path);
		nlohmann::json all_vehicles;

		try
		{
			file >> all_vehicles;

			if (!all_vehicles.is_array())
			{
				throw std::exception("Invalid json format.");
			}

			m_vehicle_class_arr.clear();
			m_vehicle_hash_idx_map.clear();
			m_vehicle_item_arr.clear();

			for (auto& item_json : all_vehicles)
			{
				if (
					item_json["Hash"].is_null() ||
					item_json["Name"].is_null()
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
		catch (const std::exception& ex)
		{
			LOG(WARNING) << "Failed to load vehicles.json:\n" << ex.what();
			return false;
		}

		return true;
	}


	bool gta_data_service::load_peds(std::filesystem::path path)
	{
		std::ifstream file(path);
		nlohmann::json all_peds;

		try
		{
			file >> all_peds;

			if (!all_peds.is_array())
			{
				throw std::exception("Invalid json format.");
			}

			m_ped_type_arr.clear();
			m_ped_hash_idx_map.clear();
			m_ped_item_arr.clear();

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
		catch (const std::exception& ex)
		{
			LOG(WARNING) << "Failed to load peds.json:\n" << ex.what();
			return false;
		}

		return true;
	}


	bool gta_data_service::load_weapons(std::filesystem::path path)
	{
		std::ifstream file(path);
		nlohmann::json all_weapons;

		try
		{
			file >> all_weapons;

			if (!all_weapons.is_array())
			{
				throw std::exception("Invalid json format.");
			}

			m_weapon_type_arr.clear();
			m_weapon_hash_idx_map.clear();
			m_weapon_item_arr.clear();

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
					item_json["DisplayName"].is_null() ||
					item_json["IsVehicleWeapon"]
				) {
					continue;
				}

				if (EXIST_IN_ARRAY(hash_blacklist_arr, item_json["Hash"]))
				{
					continue;
				}

				auto item = weapon_item(item_json);

				m_weapon_hash_idx_map[item_json["Hash"]] = (int)m_weapon_item_arr.size();

				m_weapon_item_arr.push_back(item);

				if (std::find(m_weapon_type_arr.begin(), m_weapon_type_arr.end(), item.weapon_type) == m_weapon_type_arr.end())
				{
					m_weapon_type_arr.push_back(item.weapon_type);
				}

				std::sort(m_weapon_type_arr.begin(), m_weapon_type_arr.end());
			}

		}
		catch (const std::exception& ex)
		{
			LOG(WARNING) << "Failed to load weapons.json:\n" << ex.what();
			return false;
		}

		return true;
	}
}
