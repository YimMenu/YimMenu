#pragma once
#include "natives.hpp"
#include "script.hpp"

namespace big::blip
{
	inline bool get_blip_location(Vector3 &location, int sprite, int color = -1)
	{
		Blip blip;
		for (blip = HUD::GET_FIRST_BLIP_INFO_ID(sprite);
			HUD::DOES_BLIP_EXIST(blip) &&
			color != -1 && HUD::GET_BLIP_COLOUR(blip) != color;
			blip = HUD::GET_NEXT_BLIP_INFO_ID(sprite)
			) script::get_current()->yield();

		if (!HUD::DOES_BLIP_EXIST(blip) || (color != -1 && HUD::GET_BLIP_COLOUR(blip) != color)) return false;

		location = HUD::GET_BLIP_COORDS(blip);

		return true;
	}
}