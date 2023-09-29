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
				for (int i = 0; i < 6; i++)
				{
					if (VEHICLE::IS_VEHICLE_DOOR_DAMAGED(veh, i))
					{
						VEHICLE::SET_VEHICLE_FIXED(veh);
					}
				}

				for (int i = 0; i <= 14; i++)
				{
					if (VEHICLE::DOES_EXTRA_EXIST(veh, i) && VEHICLE::IS_VEHICLE_EXTRA_TURNED_ON(veh, i) && VEHICLE::IS_EXTRA_BROKEN_OFF(veh, i))
					{
						VEHICLE::SET_VEHICLE_FIXED(veh);
					}
				}

				if (VEHICLE::IS_VEHICLE_BUMPER_BOUNCING(veh, TRUE) || VEHICLE::IS_VEHICLE_BUMPER_BOUNCING(veh, FALSE) || VEHICLE::GET_VEHICLE_NUM_OF_BROKEN_LOOSEN_PARTS(veh) > 0)
				{
					VEHICLE::SET_VEHICLE_FIXED(veh);
				}

				if (!VEHICLE::IS_VEHICLE_WINDOW_INTACT(veh, 7)) //Rear window
					VEHICLE::FIX_VEHICLE_WINDOW(veh, 7);

				g_pointers->m_gta.m_decal_manager_remove(g_pointers->m_gta.m_decal_manager, g_pointers->m_gta.m_handle_to_ptr(veh), -1, 0, 0x0001E000);

				if (!g.vehicle.god_mode)
				{
					VEHICLE::SET_VEHICLE_DEFORMATION_FIXED(veh);
				}

				if (!g.vehicle.keep_vehicle_clean)
				{
					VEHICLE::SET_VEHICLE_DIRT_LEVEL(veh, 0.f);
				}
			}
		}
	};

	keep_vehicle_repaired g_keep_vehicle_repaired("keepfixed", "KEEP_VEHICLE_FIXED", "KEEP_VEHICLE_FIXED_DESC",
	    g.vehicle.keep_vehicle_repaired);
}
