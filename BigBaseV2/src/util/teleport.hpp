#pragma once
#include "blip.hpp"
#include "vehicle.hpp"
#include "gta/enums.hpp"

namespace big::teleport
{
	inline void bring_player(Player player)
	{
		Ped ent = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);

		if (ENTITY::IS_ENTITY_DEAD(ent, true))
		{
			return g_notification_service->push_warning("Teleport", "Target player is dead.");
		}

		if (!PED::IS_PED_IN_ANY_VEHICLE(ent, true))
		{
			return g_notification_service->push_warning("Teleport", "Target player is not in a vehicle.");
		}

		Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(ent, false);
		vehicle::bring(veh, self::pos);
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

	inline void to_coords(Vector3 location)
	{
		PED::SET_PED_COORDS_KEEP_VEHICLE(self::ped, location.x, location.y, location.z + 1.f);
	}

	inline bool to_entity(Entity ent)
	{
		Vector3 location = ENTITY::GET_ENTITY_COORDS(ent, true);

		to_coords(location);

		return true;
	}

	inline bool to_player(Player player)
	{
		return to_entity(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player));
	}

	inline bool to_waypoint()
	{
		Vector3 location;

		const std::map<BlipIcons, std::vector<BlipColors>> checkpoints = {
			{BlipIcons::WAYPOINT, {  } }
		};

		if (!blip::get_blip_location(checkpoints, location))
		{
			g_notification_service->push_warning("Teleport", "Failed to find waypoint position");
			return false;
		}

		load_ground_at_3dcoord(location);
		to_coords(location);

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

		to_coords(location);

		return false;
	}
}
