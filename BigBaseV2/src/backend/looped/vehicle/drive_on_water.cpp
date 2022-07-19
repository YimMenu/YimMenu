#include "backend/looped/looped.hpp"
#include "natives.hpp"
#include "script.hpp"
#include "util/entity.hpp"

namespace big
{
	const Hash drive_on_water_surface_hash = rage::joaat("stt_prop_stunt_bblock_xl3");
	static Vector3 drive_on_water_last_loc;

	void drive_on_water_hide_surface()
	{
		Object surface = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(
			drive_on_water_last_loc.x, drive_on_water_last_loc.y, drive_on_water_last_loc.z, 
			4.0, drive_on_water_surface_hash, 0, 0, 1
		);

		if (surface)
		{
			entity::take_control_of(surface);
			ENTITY::SET_ENTITY_COORDS(surface, 0, 0, -1000.0f, 0, 0, 0, 1);
			script::get_current()->yield(10ms);
			ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&surface);
			ENTITY::DELETE_ENTITY(&surface);
			WATER::RESET_DEEP_OCEAN_SCALER();
		}
	}


	void looped::vehicle_drive_on_water()
	{
		if (g->vehicle.drive_on_water) {

		Vehicle vehicle = self::veh;
		Player player = self::id;
		Ped playerPed = self::ped;
		Vector3 location = ENTITY::GET_ENTITY_COORDS(vehicle, 1);

		auto veh_hash = ENTITY::GET_ENTITY_MODEL(vehicle);
		float height = 0;

		WATER::SET_DEEP_OCEAN_SCALER(0);
		if (!VEHICLE::IS_THIS_MODEL_A_PLANE(veh_hash) && WATER::GET_WATER_HEIGHT_NO_WAVES(location.x, location.y, location.z - 0.05f, &height))
		{
			Object surface = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(
				drive_on_water_last_loc.x, drive_on_water_last_loc.y, drive_on_water_last_loc.z,
				4.0, drive_on_water_surface_hash, 0, 0, 1
			);

			if (ENTITY::DOES_ENTITY_EXIST(surface) && height > -50.0f)
			{
				Vector3 pRot = ENTITY::GET_ENTITY_ROTATION(vehicle, 0);

				entity::take_control_of(surface);
				ENTITY::SET_ENTITY_COORDS(surface, location.x, location.y, height - 0.2f, 0, 0, 0, 1);
				ENTITY::SET_ENTITY_ROTATION(surface, 0, 0, pRot.z, 0, 1);
				drive_on_water_last_loc = location;

				if (location.z < height - 0.05f)
				{
					entity::take_control_of(vehicle);
					ENTITY::SET_ENTITY_COORDS(vehicle, location.x, location.y, height, 0, 0, 0, 1);
				}
			}
			else
			{
				STREAMING::REQUEST_MODEL(drive_on_water_surface_hash);
				while (!STREAMING::HAS_MODEL_LOADED(drive_on_water_surface_hash))
				{
					script::get_current()->yield();
				}
				surface = OBJECT::CREATE_OBJECT(
					drive_on_water_surface_hash, 
					location.x, location.y, location.z, 
					1, 1, 0
				);
				drive_on_water_last_loc = location;

				entity::take_control_of(surface);
				ENTITY::FREEZE_ENTITY_POSITION(surface, 1);
				ENTITY::SET_ENTITY_ALPHA(surface, 0, 1);
				ENTITY::SET_ENTITY_VISIBLE(surface, false, 0);
			}
		}
		else
		{
			drive_on_water_hide_surface();
		}
	}
}