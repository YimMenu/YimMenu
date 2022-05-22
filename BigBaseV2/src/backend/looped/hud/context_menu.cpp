#include "services/context_menu_service.hpp"
#include "backend/looped/looped.hpp"
#include "gta/enums.hpp"
#include "natives.hpp"

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
			PAD::DISABLE_CONTROL_ACTION(0, (int)ControllerInputs::INPUT_VEH_MOUSE_CONTROL_OVERRIDE, true);

			g_context_menu_service->get_entity_closest_to_screen_center();

			const auto cm = g_context_menu_service->get_context_menu();
			if (cm == nullptr)
				return;

			if (PAD::IS_DISABLED_CONTROL_JUST_PRESSED(0, (int)ControllerInputs::INPUT_WEAPON_WHEEL_NEXT))
				cm->current_option = cm->options.size() <= cm->current_option + 1 ? 0 : cm->current_option + 1;
			if (PAD::IS_DISABLED_CONTROL_JUST_PRESSED(0, (int)ControllerInputs::INPUT_WEAPON_WHEEL_PREV))
				cm->current_option = 0 > cm->current_option - 1 ? static_cast<int>(cm->options.size()) - 1 : cm->current_option - 1;
			if (PAD::IS_DISABLED_CONTROL_JUST_PRESSED(0, (int)ControllerInputs::INPUT_ATTACK) ||
				PAD::IS_DISABLED_CONTROL_JUST_PRESSED(0, (int)ControllerInputs::INPUT_SPECIAL_ABILITY))
			{
				if (!g_context_menu_service->m_pointer)
					return;
				cm->options.at(cm->current_option).command();
			}
		}
	}
}
