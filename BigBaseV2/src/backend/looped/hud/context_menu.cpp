#include "backend/looped/looped.hpp"
#include "natives.hpp"
#include "gta/enums.hpp"
#include "services/context_menu_service.hpp"

namespace big
{
	void looped::context_menu()
	{
		if (PAD::IS_DISABLED_CONTROL_JUST_RELEASED(0, (int)ControllerInputs::INPUT_VEH_DUCK))
		{
			g_context_menu_service->enabled = !g_context_menu_service->enabled;
		}

		if (g_context_menu_service->enabled)
		{
			PAD::DISABLE_CONTROL_ACTION(0, (int)ControllerInputs::INPUT_NEXT_WEAPON, true);
			PAD::DISABLE_CONTROL_ACTION(0, (int)ControllerInputs::INPUT_PREV_WEAPON, true);
			PAD::DISABLE_CONTROL_ACTION(0, (int)ControllerInputs::INPUT_VEH_NEXT_RADIO, true);
			PAD::DISABLE_CONTROL_ACTION(0, (int)ControllerInputs::INPUT_VEH_SELECT_NEXT_WEAPON, true);
			PAD::DISABLE_CONTROL_ACTION(0, (int)ControllerInputs::INPUT_SELECT_NEXT_WEAPON, true);
			PAD::DISABLE_CONTROL_ACTION(0, (int)ControllerInputs::INPUT_SELECT_PREV_WEAPON, true);
			PAD::DISABLE_CONTROL_ACTION(0, (int)ControllerInputs::INPUT_WEAPON_WHEEL_NEXT, true);
			PAD::DISABLE_CONTROL_ACTION(0, (int)ControllerInputs::INPUT_WEAPON_WHEEL_PREV, true);
			PAD::DISABLE_CONTROL_ACTION(0, (int)ControllerInputs::INPUT_ATTACK, true);
			PAD::DISABLE_CONTROL_ACTION(0, (int)ControllerInputs::INPUT_SPECIAL_ABILITY, true);

			g_context_menu_service->get_entity_closest_to_screen_center();


			s_context_menu* cm = g_context_menu_service->get_context_menu();

			if (PAD::IS_DISABLED_CONTROL_JUST_PRESSED(0, (int)ControllerInputs::INPUT_WEAPON_WHEEL_NEXT))
				cm->current_option = cm->options.size() <= cm->current_option + 1 ? 0 : cm->current_option + 1;
			if (PAD::IS_DISABLED_CONTROL_JUST_PRESSED(0, (int)ControllerInputs::INPUT_WEAPON_WHEEL_PREV))
				cm->current_option = 0 > cm->current_option - 1 ? cm->options.size() - 1 : cm->current_option - 1;
			if (PAD::IS_DISABLED_CONTROL_JUST_PRESSED(0, (int)ControllerInputs::INPUT_ATTACK) ||
				PAD::IS_DISABLED_CONTROL_JUST_PRESSED(0, (int)ControllerInputs::INPUT_SPECIAL_ABILITY))
			{
				if (!g_context_menu_service->pointer) return;
				cm->options.at(cm->current_option).command();
			}
		}
	}
}
