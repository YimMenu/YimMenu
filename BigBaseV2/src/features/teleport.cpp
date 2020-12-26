#include "teleport.hpp"

namespace big::features::teleport
{
	Vector3 get_ground_at_3d_coord(Vector3 location)
	{
		float groundZ;
		uint16_t attempts = 10;
		for (uint16_t i = 0; i < attempts; i++)
		{
			// Only request a collision after the first try failed because the location might already be loaded on first attempt.
			if (i)
			{
				for (uint16_t z = 0; z < 1000; z += 100)
				{
					STREAMING::REQUEST_COLLISION_AT_COORD(location.x, location.y, z);

					script::get_current()->yield();
				}
			}

			if (MISC::GET_GROUND_Z_FOR_3D_COORD(location.x, location.y, 1000.f, &groundZ, false, false))
			{
				location.z = groundZ + 1.f;

				break;
			}

			if (i == attempts - 1) location.z = 1000.f;

			script::get_current()->yield();
		}

		return location;
	}

	// Teleport the player (with/without car to a waypoint)
	bool waypoint()
	{
		Ped player = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_playerId);

		Blip blipHandle = HUD::GET_FIRST_BLIP_INFO_ID(8);
		if (!HUD::DOES_BLIP_EXIST(blipHandle)) return false;

		Vector3 location = HUD::GET_BLIP_COORDS(blipHandle);
		
		location = get_ground_at_3d_coord(location);

		PED::SET_PED_COORDS_KEEP_VEHICLE(player, location.x, location.y, location.z);

		return true;
	}

	bool bring_blip(int blipSprite, int blipColor, int flag)
	{
		Blip blipHandle = HUD::GET_FIRST_BLIP_INFO_ID(blipSprite);
		while (HUD::DOES_BLIP_EXIST(blipHandle) && (blipColor != -1 && HUD::GET_BLIP_COLOUR(blipHandle) != blipColor))
		{
			blipHandle = HUD::GET_NEXT_BLIP_INFO_ID(blipSprite);

			script::get_current()->yield();
		}
		if (!HUD::DOES_BLIP_EXIST(blipHandle) || (blipColor != -1 && HUD::GET_BLIP_COLOUR(blipHandle) != blipColor)) return false;

		Vector3 location = HUD::GET_BLIP_COORDS(blipHandle);

		Entity veh = VEHICLE::GET_CLOSEST_VEHICLE(location.x, location.y, location.z, 5.f, 0, flag);

		if (!ENTITY::DOES_ENTITY_EXIST(veh)) return false;

		while (!NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(veh))
		{
			NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(veh);

			script::get_current()->yield();
		}

		Ped player = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_playerId);
		location = ENTITY::GET_ENTITY_COORDS(player, true);

		ENTITY::SET_ENTITY_COORDS(veh, location.x, location.y, location.z + 1.f, 0, 0, 0, true);

		if (!VEHICLE::ARE_ANY_VEHICLE_SEATS_FREE(veh))
		{
			features::notify::above_map("The vehicle is full.");
			ENTITY::SET_ENTITY_COORDS(player, location.x, location.y, location.z + 3.f, 0, 0, 0, true);
		}
		else
		{
			PED::SET_PED_INTO_VEHICLE(player, veh, -2);
		}

		return true;
	}

	bool teleport_to_blip(int blipSprite, int blipColor)
	{
		Ped player = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_playerId);

		Blip blipHandle = HUD::GET_FIRST_BLIP_INFO_ID(blipSprite);
		while (HUD::DOES_BLIP_EXIST(blipHandle) && (blipColor != -1 && HUD::GET_BLIP_COLOUR(blipHandle) != blipColor))
		{
			blipHandle = HUD::GET_NEXT_BLIP_INFO_ID(blipSprite);

			script::get_current()->yield();
		}
		if (!HUD::DOES_BLIP_EXIST(blipHandle) || (blipColor != -1 && HUD::GET_BLIP_COLOUR(blipHandle) != blipColor)) return false;

		Vector3 location = HUD::GET_BLIP_COORDS(blipHandle);
		float groundZ;

		UINT16 attempts = 10;
		for (UINT16 i = 0; i < attempts; i++)
		{
			// Only request a collision after the first try failed because the location might already be loaded on first attempt.
			if (i)
			{
				for (UINT16 z = 0; z < 1000; z += 100)
				{
					STREAMING::REQUEST_COLLISION_AT_COORD(location.x, location.y, z);

					script::get_current()->yield();
				}
			}

			if (MISC::GET_GROUND_Z_FOR_3D_COORD(location.x, location.y, 1000.f, &groundZ, false, false))
			{
				location.z = groundZ + 1.f;

				break;
			}

			if (i == attempts - 1) location.z = 1000.f;

			script::get_current()->yield();
		}

		PED::SET_PED_COORDS_KEEP_VEHICLE(player, location.x, location.y, location.z);

		return true;
	}
}