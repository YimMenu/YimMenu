#pragma once
#include "natives.hpp"
#include "pointers.hpp"
#include "script.hpp"
#include "gta/enums.hpp"
#include "gta/joaat.hpp"


namespace big::blip
{
	struct blip_search {
		BlipIcons sprite;
		std::vector<BlipColors> colors;
	};

	inline bool get_blip_location(const std::map<BlipIcons, std::vector<BlipColors>>& blips_to_search, Vector3& location)
	{

		for (auto& [sprite, colors] : blips_to_search)
		{
			Blip blip = HUD::GET_FIRST_BLIP_INFO_ID((int)sprite);

			while (HUD::DOES_BLIP_EXIST(blip))
			{
				if (colors.size() == 0)
				{
					location = HUD::GET_BLIP_COORDS(blip);
					location.z += .2f;

					BlipColors color_idx = (BlipColors)HUD::GET_BLIP_COLOUR(blip);

					LOG(WARNING) << (int)sprite << " 1 " << (int)color_idx;

					return true;
				}
				else
				{
					BlipColors color_idx = (BlipColors)HUD::GET_BLIP_COLOUR(blip);

					LOG(WARNING) << (int)sprite << " " << (int)color_idx;

					if (std::find(colors.begin(), colors.end(), color_idx) != colors.end())
					{
						location = HUD::GET_BLIP_COORDS(blip);
						location.z += .2f;
						return true;
					}

				}

				blip = HUD::GET_NEXT_BLIP_INFO_ID((int)sprite);
			}
		}

		return false;
	}

