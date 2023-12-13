#include "backend/looped/looped.hpp"
#include "natives.hpp"

#include <gta/enums.hpp>

namespace big
{
	static const ControllerInputs attack_controls[] = {
	    ControllerInputs::INPUT_WEAPON_WHEEL_NEXT,
	    ControllerInputs::INPUT_WEAPON_WHEEL_PREV,
	    ControllerInputs::INPUT_ATTACK,
	    ControllerInputs::INPUT_ATTACK2,
	    ControllerInputs::INPUT_VEH_ATTACK,
	    ControllerInputs::INPUT_VEH_ATTACK2,
	    ControllerInputs::INPUT_VEH_PASSENGER_ATTACK,
	    ControllerInputs::INPUT_VEH_FLY_ATTACK,
	    ControllerInputs::INPUT_VEH_FLY_ATTACK2,
	};

	void looped::custom_gun_disable_control_action()
	{
		bool is_custom_gun_selected = g.weapons.custom_weapon != CustomWeapon::NONE;
		if (is_custom_gun_selected)
		{
			for (const auto& control : attack_controls)
				PAD::DISABLE_CONTROL_ACTION(0, static_cast<int>(control), true);
		}
	}
}
