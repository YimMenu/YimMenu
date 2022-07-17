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
#include "util/toxic.hpp"

namespace big
{
	void looped::self_SuperMan_salman_ka_fan(){
		if (g->self.SuperMan_salman_ka_fan) {
			g->self.no_ragdoll = true;
			g->vehicle.seatbelt = true;
			Hash parachute = RAGE_JOAAT("GADGET_PARACHUTE");
			WEAPON::GIVE_WEAPON_TO_PED(self::ped, parachute, 1, false, true);
			ENTITY::SET_ENTITY_INVINCIBLE(self::ped, true);
			PED::SET_PED_TO_RAGDOLL_WITH_FALL(self::ped, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0);

			if (ENTITY::IS_ENTITY_IN_AIR(self::ped) && !PED::IS_PED_RAGDOLL(self::ped))
			{
				if (PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_VEH_ACCELERATE)) { toxic::ApplyForceToEntity(self::ped, 0, 2, 0); }
				if (PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_VEH_BRAKE)) { toxic::ApplyForceToEntity(self::ped, 0, -2, 0); }
				if (PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_VEH_HANDBRAKE)) { toxic::ApplyForceToEntity(self::ped, 0, 0, 2); }
			}
		}
		else
			ENTITY::SET_ENTITY_INVINCIBLE(self::ped, false);
	}
}