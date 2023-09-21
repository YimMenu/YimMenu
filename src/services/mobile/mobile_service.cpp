#include "mobile_service.hpp"

#include "fiber_pool.hpp"
#include "natives.hpp"
#include "script.hpp"
#include "util/mobile.hpp"

namespace big
{
	//None of these will get inlined as they are just a massive switch table, but we can ask anyway.
	inline int get_property_garage_offset(int property)
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
			//Singular property entities like the Terrorbyte.
			case 30: return 156;
			case 31: return 224;
			case 32: return 223;
			case 33: return 278;
		}
		return -1;
	}

	inline int get_property_garage_size(int property)
	{
		switch (property)
		{
			case 30:
			case 32:
			case 33:
			case 14: return 1;
			case 31: return 3;
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
			case 0:
			case 1:
			case 2:
			case 3:
			case 4:
			case 7:
			case 13:
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
		return 0;
	}

	inline int get_property_stat_state(int property)
	{
		int stat_to_lookup = -1;
		switch (property)
		{
			case 0: stat_to_lookup = 1279; break;
			case 1: stat_to_lookup = 1878; break;
			case 2: stat_to_lookup = 2269; break;
			case 3: stat_to_lookup = 2932; break;
			case 4: stat_to_lookup = 3061; break;
			case 5: stat_to_lookup = 3230; break;
			case 6: stat_to_lookup = 3233; break;
			case 7: stat_to_lookup = 3235; break;
			case 8: stat_to_lookup = 4023; break;
			case 9: stat_to_lookup = 4026; break;
			case 10: stat_to_lookup = 4029; break;
			case 11: stat_to_lookup = 4032; break;
			case 12: stat_to_lookup = 6113; break;
			case 13: stat_to_lookup = 6171; break;
			case 14: stat_to_lookup = 6549; break;
			case 15: stat_to_lookup = 6562; break;
			case 16: stat_to_lookup = 6565; break;
			case 17: stat_to_lookup = 6568; break;
			case 18: stat_to_lookup = 7286; break;
			case 19: stat_to_lookup = 7288; break;
			case 20: stat_to_lookup = 7290; break;
			case 21: stat_to_lookup = 8013; break;
			case 22: stat_to_lookup = 8537; break;
			case 23: stat_to_lookup = 8980; break;
			case 24: stat_to_lookup = 8983; break;
			case 25: stat_to_lookup = 9624; break;
			case 26: stat_to_lookup = 9913; break;
			case 27: stat_to_lookup = 10441; break;
			case 28: stat_to_lookup = 10444; break;
			case 29: stat_to_lookup = 10874; break;
			case 30:
			case 31:
			case 32:
			case 33: return 1;
		}
		if (stat_to_lookup == -1)
		{
			return -1;
		}
		Hash stat_hash = STATS::_GET_STAT_HASH_FOR_CHARACTER_STAT(0, stat_to_lookup, g.player.character_slot);
		int stat_value{};
		if (STATS::STAT_GET_INT(stat_hash, &stat_value, -1))
		{
			return stat_value;
		}
		return -1;
	}

	inline std::string get_static_property_name(int property)
	{
		switch (property)
		{
			case 12: //Hangar
			{
				auto hangar_id = *scr_globals::gpbd_fm_1.at(self::id, 867).at(267).at(293).as<PINT>();
				switch (hangar_id)
				{
					case 1: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("MP_HANGAR_1"); //LSIA Hangar 1
					case 2: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("MP_HANGAR_2"); //LSIA Hangar A17
					case 3: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("MP_HANGAR_3"); //Fort Zancudo Hangar A2
					case 4: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("MP_HANGAR_4"); //Fort Zancudo Hangar 3497
					case 5: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("MP_HANGAR_5"); //Fort Zancudo Hangar 3499
				}
			}
			case 13: //Facility
			{
				auto facility_id = *scr_globals::gpbd_fm_1.at(self::id, 867).at(267).at(300).as<PINT>();
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
			}
			case 14: //Nightclub
			{
				auto nightclub_id = *scr_globals::gpbd_fm_1.at(self::id, 867).at(267).at(354).as<PINT>();
				switch (nightclub_id)
				{
					case 1: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("MP_NCLU_1"); //La Mesa Nightclub
					case 2: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("MP_NCLU_2"); //Mission Row Nightclub
					case 3: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("MP_NCLU_3"); //Strawberry Nightclub
					case 4: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("MP_NCLU_4"); //West Vinewood Nightclub
					case 5: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("MP_NCLU_5"); //Cypress Flats Nightclub
					case 6: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("MP_NCLU_6"); //LSIA Nightclub
					case 7: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("MP_NCLU_7"); //Elysian Island Nightclub
					case 8: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("MP_NCLU_8"); //Downtown Vinewood Nightclub
					case 9: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("MP_NCLU_9"); //Del Perro Nightclub
					case 10: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("MP_NCLU_10"); //Vespucci Canals Nightclub
				}
			}
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
			case 30: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("GRTRUCK"); //Mobile Operations Center
			case 31: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("MP_BHUB_CLUBT"); //Terrorbyte
			case 32: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("MP_BHUB_GAR0"); //Nightclub B1
			case 33: return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION("MP_BHUB_SUB"); //Kosatka
		}
		return std::string();
	}

	personal_vehicle::personal_vehicle(int idx, script_global vehicle_idx) :
	    m_id(idx),
	    m_vehicle_idx(vehicle_idx)
	{
		m_plate          = m_vehicle_idx.at(1).as<char*>();
		m_hash           = *m_vehicle_idx.at(66).as<Hash*>();

		for (int property_iterator = 0; property_iterator < 35; property_iterator++)
		{
			auto property_stat_state = get_property_stat_state(property_iterator);
			if (property_stat_state > 0)
			{
				auto garage_size = get_property_garage_size(property_iterator);
				auto garage_offset = get_property_garage_offset(property_iterator);
				for (int garage_slot_iterator = 0; garage_slot_iterator < garage_size; garage_slot_iterator++)
				{
					auto item_in_slot = *scr_globals::property_garage.at(garage_offset).at(garage_slot_iterator).as<PINT>() - 1;
					if (item_in_slot == idx)
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
						property_iterator = 999;
						break;
					}
				}
			}
		}

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
			case RAGE_JOAAT("avenger"):
			case RAGE_JOAAT("avenger3"):
			case RAGE_JOAAT("hauler2"):
			case RAGE_JOAAT("phantom3"):
			case RAGE_JOAAT("trailersmall2"):
			case RAGE_JOAAT("khanjali"):
			case RAGE_JOAAT("chernobog"):
			case RAGE_JOAAT("riot2"):
			case RAGE_JOAAT("thruster"):
			case RAGE_JOAAT("brickade2"):
			case RAGE_JOAAT("manchez3"):
			case RAGE_JOAAT("terbyte"):
			case RAGE_JOAAT("speedo4"):
			case RAGE_JOAAT("mule4"):
			case RAGE_JOAAT("pounder2"):
			case RAGE_JOAAT("rcbandito"):
			case RAGE_JOAAT("minitank"):
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