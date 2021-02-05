#include "teleport.hpp"
#include "functions.hpp"
#include "natives.hpp"
#include "notify.hpp"
#include "script.hpp"

namespace big
{
	bool teleport::load_ground_at_3dcoord(Vector3& location)
	{
		float groundZ;
		uint8_t attempts = 10;

		for (uint8_t i = 0; i < attempts; i++)
		{
			// Only request a collision after the first try failed because the location might already be loaded on first attempt.
			for (uint16_t z = 0; i && z < 1000; z += 100)
			{
				STREAMING::REQUEST_COLLISION_AT_COORD(location.x, location.y, (float)z);

				script::get_current()->yield();
			}

			if (MISC::GET_GROUND_Z_FOR_3D_COORD(location.x, location.y, 1000.f, &groundZ, false, false))
			{
				location.z = groundZ + 1.f;

				return true;
			}

			script::get_current()->yield();
		}

		location.z = 1000.f;

		return false;
	}

	bool teleport::bring_blip(int blipSprite, int blipColor, int flag)
	{
		Blip blip;
		for (blip = HUD::GET_FIRST_BLIP_INFO_ID(blipSprite);
			HUD::DOES_BLIP_EXIST(blip) &&
			blipColor != -1 && HUD::GET_BLIP_COLOUR(blip);
			blip = HUD::GET_NEXT_BLIP_INFO_ID(blipSprite)
		) script::get_current()->yield();
		if (!HUD::DOES_BLIP_EXIST(blip) || (blipColor != -1 && HUD::GET_BLIP_COLOUR(blip) != blipColor)) return false;

		Vector3 location = HUD::GET_BLIP_COORDS(blip);

		Entity veh = VEHICLE::GET_CLOSEST_VEHICLE(location.x, location.y, location.z, 5.f, 0, flag);

		if (!ENTITY::DOES_ENTITY_EXIST(veh)) return false;

		func::take_control_of_entity(veh);

		Ped player = PLAYER::PLAYER_PED_ID();
		location = ENTITY::GET_ENTITY_COORDS(player, true);

		ENTITY::SET_ENTITY_COORDS(veh, location.x, location.y, location.z + 1.f, 0, 0, 0, true);

		if (!VEHICLE::ARE_ANY_VEHICLE_SEATS_FREE(veh))
		{
			notify::above_map("The vehicle is full.");
			ENTITY::SET_ENTITY_COORDS(player, location.x, location.y, location.z + 3.f, 0, 0, 0, true);
		}
		else
		{
			int seatIndex = VEHICLE::IS_VEHICLE_SEAT_FREE(veh, -1, false) ? -1 : -2;
			PED::SET_PED_INTO_VEHICLE(player, veh, seatIndex);
		}

		return true;
	}

	bool teleport::teleport_to_blip(int blipSprite, int blipColor)
	{
		Ped player = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player.id);

		Blip blip;
		for (blip = HUD::GET_FIRST_BLIP_INFO_ID(blipSprite);
			HUD::DOES_BLIP_EXIST(blip) &&
			blipColor != -1 && HUD::GET_BLIP_COLOUR(blip);
			blip = HUD::GET_NEXT_BLIP_INFO_ID(blipSprite)
			) script::get_current()->yield();
		if (!HUD::DOES_BLIP_EXIST(blip) || (blipColor != -1 && HUD::GET_BLIP_COLOUR(blip) != blipColor)) return false;

		Vector3 location = HUD::GET_BLIP_COORDS(blip);
		load_ground_at_3dcoord(location);

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
		
		load_ground_at_3dcoord(location);

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

		int seatIndex = VEHICLE::IS_VEHICLE_SEAT_FREE(veh, -1, false) ? -1 : -2;

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
		load_ground_at_3dcoord(location);

		PED::SET_PED_COORDS_KEEP_VEHICLE(player, location.x, location.y, location.z);

		return true;
	}
}