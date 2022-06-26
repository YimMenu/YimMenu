#include "common.hpp"
#include "features.hpp"
#include "logger.hpp"
#include "script.hpp"
#include "natives.hpp"
#include "backend/backend.hpp"
#include "util/entity.hpp"
#include "util/vehicle.hpp"
#include "gta/VehicleValues.h"

namespace big
{
	void features::run_tick()
	{
		if (GetAsyncKeyState(g->settings.hotkeys.teleport_waypoint)) {
			teleport::to_waypoint();
		}
		backend::loop();
	}
	float features::max_vehicle_torque = 5.f;
	float features::max_vehicle_engine = 5.f;

	Vehicle features::ClonePedVehicle(Ped ped)
	{
		Vehicle pedVeh = NULL;
		Ped playerPed = PLAYER::PLAYER_PED_ID();
		if (PED::IS_PED_IN_ANY_VEHICLE(ped, FALSE))
			pedVeh = PED::GET_VEHICLE_PED_IS_IN(ped, FALSE);
		else //If they're not in a vehicle, try to get their last vehicle.
			pedVeh = PED::GET_VEHICLE_PED_IS_IN(ped, TRUE);
		if (ENTITY::DOES_ENTITY_EXIST(pedVeh))
		{
			Hash vehicleModelHash = ENTITY::GET_ENTITY_MODEL(pedVeh);
			STREAMING::REQUEST_MODEL(vehicleModelHash); //This should already be loaded since we're stealing it from someone in memory.
			Vector3 playerPosition = ENTITY::GET_ENTITY_COORDS(playerPed, FALSE);
			*(unsigned short*)g_pointers->m_model_spawn_bypass = 0x9090; //TODO just do vehicle::spawn
			Vehicle playerVeh = VEHICLE::CREATE_VEHICLE(vehicleModelHash, playerPosition.x, playerPosition.y, playerPosition.z, ENTITY::GET_ENTITY_HEADING(playerPed), TRUE, false, false);
			*(unsigned short*)g_pointers->m_model_spawn_bypass = 0x0574;
			entity::take_control_of(playerVeh);
			//
			VEHICLE::SET_VEHICLE_IS_STOLEN(playerVeh, false);
			VEHICLE::SET_VEHICLE_ENGINE_ON(playerVeh, true, true, true);
			VEHICLE::SET_VEHICLE_IS_CONSIDERED_BY_PLAYER(playerVeh, true);
			VEHICLE::SET_VEHICLE_IS_WANTED(playerVeh, false);
			ENTITY::SET_ENTITY_AS_MISSION_ENTITY(playerVeh, 1, 1);
			NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(NETWORK::NET_TO_VEH(playerVeh), true);
			DECORATOR::DECOR_SET_INT(playerVeh, "MPBitset", 0);
			ENTITY::SET_ENTITY_CLEANUP_BY_ENGINE_(playerVeh, true);

			//
			PED::SET_PED_INTO_VEHICLE(playerPed, playerVeh, -1);
			int primaryColor, secondaryColor;
			VEHICLE::GET_VEHICLE_COLOURS(pedVeh, &primaryColor, &secondaryColor);
			VEHICLE::SET_VEHICLE_COLOURS(playerVeh, primaryColor, secondaryColor);
			if (VEHICLE::GET_IS_VEHICLE_PRIMARY_COLOUR_CUSTOM(pedVeh))
			{
				int r, g, b;
				VEHICLE::GET_VEHICLE_CUSTOM_PRIMARY_COLOUR(pedVeh, &r, &g, &b);
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(playerVeh, r, g, b);
			}
			if (VEHICLE::GET_IS_VEHICLE_SECONDARY_COLOUR_CUSTOM(pedVeh))
			{
				int r, g, b;
				VEHICLE::GET_VEHICLE_CUSTOM_SECONDARY_COLOUR(pedVeh, &r, &g, &b);
				VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(playerVeh, r, g, b);
			}
			if (VEHICLE::IS_THIS_MODEL_A_CAR(vehicleModelHash) || VEHICLE::IS_THIS_MODEL_A_BIKE(vehicleModelHash))
			{
				VEHICLE::SET_VEHICLE_MOD_KIT(playerVeh, 0);
				VEHICLE::SET_VEHICLE_WHEEL_TYPE(playerVeh, VEHICLE::GET_VEHICLE_WHEEL_TYPE(pedVeh));
				for (int i = 0; i <= MOD_LIVERY; i++)
				{
					if (i > MOD_ARMOR && i < MOD_FRONTWHEEL)
						VEHICLE::TOGGLE_VEHICLE_MOD(playerVeh, i, VEHICLE::IS_TOGGLE_MOD_ON(pedVeh, i));
					else
						VEHICLE::SET_VEHICLE_MOD(playerVeh, i, VEHICLE::GET_VEHICLE_MOD(pedVeh, i), VEHICLE::GET_VEHICLE_MOD_VARIATION(pedVeh, i));
				}
				int tireSmokeColor[3], pearlescentColor, wheelColor;
				VEHICLE::SET_VEHICLE_XENON_LIGHTS_COLOR_(playerVeh, VEHICLE::GET_VEHICLE_XENON_LIGHTS_COLOR_(pedVeh));
				VEHICLE::GET_VEHICLE_TYRE_SMOKE_COLOR(pedVeh, &tireSmokeColor[0], &tireSmokeColor[1], &tireSmokeColor[2]);
				VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(playerVeh, tireSmokeColor[0], tireSmokeColor[1], tireSmokeColor[2]);
				VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(playerVeh, VEHICLE::GET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(pedVeh));
				VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(playerVeh, VEHICLE::GET_VEHICLE_NUMBER_PLATE_TEXT(pedVeh));
				VEHICLE::GET_VEHICLE_EXTRA_COLOURS(pedVeh, &pearlescentColor, &wheelColor);
				VEHICLE::SET_VEHICLE_EXTRA_COLOURS(playerVeh, pearlescentColor, wheelColor);
				if (VEHICLE::IS_VEHICLE_A_CONVERTIBLE(pedVeh, 0))
				{
					int convertableState = VEHICLE::GET_CONVERTIBLE_ROOF_STATE(pedVeh);
					if (convertableState == 0 || convertableState == 3 || convertableState == 5)
						VEHICLE::RAISE_CONVERTIBLE_ROOF(playerVeh, 1);
					else
						VEHICLE::LOWER_CONVERTIBLE_ROOF(playerVeh, 1);
				}
				for (int i = 0; i <= 3; i++)
				{
					VEHICLE::SET_VEHICLE_NEON_LIGHT_ENABLED_(playerVeh, i, VEHICLE::IS_VEHICLE_NEON_LIGHT_ENABLED_(pedVeh, i));
				}
				for (int i = 0; i <= 11; i++)
				{
					if (VEHICLE::DOES_EXTRA_EXIST(pedVeh, i))
						VEHICLE::SET_VEHICLE_EXTRA(playerVeh, i, !VEHICLE::IS_VEHICLE_EXTRA_TURNED_ON(pedVeh, i));
				}
				if ((VEHICLE::GET_VEHICLE_LIVERY_COUNT(pedVeh) > 1) && VEHICLE::GET_VEHICLE_LIVERY(pedVeh) >= 0)
				{
					VEHICLE::SET_VEHICLE_LIVERY(playerVeh, VEHICLE::GET_VEHICLE_LIVERY(pedVeh));
				}
				int neonColor[3];
				VEHICLE::GET_VEHICLE_NEON_LIGHTS_COLOUR_(pedVeh, &neonColor[0], &neonColor[1], &neonColor[2]);
				VEHICLE::SET_VEHICLE_NEON_LIGHTS_COLOUR_(playerVeh, neonColor[0], neonColor[1], neonColor[2]);
				VEHICLE::SET_VEHICLE_WINDOW_TINT(playerVeh, VEHICLE::GET_VEHICLE_WINDOW_TINT(pedVeh));
				VEHICLE::SET_VEHICLE_DIRT_LEVEL(playerVeh, VEHICLE::GET_VEHICLE_DIRT_LEVEL(pedVeh));
				VEHICLE::SET_VEHICLE_ENGINE_ON(playerVeh, TRUE, TRUE, TRUE);
			}

			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(vehicleModelHash);
		}
		return pedVeh;
	}

