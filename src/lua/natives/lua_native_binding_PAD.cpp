#include "lua_native_binding.hpp"
#include "natives.hpp"

namespace lua::native
{
	static bool LUA_NATIVE_PAD_IS_CONTROL_ENABLED(int control, int action)
	{
		auto retval = (bool)PAD::IS_CONTROL_ENABLED(control, action);
		return retval;
	}

	static bool LUA_NATIVE_PAD_IS_CONTROL_PRESSED(int control, int action)
	{
		auto retval = (bool)PAD::IS_CONTROL_PRESSED(control, action);
		return retval;
	}

	static bool LUA_NATIVE_PAD_IS_CONTROL_RELEASED(int control, int action)
	{
		auto retval = (bool)PAD::IS_CONTROL_RELEASED(control, action);
		return retval;
	}

	static bool LUA_NATIVE_PAD_IS_CONTROL_JUST_PRESSED(int control, int action)
	{
		auto retval = (bool)PAD::IS_CONTROL_JUST_PRESSED(control, action);
		return retval;
	}

	static bool LUA_NATIVE_PAD_IS_CONTROL_JUST_RELEASED(int control, int action)
	{
		auto retval = (bool)PAD::IS_CONTROL_JUST_RELEASED(control, action);
		return retval;
	}

	static int LUA_NATIVE_PAD_GET_CONTROL_VALUE(int control, int action)
	{
		auto retval = PAD::GET_CONTROL_VALUE(control, action);
		return retval;
	}

	static float LUA_NATIVE_PAD_GET_CONTROL_NORMAL(int control, int action)
	{
		auto retval = PAD::GET_CONTROL_NORMAL(control, action);
		return retval;
	}

	static void LUA_NATIVE_PAD_SET_USE_ADJUSTED_MOUSE_COORDS(bool toggle)
	{
		PAD::SET_USE_ADJUSTED_MOUSE_COORDS(toggle);
	}

	static float LUA_NATIVE_PAD_GET_CONTROL_UNBOUND_NORMAL(int control, int action)
	{
		auto retval = PAD::GET_CONTROL_UNBOUND_NORMAL(control, action);
		return retval;
	}

	static bool LUA_NATIVE_PAD_SET_CONTROL_VALUE_NEXT_FRAME(int control, int action, float value)
	{
		auto retval = (bool)PAD::SET_CONTROL_VALUE_NEXT_FRAME(control, action, value);
		return retval;
	}

	static bool LUA_NATIVE_PAD_IS_DISABLED_CONTROL_PRESSED(int control, int action)
	{
		auto retval = (bool)PAD::IS_DISABLED_CONTROL_PRESSED(control, action);
		return retval;
	}

	static bool LUA_NATIVE_PAD_IS_DISABLED_CONTROL_RELEASED(int control, int action)
	{
		auto retval = (bool)PAD::IS_DISABLED_CONTROL_RELEASED(control, action);
		return retval;
	}

	static bool LUA_NATIVE_PAD_IS_DISABLED_CONTROL_JUST_PRESSED(int control, int action)
	{
		auto retval = (bool)PAD::IS_DISABLED_CONTROL_JUST_PRESSED(control, action);
		return retval;
	}

	static bool LUA_NATIVE_PAD_IS_DISABLED_CONTROL_JUST_RELEASED(int control, int action)
	{
		auto retval = (bool)PAD::IS_DISABLED_CONTROL_JUST_RELEASED(control, action);
		return retval;
	}

	static float LUA_NATIVE_PAD_GET_DISABLED_CONTROL_NORMAL(int control, int action)
	{
		auto retval = PAD::GET_DISABLED_CONTROL_NORMAL(control, action);
		return retval;
	}

	static float LUA_NATIVE_PAD_GET_DISABLED_CONTROL_UNBOUND_NORMAL(int control, int action)
	{
		auto retval = PAD::GET_DISABLED_CONTROL_UNBOUND_NORMAL(control, action);
		return retval;
	}

