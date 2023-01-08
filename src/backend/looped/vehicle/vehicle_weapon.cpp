#include "natives.hpp"
#include "backend/looped_command.hpp"
#include "gta/enums.hpp"

namespace big
{
	class vehicle_weapon : looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override
		{
			Vehicle veh = self::veh;
			Vector3 selfvehcoords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, 0.0f, 0.6707f, 0.3711f);
			Vector3 farcoords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(veh, 0.0f, 25.0707f, 0.3711f);
			Hash weaponhash = MISC::GET_HASH_KEY(g.vehicle.selectedweapon);

			if (PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_DUCK) && PED::IS_PED_IN_VEHICLE(self::ped, self::veh, false))
			{
				if(g.vehicle.drawline){ GRAPHICS::DRAW_LINE(selfvehcoords.x, selfvehcoords.y, selfvehcoords.z, farcoords.x, farcoords.y, farcoords.z, 255, 0, 0, 180); }
				MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(selfvehcoords.x, selfvehcoords.y, selfvehcoords.z, farcoords.x, farcoords.y, farcoords.z, 250, 1, weaponhash, self::ped, 1, 0, 1.0f);
			}
		}
	};

	vehicle_weapon g_vehicle_weapon("vehweapon", "Vehicle Weapon", "When enabled changes the vehicle weapon to whatever you selected.", g.vehicle.vehicle_weapon);
	bool_command g_vehicle_drawline("vehweaponline", "Show Line", "Shows A Line When Shooting Vehicle Weapon", g.vehicle.drawline);
}

//test SET_ENABLE_HANDCUFFS for in interior if u can use weapons