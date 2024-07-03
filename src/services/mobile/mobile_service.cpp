#include "mobile_service.hpp"

#include "fiber_pool.hpp"
#include "natives.hpp"
#include "script.hpp"
#include "util/mobile.hpp"

#define MAX_GARAGE_NUM 32

namespace big
{
	int get_property_garage_offset(int property)
	{
		switch (property)
		{
			case 0: return 13 * 0;
			case 1: return 13 * 1;
			case 2: return 13 * 2;
			case 3: return 13 * 3;
			case 4: return 13 * 4;
			//Property 5 is not used.
			case 6: return 65;
			case 7: return 75;
			case 8: return 88;
			case 9: return 108;
			case 10: return 128;
			case 11: return 148;
			case 12: return 159;
			case 13: return 179;
			case 14: return 191;
			case 15: return 192;
			case 16: return 202;
			case 17: return 212;
			case 18: return 227;
			case 19: return 237;
			case 20: return 247;
			case 21: return 258;
			case 22: return 268;
			case 23: return 281;
			case 24: return 294;
			case 25: return 307;
			case 26: return 317;
			case 27: return 337;
			case 28: return 350;
			case 29: return 363;
		    case 31: return 515;
			case MAX_GARAGE_NUM+0: return 156; //Mobile Operations Center
			case MAX_GARAGE_NUM+1: return 224; //Nightclub B1
			case MAX_GARAGE_NUM+2: return 223; //Terrorbyte
			case MAX_GARAGE_NUM+3: return 278; //Kosatka
		}
		return -1;
	}

	int get_property_garage_size(int property)
	{
		switch (property)
		{
			case MAX_GARAGE_NUM+0: //Mobile Operations Center
			case MAX_GARAGE_NUM+2: //Terrorbyte
			case MAX_GARAGE_NUM+3: //Kosatka
			case 14: return 1;
		    case 31: return 2;
			case MAX_GARAGE_NUM+1: return 3; //Nightclub B1
			case 11: return 8;
			case 6:
			case 15:
			case 16:
			case 17:
			case 18:
			case 19:
			case 20:
			case 21:
			case 22:
			case 25: return 10;
			case 13: return 11;
			case 0:
			case 1:
			case 2:
			case 3:
			case 4:
			case 7:
			case 23:
			case 24:
			case 27:
			case 28: return 13;
			case 8:
			case 9:
			case 10:
			case 12:
			case 26: return 20;
			case 29: return 50;
		}
		return -1;
	}

