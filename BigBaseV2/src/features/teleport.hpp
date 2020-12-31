#pragma once
#include "features.hpp"
#include "natives.hpp"
#include "script.hpp"

namespace big::features::teleport
{
	bool bring_blip(int blipSprite, int blipColor, int flag = 70);
	bool load_ground_at_3dcoord(Vector3 location);
	Vector3 get_ground_at_3dcoord(Vector3 location);
	bool teleport_to_blip(int blipSprite, int blipColor = -1);
	void teleport_into_player_vehicle(Player player);
	void teleport_to_player(Player player);
	bool waypoint();
}