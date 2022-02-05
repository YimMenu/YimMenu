#include "common.hpp"
#include "VehicleHelper.h"
#include "script.hpp"
#include "gta_util.hpp"
#include "gta\net_object_mgr.hpp"

namespace big
{
	void vehicle_helper::add_clan_logo_to_vehicle(Vehicle vehicle, Ped ped)
	{
		rage::fvector3 x, y, z;
		float scale;
		Hash modelHash = ENTITY::GET_ENTITY_MODEL(vehicle);
		if (GetVehicleInfoForClanLogo(modelHash, x, y, z, scale))
		{
			int alpha = 200;
			if (modelHash == VEHICLE_WINDSOR || modelHash == VEHICLE_COMET4)
				alpha = 255;

			GRAPHICS::ADD_VEHICLE_CREW_EMBLEM(vehicle, ped, ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(vehicle, "chassis_dummy"), x.x, x.y, x.z, y.x, y.y, y.z, z.x, z.y, z.z, scale, 0, alpha);
			if (y.z >= 0.0f)
				GRAPHICS::ADD_VEHICLE_CREW_EMBLEM(vehicle, ped, ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(vehicle, "chassis_dummy"), x.x * -1.0f, x.y, x.z, y.x * -1.0f, y.y, y.z, z.x * -1.0f, z.y * -1.0f, z.z, scale, 1, alpha);
		}
	}

	void vehicle_helper::set_mp_parameters_for_vehicle(Vehicle vehicle)
	{
		DECORATOR::DECOR_SET_INT(vehicle, "MPBitset", 0);
		auto networkId = NETWORK::VEH_TO_NET(vehicle);
		if (NETWORK::NETWORK_GET_ENTITY_IS_NETWORKED(vehicle))
			NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(networkId, true);
		VEHICLE::SET_VEHICLE_IS_STOLEN(vehicle, FALSE);
	}

	Vehicle vehicle_helper::create_vehicle(Hash modelHash, float x, float y, float z, float heading)
	{
		while (!STREAMING::HAS_MODEL_LOADED(modelHash))
		{
			STREAMING::REQUEST_MODEL(modelHash);
			script::get_current()->yield();
		}
		*(unsigned short*)big::g_pointers->m_model_spawn_bypass = 0x9090;
		Vehicle vehicle = VEHICLE::CREATE_VEHICLE(modelHash, x, y, z, heading, TRUE, FALSE, FALSE);
		*(unsigned short*)big::g_pointers->m_model_spawn_bypass = 0x0574;
		script::get_current()->yield(); //This allows the car to initalize so when we write things like radio station, it will overwrite.
		ENTITY::SET_ENTITY_CLEANUP_BY_ENGINE_(vehicle, TRUE);
		PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), vehicle, -1);
		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(modelHash);
		if (*big::g_pointers->m_is_session_started)
			set_mp_parameters_for_vehicle(vehicle);
		return vehicle;
	}
}