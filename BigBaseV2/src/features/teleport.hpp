#pragma once
#include "common.hpp"

namespace big
{
	class teleport
	{
	public:
		static bool bring_blip(int blipSprite, int blipColor, int flag = 70);
		static bool load_ground_at_3dcoord(Vector3 location);
		static Vector3 get_ground_at_3dcoord(Vector3 location);
		static bool teleport_to_blip(int blipSprite, int blipColor = -1);
		static void teleport_into_player_vehicle(Player player);
		static void teleport_to_player(Player player);
		static bool waypoint();

	private:

	};
}