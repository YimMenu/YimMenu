#include "backend/looped/looped.hpp"
#include "core/enums.hpp"
#include "util/entity.hpp"
#include "util/math.hpp"

namespace big
{
	static const int controls[] = { 14, 15, 24 };

	void looped::weapons_delete_gun()
	{
		bool bCageGun = g->weapons.custom_weapon == CustomWeapon::DELETE_GUN;

		if (bCageGun)
		{
			if (PAD::IS_DISABLED_CONTROL_PRESSED(0, 25))
			{
				PLAYER::DISABLE_PLAYER_FIRING(PLAYER::GET_PLAYER_INDEX(), true);
				for (int control : controls)
					PAD::DISABLE_CONTROL_ACTION(0, control, true);

				if (PAD::IS_DISABLED_CONTROL_JUST_RELEASED(0, 24))
				{
					Entity entity;

					if (entity::raycast(&entity))
					{
						if (ENTITY::IS_ENTITY_A_PED(entity) && PED::IS_PED_A_PLAYER(entity))
						{
							g_notification_service->push_error("Weapons", "You can't delete player entities!");
						}
						else
						{
							Vector3 player = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
							Vector3 entLoc = ENTITY::GET_ENTITY_COORDS(entity, true);
							double dist = math::distance_between_vectors(player, entLoc);

							if (dist > 500)
							{
								g_notification_service->push_error("Weapons", "Entity is too far.");
							}
							else
							{
								if (entity::take_control_of(entity))
								{
									entity::delete_entity(entity);
								}
								else g_notification_service->push_error("Weapons", "Failed to take control of entity.");
							}
						}
					}
					else g_notification_service->push_error("Weapons", "No entity found.");
				}
			}
		}
	}
}