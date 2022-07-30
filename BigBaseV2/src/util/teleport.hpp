#pragma once
#include "blip.hpp"
#include "entity.hpp"
#include "gta/enums.hpp"

namespace big::teleport
{
	inline bool bring_player(Player player)
	{
		Entity ent = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);

		if (ENTITY::IS_ENTITY_DEAD(ent, true))
		{
			g_notification_service->push_warning("Teleport", "Target player is dead.");

			return false;
		}

		if (!PED::IS_PED_IN_ANY_VEHICLE(ent, true))
		{
			g_notification_service->push_warning("Teleport", "Target player is not in a vehicle.");

			return false;
		}

		ent = PED::GET_VEHICLE_PED_IS_IN(ent, false);
		Vector3 location = self::pos;

		if (entity::take_control_of(ent))
			ENTITY::SET_ENTITY_COORDS(ent, location.x, location.y, location.z, 0, 0, 0, 0);
		else
			g_notification_service->push_warning("Teleport", "Failed to take control of player vehicle.");

		return true;
	}

	inline bool load_ground_at_3dcoord(Vector3& location)
	{
		float groundZ;
		const uint8_t attempts = 10;

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

	inline bool into_vehicle(Vehicle veh)
	{
		if (!ENTITY::IS_ENTITY_A_VEHICLE(veh))
		{
			g_notification_service->push_warning("Teleport", "Invalid vehicle handle");

			return false;
		}

		int seat_index = 255;
		if (VEHICLE::IS_VEHICLE_SEAT_FREE(veh, -1, true))
			seat_index = -1;
		else if (VEHICLE::IS_VEHICLE_SEAT_FREE(veh, -2, true))
			seat_index = -2;

		if (seat_index == 255)
		{
			g_notification_service->push_warning("Teleport", "No seats are free in the player vehicle.");

			return false;
		}

		Vector3 location = ENTITY::GET_ENTITY_COORDS(veh, true);
		load_ground_at_3dcoord(location);

		Ped ped = self::ped;

		ENTITY::SET_ENTITY_COORDS(ped, location.x, location.y, location.z, 0, 0, 0, 0);

		script::get_current()->yield();

		PED::SET_PED_INTO_VEHICLE(ped, veh, seat_index);

		return true;
	}

	inline void to_coords(Vector3 location)
	{
		PED::SET_PED_COORDS_KEEP_VEHICLE(self::ped, location.x, location.y, location.z + 1.f);
	}

	inline bool to_blip(int sprite, int color = -1)
	{
		Vector3 location;

		if (!blip::get_blip_location(location, sprite, color))
			return false;

		if (sprite == (int)BlipIcons::Waypoint)
			load_ground_at_3dcoord(location);

		PED::SET_PED_COORDS_KEEP_VEHICLE(self::ped, location.x, location.y, location.z);

		return true;
	}

	inline bool to_entity(Entity ent)
	{
		Vector3 location = ENTITY::GET_ENTITY_COORDS(ent, true);

		PED::SET_PED_COORDS_KEEP_VEHICLE(self::ped, location.x, location.y, location.z);

		return true;
	}

	inline bool to_player(Player player)
	{
		return to_entity(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player));
	}

	inline bool to_waypoint()
	{
		if (!to_blip((int)BlipIcons::Waypoint))
		{
			g_notification_service->push_warning("Teleport", "Failed to find waypoint position");

			return false;
		}
		return true;
	}

	inline bool to_objective()
	{
		Vector3 location;

		if (!blip::get_objective_location(location))
		{
			g_notification_service->push_warning("Teleport", "Failed to find objective position");
			return false;
		}

		PED::SET_PED_COORDS_KEEP_VEHICLE(self::ped, location.x, location.y, location.z);

		return false;
	}

	inline void TPtoCoords(Entity e, Vector3 coords, bool AutoCorrectGroundHeight, bool IgnoreCurrentPedVehicle)  //G4E Function
	{
		Entity TargetEntity = e;

		if (ENTITY::IS_ENTITY_A_PED(TargetEntity))
		{
			if (PED::IS_PED_IN_ANY_VEHICLE(TargetEntity, false) && !IgnoreCurrentPedVehicle)
			{
				TargetEntity = PED::GET_VEHICLE_PED_IS_USING(TargetEntity);
			}
		}
		if (ENTITY::IS_AN_ENTITY(TargetEntity))
		{
			entity::take_control_of(TargetEntity);
		}

		if (!AutoCorrectGroundHeight)
		{
			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(TargetEntity, coords.x, coords.y, coords.z, false, false, true);
		}
		else							//NOT NEEDED BUT UwU
		{
			bool GroundFound = false;
			static std::array<float, 21> GroundCheckHeight = { 0.0, 50.0, 100.0, 150.0, 200.0, 250.0, 300.0, 350.0, 400.0, 450.0, 500.0, 550.0, 600.0, 650.0, 700.0, 750.0, 800.0, 850.0, 900.0, 950.0, 1000.00 };

			for (const float& CurrentHeight : GroundCheckHeight)
			{
				ENTITY::SET_ENTITY_COORDS_NO_OFFSET(TargetEntity, coords.x, coords.y, CurrentHeight, false, false, true);
				if (MISC::GET_GROUND_Z_FOR_3D_COORD(coords.x, coords.y, CurrentHeight, &coords.z, false, false))
				{
					GroundFound = true;
					coords.z += 3.0f;
					break;
				}
			}

			if (!GroundFound)
			{
				Vector3 ClosestRoadCoord;
				if (PATHFIND::GET_CLOSEST_ROAD(coords.x, coords.y, coords.z, 1.0f, 1,
					&ClosestRoadCoord, &ClosestRoadCoord, NULL, NULL, NULL, NULL))
				{
					coords = ClosestRoadCoord;
				}
			}
			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(TargetEntity, coords.x, coords.y, coords.z, false, false, true);
		}
	}

	inline Vector3 GetEntityCoords(Entity entity)
	{
		return ENTITY::GET_ENTITY_COORDS(entity, false);
	}
}
