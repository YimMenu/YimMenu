#pragma once
#include "natives.hpp"
#include "pointers.hpp"
#include "script.hpp"
#include "gta/enums.hpp"
#include "gta/joaat.hpp"


namespace big::blip
{
	struct blip_search {
		BlipIcons spite;
		std::vector<BlipColors> colors;
	};

	struct blip_hardcoded {
		std::string name;
		Vector3 location;
	};

	inline bool get_blip_location(const std::vector<blip_search>& blip_search_arr, Vector3& location)
	{
		LOG(WARNING) << "POS: " << self::pos.x << " " << self::pos.y << " " << self::pos.z;

		for (auto& item : blip_search_arr)
		{
			Blip blip = HUD::GET_FIRST_BLIP_INFO_ID((int)item.spite);

			while (HUD::DOES_BLIP_EXIST(blip))
			{
				LOG(WARNING) << "POI: " << (int)item.spite;

				if (item.colors.size() == 0)
				{
					location = HUD::GET_BLIP_COORDS(blip);
					location.z += 1.5f;

					BlipColors color_idx = (BlipColors)HUD::GET_BLIP_COLOUR(blip);
					LOG(WARNING) << "POI: 0T " << (int)color_idx;
					LOG(WARNING) << "POS2: " << location.x << " " << location.y << " " << location.z;

					return true;
				}
				else
				{
					BlipColors color_idx = (BlipColors)HUD::GET_BLIP_COLOUR(blip);

					if (std::find(item.colors.begin(), item.colors.end(), color_idx) != item.colors.end())
					{
						location = HUD::GET_BLIP_COORDS(blip);
						location.z += 1.5f;

						LOG(WARNING) << "POI: T " << (int)color_idx;
						LOG(WARNING) << "POS2: " << location.x << " " << location.y << " " << location.z;

						return true;
					}

					LOG(WARNING) << "POI: 1T " << (int)color_idx;
				}

				blip = HUD::GET_NEXT_BLIP_INFO_ID((int)item.spite);
			}
		}

		LOG(WARNING) << "POI: F";

		return false;
	}

