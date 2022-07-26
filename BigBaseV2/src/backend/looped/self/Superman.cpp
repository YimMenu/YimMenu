#include "backend/looped/looped.hpp"
#include "util/toxic.hpp"
#include "util/ptfx.hpp"

namespace big
{
	void looped::self_SuperMan_salman_ka_fan() {
		if (g->self.SuperMan_salman_ka_fan) {
			if (!g->self.no_ragdoll) {
				g->self.no_ragdoll = true;
				g->self.ragdoll_toggle = true;
			}
			if (!g->vehicle.seatbelt) {
				g->vehicle.seatbelt = true;
				g->self.seatbelt_toggle = true;
			}
			if (!g->self.god_mode) {
				g->self.god_mode = true;
				g->self.god_mode_toggle = true;
			}
			Hash parachute = RAGE_JOAAT("GADGET_PARACHUTE");
			WEAPON::GIVE_WEAPON_TO_PED(self::ped, parachute, 1, false, true);
			PED::SET_PED_TO_RAGDOLL_WITH_FALL(self::ped, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0);

			if (ENTITY::IS_ENTITY_IN_AIR(self::ped) && !PED::IS_PED_RAGDOLL(self::ped))
			{
				if (PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_VEH_ACCELERATE))
				{
					toxic::ApplyForceToEntity(self::ped, 0, 2, 0);
					ptfx::supermanPTFX();
				}
				if (PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_VEH_BRAKE))
				{
					toxic::ApplyForceToEntity(self::ped, 0, -2, 0);
					ptfx::supermanPTFX();
				}
				if (PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_VEH_HANDBRAKE)) {
					toxic::ApplyForceToEntity(self::ped, 0, 0, 2);
					ptfx::supermanPTFX();
				}
			}
		}
		else if (g->self.ragdoll_toggle || g->self.god_mode_toggle || g->self.seatbelt_toggle) {
			if (g->self.ragdoll_toggle) {
				g->self.no_ragdoll = false;
				g->self.ragdoll_toggle = false;
			}
			if (g->self.seatbelt_toggle) {
				g->vehicle.seatbelt = false;
				g->self.seatbelt_toggle = false;
			}
			if (g->self.god_mode_toggle) {
				g->self.god_mode = false;
				g->self.god_mode_toggle = false;
			}
		}
	}
}
			