	void features::BoostStats(Vehicle vehicle)
	{
		VEHICLE::SET_VEHICLE_DIRT_LEVEL(vehicle, 0.0f);
		ENTITY::SET_ENTITY_INVINCIBLE(vehicle, TRUE);
		ENTITY::SET_ENTITY_PROOFS(vehicle, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE);
		VEHICLE::SET_VEHICLE_STRONG(vehicle, TRUE); //2stronk
		VEHICLE::SET_VEHICLE_CAN_BE_VISIBLY_DAMAGED(vehicle, FALSE); //I don't think this really works, but fuck it. Call it anyway.
		VEHICLE::SET_VEHICLE_CAN_BREAK(vehicle, FALSE); //Hopefully this fixes the car blowing up after getting hit by a train...
		VEHICLE::SET_VEHICLE_ENGINE_CAN_DEGRADE(vehicle, FALSE);
		VEHICLE::SET_VEHICLE_IS_STOLEN(vehicle, FALSE); //What seems to be the officer, problem? *le9gagmemeface*
		VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(vehicle, FALSE); //Bulletproof Tires.
		Player player = PLAYER::PLAYER_ID();
		DECORATOR::DECOR_SET_INT(vehicle, "MPBitset", 0);
		Hash vehicleModel = ENTITY::GET_ENTITY_MODEL(vehicle);
		if (VEHICLE::IS_THIS_MODEL_A_CAR(vehicleModel) || VEHICLE::IS_THIS_MODEL_A_BIKE(vehicleModel))
		{
			VEHICLE::SET_VEHICLE_MOD_KIT(vehicle, 0); //IDK what this does, but I guess it allows individual mods to be added? It's what the game does before calling SET_VEHICLE_MOD.
			VEHICLE::SET_VEHICLE_HAS_STRONG_AXLES(vehicle, TRUE); //6stronk9meme
			VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_ENGINE, MOD_INDEX_FOUR, FALSE); //6fast9furious
			VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_BRAKES, MOD_INDEX_THREE, FALSE); //GOTTA STOP FAST
			VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_TRANSMISSION, MOD_INDEX_THREE, FALSE); //Not when I shift in to MAXIMUM OVERMEME!
			VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_SUSPENSION, MOD_INDEX_FOUR, FALSE); //How low can you go?
			VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_ARMOR, MOD_INDEX_FIVE, FALSE); //100% armor.
			VEHICLE::TOGGLE_VEHICLE_MOD(vehicle, MOD_TURBO, TRUE); //Forced induction huehuehue
		}
		VEHICLE::SET_VEHICLE_BODY_HEALTH(vehicle, 1000.0f); //This is what the game does
	}

	void features::script_func()
	{
		while (true)
		{
			TRY_CLAUSE
			{
				run_tick();
			}
			EXCEPT_CLAUSE
			script::get_current()->yield();
		}
	}
}
