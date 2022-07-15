#include "fiber_pool.hpp"
#include "gui/handling/handling_tabs.hpp"
#include "script.hpp"
#include "util/vehicle.hpp"
#include "views/view.hpp"
#include "util/mobile.hpp"
#include "core/data/speed_units.hpp"
#include "core/globals.hpp"
#include "util/entity.hpp"
#include "backend/looped/looped.hpp"
#include "natives.hpp"
#include "services/players/player_service.hpp"

namespace big
{
	void looped::self_SuperMan_salman_ka_fan(){
		if (g->self.SuperMan_salman_ka_fan) {
			Hash parachute = RAGE_JOAAT("GADGET_PARACHUTE");
			WEAPON::GIVE_WEAPON_TO_PED(self::id, parachute, 1, false, true);
			ENTITY::SET_ENTITY_INVINCIBLE(self::id, true);
			PED::SET_PED_TO_RAGDOLL_WITH_FALL(self::id, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0);

			if (ENTITY::IS_ENTITY_IN_AIR(self::id) && !PED::IS_PED_RAGDOLL(self::id))
			{
				if (PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_VEH_ACCELERATE)) { toxic::apply_force_to_entity(self::id, 0, 6, 0); }
				if (PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_VEH_BRAKE)) { toxic::apply_force_to_entity(self::id, 0, -6, 0); }
				if (PAD::IS_CONTROL_PRESSED(0, VK_SHIFT)) { toxic::apply_force_to_entity(self::id, 0, 0, 6); }
			}
		}
	}
}