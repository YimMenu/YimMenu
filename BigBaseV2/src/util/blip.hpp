#pragma once
#include "natives.hpp"
#include "script.hpp"
#include "gta/enums.hpp"

namespace big::blip
{
	struct blip_search {
		BlipIcons spite;
		std::vector<BlipColors> colors;
	};

	inline bool get_blip_location(std::vector<blip_search>& blip_search_arr, Vector3& location)
	{
		for (auto& item : blip_search_arr)
		{
			Blip blip = HUD::GET_FIRST_BLIP_INFO_ID((int)item.spite);

			while (HUD::DOES_BLIP_EXIST(blip))
			{
				LOG(WARNING) << "POI: " << (int)item.spite;

				if (item.colors.size() == 0)
				{
					location = HUD::GET_BLIP_COORDS(blip);

					BlipColors color_idx = (BlipColors)HUD::GET_BLIP_COLOUR(blip);
					LOG(WARNING) << "POI: 0T " << (int)color_idx;

					return true;
				}
				else
				{
					BlipColors color_idx = (BlipColors)HUD::GET_BLIP_COLOUR(blip);

					if (std::find(item.colors.begin(), item.colors.end(), color_idx) != item.colors.end())
					{
						location = HUD::GET_BLIP_COORDS(blip);

						LOG(WARNING) << "POI: T " << (int)color_idx;

						return true;
					}
				}

				blip = HUD::GET_NEXT_BLIP_INFO_ID((int)item.spite);
			}
		}

		LOG(WARNING) << "POI: F";

		return false;
	}

	inline bool get_objective_location(Vector3& location)
	{
		std::vector<blip_search> blip_search_arr = {
			{ BlipIcons::LEVEL, { BlipColors::YellowMission, BlipColors::YellowMission2, BlipColors::Mission, BlipColors::Green, BlipColors::Blue } },
			{ BlipIcons::RACEFLAG, { } },
			{ BlipIcons::RACE, { } },
			{ BlipIcons::CRATEDROP, { } },
			{ BlipIcons::COP_PLAYER, { BlipColors::YellowMission } },
			{ BlipIcons::GANG_COPS, { BlipColors::YellowMission } },
			{ BlipIcons::GANG_MEXICANS, { BlipColors::YellowMission } },
			{ BlipIcons::GANG_BIKERS, { BlipColors::YellowMission } },
			{ BlipIcons::OBJECTIVE_BLUE, { BlipColors::YellowMission } },
			{ BlipIcons::OBJECTIVE_GREEN, { BlipColors::YellowMission } },
			{ BlipIcons::OBJECTIVE_RED, { BlipColors::YellowMission } },
			{ BlipIcons::OBJECTIVE_YELLOW, { BlipColors::YellowMission } },
			{ BlipIcons::ONMISSION_COPS, { BlipColors::YellowMission } },
			{ BlipIcons::ONMISSION_LOST, { BlipColors::YellowMission } },
			{ BlipIcons::ONMISSION_VAGOS, { BlipColors::YellowMission } },
			{ BlipIcons::TF_CHECKPOINT, {  } },
			{ BlipIcons::AP, { BlipColors::YellowMission } },

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
			{ BlipIcons::CONTRABAND, { BlipColors::Green, BlipColors::Blue } },
			{ BlipIcons::PACKAGE, { BlipColors::Green, BlipColors::Blue } },
			{ BlipIcons::DRUGS_PACKAGE, { BlipColors::Green, BlipColors::Blue } },
			{ BlipIcons::SM_CARGO, { BlipColors::Green, BlipColors::Blue } },
			{ BlipIcons::TF_CHECKPOINT, {  } },
			{ BlipIcons::CAMERA_2, {  } }, 
			{ BlipIcons::NHP_BAG, { BlipColors::Green, BlipColors::Blue } },
			{ BlipIcons::KEYCARD, {  } },
			{ BlipIcons::ISLAND_HEIST_PREP, {  } },
			{ BlipIcons::CAR_ROBBERY_PREP, {  } },
			{ BlipIcons::SECURITY_CONTRACT, {  } },
			{ BlipIcons::EXPLOSIVE_CHARGE, {  } },
		};

		return get_blip_location(blip_search_arr, location);
	}
}