	int get_property_stat_state(int property)
	{
		Hash stat = NULL;
		switch (property)
		{
			case 0: stat = self::char_index ? "MP1_PROPERTY_HOUSE"_J : "MP0_PROPERTY_HOUSE"_J; break;
			case 1: stat = self::char_index ? "MP1_MULTI_PROPERTY_1"_J : "MP0_MULTI_PROPERTY_1"_J; break;
			case 2: stat = self::char_index ? "MP1_MULTI_PROPERTY_2"_J : "MP0_MULTI_PROPERTY_2"_J; break;
			case 3: stat = self::char_index ? "MP1_MULTI_PROPERTY_3"_J : "MP0_MULTI_PROPERTY_3"_J; break;
			case 4: stat = self::char_index ? "MP1_MULTI_PROPERTY_4"_J : "MP0_MULTI_PROPERTY_4"_J; break;
			case 5: stat = self::char_index ? "MP1_PROP_OFFICE"_J : "MP0_PROP_OFFICE"_J; break;
			case 6: stat = self::char_index ? "MP1_PROP_CLUBHOUSE"_J : "MP0_PROP_CLUBHOUSE"_J; break;
			case 7: stat = self::char_index ? "MP1_MULTI_PROPERTY_5"_J : "MP0_MULTI_PROPERTY_5"_J; break;
			case 8: stat = self::char_index ? "MP1_PROP_OFFICE_GAR1"_J : "MP0_PROP_OFFICE_GAR1"_J; break;
			case 9: stat = self::char_index ? "MP1_PROP_OFFICE_GAR2"_J : "MP0_PROP_OFFICE_GAR2"_J; break;
			case 10: stat = self::char_index ? "MP1_PROP_OFFICE_GAR3"_J : "MP0_PROP_OFFICE_GAR3"_J; break;
			case 11: stat = self::char_index ? "MP1_PROP_IE_WAREHOUSE"_J : "MP0_PROP_IE_WAREHOUSE"_J; break;
			case 12: stat = self::char_index ? "MP1_PROP_HANGAR"_J : "MP0_PROP_HANGAR"_J; break;
			case 13: stat = self::char_index ? "MP1_PROP_DEFUNCBASE"_J : "MP0_PROP_DEFUNCBASE"_J; break;
			case 14: stat = self::char_index ? "MP1_PROP_NIGHTCLUB"_J : "MP0_PROP_NIGHTCLUB"_J; break;
			case 15: stat = self::char_index ? "MP1_PROP_MEGAWARE_GAR1"_J : "MP0_PROP_MEGAWARE_GAR1"_J; break;
			case 16: stat = self::char_index ? "MP1_PROP_MEGAWARE_GAR2"_J : "MP0_PROP_MEGAWARE_GAR2"_J; break;
			case 17: stat = self::char_index ? "MP1_PROP_MEGAWARE_GAR3"_J : "MP0_PROP_MEGAWARE_GAR3"_J; break;
			case 18: stat = self::char_index ? "MP1_PROP_ARENAWARS_GAR1"_J : "MP0_PROP_ARENAWARS_GAR1"_J; break;
			case 19: stat = self::char_index ? "MP1_PROP_ARENAWARS_GAR2"_J : "MP0_PROP_ARENAWARS_GAR2"_J; break;
			case 20: stat = self::char_index ? "MP1_PROP_ARENAWARS_GAR3"_J : "MP0_PROP_ARENAWARS_GAR3"_J; break;
			case 21: stat = self::char_index ? "MP1_PROP_CASINO_GAR1"_J : "MP0_PROP_CASINO_GAR1"_J; break;
			case 22: stat = self::char_index ? "MP1_PROP_ARCADE_GAR1"_J : "MP0_PROP_ARCADE_GAR1"_J; break;
			case 23: stat = self::char_index ? "MP1_MULTI_PROPERTY_6"_J : "MP0_MULTI_PROPERTY_6"_J; break;
			case 24: stat = self::char_index ? "MP1_MULTI_PROPERTY_7"_J : "MP0_MULTI_PROPERTY_7"_J; break;
			case 25: stat = self::char_index ? "MP1_PROP_AUTO_SHOP"_J : "MP0_PROP_AUTO_SHOP"_J; break;
			case 26: stat = self::char_index ? "MP1_PROP_SECURITY_OFFICE_GAR"_J : "MP0_PROP_SECURITY_OFFICE_GAR"_J; break;
			case 27: stat = self::char_index ? "MP1_MULTI_PROPERTY_8"_J : "MP0_MULTI_PROPERTY_8"_J; break;
			case 28: stat = self::char_index ? "MP1_MULTI_PROPERTY_9"_J : "MP0_MULTI_PROPERTY_9"_J; break;
			case 29: stat = self::char_index ? "MP1_MULTSTOREY_GAR_OWNED"_J : "MP0_MULTSTOREY_GAR_OWNED"_J; break;
		    case 31: stat = self::char_index ? "MP1_PROP_BAIL_OFFICE"_J : "MP0_PROP_BAIL_OFFICE"_J; break;
			case MAX_GARAGE_NUM+0:
			case MAX_GARAGE_NUM+1:
			case MAX_GARAGE_NUM+2:
			case MAX_GARAGE_NUM+3: return 1;
		    default: return -1;
		}
		if (stat == NULL)
		{
			return -1;
		}
		int stat_value{};
		if (STATS::STAT_GET_INT(stat, &stat_value, -1))
		{
			return stat_value;
		}
		return -1;
	}

