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

	inline bool get_blip_location(const std::vector<blip_search>& blip_search_arr, Vector3& location)
	{
		for (auto& item : blip_search_arr)
		{
			Blip blip = HUD::GET_FIRST_BLIP_INFO_ID((int)item.sprite);

			while (HUD::DOES_BLIP_EXIST(blip))
			{
				if (item.colors.size() == 0)
				{
					location = HUD::GET_BLIP_COORDS(blip);
					location.z += 1.5f;

					BlipColors color_idx = (BlipColors)HUD::GET_BLIP_COLOUR(blip);

					LOG(WARNING) << (int)item.sprite << " " << (int)color_idx;

					return true;
				}
				else
				{
					BlipColors color_idx = (BlipColors)HUD::GET_BLIP_COLOUR(blip);

					if (std::find(item.colors.begin(), item.colors.end(), color_idx) != item.colors.end())
					{
						location = HUD::GET_BLIP_COORDS(blip);
						location.z += 1.5f;
						return true;
					}

					LOG(WARNING) << (int)item.sprite << " " << (int)color_idx;
				}

				blip = HUD::GET_NEXT_BLIP_INFO_ID((int)item.sprite);
			}
		}

		for (int i = 823; i < 900; i++)
		{
			Blip blip = HUD::GET_FIRST_BLIP_INFO_ID(i);

			while (HUD::DOES_BLIP_EXIST(blip))
			{
				BlipColors color_idx = (BlipColors)HUD::GET_BLIP_COLOUR(blip);

				LOG(WARNING) << i << " " << (int)color_idx;

				blip = HUD::GET_NEXT_BLIP_INFO_ID(i);
			}
		}

		return false;
	}

	inline bool get_objective_location(Vector3& location)
	{
		const std::vector<blip_search> blip_search_arr = {
			{ BlipIcons::LEVEL, { BlipColors::YELLOW_MISSION, BlipColors::YELLOW_MISSION_2, BlipColors::YELLOW_MISSION_3, BlipColors::GREEN, BlipColors::BLUE, BlipColors::BLUE_PICKUP } },
			{ BlipIcons::RACEFLAG, { } },
			{ BlipIcons::RACE, { } },
			{ BlipIcons::CRATEDROP, { } },
			{ BlipIcons::COP_PLAYER, { BlipColors::YELLOW_MISSION } },
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
			{ BlipIcons::TF_CHECKPOINT, {  } },
			{ BlipIcons::AP, { BlipColors::YELLOW_MISSION } },

			{ BlipIcons::CRIM_CUFF_KEYS, {  } },
			{ BlipIcons::CAMERA, {  } },
			{ BlipIcons::HANDCUFF_KEYS_BIKERS, {  } },
			{ BlipIcons::GANG_VEHICLE, { BlipColors::BLUE, BlipColors::BLUE_PICKUP } },
			{ BlipIcons::PLAYERSTATE_KEYHOLDER, {  } },
			{ BlipIcons::FRIEND, { BlipColors::BLUE, BlipColors::BLUE_PICKUP } },
			{ BlipIcons::PLANE_DROP, { BlipColors::BLUE, BlipColors::BLUE_PICKUP } },
			{ BlipIcons::GETAWAY_CAR, { BlipColors::BLUE, BlipColors::BLUE_PICKUP } },
			{ BlipIcons::GANG_ATTACK_PACKAGE, {  } },
			{ BlipIcons::GANG_ATTACK_PACKAGE, {  } },
			// { BlipIcons::CAPTURE_THE_FLAG, {  } },
			{ BlipIcons::TEMP_3, {  } },
			{ BlipIcons::TEMP_4, {  } },
			{ BlipIcons::TEMP_5, {  } },
			{ BlipIcons::TEMP_6, {  } },
			{ BlipIcons::DEAD_DROP, {  } },
			{ BlipIcons::ASSAULT_PACKAGE, {  } },
			{ BlipIcons::HUNT_THE_BOSS, {  } },
			{ BlipIcons::BELLY_OF_THE_BEAST, { BlipColors::BLUE, BlipColors::BLUE_PICKUP } },
			{ BlipIcons::CONTRABAND, { BlipColors::GREEN, BlipColors::BLUE, BlipColors::BLUE_PICKUP } },
			{ BlipIcons::PACKAGE, { BlipColors::GREEN, BlipColors::BLUE, BlipColors::BLUE_PICKUP } },
			{ BlipIcons::DRUGS_PACKAGE, { BlipColors::GREEN,BlipColors::BLUE, BlipColors::BLUE_PICKUP } },
			{ BlipIcons::REG_PAPERS, { BlipColors::GREEN,BlipColors::BLUE, BlipColors::BLUE_PICKUP } },
			{ BlipIcons::SUPPLIES, { BlipColors::GREEN, BlipColors::BLUE, BlipColors::BLUE_PICKUP } },
			{ BlipIcons::SM_CARGO, { BlipColors::GREEN, BlipColors::BLUE, BlipColors::BLUE_PICKUP } },
			{ BlipIcons::TF_CHECKPOINT, {  } },
			{ BlipIcons::CAMERA_2, {  } }, 
			{ BlipIcons::NHP_BAG, { BlipColors::GREEN, BlipColors::BLUE, BlipColors::BLUE_PICKUP } },
			{ BlipIcons::KEYCARD, {  } },
			{ BlipIcons::ISLAND_HEIST_PREP, {  } },
			{ BlipIcons::CAR_ROBBERY_PREP, {  } },
			{ BlipIcons::SECURITY_CONTRACT, {  } },
			{ BlipIcons::SAFE, {  } },
			{ BlipIcons::EXPLOSIVE_CHARGE, {  } },
			{ BlipIcons::MC_BAR_SUPPLIES, { BlipColors::BLUE_PICKUP } }
		};

		return get_blip_location(blip_search_arr, location);
	}
}
