#include "backend/looped_command.hpp"
#include "gta/enums.hpp"
#include "gui.hpp"
#include "natives.hpp"
#include "util/math.hpp"

namespace big
{
	class rapid_fire : looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override
		{
			if (!HUD::IS_PAUSE_MENU_ACTIVE() && !g_gui->is_open() && !PED::IS_PED_DEAD_OR_DYING(self::ped, true))
			{
				if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_ATTACK) && PED::GET_PED_CONFIG_FLAG(self::ped,78,0))
				{
					const auto weapon_entity = WEAPON::GET_CURRENT_PED_WEAPON_ENTITY_INDEX(self::ped, 0);
					if (!weapon_entity)
						return;

					auto camera_direction = math::rotation_to_direction(CAM::GET_GAMEPLAY_CAM_ROT(0));
					auto camera_position  = CAM::GET_GAMEPLAY_CAM_COORD() + camera_direction;

					Vector3 end = camera_position + camera_direction * 2000.0;
		
					PED::SET_PED_SHOOTS_AT_COORD(self::ped, end.x, end.y, end.z, true);
					WEAPON::REFILL_AMMO_INSTANTLY(self::ped);
				}
			}
		}
	};

	rapid_fire g_rapid_fire("rapidfire", "BACKEND_LOOPED_WEAPONS_RAPID_FIRE", "BACKEND_LOOPED_WEAPONS_RAPID_FIRE_DESC", g.weapons.rapid_fire);
}
