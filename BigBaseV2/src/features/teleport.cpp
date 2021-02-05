#include "teleport.hpp"
#include "natives.hpp"
#include "notify.hpp"
#include "script.hpp"

namespace big
{
	bool teleport::load_ground_at_3dcoord(Vector3 location)
	{
		float groundZ;
		uint8_t attempts = 10;
		for (uint8_t i = 0; i < attempts; i++)
		{
			// Only request a collision after the first try failed because the location might already be loaded on first attempt.
			for (uint8_t z = 0; i && z < 1000; z += 100)
			{
				STREAMING::REQUEST_COLLISION_AT_COORD(location.x, location.y, z);

				script::get_current()->yield();
			}

			if (MISC::GET_GROUND_Z_FOR_3D_COORD(location.x, location.y, 1000.f, &groundZ, false, false))
				return true;

			script::get_current()->yield();
		}

		return false;
	}

	Vector3 teleport::get_ground_at_3dcoord(Vector3 location)
	{
		float groundZ;
		uint8_t attempts = 10;
		for (uint8_t i = 0; i < attempts; i++)
		{
			// Only request a collision after the first try failed because the location might already be loaded on first attempt.
			for (uint8_t z = 0; i && z < 1000; z += 100)
			{
				STREAMING::REQUEST_COLLISION_AT_COORD(location.x, location.y, (float)z);

				script::get_current()->yield();
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

	bool teleport::bring_blip(int blipSprite, int blipColor, int flag)
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

		Ped player = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player.id);
		location = ENTITY::GET_ENTITY_COORDS(player, true);

		ENTITY::SET_ENTITY_COORDS(veh, location.x, location.y, location.z + 1.f, 0, 0, 0, true);

		if (!VEHICLE::ARE_ANY_VEHICLE_SEATS_FREE(veh))
		{
			notify::above_map("The vehicle is full.");
			ENTITY::SET_ENTITY_COORDS(player, location.x, location.y, location.z + 3.f, 0, 0, 0, true);
		}
		else
		{
			PED::SET_PED_INTO_VEHICLE(player, veh, -2);
		}

		return true;
	}

	bool teleport::teleport_to_blip(int blipSprite, int blipColor)
	{
		Ped player = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player.id);

		Blip blipHandle = HUD::GET_FIRST_BLIP_INFO_ID(blipSprite);
		while (HUD::DOES_BLIP_EXIST(blipHandle) && (blipColor != -1 && HUD::GET_BLIP_COLOUR(blipHandle) != blipColor))
		{
			blipHandle = HUD::GET_NEXT_BLIP_INFO_ID(blipSprite);

			script::get_current()->yield();
		}
		if (!HUD::DOES_BLIP_EXIST(blipHandle) || (blipColor != -1 && HUD::GET_BLIP_COLOUR(blipHandle) != blipColor)) return false;

		Vector3 location = HUD::GET_BLIP_COORDS(blipHandle);
		location = get_ground_at_3dcoord(location);

		PED::SET_PED_COORDS_KEEP_VEHICLE(player, location.x, location.y, location.z);

		return true;
	}

	void teleport::teleport_into_player_vehicle(Player player)
	{
		Ped target = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);

		if (!PED::IS_PED_IN_ANY_VEHICLE(target, true))
		{
			notify::above_map("This player is not in a vehicle right now.");

			return;
		}

		Vector3 location = ENTITY::GET_ENTITY_COORDS(target, true);
		
		for (uint8_t i = 0; !load_ground_at_3dcoord(location); i++)
			if (i == 5) break;

		Ped current = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player.id);

		Vehicle veh;
		for (veh = 0; !veh; veh = PED::GET_VEHICLE_PED_IS_IN(target, false))
		{
			if (!PED::IS_PED_IN_ANY_VEHICLE(target, true))
			{
				notify::above_map("Player is no longer in a vehicle.");

				return;
			}

			veh = PED::GET_VEHICLE_PED_IS_IN(target, false);

			if (!veh)
			{
				ENTITY::SET_ENTITY_COORDS(current, location.x, location.y, 1000.f, 0, 0, 0, 0);

				script::get_current()->yield(50ms);
			}
		}

		int seatIndex = -2;
		if (VEHICLE::IS_VEHICLE_SEAT_FREE(veh, -1, 0)) seatIndex = -1;

		PED::SET_PED_INTO_VEHICLE(current, veh, seatIndex);
	}

	void teleport::teleport_to_player(Player player)
	{
		Ped target = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);

		Vector3 location = ENTITY::GET_ENTITY_COORDS(target, true);
		load_ground_at_3dcoord(location);

		PED::SET_PED_COORDS_KEEP_VEHICLE(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player.id), location.x, location.y, location.z);
	}

	// Teleport the player (with/without car to a waypoint)
	bool teleport::waypoint()
	{
		Ped player = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player.id);

		Blip blipHandle = HUD::GET_FIRST_BLIP_INFO_ID(8);
		if (!HUD::DOES_BLIP_EXIST(blipHandle)) return false;

		Vector3 location = HUD::GET_BLIP_COORDS(blipHandle);

		location = get_ground_at_3dcoord(location);

		PED::SET_PED_COORDS_KEEP_VEHICLE(player, location.x, location.y, location.z);

		return true;
	}
}