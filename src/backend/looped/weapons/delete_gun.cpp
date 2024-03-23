#include "backend/looped/looped.hpp"
#include "core/enums.hpp"
#include "gta/enums.hpp"
#include "util/entity.hpp"
#include "util/math.hpp"

namespace big
{
	void looped::weapons_delete_gun()
	{
		if (g.weapons.custom_weapon == CustomWeapon::DELETE_GUN && (!g.self.custom_weapon_stop || WEAPON::IS_PED_ARMED(self::ped, 4 | 2)))
		{
			if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_AIM))
			{
				if (PAD::IS_DISABLED_CONTROL_JUST_RELEASED(0, (int)ControllerInputs::INPUT_ATTACK))
				{
					Entity entity;

					if (entity::raycast(&entity))
					{
						if (ENTITY::IS_ENTITY_A_PED(entity) && PED::IS_PED_A_PLAYER(entity))
						{
							g_notification_service.push_error("CUSTOM_WEAPONS"_T.data(), "BACKEND_LOOPED_WEAPONS_DELETE_GUN_PLAYER"_T.data());
						}
						else
						{
							Vector3 entLoc = ENTITY::GET_ENTITY_COORDS(entity, true);
							double dist    = math::distance_between_vectors(self::pos, entLoc);

							if (dist > 500)
							{
								g_notification_service.push_error("CUSTOM_WEAPONS"_T.data(), "BACKEND_LOOPED_WEAPONS_DELETE_GUN_TOO_FAR"_T.data());
							}
							else
							{
								if (entity::take_control_of(entity))
								{
									entity::delete_entity(entity);
								}
								else
									g_notification_service.push_error("CUSTOM_WEAPONS"_T.data(), "TELEPORT_FAILED_TO_TAKE_CONTROL"_T.data());
							}
						}
					}
					else
					{
						g_notification_service.push_error("CUSTOM_WEAPONS"_T.data(), "BACKEND_LOOPED_WEAPONS_CAGE_GUN_NO_ENTITY_FOUND"_T.data());
					}
				}
			}
		}
	}
}