	inline bool get_objective_location(Vector3& location)
	{
		const std::vector<blip_search> blip_search_arr = {
			{ BlipIcons::LEVEL, { BlipColors::YELLOW_MISSION, BlipColors::YELLOW_MISSION_2, BlipColors::YELLOW_MISSION_3, BlipColors::GREEN, BlipColors::BLUE } },
			{ BlipIcons::RACEFLAG, { } },
			{ BlipIcons::RACE, { } },
			{ BlipIcons::CRATEDROP, { } },
			{ BlipIcons::COP_PLAYER, { BlipColors::YELLOW_MISSION } },
			{ BlipIcons::GANG_COPS, { BlipColors::YELLOW_MISSION } },
			{ BlipIcons::GANG_MEXICANS, { BlipColors::YELLOW_MISSION } },
			{ BlipIcons::GANG_BIKERS, { BlipColors::YELLOW_MISSION } },
			{ BlipIcons::OBJECTIVE_BLUE, { BlipColors::YELLOW_MISSION } },
			{ BlipIcons::OBJECTIVE_GREEN, { BlipColors::YELLOW_MISSION } },
			{ BlipIcons::OBJECTIVE_RED, { BlipColors::YELLOW_MISSION } },
			{ BlipIcons::OBJECTIVE_YELLOW, { BlipColors::YELLOW_MISSION } },
			{ BlipIcons::ONMISSION_COPS, { BlipColors::YELLOW_MISSION } },
			{ BlipIcons::ONMISSION_LOST, { BlipColors::YELLOW_MISSION } },
			{ BlipIcons::ONMISSION_VAGOS, { BlipColors::YELLOW_MISSION } },
			{ BlipIcons::TF_CHECKPOINT, {  } },
			{ BlipIcons::AP, { BlipColors::YELLOW_MISSION } },

			{ BlipIcons::CRIM_CUFF_KEYS, {  } },
			{ BlipIcons::CAMERA, {  } },
			{ BlipIcons::HANDCUFF_KEYS_BIKERS, {  } },
			{ BlipIcons::PLAYERSTATE_KEYHOLDER, {  } },
			{ BlipIcons::FRIEND, {  } },
			{ BlipIcons::GANG_ATTACK_PACKAGE, {  } },
			// { BlipIcons::CAPTURE_THE_FLAG, {  } },
			{ BlipIcons::TEMP_3, {  } },
			{ BlipIcons::TEMP_4, {  } },
			{ BlipIcons::TEMP_5, {  } },
			{ BlipIcons::TEMP_6, {  } },
			{ BlipIcons::DEAD_DROP, {  } },
			{ BlipIcons::ASSAULT_PACKAGE, {  } },
			{ BlipIcons::HUNT_THE_BOSS, {  } },
			{ BlipIcons::CONTRABAND, { BlipColors::GREEN, BlipColors::BLUE } },
			{ BlipIcons::PACKAGE, { BlipColors::GREEN, BlipColors::BLUE } },
			{ BlipIcons::DRUGS_PACKAGE, { BlipColors::GREEN, BlipColors::BLUE } },
			{ BlipIcons::SUPPLIES, { BlipColors::GREEN, BlipColors::BLUE_PICKUP } },
			{ BlipIcons::SM_CARGO, { BlipColors::GREEN, BlipColors::BLUE } },
			{ BlipIcons::TF_CHECKPOINT, {  } },
			{ BlipIcons::CAMERA_2, {  } }, 
			{ BlipIcons::NHP_BAG, { BlipColors::GREEN, BlipColors::BLUE } },
			{ BlipIcons::KEYCARD, {  } },
			{ BlipIcons::ISLAND_HEIST_PREP, {  } },
			{ BlipIcons::CAR_ROBBERY_PREP, {  } },
			{ BlipIcons::SECURITY_CONTRACT, {  } },
			{ BlipIcons::SAFE, {  } },
			{ BlipIcons::EXPLOSIVE_CHARGE, {  } },
		};

		return get_blip_location(blip_search_arr, location);
	}

