#include "backend/looped/looped.hpp"
#include "backend/looped_command.hpp"
#include "fiber_pool.hpp"
#include "natives.hpp"
#include "util/entity.hpp"
#include "script.hpp"

namespace big
{
	class drive_on_water : looped_command
	{
		using looped_command::looped_command;

		const rage::joaat_t drive_on_water_surface_hash = "stt_prop_stunt_bblock_xl3"_J;
		Vector3 drive_on_water_last_loc;
		Object surface;

		void drive_on_water_hide_surface()
		{
			if (surface && entity::take_control_of(surface, 0))
			{
				ENTITY::SET_ENTITY_COORDS(surface, 0, 0, -1000.0f, 0, 0, 0, 1);
				ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&surface);
				ENTITY::DELETE_ENTITY(&surface);
				surface = 0;
			}

			WATER::RESET_DEEP_OCEAN_SCALER();
		}

		virtual void on_tick() override
		{
			Vector3 location = ENTITY::GET_ENTITY_COORDS(self::veh, true);
			float height     = 0;

			if (self::veh)
				WATER::SET_DEEP_OCEAN_SCALER(0);

			if (self::veh && location.z - height < 10
			    && WATER::GET_WATER_HEIGHT_NO_WAVES(location.x, location.y, location.z, &height))
			{
				if (ENTITY::DOES_ENTITY_EXIST(surface) && height > -50.0f)
				{
					entity::take_control_of(surface);

					drive_on_water_last_loc   = location;
					drive_on_water_last_loc.z = height - 0.5f;
					ENTITY::SET_ENTITY_COORDS(surface,
					    drive_on_water_last_loc.x,
					    drive_on_water_last_loc.y,
					    drive_on_water_last_loc.z,
					    0,
					    0,
					    0,
					    0);

					if (location.z < height - 2.f)
					{
						if (entity::take_control_of(self::veh, 0))
							ENTITY::SET_ENTITY_COORDS(self::veh, location.x, location.y, height, 0, 0, 0, 0);
					}
				}
				else
				{
					STREAMING::REQUEST_MODEL(drive_on_water_surface_hash);
					while (!STREAMING::HAS_MODEL_LOADED(drive_on_water_surface_hash))
					{
						script::get_current()->yield();
					}

					drive_on_water_last_loc   = location;
					drive_on_water_last_loc.z = height - 0.5f;
					surface                   = OBJECT::CREATE_OBJECT(drive_on_water_surface_hash,
                        drive_on_water_last_loc.x,
                        drive_on_water_last_loc.y,
                        drive_on_water_last_loc.z,
                        1,
                        1,
                        0);

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

		virtual void on_disable() override
		{
			drive_on_water_hide_surface();
		}
	};

	drive_on_water g_drive_on_water("driveonwater", "DRIVE_ON_WATER", "DRIVE_ON_WATER_DESC", g.vehicle.drive_on_water);
}
