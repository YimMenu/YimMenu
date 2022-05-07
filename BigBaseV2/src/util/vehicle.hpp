#pragma once
#include "entity.hpp"
#include "gta/joaat.hpp"
#include "math.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "script.hpp"
#include "teleport.hpp"

namespace big::vehicle
{
	inline void bring(Vehicle veh, Vector3 location, bool put_in = true)
	{
		Vector3 vecVehicleLocation = ENTITY::GET_ENTITY_COORDS(veh, true);
		teleport::load_ground_at_3dcoord(vecVehicleLocation);

		if (!entity::take_control_of(veh))
			return g_notification_service->push_warning("Vehicle", "Failed to take control of remote vehicle.");
		ENTITY::SET_ENTITY_COORDS(veh, location.x, location.y, location.z + 1.f, 0, 0, 0, 0);
		ENTITY::SET_ENTITY_HEADING(veh, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()));

		if (put_in)
		{
			for (size_t i = 0; i < 100 && math::distance_between_vectors(location, ENTITY::GET_ENTITY_COORDS(veh, true)) > 10; i++)
				script::get_current()->yield();

			PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), veh, -1);
		}
	}

	inline Vehicle get_closest_to_location(Vector3 location, float range, int flags = 70)
	{
		return VEHICLE::GET_CLOSEST_VEHICLE(location.x, location.y, location.z, range, 0, flags);
	}

	inline bool repair(Vehicle veh)
	{
		if (!ENTITY::IS_ENTITY_A_VEHICLE(veh) || !entity::take_control_of(veh)) return false;

		VEHICLE::SET_VEHICLE_FIXED(veh);
		VEHICLE::SET_VEHICLE_DEFORMATION_FIXED(veh);
		VEHICLE::SET_VEHICLE_DIRT_LEVEL(veh, 0.f);

		return true;
	}

	inline int spawn(std::string_view model, Vector3 location, float heading, bool is_networked = true)
	{
		if (const Hash hash = rage::joaat(model.data()); hash)
		{
			for (uint8_t i = 0; !STREAMING::HAS_MODEL_LOADED(hash) && i < 100; i++)
			{
				STREAMING::REQUEST_MODEL(hash);

				script::get_current()->yield();
			}
			if (!STREAMING::HAS_MODEL_LOADED(hash))
			{
				g_notification_service->push_warning("Spawn", "Failed to spawn model, did you give an incorrect model?");

				return -1;
			}

			*(unsigned short*)g_pointers->m_model_spawn_bypass = 0x9090;
			Vehicle veh = VEHICLE::CREATE_VEHICLE(hash, location.x, location.y, location.z, heading, is_networked, false, false);
			*(unsigned short*)g_pointers->m_model_spawn_bypass = 0x0574;

			script::get_current()->yield();

			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);

			if (*g_pointers->m_is_session_started)
			{
				DECORATOR::DECOR_SET_INT(veh, "MPBitset", 0);
				ENTITY::SET_ENTITY_CLEANUP_BY_ENGINE_(veh, true);
				int networkId = NETWORK::VEH_TO_NET(veh);
				if (NETWORK::NETWORK_GET_ENTITY_IS_NETWORKED(veh))
					NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(networkId, true);
				VEHICLE::SET_VEHICLE_IS_STOLEN(veh, false);
			}

			return veh;
		}

		return -1;
	}

	inline void telport_into_veh(Vehicle veh)
	{
		PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), veh, -1);
	}

	inline void max_vehicle(Vehicle veh)
	{
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::TOGGLE_VEHICLE_MOD(veh, 18 /* Turbo */, TRUE);
		VEHICLE::TOGGLE_VEHICLE_MOD(veh, 20 /* Tire Smoke */, TRUE);
		VEHICLE::TOGGLE_VEHICLE_MOD(veh, 17 /* Xenon Headlights */, TRUE);
		VEHICLE::SET_VEHICLE_WINDOW_TINT(veh, 1);
		VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(veh, false);
		for (int i = 0; i < 50; i++)
		{
			VEHICLE::SET_VEHICLE_MOD(veh, i, VEHICLE::GET_NUM_VEHICLE_MODS(veh, i) - 1, true);
		}
	}

	static constexpr char const* rgb_types[] = { "Off", "Fade", "Spasm" };

}
