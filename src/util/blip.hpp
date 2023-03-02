#pragma once
#include "gta/enums.hpp"
#include "natives.hpp"
#include "script.hpp"

namespace big::blip
{
	inline bool get_blip_location(Vector3& location, int sprite, int color = -1)
	{
		Blip blip;
		for (blip = HUD::GET_FIRST_BLIP_INFO_ID(sprite); HUD::DOES_BLIP_EXIST(blip) && color != -1 && HUD::GET_BLIP_COLOUR(blip) != color; blip = HUD::GET_NEXT_BLIP_INFO_ID(sprite))
			;

		if (!HUD::DOES_BLIP_EXIST(blip) || (color != -1 && HUD::GET_BLIP_COLOUR(blip) != color))
			return false;

		location = HUD::GET_BLIP_COORDS(blip);

		return true;
	}

	inline bool get_objective_location(Vector3& location)
	{
		if (get_blip_location(location, (int)BlipIcons::Circle, (int)BlipColors::YellowMission))
			return true;
		if (get_blip_location(location, (int)BlipIcons::Circle, (int)BlipColors::YellowMission2))
			return true;
		if (get_blip_location(location, (int)BlipIcons::Circle, (int)BlipColors::Mission))
			return true;
		if (get_blip_location(location, (int)BlipIcons::RaceFinish, (int)BlipColors::None))
			return true;
		if (get_blip_location(location, (int)BlipIcons::Circle, (int)BlipColors::Green))
			return true;
		if (get_blip_location(location, (int)BlipIcons::Circle, (int)BlipColors::Blue))
			return true;
		if (get_blip_location(location, (int)BlipIcons::CrateDrop))
			return true;

		static const int blips[] = {1, 57, 128, 129, 130, 143, 144, 145, 146, 271, 286, 287, 288};
		for (const auto& blip : blips)
		{
			if (get_blip_location(location, blip, 5))
				return true;
		}

		return false;
	}
}