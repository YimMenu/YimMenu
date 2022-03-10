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
			PAD::DISABLE_CONTROL_ACTION(0, (int)ControllerInputs::INPUT_PHONE, true);
			PAD::DISABLE_CONTROL_ACTION(0, (int)ControllerInputs::INPUT_SPECIAL_ABILITY, true);

			g_context_menu_service->get_entity_closest_to_screen_center();

			

			if (PAD::IS_DISABLED_CONTROL_JUST_PRESSED(0, (int)ControllerInputs::INPUT_WEAPON_WHEEL_NEXT))
				g_context_menu_service->current_option = g_context_menu_service->options.size() <= g_context_menu_service->current_option + 1 ? 0 : g_context_menu_service->current_option + 1;
			if (PAD::IS_DISABLED_CONTROL_JUST_PRESSED(0, (int)ControllerInputs::INPUT_WEAPON_WHEEL_PREV))
				g_context_menu_service->current_option = 0 > g_context_menu_service->current_option - 1 ? g_context_menu_service->options.size() - 1 : g_context_menu_service->current_option - 1;
			if (PAD::IS_DISABLED_CONTROL_JUST_PRESSED(0, (int)ControllerInputs::INPUT_PHONE) ||
				PAD::IS_DISABLED_CONTROL_JUST_PRESSED(0, (int)ControllerInputs::INPUT_SPECIAL_ABILITY))
				g_context_menu_service->options.at(g_context_menu_service->current_option).command();
		}
	}
}