	static int LUA_NATIVE_PAD_GET_CONTROL_HOW_LONG_AGO(int control)
	{
		auto retval = PAD::GET_CONTROL_HOW_LONG_AGO(control);
		return retval;
	}

	static bool LUA_NATIVE_PAD_IS_USING_KEYBOARD_AND_MOUSE(int control)
	{
		auto retval = (bool)PAD::IS_USING_KEYBOARD_AND_MOUSE(control);
		return retval;
	}

	static bool LUA_NATIVE_PAD_IS_USING_CURSOR(int control)
	{
		auto retval = (bool)PAD::IS_USING_CURSOR(control);
		return retval;
	}

	static bool LUA_NATIVE_PAD_SET_CURSOR_POSITION(float x, float y)
	{
		auto retval = (bool)PAD::SET_CURSOR_POSITION(x, y);
		return retval;
	}

	static bool LUA_NATIVE_PAD_IS_USING_REMOTE_PLAY(int control)
	{
		auto retval = (bool)PAD::IS_USING_REMOTE_PLAY(control);
		return retval;
	}

	static bool LUA_NATIVE_PAD_HAVE_CONTROLS_CHANGED(int control)
	{
		auto retval = (bool)PAD::HAVE_CONTROLS_CHANGED(control);
		return retval;
	}

	static const char* LUA_NATIVE_PAD_GET_CONTROL_INSTRUCTIONAL_BUTTONS_STRING(int control, int action, bool allowXOSwap)
	{
		auto retval = PAD::GET_CONTROL_INSTRUCTIONAL_BUTTONS_STRING(control, action, allowXOSwap);
		return retval;
	}

	static const char* LUA_NATIVE_PAD_GET_CONTROL_GROUP_INSTRUCTIONAL_BUTTONS_STRING(int control, int controlGroup, bool allowXOSwap)
	{
		auto retval = PAD::GET_CONTROL_GROUP_INSTRUCTIONAL_BUTTONS_STRING(control, controlGroup, allowXOSwap);
		return retval;
	}

	static void LUA_NATIVE_PAD_SET_CONTROL_LIGHT_EFFECT_COLOR(int control, int red, int green, int blue)
	{
		PAD::SET_CONTROL_LIGHT_EFFECT_COLOR(control, red, green, blue);
	}

	static void LUA_NATIVE_PAD_CLEAR_CONTROL_LIGHT_EFFECT(int control)
	{
		PAD::CLEAR_CONTROL_LIGHT_EFFECT(control);
	}

	static void LUA_NATIVE_PAD_SET_CONTROL_SHAKE(int control, int duration, int frequency)
	{
		PAD::SET_CONTROL_SHAKE(control, duration, frequency);
	}

	static void LUA_NATIVE_PAD_SET_CONTROL_TRIGGER_SHAKE(int control, int leftDuration, int leftFrequency, int rightDuration, int rightFrequency)
	{
		PAD::SET_CONTROL_TRIGGER_SHAKE(control, leftDuration, leftFrequency, rightDuration, rightFrequency);
	}

	static void LUA_NATIVE_PAD_STOP_CONTROL_SHAKE(int control)
	{
		PAD::STOP_CONTROL_SHAKE(control);
	}

	static void LUA_NATIVE_PAD_SET_CONTROL_SHAKE_SUPPRESSED_ID(int control, int uniqueId)
	{
		PAD::SET_CONTROL_SHAKE_SUPPRESSED_ID(control, uniqueId);
	}

	static void LUA_NATIVE_PAD_CLEAR_CONTROL_SHAKE_SUPPRESSED_ID(int control)
	{
		PAD::CLEAR_CONTROL_SHAKE_SUPPRESSED_ID(control);
	}

	static bool LUA_NATIVE_PAD_IS_LOOK_INVERTED()
	{
		auto retval = (bool)PAD::IS_LOOK_INVERTED();
		return retval;
	}

	static bool LUA_NATIVE_PAD_IS_MOUSE_LOOK_INVERTED()
	{
		auto retval = (bool)PAD::IS_MOUSE_LOOK_INVERTED();
		return retval;
	}

