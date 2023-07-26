#include "backend/looped/looped.hpp"
#include "backend/looped_command.hpp"
#include "fiber_pool.hpp"
#include "natives.hpp"
#include "gta/enums.hpp"

namespace big
{
	class vehinvisibility : looped_command
	{
		using looped_command::looped_command;

		bool last_driving = false;

		virtual void on_tick() override
		{
			if (!PED::GET_PED_CONFIG_FLAG(self::ped, 62, false))
			{
				if (last_driving)
				{
					ENTITY::SET_ENTITY_VISIBLE(self::veh, true, 0);
				}

				last_driving = false;
				return;
			}

			last_driving = true;

			ENTITY::SET_ENTITY_VISIBLE(self::veh, false, 0);

			if (g.vehicle.localveh_visibility)
				NETWORK::SET_ENTITY_LOCALLY_VISIBLE(self::veh);
		}

		virtual void on_disable() override
		{
			ENTITY::SET_ENTITY_VISIBLE(self::veh, true, 0);
		}
	};

	vehinvisibility g_vehinvisibility("invisveh", "VEHICLE_INVISIBILITY", "VEHICLE_INVISIBILITY_DESC", g.vehicle.vehinvisibility);
	bool_command g_localveh_visibility("localinvisveh", "VEHICLE_LOCAL_VISIBLE", "VEHICLE_LOCAL_VISIBLE_DESC",
	    g.vehicle.localveh_visibility);
}