	std::string get_static_property_name(int property)
	{
		switch (property)
		{
			case 12: //Hangar
			{
			    auto hangar_id = *scr_globals::gpbd_fm_1.at(self::id, 883).at(268).at(297).as<PINT>();
				switch (hangar_id)
				{
					case 1: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("MP_HANGAR_1"); //LSIA Hangar 1
					case 2: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("MP_HANGAR_2"); //LSIA Hangar A17
					case 3: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("MP_HANGAR_3"); //Fort Zancudo Hangar A2
					case 4: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("MP_HANGAR_4"); //Fort Zancudo Hangar 3497
					case 5: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("MP_HANGAR_5"); //Fort Zancudo Hangar 3499
				}
				break;
			}
			case 13: //Facility
			{
			    auto facility_id = *scr_globals::gpbd_fm_1.at(self::id, 883).at(268).at(304).as<PINT>();
				switch (facility_id)
				{
					case 1: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("MP_DBASE_1"); //Grand Senora Desert Facility
					case 2: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("MP_DBASE_2"); //Route 68 Facility
					case 3: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("MP_DBASE_3"); //Sandy Shores Facility
					case 4: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("MP_DBASE_4"); //Mount Gordo Facility
					case 5: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("MP_DBASE_6"); //Paleto Bay Facility
					case 6: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("MP_DBASE_7"); //Lago Zancudo Facility
					case 7: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("MP_DBASE_8"); //Zancudo River Facility
					case 8: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("MP_DBASE_9"); //Ron Alternates Wind Farm Facility
					case 9: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("MP_DBASE_10"); //Land Act Reservoir Facility
				}
				break;
			}
			case 14: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("MP_BHUB_CLUBG"); //Nightclub Service Entrance
			case 15: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("MP_BHUB_GAR1"); //Nightclub B2
			case 16: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("MP_BHUB_GAR2"); //Nightclub B3
			case 17: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("MP_BHUB_GAR3"); //Nightclub B4
			case 18: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("ARENA_GAR_F0"); //Arena Workshop
			case 19: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("ARENA_GAR_F1"); //Arena Workshop B1
			case 20: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("ARENA_GAR_F2"); //Arena Workshop B1
			case 21: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("CASINO_GARNAME"); //Casino Penthouse
			case 22: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("ARCADE_GARNAME"); //Arcade
			case 25: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("AUT_SHP_GAR"); //Auto Shop
			case 26: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("FIXER_GARNAME"); //Agency
			case 29: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("WIN22_GARNAME"); //Eclipse Blvd Garage
			case 31: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("BO_GARNAME"); //Bail Office
			case MAX_GARAGE_NUM+0: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("GRTRUCK"); //Mobile Operations Center
			case MAX_GARAGE_NUM+1: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("MP_BHUB_GAR0"); //Nightclub B1
			case MAX_GARAGE_NUM+2: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("MP_BHUB_CLUBT"); //Terrorbyte
			case MAX_GARAGE_NUM+3: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("MP_BHUB_SUB"); //Kosatka
		}
		return std::string();
	}

	void personal_vehicle::set_garage()
	{
		for (int property_iterator = 0; property_iterator < MAX_GARAGE_NUM+4; property_iterator++)
		{
			auto property_stat_state = get_property_stat_state(property_iterator);
			if (property_stat_state > 0) //Check if the player owns the property
			{
				auto garage_size = get_property_garage_size(property_iterator);
				auto garage_offset = get_property_garage_offset(property_iterator);
				for (int garage_slot_iterator = 1; garage_slot_iterator <= garage_size; garage_slot_iterator++)
				{
					auto item_in_slot = *scr_globals::property_garage.at(garage_offset).at(garage_slot_iterator).as<PINT>() - 1;
					if (item_in_slot == m_id)
					{
						auto static_property_string = get_static_property_name(property_iterator);
						if (static_property_string.empty())
						{
							m_garage = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(scr_globals::property_names.at(property_stat_state, 1951).at(16).as<const char*>());
						}
						else
						{
							m_garage = static_property_string;
						}
						return;
					}
				}
			}
		}
	}