	static int LUA_NATIVE_PAD_GET_LOCAL_PLAYER_AIM_STATE()
	{
		auto retval = PAD::GET_LOCAL_PLAYER_AIM_STATE();
		return retval;
	}

	static int LUA_NATIVE_PAD_GET_LOCAL_PLAYER_GAMEPAD_AIM_STATE()
	{
		auto retval = PAD::GET_LOCAL_PLAYER_GAMEPAD_AIM_STATE();
		return retval;
	}

	static bool LUA_NATIVE_PAD_GET_IS_USING_ALTERNATE_HANDBRAKE()
	{
		auto retval = (bool)PAD::GET_IS_USING_ALTERNATE_HANDBRAKE();
		return retval;
	}

	static bool LUA_NATIVE_PAD_GET_IS_USING_ALTERNATE_DRIVEBY()
	{
		auto retval = (bool)PAD::GET_IS_USING_ALTERNATE_DRIVEBY();
		return retval;
	}

	static bool LUA_NATIVE_PAD_GET_ALLOW_MOVEMENT_WHILE_ZOOMED()
	{
		auto retval = (bool)PAD::GET_ALLOW_MOVEMENT_WHILE_ZOOMED();
		return retval;
	}

	static void LUA_NATIVE_PAD_SET_PLAYERPAD_SHAKES_WHEN_CONTROLLER_DISABLED(bool toggle)
	{
		PAD::SET_PLAYERPAD_SHAKES_WHEN_CONTROLLER_DISABLED(toggle);
	}

	static void LUA_NATIVE_PAD_SET_INPUT_EXCLUSIVE(int control, int action)
	{
		PAD::SET_INPUT_EXCLUSIVE(control, action);
	}

	static void LUA_NATIVE_PAD_DISABLE_CONTROL_ACTION(int control, int action, bool disableRelatedActions)
	{
		PAD::DISABLE_CONTROL_ACTION(control, action, disableRelatedActions);
	}

	static void LUA_NATIVE_PAD_ENABLE_CONTROL_ACTION(int control, int action, bool enableRelatedActions)
	{
		PAD::ENABLE_CONTROL_ACTION(control, action, enableRelatedActions);
	}

	static void LUA_NATIVE_PAD_DISABLE_ALL_CONTROL_ACTIONS(int control)
	{
		PAD::DISABLE_ALL_CONTROL_ACTIONS(control);
	}

	static void LUA_NATIVE_PAD_ENABLE_ALL_CONTROL_ACTIONS(int control)
	{
		PAD::ENABLE_ALL_CONTROL_ACTIONS(control);
	}

	static bool LUA_NATIVE_PAD_INIT_PC_SCRIPTED_CONTROLS(sol::stack_object schemeName)
	{
		auto retval = (bool)PAD::INIT_PC_SCRIPTED_CONTROLS(schemeName.is<const char*>() ? schemeName.as<const char*>() : nullptr);
		return retval;
	}

	static bool LUA_NATIVE_PAD_SWITCH_PC_SCRIPTED_CONTROLS(sol::stack_object schemeName)
	{
		auto retval = (bool)PAD::SWITCH_PC_SCRIPTED_CONTROLS(schemeName.is<const char*>() ? schemeName.as<const char*>() : nullptr);
		return retval;
	}

	static void LUA_NATIVE_PAD_SHUTDOWN_PC_SCRIPTED_CONTROLS()
	{
		PAD::SHUTDOWN_PC_SCRIPTED_CONTROLS();
	}

	static void LUA_NATIVE_PAD_ALLOW_ALTERNATIVE_SCRIPT_CONTROLS_LAYOUT(int control)
	{
		PAD::ALLOW_ALTERNATIVE_SCRIPT_CONTROLS_LAYOUT(control);
	}

