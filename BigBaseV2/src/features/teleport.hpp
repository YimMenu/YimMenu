#pragma once
#include "features.hpp"
#include "natives.hpp"
#include "script.hpp"

namespace big::features::teleport
{
	bool bring_blip(int blipSprite, int blipColor, int flag = 70);
	bool teleport_to_blip(int blipSprite, int blipColor = -1);
	bool waypoint();
}