#include "backend/looped_command.hpp"
#include "gta/enums.hpp"
#include "natives.hpp"
#include "util/entity.hpp"

namespace big
{
	class triggerbot : looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override
		{
			Entity crosshair_catch;
			if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_AIM))
			{
				if (entity::raycast(&crosshair_catch))
				{
					if (ENTITY::IS_ENTITY_A_PED(crosshair_catch) && !ENTITY::IS_ENTITY_DEAD(crosshair_catch, 0))
					{
						Vector3 coords = ENTITY::GET_ENTITY_COORDS(crosshair_catch, 1);
						PED::SET_PED_SHOOTS_AT_COORD(self::ped, coords.x, coords.y, coords.z, true);
					}// Add check for vehicles, currently only shoots peds not in vehicles
				}
			}
		}
	};

	triggerbot g_triggerbot("triggerbot", "Triggerbot", "Shoots at a ped with fast ease", g.weapons.triggerbot);
}