	inline BlipColors update_property_list(BlipColors last_player_color, std::map<std::string, Vector3>& list)
	{
		BlipColors player_color = BlipColors::WHITE_PLAYER;

		if (!self::ped)
		{
			list.clear();
			return BlipColors::WHITE_0;
		}

		auto player_ped_type = PED::GET_PED_TYPE(self::ped);

		if (player_ped_type == ePedType::PED_TYPE_PLAYER_0)
		{
			player_color = BlipColors::MICHAEL;
		}
		else if (player_ped_type == ePedType::PED_TYPE_PLAYER_1)
		{
			player_color = BlipColors::FRANKLIN;
		}
		else if (player_ped_type == ePedType::PED_TYPE_PLAYER_2)
		{
			player_color = BlipColors::TREVOR;
		}
		else if (*g_pointers->m_is_session_started)
		{
			Blip player_blip = HUD::GET_MAIN_PLAYER_BLIP_ID();
			player_color = (BlipColors)HUD::GET_BLIP_COLOUR(player_blip);
		}

		if (last_player_color != player_color)
		{
			list.clear();
		}

		const std::map<BlipIcons, std::string> property_items = {
			{ BlipIcons::SAFEHOUSE, "Safe House" },
			{ BlipIcons::DOCK, "Dock" },
			{ BlipIcons::GARAGE, "Garage" },
			{ BlipIcons::HANGAR, "Hangar" },
			{ BlipIcons::HELIPAD, "Helipad" },
			{ BlipIcons::BUSINESS, "Business" },
			{ BlipIcons::WAREHOUSE, "Warehouse" },
			{ BlipIcons::WAREHOUSE_VEHICLE, "Vehicle Warehouse" },
		};

		const std::map<BlipIcons, std::string> singleton_items = {
			{ BlipIcons::BIKER_CLUBHOUSE, "Clubhouse" },
			{ BlipIcons::YACHT, "Yacht" },
			{ BlipIcons::OFFICE, "Office" },
			{ BlipIcons::PRODUCTION_WEED, "Weed Farm" },
			{ BlipIcons::PRODUCTION_CRACK, "Cocaine Factory" },
			{ BlipIcons::PRODUCTION_FAKE_ID, "Document Forgery Office" },
			{ BlipIcons::PRODUCTION_METH, "Meth Lab" },
			{ BlipIcons::PRODUCTION_MONEY, "Counterfeit Cash Factory" },
			{ BlipIcons::PROPERTY_BUNKER, "Bunker" },
			{ BlipIcons::SM_HANGAR, "Hangar" },
			{ BlipIcons::NHP_BASE, "Facility" },
			{ BlipIcons::BAT_CLUB_PROPERTY, "Nightclub" },
			{ BlipIcons::ARENA_WORKSHOP, "Arena Workshop" },
			{ BlipIcons::ARCADE, "Arcade" },
			{ BlipIcons::SUB2, "Kosatka" },
			{ BlipIcons::AUTO_SHOP_PROPERTY, "Auto Shop" },
			{ BlipIcons::AGENCY, "Agency" },
		};

		const std::map<BlipIcons, blip_hardcoded> hardcoded_items = {
			{ BlipIcons::CASINO, { "Casino", { 924.25f, 46.75f, 79.8f } } },
			{ BlipIcons::CAR_MEET, { "LS Car Meet", { 780.44f, -1867.65f, 27.99f } } },
		};


		for (auto& [sprite, name] : property_items)
		{
			Blip blip = HUD::GET_FIRST_BLIP_INFO_ID((int)sprite);

			while (HUD::DOES_BLIP_EXIST(blip))
			{
				auto sprite = HUD::GET_BLIP_SPRITE(blip);
				BlipColors color_idx = (BlipColors)HUD::GET_BLIP_COLOUR(blip);

				if (
					color_idx == player_color || 
					color_idx == BlipColors::WHITE_0 || 
					color_idx == BlipColors::GREEN || 
					color_idx == BlipColors::WHITE_PLAYER
				) {
					Vector3 location = HUD::GET_BLIP_COORDS(blip);

					Hash street_hash;
					Hash street_crossing_hash;
					PATHFIND::GET_STREET_NAME_AT_COORD(location.x, location.y, location.z, &street_hash, &street_crossing_hash);

					const char* street_name = HUD::GET_STREET_NAME_FROM_HASH_KEY(street_hash);

					list[name + " (" + street_name + ")"] = location;
				}

				blip = HUD::GET_NEXT_BLIP_INFO_ID((int)sprite);
			}
		}

		for (auto& [sprite, name] : singleton_items)
		{
			Blip blip = HUD::GET_FIRST_BLIP_INFO_ID((int)sprite);

			while (HUD::DOES_BLIP_EXIST(blip))
			{
				auto sprite = HUD::GET_BLIP_SPRITE(blip);
				BlipColors color_idx = (BlipColors)HUD::GET_BLIP_COLOUR(blip);

				if (
					color_idx == player_color ||
					color_idx == BlipColors::WHITE_0 ||
					color_idx == BlipColors::GREEN ||
					color_idx == BlipColors::WHITE_PLAYER
				) {
					Vector3 location = HUD::GET_BLIP_COORDS(blip);
					list[name] = location;
				}

				blip = HUD::GET_NEXT_BLIP_INFO_ID((int)sprite);
			}
		}

		for (auto& [sprite, item] : hardcoded_items)
		{
			Blip blip = HUD::GET_FIRST_BLIP_INFO_ID((int)sprite);

			while (HUD::DOES_BLIP_EXIST(blip))
			{
				list[item.name] = item.location;
				break;
			}
		}

		return player_color;
	}
}