	personal_vehicle::personal_vehicle(int idx, script_global vehicle_idx) :
	    m_id(idx),
	    m_vehicle_idx(vehicle_idx)
	{
		m_plate          = m_vehicle_idx.at(1).as<char*>();
		m_hash           = *m_vehicle_idx.at(66).as<Hash*>();
		set_garage();

		m_name = std::format("{} ({})", HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(m_hash)), m_plate);
	}

	std::string personal_vehicle::get_display_name() const
	{
		return m_name + "##" + std::to_string(m_id);
	}

	Hash personal_vehicle::get_hash() const
	{
		return m_hash;
	}

	int personal_vehicle::get_id() const
	{
		return m_id;
	}

	const char* personal_vehicle::get_plate() const
	{
		return m_plate;
	}

	script_global personal_vehicle::get_vehicle_idx() const
	{
		return m_vehicle_idx;
	}

	void personal_vehicle::summon() const
	{
		mobile::mechanic::summon_vehicle_by_index(m_id);
	}

	std::string personal_vehicle::get_garage() const
	{
		return m_garage;
	}

	bool personal_vehicle::is_in_selected_garage() const
	{
		return g.clone_pv.garage.empty() || m_garage == g.clone_pv.garage;
	}

	bool personal_vehicle::is_blacklisted_vehicle() const
	{
		switch (m_hash)
		{
			case "avenger"_J:
			case "avenger3"_J:
			case "hauler2"_J:
			case "phantom3"_J:
			case "trailersmall2"_J:
			case "khanjali"_J:
			case "chernobog"_J:
			case "riot2"_J:
			case "thruster"_J:
			case "brickade2"_J:
			case "manchez3"_J:
			case "terbyte"_J:
			case "speedo4"_J:
			case "mule4"_J:
			case "pounder2"_J:
			case "rcbandito"_J:
			case "minitank"_J:
				return !g.clone_pv.spawn_clone;
		}
		return false;
	}

	mobile_service::mobile_service()
	{
		g_mobile_service = this;
	}

	mobile_service::~mobile_service()
	{
		g_mobile_service = nullptr;
	}

	void mobile_service::refresh_personal_vehicles()
	{
		const auto now = std::chrono::high_resolution_clock::now();
		if (std::chrono::duration_cast<std::chrono::seconds>(now - m_last_update) < 10s)
			return;
		m_last_update = std::chrono::high_resolution_clock::now();

		g_fiber_pool->queue_job([this] {
			register_vehicles();
			refresh_garages();
		});
	}

	void mobile_service::register_vehicles()
	{
		const auto array_size = *scr_globals::vehicle_global.as<int*>();
		for (int i = 0; i < array_size; i++)
		{
			if (i % 100 == 0)
				script::get_current()->yield();

			auto veh_idx_global = scr_globals::vehicle_global.at(i, 142);

			const auto hash   = *veh_idx_global.at(66).as<Hash*>();
			const auto& it    = m_pv_lookup.find(i);
			const auto exists = it != m_pv_lookup.end();

			// double check if model is a vehicle
			if (STREAMING::IS_MODEL_A_VEHICLE(hash))
			{
				auto veh = std::make_unique<personal_vehicle>(i, veh_idx_global);

				if (exists)
				{
					// vehicle name is no longer the same, update the vehicle at that index
					if (veh->get_display_name() != it->second)
					{
						m_personal_vehicles.erase(it->second);

						it->second = veh->get_display_name();
						m_personal_vehicles.emplace(veh->get_display_name(), std::move(veh));
					}
					else
					{
						m_personal_vehicles[veh->get_display_name()]->set_garage();
					}

					continue;
				}

				m_pv_lookup.emplace(i, veh->get_display_name());                     // update lookup table
				m_personal_vehicles.emplace(veh->get_display_name(), std::move(veh));// add new vehicle

				continue;
			}

			// vehicle existed at some point but no longer does
			if (exists)
			{
				m_personal_vehicles.erase(it->second);
				m_pv_lookup.erase(i);
			}
		}
	}

	void mobile_service::refresh_garages()
	{
		m_garages.clear();
		for (const auto& [name, personal_vehicle_ptr] : personal_vehicles())
		{
			if (!personal_vehicle_ptr->is_blacklisted_vehicle())
			{
				auto garage_name = personal_vehicle_ptr->get_garage();
				if (!garage_name.empty())
				{
					m_garages.emplace(personal_vehicle_ptr->get_garage());
				}
			}
		}
	}
}