	inline bool get_objective_location(Vector3& location)
	{
		const std::map<BlipIcons, std::vector<BlipColors>> primary_checkpoints = {
			// checkpoints
			{ BlipIcons::LEVEL, { BlipColors::YELLOW_MISSION, BlipColors::YELLOW_MISSION_2, BlipColors::YELLOW_MISSION_3 } },
			{ BlipIcons::COP_PLAYER, { BlipColors::YELLOW_MISSION } },
			{ BlipIcons::RANDOM_CHARACTER, { BlipColors::YELLOW_MISSION } },
			{ BlipIcons::GANG_COPS, { BlipColors::YELLOW_MISSION } },
			{ BlipIcons::GANG_MEXICANS, { BlipColors::YELLOW_MISSION } },
			{ BlipIcons::GANG_BIKERS, { BlipColors::YELLOW_MISSION } },
			{ BlipIcons::OBJECTIVE_GREEN, { BlipColors::YELLOW_MISSION } },
			{ BlipIcons::OBJECTIVE_RED, { BlipColors::YELLOW_MISSION } },
			{ BlipIcons::OBJECTIVE_YELLOW, { BlipColors::YELLOW_MISSION } },
			{ BlipIcons::OBJECTIVE_BLUE, { BlipColors::BLUE, BlipColors::YELLOW_MISSION } },
			{ BlipIcons::ONMISSION_COPS, { BlipColors::YELLOW_MISSION } },
			{ BlipIcons::ONMISSION_LOST, { BlipColors::YELLOW_MISSION } },
			{ BlipIcons::ONMISSION_VAGOS, { BlipColors::YELLOW_MISSION } },
			{ BlipIcons::CRATEDROP, { } },
			{ BlipIcons::RACEFLAG, { } },
			{ BlipIcons::RACE, { } },
			{ BlipIcons::TF_CHECKPOINT, {  } },
		};

		const std::map<BlipIcons, std::vector<BlipColors>> secondary_checkpoints = {
			{ BlipIcons::LEVEL, { BlipColors::GREEN, BlipColors::BLUE, BlipColors::BLUE_PICKUP } },
			{ BlipIcons::CRIM_CUFF_KEYS, {  } },
			{ BlipIcons::CAMERA, {  } },
			{ BlipIcons::HANDCUFF_KEYS_BIKERS, {  } },
			{ BlipIcons::PLAYERSTATE_KEYHOLDER, {  } },
			{ BlipIcons::GANG_ATTACK_PACKAGE, {  } },
			{ BlipIcons::TEMP_3, {  } },
			{ BlipIcons::TEMP_4, { BlipColors::RED_MISSION_2 } },
			{ BlipIcons::TEMP_5, {  } },
			{ BlipIcons::TEMP_6, {  } },
			{ BlipIcons::DEAD_DROP, {  } },
			{ BlipIcons::FINDERS_KEEPERS, { BlipColors::YELLOW_MISSION_2 } },
			{ BlipIcons::ASSAULT_PACKAGE, {  } },
			{ BlipIcons::HUNT_THE_BOSS, {  } },
			{ BlipIcons::CONTRABAND, { BlipColors::GREEN, BlipColors::BLUE, BlipColors::BLUE_PICKUP } },
			{ BlipIcons::PACKAGE, { BlipColors::GREEN, BlipColors::BLUE, BlipColors::BLUE_PICKUP } },
			{ BlipIcons::DRUGS_PACKAGE, {  } },
			{ BlipIcons::LAPTOP, { BlipColors::GREEN, BlipColors::YELLOW_MISSION, BlipColors::YELLOW_MISSION_2, BlipColors::YELLOW_MISSION_3 } },
			{ BlipIcons::REG_PAPERS, { BlipColors::GREEN,BlipColors::BLUE, BlipColors::BLUE_PICKUP } },
			{ BlipIcons::SUPPLIES, { BlipColors::GREEN, BlipColors::BLUE, BlipColors::BLUE_PICKUP } },
			{ BlipIcons::SM_CARGO, { BlipColors::GREEN, BlipColors::BLUE, BlipColors::BLUE_PICKUP } },
			{ BlipIcons::NHP_BAG, { BlipColors::GREEN, BlipColors::BLUE, BlipColors::BLUE_PICKUP } },
			{ BlipIcons::BAT_CARGO, { BlipColors::GREEN, BlipColors::BLUE, BlipColors::BLUE_PICKUP } },
			{ BlipIcons::BAT_KEYPAD, { BlipColors::GREEN, BlipColors::YELLOW_MISSION, BlipColors::YELLOW_MISSION_2, BlipColors::YELLOW_MISSION_3 } },
			{ BlipIcons::RUCKSACK, {  } },
			{ BlipIcons::SHIPPING_CONTAINER, { BlipColors::RED_MISSION_2 } },
			{ BlipIcons::CAMERA_2, {  } },
			{ BlipIcons::KEYCARD, {  } },
			{ BlipIcons::ISLAND_HEIST_PREP, {  } },
			{ BlipIcons::CAR_ROBBERY_PREP, {  } },
			{ BlipIcons::SECURITY_CONTRACT, {  } },
			{ BlipIcons::PASSWORD, { BlipColors::GREEN } },
			{ BlipIcons::SAFE, {  } },
			{ BlipIcons::EXPLOSIVE_CHARGE, {  } },
		};

		if (get_blip_location(primary_checkpoints, location))
		{
			return true;
		}

		if (get_blip_location(secondary_checkpoints, location))
		{
			return true;
		}

		for (int sprite = 0; sprite <= (int)BlipIcons::MC_BAR_SUPPLIES; sprite++)
		{
			if (
				primary_checkpoints.count((BlipIcons)sprite) || 
				secondary_checkpoints.count((BlipIcons)sprite)
			) {
				continue;
			}

			Blip blip = HUD::GET_FIRST_BLIP_INFO_ID(sprite);

			while (HUD::DOES_BLIP_EXIST(blip))
			{
				if (HUD::IS_BLIP_ON_MINIMAP(blip))
				{
					BlipColors color_idx = (BlipColors)HUD::GET_BLIP_COLOUR(blip);

					LOG(WARNING) << (int)sprite << " " << (int)color_idx;

					if (color_idx == BlipColors::BLUE || color_idx == BlipColors::BLUE_PICKUP)
					{
						location = HUD::GET_BLIP_COORDS(blip);
						location.z += .2f;
						return true;
					}
				}

				blip = HUD::GET_NEXT_BLIP_INFO_ID(sprite);
			}
		}

		return false;
	}
}