	void init_native_binding_PAD(sol::state& L)
	{
		auto PAD = L["PAD"].get_or_create<sol::table>();
		PAD.set_function("IS_CONTROL_ENABLED", LUA_NATIVE_PAD_IS_CONTROL_ENABLED);
		PAD.set_function("IS_CONTROL_PRESSED", LUA_NATIVE_PAD_IS_CONTROL_PRESSED);
		PAD.set_function("IS_CONTROL_RELEASED", LUA_NATIVE_PAD_IS_CONTROL_RELEASED);
		PAD.set_function("IS_CONTROL_JUST_PRESSED", LUA_NATIVE_PAD_IS_CONTROL_JUST_PRESSED);
		PAD.set_function("IS_CONTROL_JUST_RELEASED", LUA_NATIVE_PAD_IS_CONTROL_JUST_RELEASED);
		PAD.set_function("GET_CONTROL_VALUE", LUA_NATIVE_PAD_GET_CONTROL_VALUE);
		PAD.set_function("GET_CONTROL_NORMAL", LUA_NATIVE_PAD_GET_CONTROL_NORMAL);
		PAD.set_function("SET_USE_ADJUSTED_MOUSE_COORDS", LUA_NATIVE_PAD_SET_USE_ADJUSTED_MOUSE_COORDS);
		PAD.set_function("GET_CONTROL_UNBOUND_NORMAL", LUA_NATIVE_PAD_GET_CONTROL_UNBOUND_NORMAL);
		PAD.set_function("SET_CONTROL_VALUE_NEXT_FRAME", LUA_NATIVE_PAD_SET_CONTROL_VALUE_NEXT_FRAME);
		PAD.set_function("IS_DISABLED_CONTROL_PRESSED", LUA_NATIVE_PAD_IS_DISABLED_CONTROL_PRESSED);
		PAD.set_function("IS_DISABLED_CONTROL_RELEASED", LUA_NATIVE_PAD_IS_DISABLED_CONTROL_RELEASED);
		PAD.set_function("IS_DISABLED_CONTROL_JUST_PRESSED", LUA_NATIVE_PAD_IS_DISABLED_CONTROL_JUST_PRESSED);
		PAD.set_function("IS_DISABLED_CONTROL_JUST_RELEASED", LUA_NATIVE_PAD_IS_DISABLED_CONTROL_JUST_RELEASED);
		PAD.set_function("GET_DISABLED_CONTROL_NORMAL", LUA_NATIVE_PAD_GET_DISABLED_CONTROL_NORMAL);
		PAD.set_function("GET_DISABLED_CONTROL_UNBOUND_NORMAL", LUA_NATIVE_PAD_GET_DISABLED_CONTROL_UNBOUND_NORMAL);
		PAD.set_function("GET_CONTROL_HOW_LONG_AGO", LUA_NATIVE_PAD_GET_CONTROL_HOW_LONG_AGO);
		PAD.set_function("IS_USING_KEYBOARD_AND_MOUSE", LUA_NATIVE_PAD_IS_USING_KEYBOARD_AND_MOUSE);
		PAD.set_function("IS_USING_CURSOR", LUA_NATIVE_PAD_IS_USING_CURSOR);
		PAD.set_function("SET_CURSOR_POSITION", LUA_NATIVE_PAD_SET_CURSOR_POSITION);
		PAD.set_function("IS_USING_REMOTE_PLAY", LUA_NATIVE_PAD_IS_USING_REMOTE_PLAY);
		PAD.set_function("HAVE_CONTROLS_CHANGED", LUA_NATIVE_PAD_HAVE_CONTROLS_CHANGED);
		PAD.set_function("GET_CONTROL_INSTRUCTIONAL_BUTTONS_STRING", LUA_NATIVE_PAD_GET_CONTROL_INSTRUCTIONAL_BUTTONS_STRING);
		PAD.set_function("GET_CONTROL_GROUP_INSTRUCTIONAL_BUTTONS_STRING", LUA_NATIVE_PAD_GET_CONTROL_GROUP_INSTRUCTIONAL_BUTTONS_STRING);
		PAD.set_function("SET_CONTROL_LIGHT_EFFECT_COLOR", LUA_NATIVE_PAD_SET_CONTROL_LIGHT_EFFECT_COLOR);
		PAD.set_function("CLEAR_CONTROL_LIGHT_EFFECT", LUA_NATIVE_PAD_CLEAR_CONTROL_LIGHT_EFFECT);
		PAD.set_function("SET_CONTROL_SHAKE", LUA_NATIVE_PAD_SET_CONTROL_SHAKE);
		PAD.set_function("SET_CONTROL_TRIGGER_SHAKE", LUA_NATIVE_PAD_SET_CONTROL_TRIGGER_SHAKE);
		PAD.set_function("STOP_CONTROL_SHAKE", LUA_NATIVE_PAD_STOP_CONTROL_SHAKE);
		PAD.set_function("SET_CONTROL_SHAKE_SUPPRESSED_ID", LUA_NATIVE_PAD_SET_CONTROL_SHAKE_SUPPRESSED_ID);
		PAD.set_function("CLEAR_CONTROL_SHAKE_SUPPRESSED_ID", LUA_NATIVE_PAD_CLEAR_CONTROL_SHAKE_SUPPRESSED_ID);
		PAD.set_function("IS_LOOK_INVERTED", LUA_NATIVE_PAD_IS_LOOK_INVERTED);
		PAD.set_function("IS_MOUSE_LOOK_INVERTED", LUA_NATIVE_PAD_IS_MOUSE_LOOK_INVERTED);
		PAD.set_function("GET_LOCAL_PLAYER_AIM_STATE", LUA_NATIVE_PAD_GET_LOCAL_PLAYER_AIM_STATE);
		PAD.set_function("GET_LOCAL_PLAYER_GAMEPAD_AIM_STATE", LUA_NATIVE_PAD_GET_LOCAL_PLAYER_GAMEPAD_AIM_STATE);
		PAD.set_function("GET_IS_USING_ALTERNATE_HANDBRAKE", LUA_NATIVE_PAD_GET_IS_USING_ALTERNATE_HANDBRAKE);
		PAD.set_function("GET_IS_USING_ALTERNATE_DRIVEBY", LUA_NATIVE_PAD_GET_IS_USING_ALTERNATE_DRIVEBY);
		PAD.set_function("GET_ALLOW_MOVEMENT_WHILE_ZOOMED", LUA_NATIVE_PAD_GET_ALLOW_MOVEMENT_WHILE_ZOOMED);
		PAD.set_function("SET_PLAYERPAD_SHAKES_WHEN_CONTROLLER_DISABLED", LUA_NATIVE_PAD_SET_PLAYERPAD_SHAKES_WHEN_CONTROLLER_DISABLED);
		PAD.set_function("SET_INPUT_EXCLUSIVE", LUA_NATIVE_PAD_SET_INPUT_EXCLUSIVE);
		PAD.set_function("DISABLE_CONTROL_ACTION", LUA_NATIVE_PAD_DISABLE_CONTROL_ACTION);
		PAD.set_function("ENABLE_CONTROL_ACTION", LUA_NATIVE_PAD_ENABLE_CONTROL_ACTION);
		PAD.set_function("DISABLE_ALL_CONTROL_ACTIONS", LUA_NATIVE_PAD_DISABLE_ALL_CONTROL_ACTIONS);
		PAD.set_function("ENABLE_ALL_CONTROL_ACTIONS", LUA_NATIVE_PAD_ENABLE_ALL_CONTROL_ACTIONS);
		PAD.set_function("INIT_PC_SCRIPTED_CONTROLS", LUA_NATIVE_PAD_INIT_PC_SCRIPTED_CONTROLS);
		PAD.set_function("SWITCH_PC_SCRIPTED_CONTROLS", LUA_NATIVE_PAD_SWITCH_PC_SCRIPTED_CONTROLS);
		PAD.set_function("SHUTDOWN_PC_SCRIPTED_CONTROLS", LUA_NATIVE_PAD_SHUTDOWN_PC_SCRIPTED_CONTROLS);
		PAD.set_function("ALLOW_ALTERNATIVE_SCRIPT_CONTROLS_LAYOUT", LUA_NATIVE_PAD_ALLOW_ALTERNATIVE_SCRIPT_CONTROLS_LAYOUT);
	}
}
