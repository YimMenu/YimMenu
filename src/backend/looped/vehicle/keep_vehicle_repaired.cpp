#include "backend/looped_command.hpp"
#include "natives.hpp"
#include "util/vehicle.hpp"

namespace big
{
	class keep_vehicle_repaired : looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override
		{
			auto veh = self::veh;
			if (!ENTITY::IS_ENTITY_A_VEHICLE(veh) || !entity::take_control_of(veh, 0))
			{
				return;
			}
			if (VEHICLE::GET_DOES_VEHICLE_HAVE_DAMAGE_DECALS(veh))
			{
				if (VEHICLE::IS_VEHICLE_BUMPER_BOUNCING(veh, TRUE) || VEHICLE::GET_VEHICLE_NUM_OF_BROKEN_OFF_PARTS(veh) > 0)
				{
					VEHICLE::SET_VEHICLE_FIXED(veh);
				}

				if (!VEHICLE::IS_VEHICLE_WINDOW_INTACT(veh, 7)) //Rear window
					VEHICLE::FIX_VEHICLE_WINDOW(veh, 7);

				int clan_logo_counter = GRAPHICS::DOES_VEHICLE_HAVE_CREW_EMBLEM(veh, 0) * 10;
				GRAPHICS::REMOVE_DECALS_FROM_VEHICLE(veh);
				while (clan_logo_counter-- > 0 && !GRAPHICS::DOES_VEHICLE_HAVE_CREW_EMBLEM(veh, 0))
				{
					vehicle_helper::add_clan_logo_to_vehicle(veh, self::ped);
					script::get_current()->yield(10ms);
				}

				VEHICLE::SET_VEHICLE_DEFORMATION_FIXED(veh);
				VEHICLE::SET_VEHICLE_DIRT_LEVEL(veh, 0.f);
			}
		}
	};

	keep_vehicle_repaired g_keep_vehicle_repaired("keepfixed", "KEEP_VEHICLE_FIXED", "KEEP_VEHICLE_FIXED_DESC",
	    g.vehicle.keep_vehicle_repaired);
}
