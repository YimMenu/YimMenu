#include "lua_native_binding.hpp"
#include "natives.hpp"

namespace lua::native
{
	static void LUA_NATIVE_HUD_BEGIN_TEXT_COMMAND_BUSYSPINNER_ON(sol::stack_object string)
	{
		HUD::BEGIN_TEXT_COMMAND_BUSYSPINNER_ON(string.is<const char*>() ? string.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_HUD_END_TEXT_COMMAND_BUSYSPINNER_ON(int busySpinnerType)
	{
		HUD::END_TEXT_COMMAND_BUSYSPINNER_ON(busySpinnerType);
	}

	static void LUA_NATIVE_HUD_BUSYSPINNER_OFF()
	{
		HUD::BUSYSPINNER_OFF();
	}

	static void LUA_NATIVE_HUD_PRELOAD_BUSYSPINNER()
	{
		HUD::PRELOAD_BUSYSPINNER();
	}

	static bool LUA_NATIVE_HUD_BUSYSPINNER_IS_ON()
	{
		auto retval = (bool)HUD::BUSYSPINNER_IS_ON();
		return retval;
	}

	static bool LUA_NATIVE_HUD_BUSYSPINNER_IS_DISPLAYING()
	{
		auto retval = (bool)HUD::BUSYSPINNER_IS_DISPLAYING();
		return retval;
	}

	static void LUA_NATIVE_HUD_DISABLE_PAUSEMENU_SPINNER(bool p0)
	{
		HUD::DISABLE_PAUSEMENU_SPINNER(p0);
	}

	static void LUA_NATIVE_HUD_SET_MOUSE_CURSOR_THIS_FRAME()
	{
		HUD::SET_MOUSE_CURSOR_THIS_FRAME();
	}

	static void LUA_NATIVE_HUD_SET_MOUSE_CURSOR_STYLE(int spriteId)
	{
		HUD::SET_MOUSE_CURSOR_STYLE(spriteId);
	}

	static void LUA_NATIVE_HUD_SET_MOUSE_CURSOR_VISIBLE(bool toggle)
	{
		HUD::SET_MOUSE_CURSOR_VISIBLE(toggle);
	}

	static bool LUA_NATIVE_HUD_IS_MOUSE_ROLLED_OVER_INSTRUCTIONAL_BUTTONS()
	{
		auto retval = (bool)HUD::IS_MOUSE_ROLLED_OVER_INSTRUCTIONAL_BUTTONS();
		return retval;
	}

	static bool LUA_NATIVE_HUD_GET_MOUSE_EVENT(int scaleformHandle, uintptr_t p1, uintptr_t p2, uintptr_t p3)
	{
		auto retval = (bool)HUD::GET_MOUSE_EVENT(scaleformHandle, (Any*)p1, (Any*)p2, (Any*)p3);
		return retval;
	}

	static void LUA_NATIVE_HUD_THEFEED_ONLY_SHOW_TOOLTIPS(bool toggle)
	{
		HUD::THEFEED_ONLY_SHOW_TOOLTIPS(toggle);
	}

	static void LUA_NATIVE_HUD_THEFEED_SET_SCRIPTED_MENU_HEIGHT(float pos)
	{
		HUD::THEFEED_SET_SCRIPTED_MENU_HEIGHT(pos);
	}

	static void LUA_NATIVE_HUD_THEFEED_HIDE()
	{
		HUD::THEFEED_HIDE();
	}

	static void LUA_NATIVE_HUD_THEFEED_HIDE_THIS_FRAME()
	{
		HUD::THEFEED_HIDE_THIS_FRAME();
	}

	static void LUA_NATIVE_HUD_THEFEED_SHOW()
	{
		HUD::THEFEED_SHOW();
	}

	static void LUA_NATIVE_HUD_THEFEED_FLUSH_QUEUE()
	{
		HUD::THEFEED_FLUSH_QUEUE();
	}

	static void LUA_NATIVE_HUD_THEFEED_REMOVE_ITEM(int notificationId)
	{
		HUD::THEFEED_REMOVE_ITEM(notificationId);
	}

	static void LUA_NATIVE_HUD_THEFEED_FORCE_RENDER_ON()
	{
		HUD::THEFEED_FORCE_RENDER_ON();
	}

	static void LUA_NATIVE_HUD_THEFEED_FORCE_RENDER_OFF()
	{
		HUD::THEFEED_FORCE_RENDER_OFF();
	}

	static void LUA_NATIVE_HUD_THEFEED_PAUSE()
	{
		HUD::THEFEED_PAUSE();
	}

	static void LUA_NATIVE_HUD_THEFEED_RESUME()
	{
		HUD::THEFEED_RESUME();
	}

	static bool LUA_NATIVE_HUD_THEFEED_IS_PAUSED()
	{
		auto retval = (bool)HUD::THEFEED_IS_PAUSED();
		return retval;
	}

	static void LUA_NATIVE_HUD_THEFEED_REPORT_LOGO_ON()
	{
		HUD::THEFEED_REPORT_LOGO_ON();
	}

	static void LUA_NATIVE_HUD_THEFEED_REPORT_LOGO_OFF()
	{
		HUD::THEFEED_REPORT_LOGO_OFF();
	}

	static int LUA_NATIVE_HUD_THEFEED_GET_LAST_SHOWN_PHONE_ACTIVATABLE_FEED_ID()
	{
		auto retval = HUD::THEFEED_GET_LAST_SHOWN_PHONE_ACTIVATABLE_FEED_ID();
		return retval;
	}

	static void LUA_NATIVE_HUD_THEFEED_AUTO_POST_GAMETIPS_ON()
	{
		HUD::THEFEED_AUTO_POST_GAMETIPS_ON();
	}

	static void LUA_NATIVE_HUD_THEFEED_AUTO_POST_GAMETIPS_OFF()
	{
		HUD::THEFEED_AUTO_POST_GAMETIPS_OFF();
	}

	static void LUA_NATIVE_HUD_THEFEED_SET_BACKGROUND_COLOR_FOR_NEXT_POST(int hudColorIndex)
	{
		HUD::THEFEED_SET_BACKGROUND_COLOR_FOR_NEXT_POST(hudColorIndex);
	}

	static void LUA_NATIVE_HUD_THEFEED_SET_RGBA_PARAMETER_FOR_NEXT_MESSAGE(int red, int green, int blue, int alpha)
	{
		HUD::THEFEED_SET_RGBA_PARAMETER_FOR_NEXT_MESSAGE(red, green, blue, alpha);
	}

	static void LUA_NATIVE_HUD_THEFEED_SET_FLASH_DURATION_PARAMETER_FOR_NEXT_MESSAGE(int count)
	{
		HUD::THEFEED_SET_FLASH_DURATION_PARAMETER_FOR_NEXT_MESSAGE(count);
	}

	static void LUA_NATIVE_HUD_THEFEED_SET_VIBRATE_PARAMETER_FOR_NEXT_MESSAGE(bool toggle)
	{
		HUD::THEFEED_SET_VIBRATE_PARAMETER_FOR_NEXT_MESSAGE(toggle);
	}

	static void LUA_NATIVE_HUD_THEFEED_RESET_ALL_PARAMETERS()
	{
		HUD::THEFEED_RESET_ALL_PARAMETERS();
	}

	static void LUA_NATIVE_HUD_THEFEED_FREEZE_NEXT_POST()
	{
		HUD::THEFEED_FREEZE_NEXT_POST();
	}

	static void LUA_NATIVE_HUD_THEFEED_CLEAR_FROZEN_POST()
	{
		HUD::THEFEED_CLEAR_FROZEN_POST();
	}

	static void LUA_NATIVE_HUD_THEFEED_SET_SNAP_FEED_ITEM_POSITIONS(bool p0)
	{
		HUD::THEFEED_SET_SNAP_FEED_ITEM_POSITIONS(p0);
	}

	static void LUA_NATIVE_HUD_THEFEED_UPDATE_ITEM_TEXTURE(sol::stack_object txdString1, sol::stack_object txnString1, sol::stack_object txdString2, sol::stack_object txnString2)
	{
		HUD::THEFEED_UPDATE_ITEM_TEXTURE(txdString1.is<const char*>() ? txdString1.as<const char*>() : nullptr, txnString1.is<const char*>() ? txnString1.as<const char*>() : nullptr, txdString2.is<const char*>() ? txdString2.as<const char*>() : nullptr, txnString2.is<const char*>() ? txnString2.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_HUD_BEGIN_TEXT_COMMAND_THEFEED_POST(sol::stack_object text)
	{
		HUD::BEGIN_TEXT_COMMAND_THEFEED_POST(text.is<const char*>() ? text.as<const char*>() : nullptr);
	}

	static int LUA_NATIVE_HUD_END_TEXT_COMMAND_THEFEED_POST_STATS(sol::stack_object statTitle, int iconEnum, bool stepVal, int barValue, bool isImportant, sol::stack_object pictureTextureDict, sol::stack_object pictureTextureName)
	{
		auto retval = HUD::END_TEXT_COMMAND_THEFEED_POST_STATS(statTitle.is<const char*>() ? statTitle.as<const char*>() : nullptr, iconEnum, stepVal, barValue, isImportant, pictureTextureDict.is<const char*>() ? pictureTextureDict.as<const char*>() : nullptr, pictureTextureName.is<const char*>() ? pictureTextureName.as<const char*>() : nullptr);
		return retval;
	}

	static int LUA_NATIVE_HUD_END_TEXT_COMMAND_THEFEED_POST_MESSAGETEXT(sol::stack_object txdName, sol::stack_object textureName, bool flash, int iconType, sol::stack_object sender, sol::stack_object subject)
	{
		auto retval = HUD::END_TEXT_COMMAND_THEFEED_POST_MESSAGETEXT(txdName.is<const char*>() ? txdName.as<const char*>() : nullptr, textureName.is<const char*>() ? textureName.as<const char*>() : nullptr, flash, iconType, sender.is<const char*>() ? sender.as<const char*>() : nullptr, subject.is<const char*>() ? subject.as<const char*>() : nullptr);
		return retval;
	}

	static int LUA_NATIVE_HUD_END_TEXT_COMMAND_THEFEED_POST_MESSAGETEXT_SUBTITLE_LABEL(sol::stack_object txdName, sol::stack_object textureName, bool flash, int iconType, sol::stack_object sender, sol::stack_object subject)
	{
		auto retval = HUD::END_TEXT_COMMAND_THEFEED_POST_MESSAGETEXT_SUBTITLE_LABEL(txdName.is<const char*>() ? txdName.as<const char*>() : nullptr, textureName.is<const char*>() ? textureName.as<const char*>() : nullptr, flash, iconType, sender.is<const char*>() ? sender.as<const char*>() : nullptr, subject.is<const char*>() ? subject.as<const char*>() : nullptr);
		return retval;
	}

	static int LUA_NATIVE_HUD_END_TEXT_COMMAND_THEFEED_POST_MESSAGETEXT_TU(sol::stack_object txdName, sol::stack_object textureName, bool flash, int iconType, sol::stack_object sender, sol::stack_object subject, float duration)
	{
		auto retval = HUD::END_TEXT_COMMAND_THEFEED_POST_MESSAGETEXT_TU(txdName.is<const char*>() ? txdName.as<const char*>() : nullptr, textureName.is<const char*>() ? textureName.as<const char*>() : nullptr, flash, iconType, sender.is<const char*>() ? sender.as<const char*>() : nullptr, subject.is<const char*>() ? subject.as<const char*>() : nullptr, duration);
		return retval;
	}

	static int LUA_NATIVE_HUD_END_TEXT_COMMAND_THEFEED_POST_MESSAGETEXT_WITH_CREW_TAG(sol::stack_object txdName, sol::stack_object textureName, bool flash, int iconType, sol::stack_object sender, sol::stack_object subject, float duration, sol::stack_object clanTag)
	{
		auto retval = HUD::END_TEXT_COMMAND_THEFEED_POST_MESSAGETEXT_WITH_CREW_TAG(txdName.is<const char*>() ? txdName.as<const char*>() : nullptr, textureName.is<const char*>() ? textureName.as<const char*>() : nullptr, flash, iconType, sender.is<const char*>() ? sender.as<const char*>() : nullptr, subject.is<const char*>() ? subject.as<const char*>() : nullptr, duration, clanTag.is<const char*>() ? clanTag.as<const char*>() : nullptr);
		return retval;
	}

	static int LUA_NATIVE_HUD_END_TEXT_COMMAND_THEFEED_POST_MESSAGETEXT_WITH_CREW_TAG_AND_ADDITIONAL_ICON(sol::stack_object txdName, sol::stack_object textureName, bool flash, int iconType1, sol::stack_object sender, sol::stack_object subject, float duration, sol::stack_object clanTag, int iconType2, int p9)
	{
		auto retval = HUD::END_TEXT_COMMAND_THEFEED_POST_MESSAGETEXT_WITH_CREW_TAG_AND_ADDITIONAL_ICON(txdName.is<const char*>() ? txdName.as<const char*>() : nullptr, textureName.is<const char*>() ? textureName.as<const char*>() : nullptr, flash, iconType1, sender.is<const char*>() ? sender.as<const char*>() : nullptr, subject.is<const char*>() ? subject.as<const char*>() : nullptr, duration, clanTag.is<const char*>() ? clanTag.as<const char*>() : nullptr, iconType2, p9);
		return retval;
	}

	static int LUA_NATIVE_HUD_END_TEXT_COMMAND_THEFEED_POST_TICKER(bool blink, bool p1)
	{
		auto retval = HUD::END_TEXT_COMMAND_THEFEED_POST_TICKER(blink, p1);
		return retval;
	}

	static int LUA_NATIVE_HUD_END_TEXT_COMMAND_THEFEED_POST_TICKER_FORCED(bool blink, bool p1)
	{
		auto retval = HUD::END_TEXT_COMMAND_THEFEED_POST_TICKER_FORCED(blink, p1);
		return retval;
	}

	static int LUA_NATIVE_HUD_END_TEXT_COMMAND_THEFEED_POST_TICKER_WITH_TOKENS(bool blink, bool p1)
	{
		auto retval = HUD::END_TEXT_COMMAND_THEFEED_POST_TICKER_WITH_TOKENS(blink, p1);
		return retval;
	}

	static int LUA_NATIVE_HUD_END_TEXT_COMMAND_THEFEED_POST_AWARD(sol::stack_object textureDict, sol::stack_object textureName, int rpBonus, int colorOverlay, sol::stack_object titleLabel)
	{
		auto retval = HUD::END_TEXT_COMMAND_THEFEED_POST_AWARD(textureDict.is<const char*>() ? textureDict.as<const char*>() : nullptr, textureName.is<const char*>() ? textureName.as<const char*>() : nullptr, rpBonus, colorOverlay, titleLabel.is<const char*>() ? titleLabel.as<const char*>() : nullptr);
		return retval;
	}

	static std::tuple<int, int> LUA_NATIVE_HUD_END_TEXT_COMMAND_THEFEED_POST_CREWTAG(bool p0, bool p1, int p2, int p3, bool isLeader, bool unk0, int clanDesc, int R, int G, int B)
	{
		std::tuple<int, int> return_values;
		std::get<0>(return_values) = HUD::END_TEXT_COMMAND_THEFEED_POST_CREWTAG(p0, p1, &p2, p3, isLeader, unk0, clanDesc, R, G, B);
		std::get<1>(return_values) = p2;

		return return_values;
	}

	static std::tuple<int, int> LUA_NATIVE_HUD_END_TEXT_COMMAND_THEFEED_POST_CREWTAG_WITH_GAME_NAME(bool p0, bool p1, int p2, int p3, bool isLeader, bool unk0, int clanDesc, sol::stack_object playerName, int R, int G, int B)
	{
		std::tuple<int, int> return_values;
		std::get<0>(return_values) = HUD::END_TEXT_COMMAND_THEFEED_POST_CREWTAG_WITH_GAME_NAME(p0, p1, &p2, p3, isLeader, unk0, clanDesc, playerName.is<const char*>() ? playerName.as<const char*>() : nullptr, R, G, B);
		std::get<1>(return_values) = p2;

		return return_values;
	}

	static int LUA_NATIVE_HUD_END_TEXT_COMMAND_THEFEED_POST_UNLOCK(sol::stack_object gxtLabel1, int p1, sol::stack_object gxtLabel2)
	{
		auto retval = HUD::END_TEXT_COMMAND_THEFEED_POST_UNLOCK(gxtLabel1.is<const char*>() ? gxtLabel1.as<const char*>() : nullptr, p1, gxtLabel2.is<const char*>() ? gxtLabel2.as<const char*>() : nullptr);
		return retval;
	}

	static int LUA_NATIVE_HUD_END_TEXT_COMMAND_THEFEED_POST_UNLOCK_TU(sol::stack_object gxtLabel1, int p1, sol::stack_object gxtLabel2, int p3)
	{
		auto retval = HUD::END_TEXT_COMMAND_THEFEED_POST_UNLOCK_TU(gxtLabel1.is<const char*>() ? gxtLabel1.as<const char*>() : nullptr, p1, gxtLabel2.is<const char*>() ? gxtLabel2.as<const char*>() : nullptr, p3);
		return retval;
	}

	static int LUA_NATIVE_HUD_END_TEXT_COMMAND_THEFEED_POST_UNLOCK_TU_WITH_COLOR(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5)
	{
		auto retval = HUD::END_TEXT_COMMAND_THEFEED_POST_UNLOCK_TU_WITH_COLOR(p0, p1, p2, p3, p4, p5);
		return retval;
	}

	static int LUA_NATIVE_HUD_END_TEXT_COMMAND_THEFEED_POST_MPTICKER(bool blink, bool p1)
	{
		auto retval = HUD::END_TEXT_COMMAND_THEFEED_POST_MPTICKER(blink, p1);
		return retval;
	}

	static int LUA_NATIVE_HUD_END_TEXT_COMMAND_THEFEED_POST_CREW_RANKUP_WITH_LITERAL_FLAG(sol::stack_object p0, sol::stack_object p1, sol::stack_object p2, bool p3, bool p4)
	{
		auto retval = HUD::END_TEXT_COMMAND_THEFEED_POST_CREW_RANKUP_WITH_LITERAL_FLAG(p0.is<const char*>() ? p0.as<const char*>() : nullptr, p1.is<const char*>() ? p1.as<const char*>() : nullptr, p2.is<const char*>() ? p2.as<const char*>() : nullptr, p3, p4);
		return retval;
	}

	static int LUA_NATIVE_HUD_END_TEXT_COMMAND_THEFEED_POST_VERSUS_TU(sol::stack_object txdName1, sol::stack_object textureName1, int count1, sol::stack_object txdName2, sol::stack_object textureName2, int count2, int hudColor1, int hudColor2)
	{
		auto retval = HUD::END_TEXT_COMMAND_THEFEED_POST_VERSUS_TU(txdName1.is<const char*>() ? txdName1.as<const char*>() : nullptr, textureName1.is<const char*>() ? textureName1.as<const char*>() : nullptr, count1, txdName2.is<const char*>() ? txdName2.as<const char*>() : nullptr, textureName2.is<const char*>() ? textureName2.as<const char*>() : nullptr, count2, hudColor1, hudColor2);
		return retval;
	}

	static int LUA_NATIVE_HUD_END_TEXT_COMMAND_THEFEED_POST_REPLAY(int type, int image, sol::stack_object text)
	{
		auto retval = HUD::END_TEXT_COMMAND_THEFEED_POST_REPLAY(type, image, text.is<const char*>() ? text.as<const char*>() : nullptr);
		return retval;
	}

	static int LUA_NATIVE_HUD_END_TEXT_COMMAND_THEFEED_POST_REPLAY_INPUT(int type, sol::stack_object button, sol::stack_object text)
	{
		auto retval = HUD::END_TEXT_COMMAND_THEFEED_POST_REPLAY_INPUT(type, button.is<const char*>() ? button.as<const char*>() : nullptr, text.is<const char*>() ? text.as<const char*>() : nullptr);
		return retval;
	}

	static void LUA_NATIVE_HUD_BEGIN_TEXT_COMMAND_PRINT(sol::stack_object GxtEntry)
	{
		HUD::BEGIN_TEXT_COMMAND_PRINT(GxtEntry.is<const char*>() ? GxtEntry.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_HUD_END_TEXT_COMMAND_PRINT(int duration, bool drawImmediately)
	{
		HUD::END_TEXT_COMMAND_PRINT(duration, drawImmediately);
	}

	static void LUA_NATIVE_HUD_BEGIN_TEXT_COMMAND_IS_MESSAGE_DISPLAYED(sol::stack_object text)
	{
		HUD::BEGIN_TEXT_COMMAND_IS_MESSAGE_DISPLAYED(text.is<const char*>() ? text.as<const char*>() : nullptr);
	}

	static bool LUA_NATIVE_HUD_END_TEXT_COMMAND_IS_MESSAGE_DISPLAYED()
	{
		auto retval = (bool)HUD::END_TEXT_COMMAND_IS_MESSAGE_DISPLAYED();
		return retval;
	}

	static void LUA_NATIVE_HUD_BEGIN_TEXT_COMMAND_DISPLAY_TEXT(sol::stack_object text)
	{
		HUD::BEGIN_TEXT_COMMAND_DISPLAY_TEXT(text.is<const char*>() ? text.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_HUD_END_TEXT_COMMAND_DISPLAY_TEXT(float x, float y, int p2)
	{
		HUD::END_TEXT_COMMAND_DISPLAY_TEXT(x, y, p2);
	}

	static void LUA_NATIVE_HUD_BEGIN_TEXT_COMMAND_GET_SCREEN_WIDTH_OF_DISPLAY_TEXT(sol::stack_object text)
	{
		HUD::BEGIN_TEXT_COMMAND_GET_SCREEN_WIDTH_OF_DISPLAY_TEXT(text.is<const char*>() ? text.as<const char*>() : nullptr);
	}

	static float LUA_NATIVE_HUD_END_TEXT_COMMAND_GET_SCREEN_WIDTH_OF_DISPLAY_TEXT(bool p0)
	{
		auto retval = HUD::END_TEXT_COMMAND_GET_SCREEN_WIDTH_OF_DISPLAY_TEXT(p0);
		return retval;
	}

	static void LUA_NATIVE_HUD_BEGIN_TEXT_COMMAND_GET_NUMBER_OF_LINES_FOR_STRING(sol::stack_object entry)
	{
		HUD::BEGIN_TEXT_COMMAND_GET_NUMBER_OF_LINES_FOR_STRING(entry.is<const char*>() ? entry.as<const char*>() : nullptr);
	}

	static int LUA_NATIVE_HUD_END_TEXT_COMMAND_GET_NUMBER_OF_LINES_FOR_STRING(float x, float y)
	{
		auto retval = HUD::END_TEXT_COMMAND_GET_NUMBER_OF_LINES_FOR_STRING(x, y);
		return retval;
	}

	static void LUA_NATIVE_HUD_BEGIN_TEXT_COMMAND_DISPLAY_HELP(sol::stack_object inputType)
	{
		HUD::BEGIN_TEXT_COMMAND_DISPLAY_HELP(inputType.is<const char*>() ? inputType.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_HUD_END_TEXT_COMMAND_DISPLAY_HELP(int p0, bool loop, bool beep, int shape)
	{
		HUD::END_TEXT_COMMAND_DISPLAY_HELP(p0, loop, beep, shape);
	}

	static void LUA_NATIVE_HUD_BEGIN_TEXT_COMMAND_IS_THIS_HELP_MESSAGE_BEING_DISPLAYED(sol::stack_object labelName)
	{
		HUD::BEGIN_TEXT_COMMAND_IS_THIS_HELP_MESSAGE_BEING_DISPLAYED(labelName.is<const char*>() ? labelName.as<const char*>() : nullptr);
	}

	static bool LUA_NATIVE_HUD_END_TEXT_COMMAND_IS_THIS_HELP_MESSAGE_BEING_DISPLAYED(int p0)
	{
		auto retval = (bool)HUD::END_TEXT_COMMAND_IS_THIS_HELP_MESSAGE_BEING_DISPLAYED(p0);
		return retval;
	}

	static void LUA_NATIVE_HUD_BEGIN_TEXT_COMMAND_SET_BLIP_NAME(sol::stack_object textLabel)
	{
		HUD::BEGIN_TEXT_COMMAND_SET_BLIP_NAME(textLabel.is<const char*>() ? textLabel.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_HUD_END_TEXT_COMMAND_SET_BLIP_NAME(Blip blip)
	{
		HUD::END_TEXT_COMMAND_SET_BLIP_NAME(blip);
	}

	static void LUA_NATIVE_HUD_BEGIN_TEXT_COMMAND_ADD_DIRECTLY_TO_PREVIOUS_BRIEFS(sol::stack_object p0)
	{
		HUD::BEGIN_TEXT_COMMAND_ADD_DIRECTLY_TO_PREVIOUS_BRIEFS(p0.is<const char*>() ? p0.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_HUD_END_TEXT_COMMAND_ADD_DIRECTLY_TO_PREVIOUS_BRIEFS(bool p0)
	{
		HUD::END_TEXT_COMMAND_ADD_DIRECTLY_TO_PREVIOUS_BRIEFS(p0);
	}

	static void LUA_NATIVE_HUD_BEGIN_TEXT_COMMAND_CLEAR_PRINT(sol::stack_object text)
	{
		HUD::BEGIN_TEXT_COMMAND_CLEAR_PRINT(text.is<const char*>() ? text.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_HUD_END_TEXT_COMMAND_CLEAR_PRINT()
	{
		HUD::END_TEXT_COMMAND_CLEAR_PRINT();
	}

	static void LUA_NATIVE_HUD_BEGIN_TEXT_COMMAND_OVERRIDE_BUTTON_TEXT(sol::stack_object gxtEntry)
	{
		HUD::BEGIN_TEXT_COMMAND_OVERRIDE_BUTTON_TEXT(gxtEntry.is<const char*>() ? gxtEntry.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_HUD_END_TEXT_COMMAND_OVERRIDE_BUTTON_TEXT(int p0)
	{
		HUD::END_TEXT_COMMAND_OVERRIDE_BUTTON_TEXT(p0);
	}

	static void LUA_NATIVE_HUD_ADD_TEXT_COMPONENT_INTEGER(int value)
	{
		HUD::ADD_TEXT_COMPONENT_INTEGER(value);
	}

	static void LUA_NATIVE_HUD_ADD_TEXT_COMPONENT_FLOAT(float value, int decimalPlaces)
	{
		HUD::ADD_TEXT_COMPONENT_FLOAT(value, decimalPlaces);
	}

	static void LUA_NATIVE_HUD_ADD_TEXT_COMPONENT_SUBSTRING_TEXT_LABEL(sol::stack_object labelName)
	{
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_TEXT_LABEL(labelName.is<const char*>() ? labelName.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_HUD_ADD_TEXT_COMPONENT_SUBSTRING_TEXT_LABEL_HASH_KEY(Hash gxtEntryHash)
	{
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_TEXT_LABEL_HASH_KEY(gxtEntryHash);
	}

	static void LUA_NATIVE_HUD_ADD_TEXT_COMPONENT_SUBSTRING_BLIP_NAME(Blip blip)
	{
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_BLIP_NAME(blip);
	}

	static void LUA_NATIVE_HUD_ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(sol::stack_object text)
	{
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text.is<const char*>() ? text.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_HUD_ADD_TEXT_COMPONENT_SUBSTRING_TIME(int timestamp, int flags)
	{
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_TIME(timestamp, flags);
	}

	static void LUA_NATIVE_HUD_ADD_TEXT_COMPONENT_FORMATTED_INTEGER(int value, bool commaSeparated)
	{
		HUD::ADD_TEXT_COMPONENT_FORMATTED_INTEGER(value, commaSeparated);
	}

	static void LUA_NATIVE_HUD_ADD_TEXT_COMPONENT_SUBSTRING_PHONE_NUMBER(sol::stack_object p0, int p1)
	{
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PHONE_NUMBER(p0.is<const char*>() ? p0.as<const char*>() : nullptr, p1);
	}

	static void LUA_NATIVE_HUD_ADD_TEXT_COMPONENT_SUBSTRING_WEBSITE(sol::stack_object website)
	{
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_WEBSITE(website.is<const char*>() ? website.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_HUD_ADD_TEXT_COMPONENT_SUBSTRING_KEYBOARD_DISPLAY(sol::stack_object string)
	{
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_KEYBOARD_DISPLAY(string.is<const char*>() ? string.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_HUD_SET_COLOUR_OF_NEXT_TEXT_COMPONENT(int hudColor)
	{
		HUD::SET_COLOUR_OF_NEXT_TEXT_COMPONENT(hudColor);
	}

	static const char* LUA_NATIVE_HUD_GET_CHARACTER_FROM_AUDIO_CONVERSATION_FILENAME(sol::stack_object text, int position, int length)
	{
		auto retval = HUD::GET_CHARACTER_FROM_AUDIO_CONVERSATION_FILENAME(text.is<const char*>() ? text.as<const char*>() : nullptr, position, length);
		return retval;
	}

	static const char* LUA_NATIVE_HUD_GET_CHARACTER_FROM_AUDIO_CONVERSATION_FILENAME_WITH_BYTE_LIMIT(sol::stack_object text, int position, int length, int maxLength)
	{
		auto retval = HUD::GET_CHARACTER_FROM_AUDIO_CONVERSATION_FILENAME_WITH_BYTE_LIMIT(text.is<const char*>() ? text.as<const char*>() : nullptr, position, length, maxLength);
		return retval;
	}

	static const char* LUA_NATIVE_HUD_GET_CHARACTER_FROM_AUDIO_CONVERSATION_FILENAME_BYTES(sol::stack_object text, int startPosition, int endPosition)
	{
		auto retval = HUD::GET_CHARACTER_FROM_AUDIO_CONVERSATION_FILENAME_BYTES(text.is<const char*>() ? text.as<const char*>() : nullptr, startPosition, endPosition);
		return retval;
	}

	static const char* LUA_NATIVE_HUD_GET_FILENAME_FOR_AUDIO_CONVERSATION(sol::stack_object labelName)
	{
		auto retval = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(labelName.is<const char*>() ? labelName.as<const char*>() : nullptr);
		return retval;
	}

	static void LUA_NATIVE_HUD_CLEAR_PRINTS()
	{
		HUD::CLEAR_PRINTS();
	}

	static void LUA_NATIVE_HUD_CLEAR_BRIEF()
	{
		HUD::CLEAR_BRIEF();
	}

	static void LUA_NATIVE_HUD_CLEAR_ALL_HELP_MESSAGES()
	{
		HUD::CLEAR_ALL_HELP_MESSAGES();
	}

	static void LUA_NATIVE_HUD_CLEAR_THIS_PRINT(sol::stack_object p0)
	{
		HUD::CLEAR_THIS_PRINT(p0.is<const char*>() ? p0.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_HUD_CLEAR_SMALL_PRINTS()
	{
		HUD::CLEAR_SMALL_PRINTS();
	}

	static bool LUA_NATIVE_HUD_DOES_TEXT_BLOCK_EXIST(sol::stack_object gxt)
	{
		auto retval = (bool)HUD::DOES_TEXT_BLOCK_EXIST(gxt.is<const char*>() ? gxt.as<const char*>() : nullptr);
		return retval;
	}

	static void LUA_NATIVE_HUD_REQUEST_ADDITIONAL_TEXT(sol::stack_object gxt, int slot)
	{
		HUD::REQUEST_ADDITIONAL_TEXT(gxt.is<const char*>() ? gxt.as<const char*>() : nullptr, slot);
	}

	static void LUA_NATIVE_HUD_REQUEST_ADDITIONAL_TEXT_FOR_DLC(sol::stack_object gxt, int slot)
	{
		HUD::REQUEST_ADDITIONAL_TEXT_FOR_DLC(gxt.is<const char*>() ? gxt.as<const char*>() : nullptr, slot);
	}

	static bool LUA_NATIVE_HUD_HAS_ADDITIONAL_TEXT_LOADED(int slot)
	{
		auto retval = (bool)HUD::HAS_ADDITIONAL_TEXT_LOADED(slot);
		return retval;
	}

	static void LUA_NATIVE_HUD_CLEAR_ADDITIONAL_TEXT(int p0, bool p1)
	{
		HUD::CLEAR_ADDITIONAL_TEXT(p0, p1);
	}

	static bool LUA_NATIVE_HUD_IS_STREAMING_ADDITIONAL_TEXT(int p0)
	{
		auto retval = (bool)HUD::IS_STREAMING_ADDITIONAL_TEXT(p0);
		return retval;
	}

	static bool LUA_NATIVE_HUD_HAS_THIS_ADDITIONAL_TEXT_LOADED(sol::stack_object gxt, int slot)
	{
		auto retval = (bool)HUD::HAS_THIS_ADDITIONAL_TEXT_LOADED(gxt.is<const char*>() ? gxt.as<const char*>() : nullptr, slot);
		return retval;
	}

	static bool LUA_NATIVE_HUD_IS_MESSAGE_BEING_DISPLAYED()
	{
		auto retval = (bool)HUD::IS_MESSAGE_BEING_DISPLAYED();
		return retval;
	}

	static bool LUA_NATIVE_HUD_DOES_TEXT_LABEL_EXIST(sol::stack_object gxt)
	{
		auto retval = (bool)HUD::DOES_TEXT_LABEL_EXIST(gxt.is<const char*>() ? gxt.as<const char*>() : nullptr);
		return retval;
	}

	static const char* LUA_NATIVE_HUD_GET_FIRST_N_CHARACTERS_OF_LITERAL_STRING(sol::stack_object string, int length)
	{
		auto retval = HUD::GET_FIRST_N_CHARACTERS_OF_LITERAL_STRING(string.is<const char*>() ? string.as<const char*>() : nullptr, length);
		return retval;
	}

	static int LUA_NATIVE_HUD_GET_LENGTH_OF_STRING_WITH_THIS_TEXT_LABEL(sol::stack_object gxt)
	{
		auto retval = HUD::GET_LENGTH_OF_STRING_WITH_THIS_TEXT_LABEL(gxt.is<const char*>() ? gxt.as<const char*>() : nullptr);
		return retval;
	}

	static int LUA_NATIVE_HUD_GET_LENGTH_OF_LITERAL_STRING(sol::stack_object string)
	{
		auto retval = HUD::GET_LENGTH_OF_LITERAL_STRING(string.is<const char*>() ? string.as<const char*>() : nullptr);
		return retval;
	}

	static int LUA_NATIVE_HUD_GET_LENGTH_OF_LITERAL_STRING_IN_BYTES(sol::stack_object string)
	{
		auto retval = HUD::GET_LENGTH_OF_LITERAL_STRING_IN_BYTES(string.is<const char*>() ? string.as<const char*>() : nullptr);
		return retval;
	}

	static const char* LUA_NATIVE_HUD_GET_STREET_NAME_FROM_HASH_KEY(Hash hash)
	{
		auto retval = HUD::GET_STREET_NAME_FROM_HASH_KEY(hash);
		return retval;
	}

	static bool LUA_NATIVE_HUD_IS_HUD_PREFERENCE_SWITCHED_ON()
	{
		auto retval = (bool)HUD::IS_HUD_PREFERENCE_SWITCHED_ON();
		return retval;
	}

	static bool LUA_NATIVE_HUD_IS_RADAR_PREFERENCE_SWITCHED_ON()
	{
		auto retval = (bool)HUD::IS_RADAR_PREFERENCE_SWITCHED_ON();
		return retval;
	}

	static bool LUA_NATIVE_HUD_IS_SUBTITLE_PREFERENCE_SWITCHED_ON()
	{
		auto retval = (bool)HUD::IS_SUBTITLE_PREFERENCE_SWITCHED_ON();
		return retval;
	}

	static void LUA_NATIVE_HUD_DISPLAY_HUD(bool toggle)
	{
		HUD::DISPLAY_HUD(toggle);
	}

	static void LUA_NATIVE_HUD_DISPLAY_HUD_WHEN_NOT_IN_STATE_OF_PLAY_THIS_FRAME()
	{
		HUD::DISPLAY_HUD_WHEN_NOT_IN_STATE_OF_PLAY_THIS_FRAME();
	}

	static void LUA_NATIVE_HUD_DISPLAY_HUD_WHEN_PAUSED_THIS_FRAME()
	{
		HUD::DISPLAY_HUD_WHEN_PAUSED_THIS_FRAME();
	}

	static void LUA_NATIVE_HUD_DISPLAY_RADAR(bool toggle)
	{
		HUD::DISPLAY_RADAR(toggle);
	}

	static void LUA_NATIVE_HUD_SET_FAKE_SPECTATOR_MODE(bool toggle)
	{
		HUD::SET_FAKE_SPECTATOR_MODE(toggle);
	}

	static bool LUA_NATIVE_HUD_GET_FAKE_SPECTATOR_MODE()
	{
		auto retval = (bool)HUD::GET_FAKE_SPECTATOR_MODE();
		return retval;
	}

	static bool LUA_NATIVE_HUD_IS_HUD_HIDDEN()
	{
		auto retval = (bool)HUD::IS_HUD_HIDDEN();
		return retval;
	}

	static bool LUA_NATIVE_HUD_IS_RADAR_HIDDEN()
	{
		auto retval = (bool)HUD::IS_RADAR_HIDDEN();
		return retval;
	}

	static bool LUA_NATIVE_HUD_IS_MINIMAP_RENDERING()
	{
		auto retval = (bool)HUD::IS_MINIMAP_RENDERING();
		return retval;
	}

	static void LUA_NATIVE_HUD_USE_VEHICLE_TARGETING_RETICULE(Any p0)
	{
		HUD::USE_VEHICLE_TARGETING_RETICULE(p0);
	}

	static void LUA_NATIVE_HUD_USE_VEHICLE_TARGETING_RETICULE_ON_VEHICLES_(bool enable)
	{
		HUD::_USE_VEHICLE_TARGETING_RETICULE_ON_VEHICLES(enable);
	}

	static void LUA_NATIVE_HUD_ADD_VALID_VEHICLE_HIT_HASH(Any p0)
	{
		HUD::ADD_VALID_VEHICLE_HIT_HASH(p0);
	}

	static void LUA_NATIVE_HUD_CLEAR_VALID_VEHICLE_HIT_HASHES()
	{
		HUD::CLEAR_VALID_VEHICLE_HIT_HASHES();
	}

	static void LUA_NATIVE_HUD_SET_BLIP_ROUTE(Blip blip, bool enabled)
	{
		HUD::SET_BLIP_ROUTE(blip, enabled);
	}

	static void LUA_NATIVE_HUD_CLEAR_ALL_BLIP_ROUTES()
	{
		HUD::CLEAR_ALL_BLIP_ROUTES();
	}

	static void LUA_NATIVE_HUD_SET_BLIP_ROUTE_COLOUR(Blip blip, int colour)
	{
		HUD::SET_BLIP_ROUTE_COLOUR(blip, colour);
	}

	static void LUA_NATIVE_HUD_SET_FORCE_SHOW_GPS(bool toggle)
	{
		HUD::SET_FORCE_SHOW_GPS(toggle);
	}

	static void LUA_NATIVE_HUD_SET_USE_SET_DESTINATION_IN_PAUSE_MAP(bool toggle)
	{
		HUD::SET_USE_SET_DESTINATION_IN_PAUSE_MAP(toggle);
	}

	static void LUA_NATIVE_HUD_SET_BLOCK_WANTED_FLASH(bool disabled)
	{
		HUD::SET_BLOCK_WANTED_FLASH(disabled);
	}

	static void LUA_NATIVE_HUD_ADD_NEXT_MESSAGE_TO_PREVIOUS_BRIEFS(bool p0)
	{
		HUD::ADD_NEXT_MESSAGE_TO_PREVIOUS_BRIEFS(p0);
	}

	static void LUA_NATIVE_HUD_FORCE_NEXT_MESSAGE_TO_PREVIOUS_BRIEFS_LIST(int p0)
	{
		HUD::FORCE_NEXT_MESSAGE_TO_PREVIOUS_BRIEFS_LIST(p0);
	}

	static void LUA_NATIVE_HUD_SET_RADAR_ZOOM_PRECISE(float zoom)
	{
		HUD::SET_RADAR_ZOOM_PRECISE(zoom);
	}

	static void LUA_NATIVE_HUD_SET_RADAR_ZOOM(int zoomLevel)
	{
		HUD::SET_RADAR_ZOOM(zoomLevel);
	}

	static void LUA_NATIVE_HUD_SET_RADAR_ZOOM_TO_BLIP(Blip blip, float zoom)
	{
		HUD::SET_RADAR_ZOOM_TO_BLIP(blip, zoom);
	}

	static void LUA_NATIVE_HUD_SET_RADAR_ZOOM_TO_DISTANCE(float zoom)
	{
		HUD::SET_RADAR_ZOOM_TO_DISTANCE(zoom);
	}

	static void LUA_NATIVE_HUD_UPDATE_RADAR_ZOOM_TO_BLIP()
	{
		HUD::UPDATE_RADAR_ZOOM_TO_BLIP();
	}

	static std::tuple<int, int, int, int> LUA_NATIVE_HUD_GET_HUD_COLOUR(int hudColorIndex, int r, int g, int b, int a)
	{
		std::tuple<int, int, int, int> return_values;
		HUD::GET_HUD_COLOUR(hudColorIndex, &r, &g, &b, &a);
		std::get<0>(return_values) = r;
		std::get<1>(return_values) = g;
		std::get<2>(return_values) = b;
		std::get<3>(return_values) = a;

		return return_values;
	}

	static void LUA_NATIVE_HUD_SET_SCRIPT_VARIABLE_HUD_COLOUR(int r, int g, int b, int a)
	{
		HUD::SET_SCRIPT_VARIABLE_HUD_COLOUR(r, g, b, a);
	}

	static void LUA_NATIVE_HUD_SET_SECOND_SCRIPT_VARIABLE_HUD_COLOUR(int r, int g, int b, int a)
	{
		HUD::SET_SECOND_SCRIPT_VARIABLE_HUD_COLOUR(r, g, b, a);
	}

	static void LUA_NATIVE_HUD_REPLACE_HUD_COLOUR(int hudColorIndex, int hudColorIndex2)
	{
		HUD::REPLACE_HUD_COLOUR(hudColorIndex, hudColorIndex2);
	}

	static void LUA_NATIVE_HUD_REPLACE_HUD_COLOUR_WITH_RGBA(int hudColorIndex, int r, int g, int b, int a)
	{
		HUD::REPLACE_HUD_COLOUR_WITH_RGBA(hudColorIndex, r, g, b, a);
	}

	static void LUA_NATIVE_HUD_SET_ABILITY_BAR_VISIBILITY(bool visible)
	{
		HUD::SET_ABILITY_BAR_VISIBILITY(visible);
	}

	static void LUA_NATIVE_HUD_SET_ALLOW_ABILITY_BAR(bool toggle)
	{
		HUD::SET_ALLOW_ABILITY_BAR(toggle);
	}

	static void LUA_NATIVE_HUD_FLASH_ABILITY_BAR(int millisecondsToFlash)
	{
		HUD::FLASH_ABILITY_BAR(millisecondsToFlash);
	}

	static void LUA_NATIVE_HUD_SET_ABILITY_BAR_VALUE(float p0, float p1)
	{
		HUD::SET_ABILITY_BAR_VALUE(p0, p1);
	}

	static void LUA_NATIVE_HUD_FLASH_WANTED_DISPLAY(bool p0)
	{
		HUD::FLASH_WANTED_DISPLAY(p0);
	}

	static void LUA_NATIVE_HUD_FORCE_OFF_WANTED_STAR_FLASH(bool toggle)
	{
		HUD::FORCE_OFF_WANTED_STAR_FLASH(toggle);
	}

	static void LUA_NATIVE_HUD_SET_CUSTOM_MP_HUD_COLOR(int hudColorId)
	{
		HUD::SET_CUSTOM_MP_HUD_COLOR(hudColorId);
	}

	static float LUA_NATIVE_HUD_GET_RENDERED_CHARACTER_HEIGHT(float size, int font)
	{
		auto retval = HUD::GET_RENDERED_CHARACTER_HEIGHT(size, font);
		return retval;
	}

	static void LUA_NATIVE_HUD_SET_TEXT_SCALE(float scale, float size)
	{
		HUD::SET_TEXT_SCALE(scale, size);
	}

	static void LUA_NATIVE_HUD_SET_TEXT_COLOUR(int red, int green, int blue, int alpha)
	{
		HUD::SET_TEXT_COLOUR(red, green, blue, alpha);
	}

	static void LUA_NATIVE_HUD_SET_TEXT_CENTRE(bool align)
	{
		HUD::SET_TEXT_CENTRE(align);
	}

	static void LUA_NATIVE_HUD_SET_TEXT_RIGHT_JUSTIFY(bool toggle)
	{
		HUD::SET_TEXT_RIGHT_JUSTIFY(toggle);
	}

	static void LUA_NATIVE_HUD_SET_TEXT_JUSTIFICATION(int justifyType)
	{
		HUD::SET_TEXT_JUSTIFICATION(justifyType);
	}

	static void LUA_NATIVE_HUD_SET_TEXT_LINE_HEIGHT_MULT(float lineHeightMult)
	{
		HUD::SET_TEXT_LINE_HEIGHT_MULT(lineHeightMult);
	}

	static void LUA_NATIVE_HUD_SET_TEXT_WRAP(float start, float end)
	{
		HUD::SET_TEXT_WRAP(start, end);
	}

	static void LUA_NATIVE_HUD_SET_TEXT_LEADING(int p0)
	{
		HUD::SET_TEXT_LEADING(p0);
	}

	static void LUA_NATIVE_HUD_SET_TEXT_PROPORTIONAL(bool p0)
	{
		HUD::SET_TEXT_PROPORTIONAL(p0);
	}

	static void LUA_NATIVE_HUD_SET_TEXT_FONT(int fontType)
	{
		HUD::SET_TEXT_FONT(fontType);
	}

	static void LUA_NATIVE_HUD_SET_TEXT_DROP_SHADOW()
	{
		HUD::SET_TEXT_DROP_SHADOW();
	}

	static void LUA_NATIVE_HUD_SET_TEXT_DROPSHADOW(int distance, int r, int g, int b, int a)
	{
		HUD::SET_TEXT_DROPSHADOW(distance, r, g, b, a);
	}

	static void LUA_NATIVE_HUD_SET_TEXT_OUTLINE()
	{
		HUD::SET_TEXT_OUTLINE();
	}

	static void LUA_NATIVE_HUD_SET_TEXT_EDGE(int p0, int r, int g, int b, int a)
	{
		HUD::SET_TEXT_EDGE(p0, r, g, b, a);
	}

	static void LUA_NATIVE_HUD_SET_TEXT_RENDER_ID(int renderId)
	{
		HUD::SET_TEXT_RENDER_ID(renderId);
	}

	static int LUA_NATIVE_HUD_GET_DEFAULT_SCRIPT_RENDERTARGET_RENDER_ID()
	{
		auto retval = HUD::GET_DEFAULT_SCRIPT_RENDERTARGET_RENDER_ID();
		return retval;
	}

	static bool LUA_NATIVE_HUD_REGISTER_NAMED_RENDERTARGET(sol::stack_object name, bool p1)
	{
		auto retval = (bool)HUD::REGISTER_NAMED_RENDERTARGET(name.is<const char*>() ? name.as<const char*>() : nullptr, p1);
		return retval;
	}

	static bool LUA_NATIVE_HUD_IS_NAMED_RENDERTARGET_REGISTERED(sol::stack_object name)
	{
		auto retval = (bool)HUD::IS_NAMED_RENDERTARGET_REGISTERED(name.is<const char*>() ? name.as<const char*>() : nullptr);
		return retval;
	}

	static bool LUA_NATIVE_HUD_RELEASE_NAMED_RENDERTARGET(sol::stack_object name)
	{
		auto retval = (bool)HUD::RELEASE_NAMED_RENDERTARGET(name.is<const char*>() ? name.as<const char*>() : nullptr);
		return retval;
	}

	static void LUA_NATIVE_HUD_LINK_NAMED_RENDERTARGET(Hash modelHash)
	{
		HUD::LINK_NAMED_RENDERTARGET(modelHash);
	}

	static int LUA_NATIVE_HUD_GET_NAMED_RENDERTARGET_RENDER_ID(sol::stack_object name)
	{
		auto retval = HUD::GET_NAMED_RENDERTARGET_RENDER_ID(name.is<const char*>() ? name.as<const char*>() : nullptr);
		return retval;
	}

	static bool LUA_NATIVE_HUD_IS_NAMED_RENDERTARGET_LINKED(Hash modelHash)
	{
		auto retval = (bool)HUD::IS_NAMED_RENDERTARGET_LINKED(modelHash);
		return retval;
	}

	static void LUA_NATIVE_HUD_CLEAR_HELP(bool toggle)
	{
		HUD::CLEAR_HELP(toggle);
	}

	static bool LUA_NATIVE_HUD_IS_HELP_MESSAGE_ON_SCREEN()
	{
		auto retval = (bool)HUD::IS_HELP_MESSAGE_ON_SCREEN();
		return retval;
	}

	static bool LUA_NATIVE_HUD_HAS_SCRIPT_HIDDEN_HELP_THIS_FRAME()
	{
		auto retval = (bool)HUD::HAS_SCRIPT_HIDDEN_HELP_THIS_FRAME();
		return retval;
	}

	static bool LUA_NATIVE_HUD_IS_HELP_MESSAGE_BEING_DISPLAYED()
	{
		auto retval = (bool)HUD::IS_HELP_MESSAGE_BEING_DISPLAYED();
		return retval;
	}

	static bool LUA_NATIVE_HUD_IS_HELP_MESSAGE_FADING_OUT()
	{
		auto retval = (bool)HUD::IS_HELP_MESSAGE_FADING_OUT();
		return retval;
	}

	static void LUA_NATIVE_HUD_SET_HELP_MESSAGE_STYLE(int style, int hudColor, int alpha, int p3, int p4)
	{
		HUD::SET_HELP_MESSAGE_STYLE(style, hudColor, alpha, p3, p4);
	}

	static int LUA_NATIVE_HUD_GET_STANDARD_BLIP_ENUM_ID()
	{
		auto retval = HUD::GET_STANDARD_BLIP_ENUM_ID();
		return retval;
	}

	static int LUA_NATIVE_HUD_GET_WAYPOINT_BLIP_ENUM_ID()
	{
		auto retval = HUD::GET_WAYPOINT_BLIP_ENUM_ID();
		return retval;
	}

	static int LUA_NATIVE_HUD_GET_NUMBER_OF_ACTIVE_BLIPS()
	{
		auto retval = HUD::GET_NUMBER_OF_ACTIVE_BLIPS();
		return retval;
	}

	static Blip LUA_NATIVE_HUD_GET_NEXT_BLIP_INFO_ID(int blipSprite)
	{
		auto retval = HUD::GET_NEXT_BLIP_INFO_ID(blipSprite);
		return retval;
	}

	static Blip LUA_NATIVE_HUD_GET_FIRST_BLIP_INFO_ID(int blipSprite)
	{
		auto retval = HUD::GET_FIRST_BLIP_INFO_ID(blipSprite);
		return retval;
	}

	static Blip LUA_NATIVE_HUD_GET_CLOSEST_BLIP_INFO_ID(int blipSprite)
	{
		auto retval = HUD::GET_CLOSEST_BLIP_INFO_ID(blipSprite);
		return retval;
	}

	static Vector3 LUA_NATIVE_HUD_GET_BLIP_INFO_ID_COORD(Blip blip)
	{
		auto retval = HUD::GET_BLIP_INFO_ID_COORD(blip);
		return retval;
	}

	static int LUA_NATIVE_HUD_GET_BLIP_INFO_ID_DISPLAY(Blip blip)
	{
		auto retval = HUD::GET_BLIP_INFO_ID_DISPLAY(blip);
		return retval;
	}

	static int LUA_NATIVE_HUD_GET_BLIP_INFO_ID_TYPE(Blip blip)
	{
		auto retval = HUD::GET_BLIP_INFO_ID_TYPE(blip);
		return retval;
	}

	static Entity LUA_NATIVE_HUD_GET_BLIP_INFO_ID_ENTITY_INDEX(Blip blip)
	{
		auto retval = HUD::GET_BLIP_INFO_ID_ENTITY_INDEX(blip);
		return retval;
	}

	static Pickup LUA_NATIVE_HUD_GET_BLIP_INFO_ID_PICKUP_INDEX(Blip blip)
	{
		auto retval = HUD::GET_BLIP_INFO_ID_PICKUP_INDEX(blip);
		return retval;
	}

	static Blip LUA_NATIVE_HUD_GET_BLIP_FROM_ENTITY(Entity entity)
	{
		auto retval = HUD::GET_BLIP_FROM_ENTITY(entity);
		return retval;
	}

	static Blip LUA_NATIVE_HUD_ADD_BLIP_FOR_RADIUS(float posX, float posY, float posZ, float radius)
	{
		auto retval = HUD::ADD_BLIP_FOR_RADIUS(posX, posY, posZ, radius);
		return retval;
	}

	static Blip LUA_NATIVE_HUD_ADD_BLIP_FOR_AREA(float x, float y, float z, float width, float height)
	{
		auto retval = HUD::ADD_BLIP_FOR_AREA(x, y, z, width, height);
		return retval;
	}

	static Blip LUA_NATIVE_HUD_ADD_BLIP_FOR_ENTITY(Entity entity)
	{
		auto retval = HUD::ADD_BLIP_FOR_ENTITY(entity);
		return retval;
	}

	static Blip LUA_NATIVE_HUD_ADD_BLIP_FOR_PICKUP(Pickup pickup)
	{
		auto retval = HUD::ADD_BLIP_FOR_PICKUP(pickup);
		return retval;
	}

	static Blip LUA_NATIVE_HUD_ADD_BLIP_FOR_COORD(float x, float y, float z)
	{
		auto retval = HUD::ADD_BLIP_FOR_COORD(x, y, z);
		return retval;
	}

	static void LUA_NATIVE_HUD_TRIGGER_SONAR_BLIP(float posX, float posY, float posZ, float radius, int p4)
	{
		HUD::TRIGGER_SONAR_BLIP(posX, posY, posZ, radius, p4);
	}

	static void LUA_NATIVE_HUD_ALLOW_SONAR_BLIPS(bool toggle)
	{
		HUD::ALLOW_SONAR_BLIPS(toggle);
	}

	static void LUA_NATIVE_HUD_SET_BLIP_COORDS(Blip blip, float posX, float posY, float posZ)
	{
		HUD::SET_BLIP_COORDS(blip, posX, posY, posZ);
	}

	static Vector3 LUA_NATIVE_HUD_GET_BLIP_COORDS(Blip blip)
	{
		auto retval = HUD::GET_BLIP_COORDS(blip);
		return retval;
	}

	static void LUA_NATIVE_HUD_SET_BLIP_SPRITE(Blip blip, int spriteId)
	{
		HUD::SET_BLIP_SPRITE(blip, spriteId);
	}

	static int LUA_NATIVE_HUD_GET_BLIP_SPRITE(Blip blip)
	{
		auto retval = HUD::GET_BLIP_SPRITE(blip);
		return retval;
	}

	static void LUA_NATIVE_HUD_SET_COP_BLIP_SPRITE(int p0, float p1)
	{
		HUD::SET_COP_BLIP_SPRITE(p0, p1);
	}

	static void LUA_NATIVE_HUD_SET_COP_BLIP_SPRITE_AS_STANDARD()
	{
		HUD::SET_COP_BLIP_SPRITE_AS_STANDARD();
	}

	static void LUA_NATIVE_HUD_SET_BLIP_NAME_FROM_TEXT_FILE(Blip blip, sol::stack_object gxtEntry)
	{
		HUD::SET_BLIP_NAME_FROM_TEXT_FILE(blip, gxtEntry.is<const char*>() ? gxtEntry.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_HUD_SET_BLIP_NAME_TO_PLAYER_NAME(Blip blip, Player player)
	{
		HUD::SET_BLIP_NAME_TO_PLAYER_NAME(blip, player);
	}

	static void LUA_NATIVE_HUD_SET_BLIP_ALPHA(Blip blip, int alpha)
	{
		HUD::SET_BLIP_ALPHA(blip, alpha);
	}

	static int LUA_NATIVE_HUD_GET_BLIP_ALPHA(Blip blip)
	{
		auto retval = HUD::GET_BLIP_ALPHA(blip);
		return retval;
	}

	static void LUA_NATIVE_HUD_SET_BLIP_FADE(Blip blip, int opacity, int duration)
	{
		HUD::SET_BLIP_FADE(blip, opacity, duration);
	}

	static int LUA_NATIVE_HUD_GET_BLIP_FADE_DIRECTION(Blip blip)
	{
		auto retval = HUD::GET_BLIP_FADE_DIRECTION(blip);
		return retval;
	}

	static void LUA_NATIVE_HUD_SET_BLIP_ROTATION(Blip blip, int rotation)
	{
		HUD::SET_BLIP_ROTATION(blip, rotation);
	}

	static void LUA_NATIVE_HUD_SET_BLIP_ROTATION_WITH_FLOAT(Blip blip, float heading)
	{
		HUD::SET_BLIP_ROTATION_WITH_FLOAT(blip, heading);
	}

	static int LUA_NATIVE_HUD_GET_BLIP_ROTATION(Blip blip)
	{
		auto retval = HUD::GET_BLIP_ROTATION(blip);
		return retval;
	}

	static void LUA_NATIVE_HUD_SET_BLIP_FLASH_TIMER(Blip blip, int duration)
	{
		HUD::SET_BLIP_FLASH_TIMER(blip, duration);
	}

	static void LUA_NATIVE_HUD_SET_BLIP_FLASH_INTERVAL(Blip blip, Any p1)
	{
		HUD::SET_BLIP_FLASH_INTERVAL(blip, p1);
	}

	static void LUA_NATIVE_HUD_SET_BLIP_COLOUR(Blip blip, int color)
	{
		HUD::SET_BLIP_COLOUR(blip, color);
	}

	static void LUA_NATIVE_HUD_SET_BLIP_SECONDARY_COLOUR(Blip blip, int r, int g, int b)
	{
		HUD::SET_BLIP_SECONDARY_COLOUR(blip, r, g, b);
	}

	static int LUA_NATIVE_HUD_GET_BLIP_COLOUR(Blip blip)
	{
		auto retval = HUD::GET_BLIP_COLOUR(blip);
		return retval;
	}

	static int LUA_NATIVE_HUD_GET_BLIP_HUD_COLOUR(Blip blip)
	{
		auto retval = HUD::GET_BLIP_HUD_COLOUR(blip);
		return retval;
	}

	static bool LUA_NATIVE_HUD_IS_BLIP_SHORT_RANGE(Blip blip)
	{
		auto retval = (bool)HUD::IS_BLIP_SHORT_RANGE(blip);
		return retval;
	}

	static bool LUA_NATIVE_HUD_IS_BLIP_ON_MINIMAP(Blip blip)
	{
		auto retval = (bool)HUD::IS_BLIP_ON_MINIMAP(blip);
		return retval;
	}

	static bool LUA_NATIVE_HUD_DOES_BLIP_HAVE_GPS_ROUTE(Blip blip)
	{
		auto retval = (bool)HUD::DOES_BLIP_HAVE_GPS_ROUTE(blip);
		return retval;
	}

	static void LUA_NATIVE_HUD_SET_BLIP_HIDDEN_ON_LEGEND(Blip blip, bool toggle)
	{
		HUD::SET_BLIP_HIDDEN_ON_LEGEND(blip, toggle);
	}

	static void LUA_NATIVE_HUD_SET_BLIP_HIGH_DETAIL(Blip blip, bool toggle)
	{
		HUD::SET_BLIP_HIGH_DETAIL(blip, toggle);
	}

	static void LUA_NATIVE_HUD_SET_BLIP_AS_MISSION_CREATOR_BLIP(Blip blip, bool toggle)
	{
		HUD::SET_BLIP_AS_MISSION_CREATOR_BLIP(blip, toggle);
	}

	static bool LUA_NATIVE_HUD_IS_MISSION_CREATOR_BLIP(Blip blip)
	{
		auto retval = (bool)HUD::IS_MISSION_CREATOR_BLIP(blip);
		return retval;
	}

	static Blip LUA_NATIVE_HUD_GET_NEW_SELECTED_MISSION_CREATOR_BLIP()
	{
		auto retval = HUD::GET_NEW_SELECTED_MISSION_CREATOR_BLIP();
		return retval;
	}

	static bool LUA_NATIVE_HUD_IS_HOVERING_OVER_MISSION_CREATOR_BLIP()
	{
		auto retval = (bool)HUD::IS_HOVERING_OVER_MISSION_CREATOR_BLIP();
		return retval;
	}

	static void LUA_NATIVE_HUD_SHOW_START_MISSION_INSTRUCTIONAL_BUTTON(bool toggle)
	{
		HUD::SHOW_START_MISSION_INSTRUCTIONAL_BUTTON(toggle);
	}

	static void LUA_NATIVE_HUD_SHOW_CONTACT_INSTRUCTIONAL_BUTTON(bool toggle)
	{
		HUD::SHOW_CONTACT_INSTRUCTIONAL_BUTTON(toggle);
	}

	static void LUA_NATIVE_HUD_RELOAD_MAP_MENU()
	{
		HUD::RELOAD_MAP_MENU();
	}

	static void LUA_NATIVE_HUD_SET_BLIP_MARKER_LONG_DISTANCE(Any p0, Any p1)
	{
		HUD::SET_BLIP_MARKER_LONG_DISTANCE(p0, p1);
	}

	static void LUA_NATIVE_HUD_SET_BLIP_FLASHES(Blip blip, bool toggle)
	{
		HUD::SET_BLIP_FLASHES(blip, toggle);
	}

	static void LUA_NATIVE_HUD_SET_BLIP_FLASHES_ALTERNATE(Blip blip, bool toggle)
	{
		HUD::SET_BLIP_FLASHES_ALTERNATE(blip, toggle);
	}

	static bool LUA_NATIVE_HUD_IS_BLIP_FLASHING(Blip blip)
	{
		auto retval = (bool)HUD::IS_BLIP_FLASHING(blip);
		return retval;
	}

	static void LUA_NATIVE_HUD_SET_BLIP_AS_SHORT_RANGE(Blip blip, bool toggle)
	{
		HUD::SET_BLIP_AS_SHORT_RANGE(blip, toggle);
	}

	static void LUA_NATIVE_HUD_SET_BLIP_SCALE(Blip blip, float scale)
	{
		HUD::SET_BLIP_SCALE(blip, scale);
	}

	static void LUA_NATIVE_HUD_SET_BLIP_SCALE_2D(Blip blip, float xScale, float yScale)
	{
		HUD::SET_BLIP_SCALE_2D(blip, xScale, yScale);
	}

	static void LUA_NATIVE_HUD_SET_BLIP_PRIORITY(Blip blip, int priority)
	{
		HUD::SET_BLIP_PRIORITY(blip, priority);
	}

	static void LUA_NATIVE_HUD_SET_BLIP_DISPLAY(Blip blip, int displayId)
	{
		HUD::SET_BLIP_DISPLAY(blip, displayId);
	}

	static void LUA_NATIVE_HUD_SET_BLIP_CATEGORY(Blip blip, int index)
	{
		HUD::SET_BLIP_CATEGORY(blip, index);
	}

	static Blip LUA_NATIVE_HUD_REMOVE_BLIP(Blip blip)
	{
		HUD::REMOVE_BLIP(&blip);
		return blip;
	}

	static void LUA_NATIVE_HUD_SET_BLIP_AS_FRIENDLY(Blip blip, bool toggle)
	{
		HUD::SET_BLIP_AS_FRIENDLY(blip, toggle);
	}

	static void LUA_NATIVE_HUD_PULSE_BLIP(Blip blip)
	{
		HUD::PULSE_BLIP(blip);
	}

	static void LUA_NATIVE_HUD_SHOW_NUMBER_ON_BLIP(Blip blip, int number)
	{
		HUD::SHOW_NUMBER_ON_BLIP(blip, number);
	}

	static void LUA_NATIVE_HUD_HIDE_NUMBER_ON_BLIP(Blip blip)
	{
		HUD::HIDE_NUMBER_ON_BLIP(blip);
	}

	static void LUA_NATIVE_HUD_SHOW_HEIGHT_ON_BLIP(Blip blip, bool toggle)
	{
		HUD::SHOW_HEIGHT_ON_BLIP(blip, toggle);
	}

	static void LUA_NATIVE_HUD_SHOW_TICK_ON_BLIP(Blip blip, bool toggle)
	{
		HUD::SHOW_TICK_ON_BLIP(blip, toggle);
	}

	static void LUA_NATIVE_HUD_SHOW_GOLD_TICK_ON_BLIP(Blip blip, bool toggle)
	{
		HUD::SHOW_GOLD_TICK_ON_BLIP(blip, toggle);
	}

	static void LUA_NATIVE_HUD_SHOW_FOR_SALE_ICON_ON_BLIP(Blip blip, bool toggle)
	{
		HUD::SHOW_FOR_SALE_ICON_ON_BLIP(blip, toggle);
	}

	static void LUA_NATIVE_HUD_SHOW_HEADING_INDICATOR_ON_BLIP(Blip blip, bool toggle)
	{
		HUD::SHOW_HEADING_INDICATOR_ON_BLIP(blip, toggle);
	}

	static void LUA_NATIVE_HUD_SHOW_OUTLINE_INDICATOR_ON_BLIP(Blip blip, bool toggle)
	{
		HUD::SHOW_OUTLINE_INDICATOR_ON_BLIP(blip, toggle);
	}

	static void LUA_NATIVE_HUD_SHOW_FRIEND_INDICATOR_ON_BLIP(Blip blip, bool toggle)
	{
		HUD::SHOW_FRIEND_INDICATOR_ON_BLIP(blip, toggle);
	}

	static void LUA_NATIVE_HUD_SHOW_CREW_INDICATOR_ON_BLIP(Blip blip, bool toggle)
	{
		HUD::SHOW_CREW_INDICATOR_ON_BLIP(blip, toggle);
	}

	static void LUA_NATIVE_HUD_SET_BLIP_EXTENDED_HEIGHT_THRESHOLD(Blip blip, bool toggle)
	{
		HUD::SET_BLIP_EXTENDED_HEIGHT_THRESHOLD(blip, toggle);
	}

	static void LUA_NATIVE_HUD_SET_BLIP_SHORT_HEIGHT_THRESHOLD(Any p0, Any p1)
	{
		HUD::SET_BLIP_SHORT_HEIGHT_THRESHOLD(p0, p1);
	}

	static void LUA_NATIVE_HUD_SET_BLIP_USE_HEIGHT_INDICATOR_ON_EDGE(Blip blip, Any p1)
	{
		HUD::SET_BLIP_USE_HEIGHT_INDICATOR_ON_EDGE(blip, p1);
	}

	static void LUA_NATIVE_HUD_SET_BLIP_AS_MINIMAL_ON_EDGE(Blip blip, bool toggle)
	{
		HUD::SET_BLIP_AS_MINIMAL_ON_EDGE(blip, toggle);
	}

	static void LUA_NATIVE_HUD_SET_RADIUS_BLIP_EDGE(Blip blip, bool toggle)
	{
		HUD::SET_RADIUS_BLIP_EDGE(blip, toggle);
	}

	static bool LUA_NATIVE_HUD_DOES_BLIP_EXIST(Blip blip)
	{
		auto retval = (bool)HUD::DOES_BLIP_EXIST(blip);
		return retval;
	}

	static void LUA_NATIVE_HUD_SET_WAYPOINT_OFF()
	{
		HUD::SET_WAYPOINT_OFF();
	}

	static void LUA_NATIVE_HUD_DELETE_WAYPOINTS_FROM_THIS_PLAYER()
	{
		HUD::DELETE_WAYPOINTS_FROM_THIS_PLAYER();
	}

	static void LUA_NATIVE_HUD_REFRESH_WAYPOINT()
	{
		HUD::REFRESH_WAYPOINT();
	}

	static bool LUA_NATIVE_HUD_IS_WAYPOINT_ACTIVE()
	{
		auto retval = (bool)HUD::IS_WAYPOINT_ACTIVE();
		return retval;
	}

	static void LUA_NATIVE_HUD_SET_NEW_WAYPOINT(float x, float y)
	{
		HUD::SET_NEW_WAYPOINT(x, y);
	}

	static void LUA_NATIVE_HUD_SET_BLIP_BRIGHT(Blip blip, bool toggle)
	{
		HUD::SET_BLIP_BRIGHT(blip, toggle);
	}

	static void LUA_NATIVE_HUD_SET_BLIP_SHOW_CONE(Blip blip, bool toggle, int hudColorIndex)
	{
		HUD::SET_BLIP_SHOW_CONE(blip, toggle, hudColorIndex);
	}

	static void LUA_NATIVE_HUD_REMOVE_COP_BLIP_FROM_PED(Ped ped)
	{
		HUD::REMOVE_COP_BLIP_FROM_PED(ped);
	}

	static void LUA_NATIVE_HUD_SETUP_FAKE_CONE_DATA(Blip blip, float p1, float p2, float p3, float p4, float p5, float p6, Any p7, int p8)
	{
		HUD::SETUP_FAKE_CONE_DATA(blip, p1, p2, p3, p4, p5, p6, p7, p8);
	}

	static void LUA_NATIVE_HUD_REMOVE_FAKE_CONE_DATA(Blip blip)
	{
		HUD::REMOVE_FAKE_CONE_DATA(blip);
	}

	static void LUA_NATIVE_HUD_CLEAR_FAKE_CONE_ARRAY()
	{
		HUD::CLEAR_FAKE_CONE_ARRAY();
	}

	static void LUA_NATIVE_HUD_SET_BLIP_GPS_ROUTE_DISPLAY_DISTANCE_(Blip blip, int blipChangeParam46, bool blipChangeParam47)
	{
		HUD::_SET_BLIP_GPS_ROUTE_DISPLAY_DISTANCE(blip, blipChangeParam46, blipChangeParam47);
	}

	static bool LUA_NATIVE_HUD_SET_MINIMAP_COMPONENT(int componentId, bool toggle, int overrideColor)
	{
		auto retval = (bool)HUD::SET_MINIMAP_COMPONENT(componentId, toggle, overrideColor);
		return retval;
	}

	static void LUA_NATIVE_HUD_SET_MINIMAP_SONAR_SWEEP(bool toggle)
	{
		HUD::SET_MINIMAP_SONAR_SWEEP(toggle);
	}

	static void LUA_NATIVE_HUD_SHOW_ACCOUNT_PICKER()
	{
		HUD::SHOW_ACCOUNT_PICKER();
	}

	static Blip LUA_NATIVE_HUD_GET_MAIN_PLAYER_BLIP_ID()
	{
		auto retval = HUD::GET_MAIN_PLAYER_BLIP_ID();
		return retval;
	}

	static void LUA_NATIVE_HUD_SET_PM_WARNINGSCREEN_ACTIVE(bool p0)
	{
		HUD::SET_PM_WARNINGSCREEN_ACTIVE(p0);
	}

	static void LUA_NATIVE_HUD_HIDE_LOADING_ON_FADE_THIS_FRAME()
	{
		HUD::HIDE_LOADING_ON_FADE_THIS_FRAME();
	}

	static void LUA_NATIVE_HUD_SET_RADAR_AS_INTERIOR_THIS_FRAME(Hash interior, float x, float y, int z, int zoom)
	{
		HUD::SET_RADAR_AS_INTERIOR_THIS_FRAME(interior, x, y, z, zoom);
	}

	static void LUA_NATIVE_HUD_SET_INSIDE_VERY_SMALL_INTERIOR(bool toggle)
	{
		HUD::SET_INSIDE_VERY_SMALL_INTERIOR(toggle);
	}

	static void LUA_NATIVE_HUD_SET_INSIDE_VERY_LARGE_INTERIOR(bool toggle)
	{
		HUD::SET_INSIDE_VERY_LARGE_INTERIOR(toggle);
	}

	static void LUA_NATIVE_HUD_SET_RADAR_AS_EXTERIOR_THIS_FRAME()
	{
		HUD::SET_RADAR_AS_EXTERIOR_THIS_FRAME();
	}

	static void LUA_NATIVE_HUD_SET_FAKE_PAUSEMAP_PLAYER_POSITION_THIS_FRAME(float x, float y)
	{
		HUD::SET_FAKE_PAUSEMAP_PLAYER_POSITION_THIS_FRAME(x, y);
	}

	static void LUA_NATIVE_HUD_SET_FAKE_GPS_PLAYER_POSITION_THIS_FRAME(float x, float y, Any p2)
	{
		HUD::SET_FAKE_GPS_PLAYER_POSITION_THIS_FRAME(x, y, p2);
	}

	static bool LUA_NATIVE_HUD_IS_PAUSEMAP_IN_INTERIOR_MODE()
	{
		auto retval = (bool)HUD::IS_PAUSEMAP_IN_INTERIOR_MODE();
		return retval;
	}

	static void LUA_NATIVE_HUD_HIDE_MINIMAP_EXTERIOR_MAP_THIS_FRAME()
	{
		HUD::HIDE_MINIMAP_EXTERIOR_MAP_THIS_FRAME();
	}

	static void LUA_NATIVE_HUD_HIDE_MINIMAP_INTERIOR_MAP_THIS_FRAME()
	{
		HUD::HIDE_MINIMAP_INTERIOR_MAP_THIS_FRAME();
	}

	static void LUA_NATIVE_HUD_SET_USE_ISLAND_MAP(bool toggle)
	{
		HUD::SET_USE_ISLAND_MAP(toggle);
	}

	static void LUA_NATIVE_HUD_SET_PAUSE_EXTERIOR_RENDERING_WHILE_IN_INTERIOR_()
	{
		HUD::_SET_PAUSE_EXTERIOR_RENDERING_WHILE_IN_INTERIOR();
	}

	static void LUA_NATIVE_HUD_DONT_TILT_MINIMAP_THIS_FRAME()
	{
		HUD::DONT_TILT_MINIMAP_THIS_FRAME();
	}

	static void LUA_NATIVE_HUD_DONT_ZOOM_MINIMAP_WHEN_RUNNING_THIS_FRAME()
	{
		HUD::DONT_ZOOM_MINIMAP_WHEN_RUNNING_THIS_FRAME();
	}

	static void LUA_NATIVE_HUD_DONT_ZOOM_MINIMAP_WHEN_SNIPING_THIS_FRAME()
	{
		HUD::DONT_ZOOM_MINIMAP_WHEN_SNIPING_THIS_FRAME();
	}

	static void LUA_NATIVE_HUD_SET_WIDESCREEN_FORMAT(Any p0)
	{
		HUD::SET_WIDESCREEN_FORMAT(p0);
	}

	static void LUA_NATIVE_HUD_DISPLAY_AREA_NAME(bool toggle)
	{
		HUD::DISPLAY_AREA_NAME(toggle);
	}

	static void LUA_NATIVE_HUD_DISPLAY_CASH(bool toggle)
	{
		HUD::DISPLAY_CASH(toggle);
	}

	static void LUA_NATIVE_HUD_USE_FAKE_MP_CASH(bool toggle)
	{
		HUD::USE_FAKE_MP_CASH(toggle);
	}

	static void LUA_NATIVE_HUD_CHANGE_FAKE_MP_CASH(int cash, int bank)
	{
		HUD::CHANGE_FAKE_MP_CASH(cash, bank);
	}

	static void LUA_NATIVE_HUD_DISPLAY_AMMO_THIS_FRAME(bool display)
	{
		HUD::DISPLAY_AMMO_THIS_FRAME(display);
	}

	static void LUA_NATIVE_HUD_DISPLAY_SNIPER_SCOPE_THIS_FRAME()
	{
		HUD::DISPLAY_SNIPER_SCOPE_THIS_FRAME();
	}

	static void LUA_NATIVE_HUD_HIDE_HUD_AND_RADAR_THIS_FRAME()
	{
		HUD::HIDE_HUD_AND_RADAR_THIS_FRAME();
	}

	static void LUA_NATIVE_HUD_ALLOW_DISPLAY_OF_MULTIPLAYER_CASH_TEXT(bool allow)
	{
		HUD::ALLOW_DISPLAY_OF_MULTIPLAYER_CASH_TEXT(allow);
	}

	static void LUA_NATIVE_HUD_SET_MULTIPLAYER_WALLET_CASH()
	{
		HUD::SET_MULTIPLAYER_WALLET_CASH();
	}

	static void LUA_NATIVE_HUD_REMOVE_MULTIPLAYER_WALLET_CASH()
	{
		HUD::REMOVE_MULTIPLAYER_WALLET_CASH();
	}

	static void LUA_NATIVE_HUD_SET_MULTIPLAYER_BANK_CASH()
	{
		HUD::SET_MULTIPLAYER_BANK_CASH();
	}

	static void LUA_NATIVE_HUD_REMOVE_MULTIPLAYER_BANK_CASH()
	{
		HUD::REMOVE_MULTIPLAYER_BANK_CASH();
	}

	static void LUA_NATIVE_HUD_SET_MULTIPLAYER_HUD_CASH(int p0, bool p1)
	{
		HUD::SET_MULTIPLAYER_HUD_CASH(p0, p1);
	}

	static void LUA_NATIVE_HUD_REMOVE_MULTIPLAYER_HUD_CASH()
	{
		HUD::REMOVE_MULTIPLAYER_HUD_CASH();
	}

	static void LUA_NATIVE_HUD_HIDE_HELP_TEXT_THIS_FRAME()
	{
		HUD::HIDE_HELP_TEXT_THIS_FRAME();
	}

	static bool LUA_NATIVE_HUD_IS_IME_IN_PROGRESS()
	{
		auto retval = (bool)HUD::IS_IME_IN_PROGRESS();
		return retval;
	}

	static void LUA_NATIVE_HUD_DISPLAY_HELP_TEXT_THIS_FRAME(sol::stack_object message, bool p1)
	{
		HUD::DISPLAY_HELP_TEXT_THIS_FRAME(message.is<const char*>() ? message.as<const char*>() : nullptr, p1);
	}

	static void LUA_NATIVE_HUD_HUD_FORCE_WEAPON_WHEEL(bool show)
	{
		HUD::HUD_FORCE_WEAPON_WHEEL(show);
	}

	static void LUA_NATIVE_HUD_HUD_FORCE_SPECIAL_VEHICLE_WEAPON_WHEEL()
	{
		HUD::HUD_FORCE_SPECIAL_VEHICLE_WEAPON_WHEEL();
	}

	static void LUA_NATIVE_HUD_HUD_SUPPRESS_WEAPON_WHEEL_RESULTS_THIS_FRAME()
	{
		HUD::HUD_SUPPRESS_WEAPON_WHEEL_RESULTS_THIS_FRAME();
	}

	static Hash LUA_NATIVE_HUD_HUD_GET_WEAPON_WHEEL_CURRENTLY_HIGHLIGHTED()
	{
		auto retval = HUD::HUD_GET_WEAPON_WHEEL_CURRENTLY_HIGHLIGHTED();
		return retval;
	}

	static void LUA_NATIVE_HUD_HUD_SET_WEAPON_WHEEL_TOP_SLOT(Hash weaponHash)
	{
		HUD::HUD_SET_WEAPON_WHEEL_TOP_SLOT(weaponHash);
	}

	static Hash LUA_NATIVE_HUD_HUD_GET_WEAPON_WHEEL_TOP_SLOT(int weaponTypeIndex)
	{
		auto retval = HUD::HUD_GET_WEAPON_WHEEL_TOP_SLOT(weaponTypeIndex);
		return retval;
	}

	static void LUA_NATIVE_HUD_HUD_SHOWING_CHARACTER_SWITCH_SELECTION(bool toggle)
	{
		HUD::HUD_SHOWING_CHARACTER_SWITCH_SELECTION(toggle);
	}

	static void LUA_NATIVE_HUD_SET_GPS_FLAGS(int p0, float p1)
	{
		HUD::SET_GPS_FLAGS(p0, p1);
	}

	static void LUA_NATIVE_HUD_CLEAR_GPS_FLAGS()
	{
		HUD::CLEAR_GPS_FLAGS();
	}

	static void LUA_NATIVE_HUD_SET_RACE_TRACK_RENDER(bool toggle)
	{
		HUD::SET_RACE_TRACK_RENDER(toggle);
	}

	static void LUA_NATIVE_HUD_CLEAR_GPS_RACE_TRACK()
	{
		HUD::CLEAR_GPS_RACE_TRACK();
	}

	static void LUA_NATIVE_HUD_START_GPS_CUSTOM_ROUTE(int hudColor, bool displayOnFoot, bool followPlayer)
	{
		HUD::START_GPS_CUSTOM_ROUTE(hudColor, displayOnFoot, followPlayer);
	}

	static void LUA_NATIVE_HUD_ADD_POINT_TO_GPS_CUSTOM_ROUTE(float x, float y, float z)
	{
		HUD::ADD_POINT_TO_GPS_CUSTOM_ROUTE(x, y, z);
	}

	static void LUA_NATIVE_HUD_SET_GPS_CUSTOM_ROUTE_RENDER(bool toggle, int radarThickness, int mapThickness)
	{
		HUD::SET_GPS_CUSTOM_ROUTE_RENDER(toggle, radarThickness, mapThickness);
	}

	static void LUA_NATIVE_HUD_CLEAR_GPS_CUSTOM_ROUTE()
	{
		HUD::CLEAR_GPS_CUSTOM_ROUTE();
	}

	static void LUA_NATIVE_HUD_START_GPS_MULTI_ROUTE(int hudColor, bool routeFromPlayer, bool displayOnFoot)
	{
		HUD::START_GPS_MULTI_ROUTE(hudColor, routeFromPlayer, displayOnFoot);
	}

	static void LUA_NATIVE_HUD_ADD_POINT_TO_GPS_MULTI_ROUTE(float x, float y, float z)
	{
		HUD::ADD_POINT_TO_GPS_MULTI_ROUTE(x, y, z);
	}

	static void LUA_NATIVE_HUD_SET_GPS_MULTI_ROUTE_RENDER(bool toggle)
	{
		HUD::SET_GPS_MULTI_ROUTE_RENDER(toggle);
	}

	static void LUA_NATIVE_HUD_CLEAR_GPS_MULTI_ROUTE()
	{
		HUD::CLEAR_GPS_MULTI_ROUTE();
	}

	static void LUA_NATIVE_HUD_CLEAR_GPS_PLAYER_WAYPOINT()
	{
		HUD::CLEAR_GPS_PLAYER_WAYPOINT();
	}

	static void LUA_NATIVE_HUD_SET_GPS_FLASHES(bool toggle)
	{
		HUD::SET_GPS_FLASHES(toggle);
	}

	static void LUA_NATIVE_HUD_SET_PLAYER_ICON_COLOUR(int color)
	{
		HUD::SET_PLAYER_ICON_COLOUR(color);
	}

	static void LUA_NATIVE_HUD_FLASH_MINIMAP_DISPLAY()
	{
		HUD::FLASH_MINIMAP_DISPLAY();
	}

	static void LUA_NATIVE_HUD_FLASH_MINIMAP_DISPLAY_WITH_COLOR(int hudColorIndex)
	{
		HUD::FLASH_MINIMAP_DISPLAY_WITH_COLOR(hudColorIndex);
	}

	static void LUA_NATIVE_HUD_TOGGLE_STEALTH_RADAR(bool toggle)
	{
		HUD::TOGGLE_STEALTH_RADAR(toggle);
	}

	static void LUA_NATIVE_HUD_SET_MINIMAP_IN_SPECTATOR_MODE(bool toggle, Ped ped)
	{
		HUD::SET_MINIMAP_IN_SPECTATOR_MODE(toggle, ped);
	}

	static void LUA_NATIVE_HUD_SET_MISSION_NAME(bool p0, sol::stack_object name)
	{
		HUD::SET_MISSION_NAME(p0, name.is<const char*>() ? name.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_HUD_SET_MISSION_NAME_FOR_UGC_MISSION(bool p0, sol::stack_object name)
	{
		HUD::SET_MISSION_NAME_FOR_UGC_MISSION(p0, name.is<const char*>() ? name.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_HUD_SET_DESCRIPTION_FOR_UGC_MISSION_EIGHT_STRINGS(bool p0, sol::stack_object p1, sol::stack_object p2, sol::stack_object p3, sol::stack_object p4, sol::stack_object p5, sol::stack_object p6, sol::stack_object p7, sol::stack_object p8)
	{
		HUD::SET_DESCRIPTION_FOR_UGC_MISSION_EIGHT_STRINGS(p0, p1.is<const char*>() ? p1.as<const char*>() : nullptr, p2.is<const char*>() ? p2.as<const char*>() : nullptr, p3.is<const char*>() ? p3.as<const char*>() : nullptr, p4.is<const char*>() ? p4.as<const char*>() : nullptr, p5.is<const char*>() ? p5.as<const char*>() : nullptr, p6.is<const char*>() ? p6.as<const char*>() : nullptr, p7.is<const char*>() ? p7.as<const char*>() : nullptr, p8.is<const char*>() ? p8.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_HUD_SET_MINIMAP_BLOCK_WAYPOINT(bool toggle)
	{
		HUD::SET_MINIMAP_BLOCK_WAYPOINT(toggle);
	}

	static void LUA_NATIVE_HUD_SET_MINIMAP_IN_PROLOGUE(bool toggle)
	{
		HUD::SET_MINIMAP_IN_PROLOGUE(toggle);
	}

	static void LUA_NATIVE_HUD_SET_MINIMAP_HIDE_FOW(bool toggle)
	{
		HUD::SET_MINIMAP_HIDE_FOW(toggle);
	}

	static float LUA_NATIVE_HUD_GET_MINIMAP_FOW_DISCOVERY_RATIO()
	{
		auto retval = HUD::GET_MINIMAP_FOW_DISCOVERY_RATIO();
		return retval;
	}

	static bool LUA_NATIVE_HUD_GET_MINIMAP_FOW_COORDINATE_IS_REVEALED(float x, float y, float z)
	{
		auto retval = (bool)HUD::GET_MINIMAP_FOW_COORDINATE_IS_REVEALED(x, y, z);
		return retval;
	}

	static void LUA_NATIVE_HUD_SET_MINIMAP_FOW_DO_NOT_UPDATE(bool p0)
	{
		HUD::SET_MINIMAP_FOW_DO_NOT_UPDATE(p0);
	}

	static void LUA_NATIVE_HUD_SET_MINIMAP_FOW_REVEAL_COORDINATE(float x, float y, float z)
	{
		HUD::SET_MINIMAP_FOW_REVEAL_COORDINATE(x, y, z);
	}

	static void LUA_NATIVE_HUD_SET_MINIMAP_GOLF_COURSE(int hole)
	{
		HUD::SET_MINIMAP_GOLF_COURSE(hole);
	}

	static void LUA_NATIVE_HUD_SET_MINIMAP_GOLF_COURSE_OFF()
	{
		HUD::SET_MINIMAP_GOLF_COURSE_OFF();
	}

	static void LUA_NATIVE_HUD_LOCK_MINIMAP_ANGLE(int angle)
	{
		HUD::LOCK_MINIMAP_ANGLE(angle);
	}

	static void LUA_NATIVE_HUD_UNLOCK_MINIMAP_ANGLE()
	{
		HUD::UNLOCK_MINIMAP_ANGLE();
	}

	static void LUA_NATIVE_HUD_LOCK_MINIMAP_POSITION(float x, float y)
	{
		HUD::LOCK_MINIMAP_POSITION(x, y);
	}

	static void LUA_NATIVE_HUD_UNLOCK_MINIMAP_POSITION()
	{
		HUD::UNLOCK_MINIMAP_POSITION();
	}

	static void LUA_NATIVE_HUD_SET_FAKE_MINIMAP_MAX_ALTIMETER_HEIGHT(float altitude, bool p1, Any p2)
	{
		HUD::SET_FAKE_MINIMAP_MAX_ALTIMETER_HEIGHT(altitude, p1, p2);
	}

	static void LUA_NATIVE_HUD_SET_HEALTH_HUD_DISPLAY_VALUES(int health, int capacity, bool wasAdded)
	{
		HUD::SET_HEALTH_HUD_DISPLAY_VALUES(health, capacity, wasAdded);
	}

	static void LUA_NATIVE_HUD_SET_MAX_HEALTH_HUD_DISPLAY(int maximumValue)
	{
		HUD::SET_MAX_HEALTH_HUD_DISPLAY(maximumValue);
	}

	static void LUA_NATIVE_HUD_SET_MAX_ARMOUR_HUD_DISPLAY(int maximumValue)
	{
		HUD::SET_MAX_ARMOUR_HUD_DISPLAY(maximumValue);
	}

	static void LUA_NATIVE_HUD_SET_BIGMAP_ACTIVE(bool toggleBigMap, bool showFullMap)
	{
		HUD::SET_BIGMAP_ACTIVE(toggleBigMap, showFullMap);
	}

	static bool LUA_NATIVE_HUD_IS_HUD_COMPONENT_ACTIVE(int id)
	{
		auto retval = (bool)HUD::IS_HUD_COMPONENT_ACTIVE(id);
		return retval;
	}

	static bool LUA_NATIVE_HUD_IS_SCRIPTED_HUD_COMPONENT_ACTIVE(int id)
	{
		auto retval = (bool)HUD::IS_SCRIPTED_HUD_COMPONENT_ACTIVE(id);
		return retval;
	}

	static void LUA_NATIVE_HUD_HIDE_SCRIPTED_HUD_COMPONENT_THIS_FRAME(int id)
	{
		HUD::HIDE_SCRIPTED_HUD_COMPONENT_THIS_FRAME(id);
	}

	static void LUA_NATIVE_HUD_SHOW_SCRIPTED_HUD_COMPONENT_THIS_FRAME(int id)
	{
		HUD::SHOW_SCRIPTED_HUD_COMPONENT_THIS_FRAME(id);
	}

	static bool LUA_NATIVE_HUD_IS_SCRIPTED_HUD_COMPONENT_HIDDEN_THIS_FRAME(int id)
	{
		auto retval = (bool)HUD::IS_SCRIPTED_HUD_COMPONENT_HIDDEN_THIS_FRAME(id);
		return retval;
	}

	static void LUA_NATIVE_HUD_HIDE_HUD_COMPONENT_THIS_FRAME(int id)
	{
		HUD::HIDE_HUD_COMPONENT_THIS_FRAME(id);
	}

	static void LUA_NATIVE_HUD_SHOW_HUD_COMPONENT_THIS_FRAME(int id)
	{
		HUD::SHOW_HUD_COMPONENT_THIS_FRAME(id);
	}

	static void LUA_NATIVE_HUD_HIDE_STREET_AND_CAR_NAMES_THIS_FRAME()
	{
		HUD::HIDE_STREET_AND_CAR_NAMES_THIS_FRAME();
	}

	static void LUA_NATIVE_HUD_RESET_RETICULE_VALUES()
	{
		HUD::RESET_RETICULE_VALUES();
	}

	static void LUA_NATIVE_HUD_RESET_HUD_COMPONENT_VALUES(int id)
	{
		HUD::RESET_HUD_COMPONENT_VALUES(id);
	}

	static void LUA_NATIVE_HUD_SET_HUD_COMPONENT_POSITION(int id, float x, float y)
	{
		HUD::SET_HUD_COMPONENT_POSITION(id, x, y);
	}

	static Vector3 LUA_NATIVE_HUD_GET_HUD_COMPONENT_POSITION(int id)
	{
		auto retval = HUD::GET_HUD_COMPONENT_POSITION(id);
		return retval;
	}

	static void LUA_NATIVE_HUD_CLEAR_REMINDER_MESSAGE()
	{
		HUD::CLEAR_REMINDER_MESSAGE();
	}

	static std::tuple<int, float, float> LUA_NATIVE_HUD_GET_HUD_SCREEN_POSITION_FROM_WORLD_POSITION(float worldX, float worldY, float worldZ, float screenX, float screenY)
	{
		std::tuple<int, float, float> return_values;
		std::get<0>(return_values) = HUD::GET_HUD_SCREEN_POSITION_FROM_WORLD_POSITION(worldX, worldY, worldZ, &screenX, &screenY);
		std::get<1>(return_values) = screenX;
		std::get<2>(return_values) = screenY;

		return return_values;
	}

	static void LUA_NATIVE_HUD_OPEN_REPORTUGC_MENU()
	{
		HUD::OPEN_REPORTUGC_MENU();
	}

	static void LUA_NATIVE_HUD_FORCE_CLOSE_REPORTUGC_MENU()
	{
		HUD::FORCE_CLOSE_REPORTUGC_MENU();
	}

	static bool LUA_NATIVE_HUD_IS_REPORTUGC_MENU_OPEN()
	{
		auto retval = (bool)HUD::IS_REPORTUGC_MENU_OPEN();
		return retval;
	}

	static bool LUA_NATIVE_HUD_IS_FLOATING_HELP_TEXT_ON_SCREEN(int hudIndex)
	{
		auto retval = (bool)HUD::IS_FLOATING_HELP_TEXT_ON_SCREEN(hudIndex);
		return retval;
	}

	static void LUA_NATIVE_HUD_SET_FLOATING_HELP_TEXT_SCREEN_POSITION(int hudIndex, float x, float y)
	{
		HUD::SET_FLOATING_HELP_TEXT_SCREEN_POSITION(hudIndex, x, y);
	}

	static void LUA_NATIVE_HUD_SET_FLOATING_HELP_TEXT_WORLD_POSITION(int hudIndex, float x, float y, float z)
	{
		HUD::SET_FLOATING_HELP_TEXT_WORLD_POSITION(hudIndex, x, y, z);
	}

	static void LUA_NATIVE_HUD_SET_FLOATING_HELP_TEXT_TO_ENTITY(int hudIndex, Entity entity, float offsetX, float offsetY)
	{
		HUD::SET_FLOATING_HELP_TEXT_TO_ENTITY(hudIndex, entity, offsetX, offsetY);
	}

	static void LUA_NATIVE_HUD_SET_FLOATING_HELP_TEXT_STYLE(int hudIndex, int p1, int p2, int p3, int p4, int p5)
	{
		HUD::SET_FLOATING_HELP_TEXT_STYLE(hudIndex, p1, p2, p3, p4, p5);
	}

	static void LUA_NATIVE_HUD_CLEAR_FLOATING_HELP(int hudIndex, bool p1)
	{
		HUD::CLEAR_FLOATING_HELP(hudIndex, p1);
	}

	static void LUA_NATIVE_HUD_CREATE_MP_GAMER_TAG_WITH_CREW_COLOR(Player player, sol::stack_object username, bool pointedClanTag, bool isRockstarClan, sol::stack_object clanTag, int clanFlag, int r, int g, int b)
	{
		HUD::CREATE_MP_GAMER_TAG_WITH_CREW_COLOR(player, username.is<const char*>() ? username.as<const char*>() : nullptr, pointedClanTag, isRockstarClan, clanTag.is<const char*>() ? clanTag.as<const char*>() : nullptr, clanFlag, r, g, b);
	}

	static bool LUA_NATIVE_HUD_IS_MP_GAMER_TAG_MOVIE_ACTIVE()
	{
		auto retval = (bool)HUD::IS_MP_GAMER_TAG_MOVIE_ACTIVE();
		return retval;
	}

	static int LUA_NATIVE_HUD_CREATE_FAKE_MP_GAMER_TAG(Ped ped, sol::stack_object username, bool pointedClanTag, bool isRockstarClan, sol::stack_object clanTag, int clanFlag)
	{
		auto retval = HUD::CREATE_FAKE_MP_GAMER_TAG(ped, username.is<const char*>() ? username.as<const char*>() : nullptr, pointedClanTag, isRockstarClan, clanTag.is<const char*>() ? clanTag.as<const char*>() : nullptr, clanFlag);
		return retval;
	}

	static void LUA_NATIVE_HUD_REMOVE_MP_GAMER_TAG(int gamerTagId)
	{
		HUD::REMOVE_MP_GAMER_TAG(gamerTagId);
	}

	static bool LUA_NATIVE_HUD_IS_MP_GAMER_TAG_ACTIVE(int gamerTagId)
	{
		auto retval = (bool)HUD::IS_MP_GAMER_TAG_ACTIVE(gamerTagId);
		return retval;
	}

	static bool LUA_NATIVE_HUD_IS_MP_GAMER_TAG_FREE(int gamerTagId)
	{
		auto retval = (bool)HUD::IS_MP_GAMER_TAG_FREE(gamerTagId);
		return retval;
	}

	static void LUA_NATIVE_HUD_SET_MP_GAMER_TAG_VISIBILITY(int gamerTagId, int component, bool toggle, Any p3)
	{
		HUD::SET_MP_GAMER_TAG_VISIBILITY(gamerTagId, component, toggle, p3);
	}

	static void LUA_NATIVE_HUD_SET_ALL_MP_GAMER_TAGS_VISIBILITY(int gamerTagId, bool toggle)
	{
		HUD::SET_ALL_MP_GAMER_TAGS_VISIBILITY(gamerTagId, toggle);
	}

	static void LUA_NATIVE_HUD_SET_MP_GAMER_TAGS_SHOULD_USE_VEHICLE_HEALTH(int gamerTagId, bool toggle)
	{
		HUD::SET_MP_GAMER_TAGS_SHOULD_USE_VEHICLE_HEALTH(gamerTagId, toggle);
	}

	static void LUA_NATIVE_HUD_SET_MP_GAMER_TAGS_SHOULD_USE_POINTS_HEALTH(int gamerTagId, bool toggle)
	{
		HUD::SET_MP_GAMER_TAGS_SHOULD_USE_POINTS_HEALTH(gamerTagId, toggle);
	}

	static void LUA_NATIVE_HUD_SET_MP_GAMER_TAGS_POINT_HEALTH(int gamerTagId, int value, int maximumValue)
	{
		HUD::SET_MP_GAMER_TAGS_POINT_HEALTH(gamerTagId, value, maximumValue);
	}

	static void LUA_NATIVE_HUD_SET_MP_GAMER_TAG_COLOUR(int gamerTagId, int component, int hudColorIndex)
	{
		HUD::SET_MP_GAMER_TAG_COLOUR(gamerTagId, component, hudColorIndex);
	}

	static void LUA_NATIVE_HUD_SET_MP_GAMER_TAG_HEALTH_BAR_COLOUR(int gamerTagId, int hudColorIndex)
	{
		HUD::SET_MP_GAMER_TAG_HEALTH_BAR_COLOUR(gamerTagId, hudColorIndex);
	}

	static void LUA_NATIVE_HUD_SET_MP_GAMER_TAG_ALPHA(int gamerTagId, int component, int alpha)
	{
		HUD::SET_MP_GAMER_TAG_ALPHA(gamerTagId, component, alpha);
	}

	static void LUA_NATIVE_HUD_SET_MP_GAMER_TAG_WANTED_LEVEL(int gamerTagId, int wantedlvl)
	{
		HUD::SET_MP_GAMER_TAG_WANTED_LEVEL(gamerTagId, wantedlvl);
	}

	static void LUA_NATIVE_HUD_SET_MP_GAMER_TAG_NUM_PACKAGES(int gamerTagId, int p1)
	{
		HUD::SET_MP_GAMER_TAG_NUM_PACKAGES(gamerTagId, p1);
	}

	static void LUA_NATIVE_HUD_SET_MP_GAMER_TAG_NAME(int gamerTagId, sol::stack_object string)
	{
		HUD::SET_MP_GAMER_TAG_NAME(gamerTagId, string.is<const char*>() ? string.as<const char*>() : nullptr);
	}

	static bool LUA_NATIVE_HUD_IS_UPDATING_MP_GAMER_TAG_NAME_AND_CREW_DETAILS(int gamerTagId)
	{
		auto retval = (bool)HUD::IS_UPDATING_MP_GAMER_TAG_NAME_AND_CREW_DETAILS(gamerTagId);
		return retval;
	}

	static void LUA_NATIVE_HUD_SET_MP_GAMER_TAG_BIG_TEXT(int gamerTagId, sol::stack_object string)
	{
		HUD::SET_MP_GAMER_TAG_BIG_TEXT(gamerTagId, string.is<const char*>() ? string.as<const char*>() : nullptr);
	}

	static int LUA_NATIVE_HUD_GET_CURRENT_WEBPAGE_ID()
	{
		auto retval = HUD::GET_CURRENT_WEBPAGE_ID();
		return retval;
	}

	static int LUA_NATIVE_HUD_GET_CURRENT_WEBSITE_ID()
	{
		auto retval = HUD::GET_CURRENT_WEBSITE_ID();
		return retval;
	}

	static int LUA_NATIVE_HUD_GET_GLOBAL_ACTIONSCRIPT_FLAG(int flagIndex)
	{
		auto retval = HUD::GET_GLOBAL_ACTIONSCRIPT_FLAG(flagIndex);
		return retval;
	}

	static void LUA_NATIVE_HUD_RESET_GLOBAL_ACTIONSCRIPT_FLAG(int flagIndex)
	{
		HUD::RESET_GLOBAL_ACTIONSCRIPT_FLAG(flagIndex);
	}

	static bool LUA_NATIVE_HUD_IS_WARNING_MESSAGE_READY_FOR_CONTROL()
	{
		auto retval = (bool)HUD::IS_WARNING_MESSAGE_READY_FOR_CONTROL();
		return retval;
	}

	static void LUA_NATIVE_HUD_SET_WARNING_MESSAGE(sol::stack_object titleMsg, int flags, sol::stack_object promptMsg, bool p3, int p4, sol::stack_object p5, sol::stack_object p6, bool showBackground, int errorCode)
	{
		HUD::SET_WARNING_MESSAGE(titleMsg.is<const char*>() ? titleMsg.as<const char*>() : nullptr, flags, promptMsg.is<const char*>() ? promptMsg.as<const char*>() : nullptr, p3, p4, p5.is<const char*>() ? p5.as<const char*>() : nullptr, p6.is<const char*>() ? p6.as<const char*>() : nullptr, showBackground, errorCode);
	}

	static void LUA_NATIVE_HUD_SET_WARNING_MESSAGE_WITH_HEADER(sol::stack_object entryHeader, sol::stack_object entryLine1, int instructionalKey, sol::stack_object entryLine2, bool p4, Any p5, uintptr_t showBackground, uintptr_t p7, bool p8, Any p9)
	{
		HUD::SET_WARNING_MESSAGE_WITH_HEADER(entryHeader.is<const char*>() ? entryHeader.as<const char*>() : nullptr, entryLine1.is<const char*>() ? entryLine1.as<const char*>() : nullptr, instructionalKey, entryLine2.is<const char*>() ? entryLine2.as<const char*>() : nullptr, p4, p5, (Any*)showBackground, (Any*)p7, p8, p9);
	}

	static void LUA_NATIVE_HUD_SET_WARNING_MESSAGE_WITH_HEADER_AND_SUBSTRING_FLAGS(sol::stack_object entryHeader, sol::stack_object entryLine1, int instructionalKey, sol::stack_object entryLine2, bool p4, Any p5, Any additionalIntInfo, sol::stack_object additionalTextInfoLine1, sol::stack_object additionalTextInfoLine2, bool showBackground, int errorCode)
	{
		HUD::SET_WARNING_MESSAGE_WITH_HEADER_AND_SUBSTRING_FLAGS(entryHeader.is<const char*>() ? entryHeader.as<const char*>() : nullptr, entryLine1.is<const char*>() ? entryLine1.as<const char*>() : nullptr, instructionalKey, entryLine2.is<const char*>() ? entryLine2.as<const char*>() : nullptr, p4, p5, additionalIntInfo, additionalTextInfoLine1.is<const char*>() ? additionalTextInfoLine1.as<const char*>() : nullptr, additionalTextInfoLine2.is<const char*>() ? additionalTextInfoLine2.as<const char*>() : nullptr, showBackground, errorCode);
	}

	static void LUA_NATIVE_HUD_SET_WARNING_MESSAGE_WITH_HEADER_EXTENDED(sol::stack_object entryHeader, sol::stack_object entryLine1, int flags, sol::stack_object entryLine2, bool p4, Any p5, uintptr_t p6, uintptr_t p7, bool showBg, Any p9, Any p10)
	{
		HUD::SET_WARNING_MESSAGE_WITH_HEADER_EXTENDED(entryHeader.is<const char*>() ? entryHeader.as<const char*>() : nullptr, entryLine1.is<const char*>() ? entryLine1.as<const char*>() : nullptr, flags, entryLine2.is<const char*>() ? entryLine2.as<const char*>() : nullptr, p4, p5, (Any*)p6, (Any*)p7, showBg, p9, p10);
	}

	static void LUA_NATIVE_HUD_SET_WARNING_MESSAGE_WITH_HEADER_AND_SUBSTRING_FLAGS_EXTENDED(sol::stack_object labelTitle, sol::stack_object labelMessage, int p2, int p3, sol::stack_object labelMessage2, bool p5, int p6, int p7, sol::stack_object p8, sol::stack_object p9, bool background, int errorCode)
	{
		HUD::SET_WARNING_MESSAGE_WITH_HEADER_AND_SUBSTRING_FLAGS_EXTENDED(labelTitle.is<const char*>() ? labelTitle.as<const char*>() : nullptr, labelMessage.is<const char*>() ? labelMessage.as<const char*>() : nullptr, p2, p3, labelMessage2.is<const char*>() ? labelMessage2.as<const char*>() : nullptr, p5, p6, p7, p8.is<const char*>() ? p8.as<const char*>() : nullptr, p9.is<const char*>() ? p9.as<const char*>() : nullptr, background, errorCode);
	}

	static Hash LUA_NATIVE_HUD_GET_WARNING_SCREEN_MESSAGE_HASH()
	{
		auto retval = HUD::GET_WARNING_SCREEN_MESSAGE_HASH();
		return retval;
	}

	static bool LUA_NATIVE_HUD_SET_WARNING_MESSAGE_OPTION_ITEMS(int index, sol::stack_object name, int cash, int rp, int lvl, int colour)
	{
		auto retval = (bool)HUD::SET_WARNING_MESSAGE_OPTION_ITEMS(index, name.is<const char*>() ? name.as<const char*>() : nullptr, cash, rp, lvl, colour);
		return retval;
	}

	static bool LUA_NATIVE_HUD_SET_WARNING_MESSAGE_OPTION_HIGHLIGHT(Any p0)
	{
		auto retval = (bool)HUD::SET_WARNING_MESSAGE_OPTION_HIGHLIGHT(p0);
		return retval;
	}

	static void LUA_NATIVE_HUD_REMOVE_WARNING_MESSAGE_OPTION_ITEMS()
	{
		HUD::REMOVE_WARNING_MESSAGE_OPTION_ITEMS();
	}

	static bool LUA_NATIVE_HUD_IS_WARNING_MESSAGE_ACTIVE()
	{
		auto retval = (bool)HUD::IS_WARNING_MESSAGE_ACTIVE();
		return retval;
	}

	static void LUA_NATIVE_HUD_CLEAR_DYNAMIC_PAUSE_MENU_ERROR_MESSAGE()
	{
		HUD::CLEAR_DYNAMIC_PAUSE_MENU_ERROR_MESSAGE();
	}

	static void LUA_NATIVE_HUD_CUSTOM_MINIMAP_SET_ACTIVE(bool toggle)
	{
		HUD::CUSTOM_MINIMAP_SET_ACTIVE(toggle);
	}

	static void LUA_NATIVE_HUD_CUSTOM_MINIMAP_SET_BLIP_OBJECT(int spriteId)
	{
		HUD::CUSTOM_MINIMAP_SET_BLIP_OBJECT(spriteId);
	}

	static int LUA_NATIVE_HUD_CUSTOM_MINIMAP_CREATE_BLIP(float x, float y, float z)
	{
		auto retval = HUD::CUSTOM_MINIMAP_CREATE_BLIP(x, y, z);
		return retval;
	}

	static void LUA_NATIVE_HUD_CUSTOM_MINIMAP_CLEAR_BLIPS()
	{
		HUD::CUSTOM_MINIMAP_CLEAR_BLIPS();
	}

	static bool LUA_NATIVE_HUD_FORCE_SONAR_BLIPS_THIS_FRAME()
	{
		auto retval = (bool)HUD::FORCE_SONAR_BLIPS_THIS_FRAME();
		return retval;
	}

	static Blip LUA_NATIVE_HUD_GET_NORTH_BLID_INDEX()
	{
		auto retval = HUD::GET_NORTH_BLID_INDEX();
		return retval;
	}

	static void LUA_NATIVE_HUD_DISPLAY_PLAYER_NAME_TAGS_ON_BLIPS(bool toggle)
	{
		HUD::DISPLAY_PLAYER_NAME_TAGS_ON_BLIPS(toggle);
	}

	static void LUA_NATIVE_HUD_DRAW_FRONTEND_BACKGROUND_THIS_FRAME()
	{
		HUD::DRAW_FRONTEND_BACKGROUND_THIS_FRAME();
	}

	static void LUA_NATIVE_HUD_DRAW_HUD_OVER_FADE_THIS_FRAME()
	{
		HUD::DRAW_HUD_OVER_FADE_THIS_FRAME();
	}

	static void LUA_NATIVE_HUD_ACTIVATE_FRONTEND_MENU(Hash menuhash, bool togglePause, int component)
	{
		HUD::ACTIVATE_FRONTEND_MENU(menuhash, togglePause, component);
	}

	static void LUA_NATIVE_HUD_RESTART_FRONTEND_MENU(Hash menuHash, int p1)
	{
		HUD::RESTART_FRONTEND_MENU(menuHash, p1);
	}

	static Hash LUA_NATIVE_HUD_GET_CURRENT_FRONTEND_MENU_VERSION()
	{
		auto retval = HUD::GET_CURRENT_FRONTEND_MENU_VERSION();
		return retval;
	}

	static void LUA_NATIVE_HUD_SET_PAUSE_MENU_ACTIVE(bool toggle)
	{
		HUD::SET_PAUSE_MENU_ACTIVE(toggle);
	}

	static void LUA_NATIVE_HUD_DISABLE_FRONTEND_THIS_FRAME()
	{
		HUD::DISABLE_FRONTEND_THIS_FRAME();
	}

	static void LUA_NATIVE_HUD_SUPPRESS_FRONTEND_RENDERING_THIS_FRAME()
	{
		HUD::SUPPRESS_FRONTEND_RENDERING_THIS_FRAME();
	}

	static void LUA_NATIVE_HUD_ALLOW_PAUSE_WHEN_NOT_IN_STATE_OF_PLAY_THIS_FRAME()
	{
		HUD::ALLOW_PAUSE_WHEN_NOT_IN_STATE_OF_PLAY_THIS_FRAME();
	}

	static void LUA_NATIVE_HUD_SET_FRONTEND_ACTIVE(bool active)
	{
		HUD::SET_FRONTEND_ACTIVE(active);
	}

	static bool LUA_NATIVE_HUD_IS_PAUSE_MENU_ACTIVE()
	{
		auto retval = (bool)HUD::IS_PAUSE_MENU_ACTIVE();
		return retval;
	}

	static bool LUA_NATIVE_HUD_IS_STORE_PENDING_NETWORK_SHUTDOWN_TO_OPEN()
	{
		auto retval = (bool)HUD::IS_STORE_PENDING_NETWORK_SHUTDOWN_TO_OPEN();
		return retval;
	}

	static int LUA_NATIVE_HUD_GET_PAUSE_MENU_STATE()
	{
		auto retval = HUD::GET_PAUSE_MENU_STATE();
		return retval;
	}

	static Vector3 LUA_NATIVE_HUD_GET_PAUSE_MENU_POSITION()
	{
		auto retval = HUD::GET_PAUSE_MENU_POSITION();
		return retval;
	}

	static bool LUA_NATIVE_HUD_IS_PAUSE_MENU_RESTARTING()
	{
		auto retval = (bool)HUD::IS_PAUSE_MENU_RESTARTING();
		return retval;
	}

	static void LUA_NATIVE_HUD_FORCE_SCRIPTED_GFX_WHEN_FRONTEND_ACTIVE(sol::stack_object p0)
	{
		HUD::FORCE_SCRIPTED_GFX_WHEN_FRONTEND_ACTIVE(p0.is<const char*>() ? p0.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_HUD_PAUSE_MENUCEPTION_GO_DEEPER(int page)
	{
		HUD::PAUSE_MENUCEPTION_GO_DEEPER(page);
	}

	static void LUA_NATIVE_HUD_PAUSE_MENUCEPTION_THE_KICK()
	{
		HUD::PAUSE_MENUCEPTION_THE_KICK();
	}

	static void LUA_NATIVE_HUD_PAUSE_TOGGLE_FULLSCREEN_MAP(Any p0)
	{
		HUD::PAUSE_TOGGLE_FULLSCREEN_MAP(p0);
	}

	static void LUA_NATIVE_HUD_PAUSE_MENU_ACTIVATE_CONTEXT(Hash contextHash)
	{
		HUD::PAUSE_MENU_ACTIVATE_CONTEXT(contextHash);
	}

	static void LUA_NATIVE_HUD_PAUSE_MENU_DEACTIVATE_CONTEXT(Hash contextHash)
	{
		HUD::PAUSE_MENU_DEACTIVATE_CONTEXT(contextHash);
	}

	static bool LUA_NATIVE_HUD_PAUSE_MENU_IS_CONTEXT_ACTIVE(Hash contextHash)
	{
		auto retval = (bool)HUD::PAUSE_MENU_IS_CONTEXT_ACTIVE(contextHash);
		return retval;
	}

	static bool LUA_NATIVE_HUD_PAUSE_MENU_IS_CONTEXT_MENU_ACTIVE()
	{
		auto retval = (bool)HUD::PAUSE_MENU_IS_CONTEXT_MENU_ACTIVE();
		return retval;
	}

	static int LUA_NATIVE_HUD_PAUSE_MENU_GET_HAIR_COLOUR_INDEX()
	{
		auto retval = HUD::PAUSE_MENU_GET_HAIR_COLOUR_INDEX();
		return retval;
	}

	static int LUA_NATIVE_HUD_PAUSE_MENU_GET_MOUSE_HOVER_INDEX()
	{
		auto retval = HUD::PAUSE_MENU_GET_MOUSE_HOVER_INDEX();
		return retval;
	}

	static int LUA_NATIVE_HUD_PAUSE_MENU_GET_MOUSE_HOVER_UNIQUE_ID()
	{
		auto retval = HUD::PAUSE_MENU_GET_MOUSE_HOVER_UNIQUE_ID();
		return retval;
	}

	static bool LUA_NATIVE_HUD_PAUSE_MENU_GET_MOUSE_CLICK_EVENT(uintptr_t p0, uintptr_t p1, uintptr_t p2)
	{
		auto retval = (bool)HUD::PAUSE_MENU_GET_MOUSE_CLICK_EVENT((Any*)p0, (Any*)p1, (Any*)p2);
		return retval;
	}

	static void LUA_NATIVE_HUD_PAUSE_MENU_REDRAW_INSTRUCTIONAL_BUTTONS(int p0)
	{
		HUD::PAUSE_MENU_REDRAW_INSTRUCTIONAL_BUTTONS(p0);
	}

	static void LUA_NATIVE_HUD_PAUSE_MENU_SET_BUSY_SPINNER(bool p0, int position, int spinnerIndex)
	{
		HUD::PAUSE_MENU_SET_BUSY_SPINNER(p0, position, spinnerIndex);
	}

	static void LUA_NATIVE_HUD_PAUSE_MENU_SET_WARN_ON_TAB_CHANGE(bool p0)
	{
		HUD::PAUSE_MENU_SET_WARN_ON_TAB_CHANGE(p0);
	}

	static bool LUA_NATIVE_HUD_IS_FRONTEND_READY_FOR_CONTROL()
	{
		auto retval = (bool)HUD::IS_FRONTEND_READY_FOR_CONTROL();
		return retval;
	}

	static void LUA_NATIVE_HUD_TAKE_CONTROL_OF_FRONTEND()
	{
		HUD::TAKE_CONTROL_OF_FRONTEND();
	}

	static void LUA_NATIVE_HUD_RELEASE_CONTROL_OF_FRONTEND()
	{
		HUD::RELEASE_CONTROL_OF_FRONTEND();
	}

	static bool LUA_NATIVE_HUD_CODE_WANTS_SCRIPT_TO_TAKE_CONTROL()
	{
		auto retval = (bool)HUD::CODE_WANTS_SCRIPT_TO_TAKE_CONTROL();
		return retval;
	}

	static int LUA_NATIVE_HUD_GET_SCREEN_CODE_WANTS_SCRIPT_TO_CONTROL()
	{
		auto retval = HUD::GET_SCREEN_CODE_WANTS_SCRIPT_TO_CONTROL();
		return retval;
	}

	static bool LUA_NATIVE_HUD_IS_NAVIGATING_MENU_CONTENT()
	{
		auto retval = (bool)HUD::IS_NAVIGATING_MENU_CONTENT();
		return retval;
	}

	static bool LUA_NATIVE_HUD_HAS_MENU_TRIGGER_EVENT_OCCURRED()
	{
		auto retval = (bool)HUD::HAS_MENU_TRIGGER_EVENT_OCCURRED();
		return retval;
	}

	static bool LUA_NATIVE_HUD_HAS_MENU_LAYOUT_CHANGED_EVENT_OCCURRED()
	{
		auto retval = (bool)HUD::HAS_MENU_LAYOUT_CHANGED_EVENT_OCCURRED();
		return retval;
	}

	static void LUA_NATIVE_HUD_SET_SAVEGAME_LIST_UNIQUE_ID(Any p0)
	{
		HUD::SET_SAVEGAME_LIST_UNIQUE_ID(p0);
	}

	static std::tuple<int, int> LUA_NATIVE_HUD_GET_MENU_TRIGGER_EVENT_DETAILS(int lastItemMenuId, int selectedItemUniqueId)
	{
		std::tuple<int, int> return_values;
		HUD::GET_MENU_TRIGGER_EVENT_DETAILS(&lastItemMenuId, &selectedItemUniqueId);
		std::get<0>(return_values) = lastItemMenuId;
		std::get<1>(return_values) = selectedItemUniqueId;

		return return_values;
	}

	static std::tuple<int, int, int> LUA_NATIVE_HUD_GET_MENU_LAYOUT_CHANGED_EVENT_DETAILS(int lastItemMenuId, int selectedItemMenuId, int selectedItemUniqueId)
	{
		std::tuple<int, int, int> return_values;
		HUD::GET_MENU_LAYOUT_CHANGED_EVENT_DETAILS(&lastItemMenuId, &selectedItemMenuId, &selectedItemUniqueId);
		std::get<0>(return_values) = lastItemMenuId;
		std::get<1>(return_values) = selectedItemMenuId;
		std::get<2>(return_values) = selectedItemUniqueId;

		return return_values;
	}

	static std::tuple<bool, int, int, int> LUA_NATIVE_HUD_GET_PM_PLAYER_CREW_COLOR(int r, int g, int b)
	{
		std::tuple<bool, int, int, int> return_values;
		std::get<0>(return_values) = (bool)HUD::GET_PM_PLAYER_CREW_COLOR(&r, &g, &b);
		std::get<1>(return_values) = r;
		std::get<2>(return_values) = g;
		std::get<3>(return_values) = b;

		return return_values;
	}

	static bool LUA_NATIVE_HUD_GET_MENU_PED_INT_STAT(Any p0, uintptr_t p1)
	{
		auto retval = (bool)HUD::GET_MENU_PED_INT_STAT(p0, (Any*)p1);
		return retval;
	}

	static bool LUA_NATIVE_HUD_GET_CHARACTER_MENU_PED_INT_STAT(Any p0, uintptr_t p1, Any p2)
	{
		auto retval = (bool)HUD::GET_CHARACTER_MENU_PED_INT_STAT(p0, (Any*)p1, p2);
		return retval;
	}

	static std::tuple<bool, int> LUA_NATIVE_HUD_GET_MENU_PED_MASKED_INT_STAT(Hash statHash, int outValue, int mask, bool p3)
	{
		std::tuple<bool, int> return_values;
		std::get<0>(return_values) = (bool)HUD::GET_MENU_PED_MASKED_INT_STAT(statHash, &outValue, mask, p3);
		std::get<1>(return_values) = outValue;

		return return_values;
	}

	static bool LUA_NATIVE_HUD_GET_CHARACTER_MENU_PED_MASKED_INT_STAT(Hash statHash, uintptr_t outValue, int p2, int mask, bool p4)
	{
		auto retval = (bool)HUD::GET_CHARACTER_MENU_PED_MASKED_INT_STAT(statHash, (Any*)outValue, p2, mask, p4);
		return retval;
	}

	static std::tuple<bool, float> LUA_NATIVE_HUD_GET_MENU_PED_FLOAT_STAT(Hash statHash, float outValue)
	{
		std::tuple<bool, float> return_values;
		std::get<0>(return_values) = (bool)HUD::GET_MENU_PED_FLOAT_STAT(statHash, &outValue);
		std::get<1>(return_values) = outValue;

		return return_values;
	}

	static std::tuple<bool, float> LUA_NATIVE_HUD_GET_CHARACTER_MENU_PED_FLOAT_STAT(float statHash, float outValue, bool p2)
	{
		std::tuple<bool, float> return_values;
		std::get<0>(return_values) = (bool)HUD::GET_CHARACTER_MENU_PED_FLOAT_STAT(statHash, &outValue, p2);
		std::get<1>(return_values) = outValue;

		return return_values;
	}

	static std::tuple<bool, bool> LUA_NATIVE_HUD_GET_MENU_PED_BOOL_STAT(Hash statHash, bool outValue)
	{
		std::tuple<bool, bool> return_values;
		std::get<0>(return_values) = (bool)HUD::GET_MENU_PED_BOOL_STAT(statHash, (BOOL*)&outValue);
		std::get<1>(return_values) = outValue;

		return return_values;
	}

	static void LUA_NATIVE_HUD_CLEAR_PED_IN_PAUSE_MENU()
	{
		HUD::CLEAR_PED_IN_PAUSE_MENU();
	}

	static void LUA_NATIVE_HUD_GIVE_PED_TO_PAUSE_MENU(Ped ped, int p1)
	{
		HUD::GIVE_PED_TO_PAUSE_MENU(ped, p1);
	}

	static void LUA_NATIVE_HUD_SET_PAUSE_MENU_PED_LIGHTING(bool state)
	{
		HUD::SET_PAUSE_MENU_PED_LIGHTING(state);
	}

	static void LUA_NATIVE_HUD_SET_PAUSE_MENU_PED_SLEEP_STATE(bool state)
	{
		HUD::SET_PAUSE_MENU_PED_SLEEP_STATE(state);
	}

	static void LUA_NATIVE_HUD_OPEN_ONLINE_POLICIES_MENU()
	{
		HUD::OPEN_ONLINE_POLICIES_MENU();
	}

	static bool LUA_NATIVE_HUD_ARE_ONLINE_POLICIES_UP_TO_DATE()
	{
		auto retval = (bool)HUD::ARE_ONLINE_POLICIES_UP_TO_DATE();
		return retval;
	}

	static bool LUA_NATIVE_HUD_IS_ONLINE_POLICIES_MENU_ACTIVE()
	{
		auto retval = (bool)HUD::IS_ONLINE_POLICIES_MENU_ACTIVE();
		return retval;
	}

	static void LUA_NATIVE_HUD_OPEN_SOCIAL_CLUB_MENU(Hash menu)
	{
		HUD::OPEN_SOCIAL_CLUB_MENU(menu);
	}

	static void LUA_NATIVE_HUD_CLOSE_SOCIAL_CLUB_MENU()
	{
		HUD::CLOSE_SOCIAL_CLUB_MENU();
	}

	static void LUA_NATIVE_HUD_SET_SOCIAL_CLUB_TOUR(sol::stack_object name)
	{
		HUD::SET_SOCIAL_CLUB_TOUR(name.is<const char*>() ? name.as<const char*>() : nullptr);
	}

	static bool LUA_NATIVE_HUD_IS_SOCIAL_CLUB_ACTIVE()
	{
		auto retval = (bool)HUD::IS_SOCIAL_CLUB_ACTIVE();
		return retval;
	}

	static void LUA_NATIVE_HUD_SET_TEXT_INPUT_BOX_ENABLED(bool p0)
	{
		HUD::SET_TEXT_INPUT_BOX_ENABLED(p0);
	}

	static void LUA_NATIVE_HUD_FORCE_CLOSE_TEXT_INPUT_BOX()
	{
		HUD::FORCE_CLOSE_TEXT_INPUT_BOX();
	}

	static void LUA_NATIVE_HUD_SET_ALLOW_COMMA_ON_TEXT_INPUT(Any p0)
	{
		HUD::SET_ALLOW_COMMA_ON_TEXT_INPUT(p0);
	}

	static void LUA_NATIVE_HUD_OVERRIDE_MP_TEXT_CHAT_TEAM_STRING(Hash gxtEntryHash)
	{
		HUD::OVERRIDE_MP_TEXT_CHAT_TEAM_STRING(gxtEntryHash);
	}

	static bool LUA_NATIVE_HUD_IS_MP_TEXT_CHAT_TYPING()
	{
		auto retval = (bool)HUD::IS_MP_TEXT_CHAT_TYPING();
		return retval;
	}

	static void LUA_NATIVE_HUD_CLOSE_MP_TEXT_CHAT()
	{
		HUD::CLOSE_MP_TEXT_CHAT();
	}

	static void LUA_NATIVE_HUD_MP_TEXT_CHAT_IS_TEAM_JOB(Any p0)
	{
		HUD::MP_TEXT_CHAT_IS_TEAM_JOB(p0);
	}

	static void LUA_NATIVE_HUD_OVERRIDE_MP_TEXT_CHAT_COLOR(int p0, int hudColor)
	{
		HUD::OVERRIDE_MP_TEXT_CHAT_COLOR(p0, hudColor);
	}

	static void LUA_NATIVE_HUD_MP_TEXT_CHAT_DISABLE(bool toggle)
	{
		HUD::MP_TEXT_CHAT_DISABLE(toggle);
	}

	static void LUA_NATIVE_HUD_FLAG_PLAYER_CONTEXT_IN_TOURNAMENT(bool toggle)
	{
		HUD::FLAG_PLAYER_CONTEXT_IN_TOURNAMENT(toggle);
	}

	static void LUA_NATIVE_HUD_SET_PED_HAS_AI_BLIP(Ped ped, bool hasCone)
	{
		HUD::SET_PED_HAS_AI_BLIP(ped, hasCone);
	}

	static void LUA_NATIVE_HUD_SET_PED_HAS_AI_BLIP_WITH_COLOUR(Ped ped, bool hasCone, int color)
	{
		HUD::SET_PED_HAS_AI_BLIP_WITH_COLOUR(ped, hasCone, color);
	}

	static bool LUA_NATIVE_HUD_DOES_PED_HAVE_AI_BLIP(Ped ped)
	{
		auto retval = (bool)HUD::DOES_PED_HAVE_AI_BLIP(ped);
		return retval;
	}

	static void LUA_NATIVE_HUD_SET_PED_AI_BLIP_GANG_ID(Ped ped, int gangId)
	{
		HUD::SET_PED_AI_BLIP_GANG_ID(ped, gangId);
	}

	static void LUA_NATIVE_HUD_SET_PED_AI_BLIP_HAS_CONE(Ped ped, bool toggle)
	{
		HUD::SET_PED_AI_BLIP_HAS_CONE(ped, toggle);
	}

	static void LUA_NATIVE_HUD_SET_PED_AI_BLIP_FORCED_ON(Ped ped, bool toggle)
	{
		HUD::SET_PED_AI_BLIP_FORCED_ON(ped, toggle);
	}

	static void LUA_NATIVE_HUD_SET_PED_AI_BLIP_NOTICE_RANGE(Ped ped, float range)
	{
		HUD::SET_PED_AI_BLIP_NOTICE_RANGE(ped, range);
	}

	static void LUA_NATIVE_HUD_SET_PED_AI_BLIP_SPRITE(Ped ped, int spriteId)
	{
		HUD::SET_PED_AI_BLIP_SPRITE(ped, spriteId);
	}

	static Blip LUA_NATIVE_HUD_GET_AI_PED_PED_BLIP_INDEX(Ped ped)
	{
		auto retval = HUD::GET_AI_PED_PED_BLIP_INDEX(ped);
		return retval;
	}

	static Blip LUA_NATIVE_HUD_GET_AI_PED_VEHICLE_BLIP_INDEX(Ped ped)
	{
		auto retval = HUD::GET_AI_PED_VEHICLE_BLIP_INDEX(ped);
		return retval;
	}

	static bool LUA_NATIVE_HUD_HAS_DIRECTOR_MODE_BEEN_LAUNCHED_BY_CODE()
	{
		auto retval = (bool)HUD::HAS_DIRECTOR_MODE_BEEN_LAUNCHED_BY_CODE();
		return retval;
	}

	static void LUA_NATIVE_HUD_SET_DIRECTOR_MODE_LAUNCHED_BY_SCRIPT()
	{
		HUD::SET_DIRECTOR_MODE_LAUNCHED_BY_SCRIPT();
	}

	static void LUA_NATIVE_HUD_SET_PLAYER_IS_IN_DIRECTOR_MODE(bool toggle)
	{
		HUD::SET_PLAYER_IS_IN_DIRECTOR_MODE(toggle);
	}

	static void LUA_NATIVE_HUD_SET_DIRECTOR_MODE_AVAILABLE(bool toggle)
	{
		HUD::SET_DIRECTOR_MODE_AVAILABLE(toggle);
	}

	static void LUA_NATIVE_HUD_HIDE_HUDMARKERS_THIS_FRAME()
	{
		HUD::HIDE_HUDMARKERS_THIS_FRAME();
	}

	void init_native_binding_HUD(sol::state& L)
	{
		auto HUD = L["HUD"].get_or_create<sol::table>();
		HUD.set_function("BEGIN_TEXT_COMMAND_BUSYSPINNER_ON", LUA_NATIVE_HUD_BEGIN_TEXT_COMMAND_BUSYSPINNER_ON);
		HUD.set_function("END_TEXT_COMMAND_BUSYSPINNER_ON", LUA_NATIVE_HUD_END_TEXT_COMMAND_BUSYSPINNER_ON);
		HUD.set_function("BUSYSPINNER_OFF", LUA_NATIVE_HUD_BUSYSPINNER_OFF);
		HUD.set_function("PRELOAD_BUSYSPINNER", LUA_NATIVE_HUD_PRELOAD_BUSYSPINNER);
		HUD.set_function("BUSYSPINNER_IS_ON", LUA_NATIVE_HUD_BUSYSPINNER_IS_ON);
		HUD.set_function("BUSYSPINNER_IS_DISPLAYING", LUA_NATIVE_HUD_BUSYSPINNER_IS_DISPLAYING);
		HUD.set_function("DISABLE_PAUSEMENU_SPINNER", LUA_NATIVE_HUD_DISABLE_PAUSEMENU_SPINNER);
		HUD.set_function("SET_MOUSE_CURSOR_THIS_FRAME", LUA_NATIVE_HUD_SET_MOUSE_CURSOR_THIS_FRAME);
		HUD.set_function("SET_MOUSE_CURSOR_STYLE", LUA_NATIVE_HUD_SET_MOUSE_CURSOR_STYLE);
		HUD.set_function("SET_MOUSE_CURSOR_VISIBLE", LUA_NATIVE_HUD_SET_MOUSE_CURSOR_VISIBLE);
		HUD.set_function("IS_MOUSE_ROLLED_OVER_INSTRUCTIONAL_BUTTONS", LUA_NATIVE_HUD_IS_MOUSE_ROLLED_OVER_INSTRUCTIONAL_BUTTONS);
		HUD.set_function("GET_MOUSE_EVENT", LUA_NATIVE_HUD_GET_MOUSE_EVENT);
		HUD.set_function("THEFEED_ONLY_SHOW_TOOLTIPS", LUA_NATIVE_HUD_THEFEED_ONLY_SHOW_TOOLTIPS);
		HUD.set_function("THEFEED_SET_SCRIPTED_MENU_HEIGHT", LUA_NATIVE_HUD_THEFEED_SET_SCRIPTED_MENU_HEIGHT);
		HUD.set_function("THEFEED_HIDE", LUA_NATIVE_HUD_THEFEED_HIDE);
		HUD.set_function("THEFEED_HIDE_THIS_FRAME", LUA_NATIVE_HUD_THEFEED_HIDE_THIS_FRAME);
		HUD.set_function("THEFEED_SHOW", LUA_NATIVE_HUD_THEFEED_SHOW);
		HUD.set_function("THEFEED_FLUSH_QUEUE", LUA_NATIVE_HUD_THEFEED_FLUSH_QUEUE);
		HUD.set_function("THEFEED_REMOVE_ITEM", LUA_NATIVE_HUD_THEFEED_REMOVE_ITEM);
		HUD.set_function("THEFEED_FORCE_RENDER_ON", LUA_NATIVE_HUD_THEFEED_FORCE_RENDER_ON);
		HUD.set_function("THEFEED_FORCE_RENDER_OFF", LUA_NATIVE_HUD_THEFEED_FORCE_RENDER_OFF);
		HUD.set_function("THEFEED_PAUSE", LUA_NATIVE_HUD_THEFEED_PAUSE);
		HUD.set_function("THEFEED_RESUME", LUA_NATIVE_HUD_THEFEED_RESUME);
		HUD.set_function("THEFEED_IS_PAUSED", LUA_NATIVE_HUD_THEFEED_IS_PAUSED);
		HUD.set_function("THEFEED_REPORT_LOGO_ON", LUA_NATIVE_HUD_THEFEED_REPORT_LOGO_ON);
		HUD.set_function("THEFEED_REPORT_LOGO_OFF", LUA_NATIVE_HUD_THEFEED_REPORT_LOGO_OFF);
		HUD.set_function("THEFEED_GET_LAST_SHOWN_PHONE_ACTIVATABLE_FEED_ID", LUA_NATIVE_HUD_THEFEED_GET_LAST_SHOWN_PHONE_ACTIVATABLE_FEED_ID);
		HUD.set_function("THEFEED_AUTO_POST_GAMETIPS_ON", LUA_NATIVE_HUD_THEFEED_AUTO_POST_GAMETIPS_ON);
		HUD.set_function("THEFEED_AUTO_POST_GAMETIPS_OFF", LUA_NATIVE_HUD_THEFEED_AUTO_POST_GAMETIPS_OFF);
		HUD.set_function("THEFEED_SET_BACKGROUND_COLOR_FOR_NEXT_POST", LUA_NATIVE_HUD_THEFEED_SET_BACKGROUND_COLOR_FOR_NEXT_POST);
		HUD.set_function("THEFEED_SET_RGBA_PARAMETER_FOR_NEXT_MESSAGE", LUA_NATIVE_HUD_THEFEED_SET_RGBA_PARAMETER_FOR_NEXT_MESSAGE);
		HUD.set_function("THEFEED_SET_FLASH_DURATION_PARAMETER_FOR_NEXT_MESSAGE", LUA_NATIVE_HUD_THEFEED_SET_FLASH_DURATION_PARAMETER_FOR_NEXT_MESSAGE);
		HUD.set_function("THEFEED_SET_VIBRATE_PARAMETER_FOR_NEXT_MESSAGE", LUA_NATIVE_HUD_THEFEED_SET_VIBRATE_PARAMETER_FOR_NEXT_MESSAGE);
		HUD.set_function("THEFEED_RESET_ALL_PARAMETERS", LUA_NATIVE_HUD_THEFEED_RESET_ALL_PARAMETERS);
		HUD.set_function("THEFEED_FREEZE_NEXT_POST", LUA_NATIVE_HUD_THEFEED_FREEZE_NEXT_POST);
		HUD.set_function("THEFEED_CLEAR_FROZEN_POST", LUA_NATIVE_HUD_THEFEED_CLEAR_FROZEN_POST);
		HUD.set_function("THEFEED_SET_SNAP_FEED_ITEM_POSITIONS", LUA_NATIVE_HUD_THEFEED_SET_SNAP_FEED_ITEM_POSITIONS);
		HUD.set_function("THEFEED_UPDATE_ITEM_TEXTURE", LUA_NATIVE_HUD_THEFEED_UPDATE_ITEM_TEXTURE);
		HUD.set_function("BEGIN_TEXT_COMMAND_THEFEED_POST", LUA_NATIVE_HUD_BEGIN_TEXT_COMMAND_THEFEED_POST);
		HUD.set_function("END_TEXT_COMMAND_THEFEED_POST_STATS", LUA_NATIVE_HUD_END_TEXT_COMMAND_THEFEED_POST_STATS);
		HUD.set_function("END_TEXT_COMMAND_THEFEED_POST_MESSAGETEXT", LUA_NATIVE_HUD_END_TEXT_COMMAND_THEFEED_POST_MESSAGETEXT);
		HUD.set_function("END_TEXT_COMMAND_THEFEED_POST_MESSAGETEXT_SUBTITLE_LABEL", LUA_NATIVE_HUD_END_TEXT_COMMAND_THEFEED_POST_MESSAGETEXT_SUBTITLE_LABEL);
		HUD.set_function("END_TEXT_COMMAND_THEFEED_POST_MESSAGETEXT_TU", LUA_NATIVE_HUD_END_TEXT_COMMAND_THEFEED_POST_MESSAGETEXT_TU);
		HUD.set_function("END_TEXT_COMMAND_THEFEED_POST_MESSAGETEXT_WITH_CREW_TAG", LUA_NATIVE_HUD_END_TEXT_COMMAND_THEFEED_POST_MESSAGETEXT_WITH_CREW_TAG);
		HUD.set_function("END_TEXT_COMMAND_THEFEED_POST_MESSAGETEXT_WITH_CREW_TAG_AND_ADDITIONAL_ICON", LUA_NATIVE_HUD_END_TEXT_COMMAND_THEFEED_POST_MESSAGETEXT_WITH_CREW_TAG_AND_ADDITIONAL_ICON);
		HUD.set_function("END_TEXT_COMMAND_THEFEED_POST_TICKER", LUA_NATIVE_HUD_END_TEXT_COMMAND_THEFEED_POST_TICKER);
		HUD.set_function("END_TEXT_COMMAND_THEFEED_POST_TICKER_FORCED", LUA_NATIVE_HUD_END_TEXT_COMMAND_THEFEED_POST_TICKER_FORCED);
		HUD.set_function("END_TEXT_COMMAND_THEFEED_POST_TICKER_WITH_TOKENS", LUA_NATIVE_HUD_END_TEXT_COMMAND_THEFEED_POST_TICKER_WITH_TOKENS);
		HUD.set_function("END_TEXT_COMMAND_THEFEED_POST_AWARD", LUA_NATIVE_HUD_END_TEXT_COMMAND_THEFEED_POST_AWARD);
		HUD.set_function("END_TEXT_COMMAND_THEFEED_POST_CREWTAG", LUA_NATIVE_HUD_END_TEXT_COMMAND_THEFEED_POST_CREWTAG);
		HUD.set_function("END_TEXT_COMMAND_THEFEED_POST_CREWTAG_WITH_GAME_NAME", LUA_NATIVE_HUD_END_TEXT_COMMAND_THEFEED_POST_CREWTAG_WITH_GAME_NAME);
		HUD.set_function("END_TEXT_COMMAND_THEFEED_POST_UNLOCK", LUA_NATIVE_HUD_END_TEXT_COMMAND_THEFEED_POST_UNLOCK);
		HUD.set_function("END_TEXT_COMMAND_THEFEED_POST_UNLOCK_TU", LUA_NATIVE_HUD_END_TEXT_COMMAND_THEFEED_POST_UNLOCK_TU);
		HUD.set_function("END_TEXT_COMMAND_THEFEED_POST_UNLOCK_TU_WITH_COLOR", LUA_NATIVE_HUD_END_TEXT_COMMAND_THEFEED_POST_UNLOCK_TU_WITH_COLOR);
		HUD.set_function("END_TEXT_COMMAND_THEFEED_POST_MPTICKER", LUA_NATIVE_HUD_END_TEXT_COMMAND_THEFEED_POST_MPTICKER);
		HUD.set_function("END_TEXT_COMMAND_THEFEED_POST_CREW_RANKUP_WITH_LITERAL_FLAG", LUA_NATIVE_HUD_END_TEXT_COMMAND_THEFEED_POST_CREW_RANKUP_WITH_LITERAL_FLAG);
		HUD.set_function("END_TEXT_COMMAND_THEFEED_POST_VERSUS_TU", LUA_NATIVE_HUD_END_TEXT_COMMAND_THEFEED_POST_VERSUS_TU);
		HUD.set_function("END_TEXT_COMMAND_THEFEED_POST_REPLAY", LUA_NATIVE_HUD_END_TEXT_COMMAND_THEFEED_POST_REPLAY);
		HUD.set_function("END_TEXT_COMMAND_THEFEED_POST_REPLAY_INPUT", LUA_NATIVE_HUD_END_TEXT_COMMAND_THEFEED_POST_REPLAY_INPUT);
		HUD.set_function("BEGIN_TEXT_COMMAND_PRINT", LUA_NATIVE_HUD_BEGIN_TEXT_COMMAND_PRINT);
		HUD.set_function("END_TEXT_COMMAND_PRINT", LUA_NATIVE_HUD_END_TEXT_COMMAND_PRINT);
		HUD.set_function("BEGIN_TEXT_COMMAND_IS_MESSAGE_DISPLAYED", LUA_NATIVE_HUD_BEGIN_TEXT_COMMAND_IS_MESSAGE_DISPLAYED);
		HUD.set_function("END_TEXT_COMMAND_IS_MESSAGE_DISPLAYED", LUA_NATIVE_HUD_END_TEXT_COMMAND_IS_MESSAGE_DISPLAYED);
		HUD.set_function("BEGIN_TEXT_COMMAND_DISPLAY_TEXT", LUA_NATIVE_HUD_BEGIN_TEXT_COMMAND_DISPLAY_TEXT);
		HUD.set_function("END_TEXT_COMMAND_DISPLAY_TEXT", LUA_NATIVE_HUD_END_TEXT_COMMAND_DISPLAY_TEXT);
		HUD.set_function("BEGIN_TEXT_COMMAND_GET_SCREEN_WIDTH_OF_DISPLAY_TEXT", LUA_NATIVE_HUD_BEGIN_TEXT_COMMAND_GET_SCREEN_WIDTH_OF_DISPLAY_TEXT);
		HUD.set_function("END_TEXT_COMMAND_GET_SCREEN_WIDTH_OF_DISPLAY_TEXT", LUA_NATIVE_HUD_END_TEXT_COMMAND_GET_SCREEN_WIDTH_OF_DISPLAY_TEXT);
		HUD.set_function("BEGIN_TEXT_COMMAND_GET_NUMBER_OF_LINES_FOR_STRING", LUA_NATIVE_HUD_BEGIN_TEXT_COMMAND_GET_NUMBER_OF_LINES_FOR_STRING);
		HUD.set_function("END_TEXT_COMMAND_GET_NUMBER_OF_LINES_FOR_STRING", LUA_NATIVE_HUD_END_TEXT_COMMAND_GET_NUMBER_OF_LINES_FOR_STRING);
		HUD.set_function("BEGIN_TEXT_COMMAND_DISPLAY_HELP", LUA_NATIVE_HUD_BEGIN_TEXT_COMMAND_DISPLAY_HELP);
		HUD.set_function("END_TEXT_COMMAND_DISPLAY_HELP", LUA_NATIVE_HUD_END_TEXT_COMMAND_DISPLAY_HELP);
		HUD.set_function("BEGIN_TEXT_COMMAND_IS_THIS_HELP_MESSAGE_BEING_DISPLAYED", LUA_NATIVE_HUD_BEGIN_TEXT_COMMAND_IS_THIS_HELP_MESSAGE_BEING_DISPLAYED);
		HUD.set_function("END_TEXT_COMMAND_IS_THIS_HELP_MESSAGE_BEING_DISPLAYED", LUA_NATIVE_HUD_END_TEXT_COMMAND_IS_THIS_HELP_MESSAGE_BEING_DISPLAYED);
		HUD.set_function("BEGIN_TEXT_COMMAND_SET_BLIP_NAME", LUA_NATIVE_HUD_BEGIN_TEXT_COMMAND_SET_BLIP_NAME);
		HUD.set_function("END_TEXT_COMMAND_SET_BLIP_NAME", LUA_NATIVE_HUD_END_TEXT_COMMAND_SET_BLIP_NAME);
		HUD.set_function("BEGIN_TEXT_COMMAND_ADD_DIRECTLY_TO_PREVIOUS_BRIEFS", LUA_NATIVE_HUD_BEGIN_TEXT_COMMAND_ADD_DIRECTLY_TO_PREVIOUS_BRIEFS);
		HUD.set_function("END_TEXT_COMMAND_ADD_DIRECTLY_TO_PREVIOUS_BRIEFS", LUA_NATIVE_HUD_END_TEXT_COMMAND_ADD_DIRECTLY_TO_PREVIOUS_BRIEFS);
		HUD.set_function("BEGIN_TEXT_COMMAND_CLEAR_PRINT", LUA_NATIVE_HUD_BEGIN_TEXT_COMMAND_CLEAR_PRINT);
		HUD.set_function("END_TEXT_COMMAND_CLEAR_PRINT", LUA_NATIVE_HUD_END_TEXT_COMMAND_CLEAR_PRINT);
		HUD.set_function("BEGIN_TEXT_COMMAND_OVERRIDE_BUTTON_TEXT", LUA_NATIVE_HUD_BEGIN_TEXT_COMMAND_OVERRIDE_BUTTON_TEXT);
		HUD.set_function("END_TEXT_COMMAND_OVERRIDE_BUTTON_TEXT", LUA_NATIVE_HUD_END_TEXT_COMMAND_OVERRIDE_BUTTON_TEXT);
		HUD.set_function("ADD_TEXT_COMPONENT_INTEGER", LUA_NATIVE_HUD_ADD_TEXT_COMPONENT_INTEGER);
		HUD.set_function("ADD_TEXT_COMPONENT_FLOAT", LUA_NATIVE_HUD_ADD_TEXT_COMPONENT_FLOAT);
		HUD.set_function("ADD_TEXT_COMPONENT_SUBSTRING_TEXT_LABEL", LUA_NATIVE_HUD_ADD_TEXT_COMPONENT_SUBSTRING_TEXT_LABEL);
		HUD.set_function("ADD_TEXT_COMPONENT_SUBSTRING_TEXT_LABEL_HASH_KEY", LUA_NATIVE_HUD_ADD_TEXT_COMPONENT_SUBSTRING_TEXT_LABEL_HASH_KEY);
		HUD.set_function("ADD_TEXT_COMPONENT_SUBSTRING_BLIP_NAME", LUA_NATIVE_HUD_ADD_TEXT_COMPONENT_SUBSTRING_BLIP_NAME);
		HUD.set_function("ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME", LUA_NATIVE_HUD_ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME);
		HUD.set_function("ADD_TEXT_COMPONENT_SUBSTRING_TIME", LUA_NATIVE_HUD_ADD_TEXT_COMPONENT_SUBSTRING_TIME);
		HUD.set_function("ADD_TEXT_COMPONENT_FORMATTED_INTEGER", LUA_NATIVE_HUD_ADD_TEXT_COMPONENT_FORMATTED_INTEGER);
		HUD.set_function("ADD_TEXT_COMPONENT_SUBSTRING_PHONE_NUMBER", LUA_NATIVE_HUD_ADD_TEXT_COMPONENT_SUBSTRING_PHONE_NUMBER);
		HUD.set_function("ADD_TEXT_COMPONENT_SUBSTRING_WEBSITE", LUA_NATIVE_HUD_ADD_TEXT_COMPONENT_SUBSTRING_WEBSITE);
		HUD.set_function("ADD_TEXT_COMPONENT_SUBSTRING_KEYBOARD_DISPLAY", LUA_NATIVE_HUD_ADD_TEXT_COMPONENT_SUBSTRING_KEYBOARD_DISPLAY);
		HUD.set_function("SET_COLOUR_OF_NEXT_TEXT_COMPONENT", LUA_NATIVE_HUD_SET_COLOUR_OF_NEXT_TEXT_COMPONENT);
		HUD.set_function("GET_CHARACTER_FROM_AUDIO_CONVERSATION_FILENAME", LUA_NATIVE_HUD_GET_CHARACTER_FROM_AUDIO_CONVERSATION_FILENAME);
		HUD.set_function("GET_CHARACTER_FROM_AUDIO_CONVERSATION_FILENAME_WITH_BYTE_LIMIT", LUA_NATIVE_HUD_GET_CHARACTER_FROM_AUDIO_CONVERSATION_FILENAME_WITH_BYTE_LIMIT);
		HUD.set_function("GET_CHARACTER_FROM_AUDIO_CONVERSATION_FILENAME_BYTES", LUA_NATIVE_HUD_GET_CHARACTER_FROM_AUDIO_CONVERSATION_FILENAME_BYTES);
		HUD.set_function("GET_FILENAME_FOR_AUDIO_CONVERSATION", LUA_NATIVE_HUD_GET_FILENAME_FOR_AUDIO_CONVERSATION);
		HUD.set_function("CLEAR_PRINTS", LUA_NATIVE_HUD_CLEAR_PRINTS);
		HUD.set_function("CLEAR_BRIEF", LUA_NATIVE_HUD_CLEAR_BRIEF);
		HUD.set_function("CLEAR_ALL_HELP_MESSAGES", LUA_NATIVE_HUD_CLEAR_ALL_HELP_MESSAGES);
		HUD.set_function("CLEAR_THIS_PRINT", LUA_NATIVE_HUD_CLEAR_THIS_PRINT);
		HUD.set_function("CLEAR_SMALL_PRINTS", LUA_NATIVE_HUD_CLEAR_SMALL_PRINTS);
		HUD.set_function("DOES_TEXT_BLOCK_EXIST", LUA_NATIVE_HUD_DOES_TEXT_BLOCK_EXIST);
		HUD.set_function("REQUEST_ADDITIONAL_TEXT", LUA_NATIVE_HUD_REQUEST_ADDITIONAL_TEXT);
		HUD.set_function("REQUEST_ADDITIONAL_TEXT_FOR_DLC", LUA_NATIVE_HUD_REQUEST_ADDITIONAL_TEXT_FOR_DLC);
		HUD.set_function("HAS_ADDITIONAL_TEXT_LOADED", LUA_NATIVE_HUD_HAS_ADDITIONAL_TEXT_LOADED);
		HUD.set_function("CLEAR_ADDITIONAL_TEXT", LUA_NATIVE_HUD_CLEAR_ADDITIONAL_TEXT);
		HUD.set_function("IS_STREAMING_ADDITIONAL_TEXT", LUA_NATIVE_HUD_IS_STREAMING_ADDITIONAL_TEXT);
		HUD.set_function("HAS_THIS_ADDITIONAL_TEXT_LOADED", LUA_NATIVE_HUD_HAS_THIS_ADDITIONAL_TEXT_LOADED);
		HUD.set_function("IS_MESSAGE_BEING_DISPLAYED", LUA_NATIVE_HUD_IS_MESSAGE_BEING_DISPLAYED);
		HUD.set_function("DOES_TEXT_LABEL_EXIST", LUA_NATIVE_HUD_DOES_TEXT_LABEL_EXIST);
		HUD.set_function("GET_FIRST_N_CHARACTERS_OF_LITERAL_STRING", LUA_NATIVE_HUD_GET_FIRST_N_CHARACTERS_OF_LITERAL_STRING);
		HUD.set_function("GET_LENGTH_OF_STRING_WITH_THIS_TEXT_LABEL", LUA_NATIVE_HUD_GET_LENGTH_OF_STRING_WITH_THIS_TEXT_LABEL);
		HUD.set_function("GET_LENGTH_OF_LITERAL_STRING", LUA_NATIVE_HUD_GET_LENGTH_OF_LITERAL_STRING);
		HUD.set_function("GET_LENGTH_OF_LITERAL_STRING_IN_BYTES", LUA_NATIVE_HUD_GET_LENGTH_OF_LITERAL_STRING_IN_BYTES);
		HUD.set_function("GET_STREET_NAME_FROM_HASH_KEY", LUA_NATIVE_HUD_GET_STREET_NAME_FROM_HASH_KEY);
		HUD.set_function("IS_HUD_PREFERENCE_SWITCHED_ON", LUA_NATIVE_HUD_IS_HUD_PREFERENCE_SWITCHED_ON);
		HUD.set_function("IS_RADAR_PREFERENCE_SWITCHED_ON", LUA_NATIVE_HUD_IS_RADAR_PREFERENCE_SWITCHED_ON);
		HUD.set_function("IS_SUBTITLE_PREFERENCE_SWITCHED_ON", LUA_NATIVE_HUD_IS_SUBTITLE_PREFERENCE_SWITCHED_ON);
		HUD.set_function("DISPLAY_HUD", LUA_NATIVE_HUD_DISPLAY_HUD);
		HUD.set_function("DISPLAY_HUD_WHEN_NOT_IN_STATE_OF_PLAY_THIS_FRAME", LUA_NATIVE_HUD_DISPLAY_HUD_WHEN_NOT_IN_STATE_OF_PLAY_THIS_FRAME);
		HUD.set_function("DISPLAY_HUD_WHEN_PAUSED_THIS_FRAME", LUA_NATIVE_HUD_DISPLAY_HUD_WHEN_PAUSED_THIS_FRAME);
		HUD.set_function("DISPLAY_RADAR", LUA_NATIVE_HUD_DISPLAY_RADAR);
		HUD.set_function("SET_FAKE_SPECTATOR_MODE", LUA_NATIVE_HUD_SET_FAKE_SPECTATOR_MODE);
		HUD.set_function("GET_FAKE_SPECTATOR_MODE", LUA_NATIVE_HUD_GET_FAKE_SPECTATOR_MODE);
		HUD.set_function("IS_HUD_HIDDEN", LUA_NATIVE_HUD_IS_HUD_HIDDEN);
		HUD.set_function("IS_RADAR_HIDDEN", LUA_NATIVE_HUD_IS_RADAR_HIDDEN);
		HUD.set_function("IS_MINIMAP_RENDERING", LUA_NATIVE_HUD_IS_MINIMAP_RENDERING);
		HUD.set_function("USE_VEHICLE_TARGETING_RETICULE", LUA_NATIVE_HUD_USE_VEHICLE_TARGETING_RETICULE);
		HUD.set_function("USE_VEHICLE_TARGETING_RETICULE_ON_VEHICLES_", LUA_NATIVE_HUD_USE_VEHICLE_TARGETING_RETICULE_ON_VEHICLES_);
		HUD.set_function("ADD_VALID_VEHICLE_HIT_HASH", LUA_NATIVE_HUD_ADD_VALID_VEHICLE_HIT_HASH);
		HUD.set_function("CLEAR_VALID_VEHICLE_HIT_HASHES", LUA_NATIVE_HUD_CLEAR_VALID_VEHICLE_HIT_HASHES);
		HUD.set_function("SET_BLIP_ROUTE", LUA_NATIVE_HUD_SET_BLIP_ROUTE);
		HUD.set_function("CLEAR_ALL_BLIP_ROUTES", LUA_NATIVE_HUD_CLEAR_ALL_BLIP_ROUTES);
		HUD.set_function("SET_BLIP_ROUTE_COLOUR", LUA_NATIVE_HUD_SET_BLIP_ROUTE_COLOUR);
		HUD.set_function("SET_FORCE_SHOW_GPS", LUA_NATIVE_HUD_SET_FORCE_SHOW_GPS);
		HUD.set_function("SET_USE_SET_DESTINATION_IN_PAUSE_MAP", LUA_NATIVE_HUD_SET_USE_SET_DESTINATION_IN_PAUSE_MAP);
		HUD.set_function("SET_BLOCK_WANTED_FLASH", LUA_NATIVE_HUD_SET_BLOCK_WANTED_FLASH);
		HUD.set_function("ADD_NEXT_MESSAGE_TO_PREVIOUS_BRIEFS", LUA_NATIVE_HUD_ADD_NEXT_MESSAGE_TO_PREVIOUS_BRIEFS);
		HUD.set_function("FORCE_NEXT_MESSAGE_TO_PREVIOUS_BRIEFS_LIST", LUA_NATIVE_HUD_FORCE_NEXT_MESSAGE_TO_PREVIOUS_BRIEFS_LIST);
		HUD.set_function("SET_RADAR_ZOOM_PRECISE", LUA_NATIVE_HUD_SET_RADAR_ZOOM_PRECISE);
		HUD.set_function("SET_RADAR_ZOOM", LUA_NATIVE_HUD_SET_RADAR_ZOOM);
		HUD.set_function("SET_RADAR_ZOOM_TO_BLIP", LUA_NATIVE_HUD_SET_RADAR_ZOOM_TO_BLIP);
		HUD.set_function("SET_RADAR_ZOOM_TO_DISTANCE", LUA_NATIVE_HUD_SET_RADAR_ZOOM_TO_DISTANCE);
		HUD.set_function("UPDATE_RADAR_ZOOM_TO_BLIP", LUA_NATIVE_HUD_UPDATE_RADAR_ZOOM_TO_BLIP);
		HUD.set_function("GET_HUD_COLOUR", LUA_NATIVE_HUD_GET_HUD_COLOUR);
		HUD.set_function("SET_SCRIPT_VARIABLE_HUD_COLOUR", LUA_NATIVE_HUD_SET_SCRIPT_VARIABLE_HUD_COLOUR);
		HUD.set_function("SET_SECOND_SCRIPT_VARIABLE_HUD_COLOUR", LUA_NATIVE_HUD_SET_SECOND_SCRIPT_VARIABLE_HUD_COLOUR);
		HUD.set_function("REPLACE_HUD_COLOUR", LUA_NATIVE_HUD_REPLACE_HUD_COLOUR);
		HUD.set_function("REPLACE_HUD_COLOUR_WITH_RGBA", LUA_NATIVE_HUD_REPLACE_HUD_COLOUR_WITH_RGBA);
		HUD.set_function("SET_ABILITY_BAR_VISIBILITY", LUA_NATIVE_HUD_SET_ABILITY_BAR_VISIBILITY);
		HUD.set_function("SET_ALLOW_ABILITY_BAR", LUA_NATIVE_HUD_SET_ALLOW_ABILITY_BAR);
		HUD.set_function("FLASH_ABILITY_BAR", LUA_NATIVE_HUD_FLASH_ABILITY_BAR);
		HUD.set_function("SET_ABILITY_BAR_VALUE", LUA_NATIVE_HUD_SET_ABILITY_BAR_VALUE);
		HUD.set_function("FLASH_WANTED_DISPLAY", LUA_NATIVE_HUD_FLASH_WANTED_DISPLAY);
		HUD.set_function("FORCE_OFF_WANTED_STAR_FLASH", LUA_NATIVE_HUD_FORCE_OFF_WANTED_STAR_FLASH);
		HUD.set_function("SET_CUSTOM_MP_HUD_COLOR", LUA_NATIVE_HUD_SET_CUSTOM_MP_HUD_COLOR);
		HUD.set_function("GET_RENDERED_CHARACTER_HEIGHT", LUA_NATIVE_HUD_GET_RENDERED_CHARACTER_HEIGHT);
		HUD.set_function("SET_TEXT_SCALE", LUA_NATIVE_HUD_SET_TEXT_SCALE);
		HUD.set_function("SET_TEXT_COLOUR", LUA_NATIVE_HUD_SET_TEXT_COLOUR);
		HUD.set_function("SET_TEXT_CENTRE", LUA_NATIVE_HUD_SET_TEXT_CENTRE);
		HUD.set_function("SET_TEXT_RIGHT_JUSTIFY", LUA_NATIVE_HUD_SET_TEXT_RIGHT_JUSTIFY);
		HUD.set_function("SET_TEXT_JUSTIFICATION", LUA_NATIVE_HUD_SET_TEXT_JUSTIFICATION);
		HUD.set_function("SET_TEXT_LINE_HEIGHT_MULT", LUA_NATIVE_HUD_SET_TEXT_LINE_HEIGHT_MULT);
		HUD.set_function("SET_TEXT_WRAP", LUA_NATIVE_HUD_SET_TEXT_WRAP);
		HUD.set_function("SET_TEXT_LEADING", LUA_NATIVE_HUD_SET_TEXT_LEADING);
		HUD.set_function("SET_TEXT_PROPORTIONAL", LUA_NATIVE_HUD_SET_TEXT_PROPORTIONAL);
		HUD.set_function("SET_TEXT_FONT", LUA_NATIVE_HUD_SET_TEXT_FONT);
		HUD.set_function("SET_TEXT_DROP_SHADOW", LUA_NATIVE_HUD_SET_TEXT_DROP_SHADOW);
		HUD.set_function("SET_TEXT_DROPSHADOW", LUA_NATIVE_HUD_SET_TEXT_DROPSHADOW);
		HUD.set_function("SET_TEXT_OUTLINE", LUA_NATIVE_HUD_SET_TEXT_OUTLINE);
		HUD.set_function("SET_TEXT_EDGE", LUA_NATIVE_HUD_SET_TEXT_EDGE);
		HUD.set_function("SET_TEXT_RENDER_ID", LUA_NATIVE_HUD_SET_TEXT_RENDER_ID);
		HUD.set_function("GET_DEFAULT_SCRIPT_RENDERTARGET_RENDER_ID", LUA_NATIVE_HUD_GET_DEFAULT_SCRIPT_RENDERTARGET_RENDER_ID);
		HUD.set_function("REGISTER_NAMED_RENDERTARGET", LUA_NATIVE_HUD_REGISTER_NAMED_RENDERTARGET);
		HUD.set_function("IS_NAMED_RENDERTARGET_REGISTERED", LUA_NATIVE_HUD_IS_NAMED_RENDERTARGET_REGISTERED);
		HUD.set_function("RELEASE_NAMED_RENDERTARGET", LUA_NATIVE_HUD_RELEASE_NAMED_RENDERTARGET);
		HUD.set_function("LINK_NAMED_RENDERTARGET", LUA_NATIVE_HUD_LINK_NAMED_RENDERTARGET);
		HUD.set_function("GET_NAMED_RENDERTARGET_RENDER_ID", LUA_NATIVE_HUD_GET_NAMED_RENDERTARGET_RENDER_ID);
		HUD.set_function("IS_NAMED_RENDERTARGET_LINKED", LUA_NATIVE_HUD_IS_NAMED_RENDERTARGET_LINKED);
		HUD.set_function("CLEAR_HELP", LUA_NATIVE_HUD_CLEAR_HELP);
		HUD.set_function("IS_HELP_MESSAGE_ON_SCREEN", LUA_NATIVE_HUD_IS_HELP_MESSAGE_ON_SCREEN);
		HUD.set_function("HAS_SCRIPT_HIDDEN_HELP_THIS_FRAME", LUA_NATIVE_HUD_HAS_SCRIPT_HIDDEN_HELP_THIS_FRAME);
		HUD.set_function("IS_HELP_MESSAGE_BEING_DISPLAYED", LUA_NATIVE_HUD_IS_HELP_MESSAGE_BEING_DISPLAYED);
		HUD.set_function("IS_HELP_MESSAGE_FADING_OUT", LUA_NATIVE_HUD_IS_HELP_MESSAGE_FADING_OUT);
		HUD.set_function("SET_HELP_MESSAGE_STYLE", LUA_NATIVE_HUD_SET_HELP_MESSAGE_STYLE);
		HUD.set_function("GET_STANDARD_BLIP_ENUM_ID", LUA_NATIVE_HUD_GET_STANDARD_BLIP_ENUM_ID);
		HUD.set_function("GET_WAYPOINT_BLIP_ENUM_ID", LUA_NATIVE_HUD_GET_WAYPOINT_BLIP_ENUM_ID);
		HUD.set_function("GET_NUMBER_OF_ACTIVE_BLIPS", LUA_NATIVE_HUD_GET_NUMBER_OF_ACTIVE_BLIPS);
		HUD.set_function("GET_NEXT_BLIP_INFO_ID", LUA_NATIVE_HUD_GET_NEXT_BLIP_INFO_ID);
		HUD.set_function("GET_FIRST_BLIP_INFO_ID", LUA_NATIVE_HUD_GET_FIRST_BLIP_INFO_ID);
		HUD.set_function("GET_CLOSEST_BLIP_INFO_ID", LUA_NATIVE_HUD_GET_CLOSEST_BLIP_INFO_ID);
		HUD.set_function("GET_BLIP_INFO_ID_COORD", LUA_NATIVE_HUD_GET_BLIP_INFO_ID_COORD);
		HUD.set_function("GET_BLIP_INFO_ID_DISPLAY", LUA_NATIVE_HUD_GET_BLIP_INFO_ID_DISPLAY);
		HUD.set_function("GET_BLIP_INFO_ID_TYPE", LUA_NATIVE_HUD_GET_BLIP_INFO_ID_TYPE);
		HUD.set_function("GET_BLIP_INFO_ID_ENTITY_INDEX", LUA_NATIVE_HUD_GET_BLIP_INFO_ID_ENTITY_INDEX);
		HUD.set_function("GET_BLIP_INFO_ID_PICKUP_INDEX", LUA_NATIVE_HUD_GET_BLIP_INFO_ID_PICKUP_INDEX);
		HUD.set_function("GET_BLIP_FROM_ENTITY", LUA_NATIVE_HUD_GET_BLIP_FROM_ENTITY);
		HUD.set_function("ADD_BLIP_FOR_RADIUS", LUA_NATIVE_HUD_ADD_BLIP_FOR_RADIUS);
		HUD.set_function("ADD_BLIP_FOR_AREA", LUA_NATIVE_HUD_ADD_BLIP_FOR_AREA);
		HUD.set_function("ADD_BLIP_FOR_ENTITY", LUA_NATIVE_HUD_ADD_BLIP_FOR_ENTITY);
		HUD.set_function("ADD_BLIP_FOR_PICKUP", LUA_NATIVE_HUD_ADD_BLIP_FOR_PICKUP);
		HUD.set_function("ADD_BLIP_FOR_COORD", LUA_NATIVE_HUD_ADD_BLIP_FOR_COORD);
		HUD.set_function("TRIGGER_SONAR_BLIP", LUA_NATIVE_HUD_TRIGGER_SONAR_BLIP);
		HUD.set_function("ALLOW_SONAR_BLIPS", LUA_NATIVE_HUD_ALLOW_SONAR_BLIPS);
		HUD.set_function("SET_BLIP_COORDS", LUA_NATIVE_HUD_SET_BLIP_COORDS);
		HUD.set_function("GET_BLIP_COORDS", LUA_NATIVE_HUD_GET_BLIP_COORDS);
		HUD.set_function("SET_BLIP_SPRITE", LUA_NATIVE_HUD_SET_BLIP_SPRITE);
		HUD.set_function("GET_BLIP_SPRITE", LUA_NATIVE_HUD_GET_BLIP_SPRITE);
		HUD.set_function("SET_COP_BLIP_SPRITE", LUA_NATIVE_HUD_SET_COP_BLIP_SPRITE);
		HUD.set_function("SET_COP_BLIP_SPRITE_AS_STANDARD", LUA_NATIVE_HUD_SET_COP_BLIP_SPRITE_AS_STANDARD);
		HUD.set_function("SET_BLIP_NAME_FROM_TEXT_FILE", LUA_NATIVE_HUD_SET_BLIP_NAME_FROM_TEXT_FILE);
		HUD.set_function("SET_BLIP_NAME_TO_PLAYER_NAME", LUA_NATIVE_HUD_SET_BLIP_NAME_TO_PLAYER_NAME);
		HUD.set_function("SET_BLIP_ALPHA", LUA_NATIVE_HUD_SET_BLIP_ALPHA);
		HUD.set_function("GET_BLIP_ALPHA", LUA_NATIVE_HUD_GET_BLIP_ALPHA);
		HUD.set_function("SET_BLIP_FADE", LUA_NATIVE_HUD_SET_BLIP_FADE);
		HUD.set_function("GET_BLIP_FADE_DIRECTION", LUA_NATIVE_HUD_GET_BLIP_FADE_DIRECTION);
		HUD.set_function("SET_BLIP_ROTATION", LUA_NATIVE_HUD_SET_BLIP_ROTATION);
		HUD.set_function("SET_BLIP_ROTATION_WITH_FLOAT", LUA_NATIVE_HUD_SET_BLIP_ROTATION_WITH_FLOAT);
		HUD.set_function("GET_BLIP_ROTATION", LUA_NATIVE_HUD_GET_BLIP_ROTATION);
		HUD.set_function("SET_BLIP_FLASH_TIMER", LUA_NATIVE_HUD_SET_BLIP_FLASH_TIMER);
		HUD.set_function("SET_BLIP_FLASH_INTERVAL", LUA_NATIVE_HUD_SET_BLIP_FLASH_INTERVAL);
		HUD.set_function("SET_BLIP_COLOUR", LUA_NATIVE_HUD_SET_BLIP_COLOUR);
		HUD.set_function("SET_BLIP_SECONDARY_COLOUR", LUA_NATIVE_HUD_SET_BLIP_SECONDARY_COLOUR);
		HUD.set_function("GET_BLIP_COLOUR", LUA_NATIVE_HUD_GET_BLIP_COLOUR);
		HUD.set_function("GET_BLIP_HUD_COLOUR", LUA_NATIVE_HUD_GET_BLIP_HUD_COLOUR);
		HUD.set_function("IS_BLIP_SHORT_RANGE", LUA_NATIVE_HUD_IS_BLIP_SHORT_RANGE);
		HUD.set_function("IS_BLIP_ON_MINIMAP", LUA_NATIVE_HUD_IS_BLIP_ON_MINIMAP);
		HUD.set_function("DOES_BLIP_HAVE_GPS_ROUTE", LUA_NATIVE_HUD_DOES_BLIP_HAVE_GPS_ROUTE);
		HUD.set_function("SET_BLIP_HIDDEN_ON_LEGEND", LUA_NATIVE_HUD_SET_BLIP_HIDDEN_ON_LEGEND);
		HUD.set_function("SET_BLIP_HIGH_DETAIL", LUA_NATIVE_HUD_SET_BLIP_HIGH_DETAIL);
		HUD.set_function("SET_BLIP_AS_MISSION_CREATOR_BLIP", LUA_NATIVE_HUD_SET_BLIP_AS_MISSION_CREATOR_BLIP);
		HUD.set_function("IS_MISSION_CREATOR_BLIP", LUA_NATIVE_HUD_IS_MISSION_CREATOR_BLIP);
		HUD.set_function("GET_NEW_SELECTED_MISSION_CREATOR_BLIP", LUA_NATIVE_HUD_GET_NEW_SELECTED_MISSION_CREATOR_BLIP);
		HUD.set_function("IS_HOVERING_OVER_MISSION_CREATOR_BLIP", LUA_NATIVE_HUD_IS_HOVERING_OVER_MISSION_CREATOR_BLIP);
		HUD.set_function("SHOW_START_MISSION_INSTRUCTIONAL_BUTTON", LUA_NATIVE_HUD_SHOW_START_MISSION_INSTRUCTIONAL_BUTTON);
		HUD.set_function("SHOW_CONTACT_INSTRUCTIONAL_BUTTON", LUA_NATIVE_HUD_SHOW_CONTACT_INSTRUCTIONAL_BUTTON);
		HUD.set_function("RELOAD_MAP_MENU", LUA_NATIVE_HUD_RELOAD_MAP_MENU);
		HUD.set_function("SET_BLIP_MARKER_LONG_DISTANCE", LUA_NATIVE_HUD_SET_BLIP_MARKER_LONG_DISTANCE);
		HUD.set_function("SET_BLIP_FLASHES", LUA_NATIVE_HUD_SET_BLIP_FLASHES);
		HUD.set_function("SET_BLIP_FLASHES_ALTERNATE", LUA_NATIVE_HUD_SET_BLIP_FLASHES_ALTERNATE);
		HUD.set_function("IS_BLIP_FLASHING", LUA_NATIVE_HUD_IS_BLIP_FLASHING);
		HUD.set_function("SET_BLIP_AS_SHORT_RANGE", LUA_NATIVE_HUD_SET_BLIP_AS_SHORT_RANGE);
		HUD.set_function("SET_BLIP_SCALE", LUA_NATIVE_HUD_SET_BLIP_SCALE);
		HUD.set_function("SET_BLIP_SCALE_2D", LUA_NATIVE_HUD_SET_BLIP_SCALE_2D);
		HUD.set_function("SET_BLIP_PRIORITY", LUA_NATIVE_HUD_SET_BLIP_PRIORITY);
		HUD.set_function("SET_BLIP_DISPLAY", LUA_NATIVE_HUD_SET_BLIP_DISPLAY);
		HUD.set_function("SET_BLIP_CATEGORY", LUA_NATIVE_HUD_SET_BLIP_CATEGORY);
		HUD.set_function("REMOVE_BLIP", LUA_NATIVE_HUD_REMOVE_BLIP);
		HUD.set_function("SET_BLIP_AS_FRIENDLY", LUA_NATIVE_HUD_SET_BLIP_AS_FRIENDLY);
		HUD.set_function("PULSE_BLIP", LUA_NATIVE_HUD_PULSE_BLIP);
		HUD.set_function("SHOW_NUMBER_ON_BLIP", LUA_NATIVE_HUD_SHOW_NUMBER_ON_BLIP);
		HUD.set_function("HIDE_NUMBER_ON_BLIP", LUA_NATIVE_HUD_HIDE_NUMBER_ON_BLIP);
		HUD.set_function("SHOW_HEIGHT_ON_BLIP", LUA_NATIVE_HUD_SHOW_HEIGHT_ON_BLIP);
		HUD.set_function("SHOW_TICK_ON_BLIP", LUA_NATIVE_HUD_SHOW_TICK_ON_BLIP);
		HUD.set_function("SHOW_GOLD_TICK_ON_BLIP", LUA_NATIVE_HUD_SHOW_GOLD_TICK_ON_BLIP);
		HUD.set_function("SHOW_FOR_SALE_ICON_ON_BLIP", LUA_NATIVE_HUD_SHOW_FOR_SALE_ICON_ON_BLIP);
		HUD.set_function("SHOW_HEADING_INDICATOR_ON_BLIP", LUA_NATIVE_HUD_SHOW_HEADING_INDICATOR_ON_BLIP);
		HUD.set_function("SHOW_OUTLINE_INDICATOR_ON_BLIP", LUA_NATIVE_HUD_SHOW_OUTLINE_INDICATOR_ON_BLIP);
		HUD.set_function("SHOW_FRIEND_INDICATOR_ON_BLIP", LUA_NATIVE_HUD_SHOW_FRIEND_INDICATOR_ON_BLIP);
		HUD.set_function("SHOW_CREW_INDICATOR_ON_BLIP", LUA_NATIVE_HUD_SHOW_CREW_INDICATOR_ON_BLIP);
		HUD.set_function("SET_BLIP_EXTENDED_HEIGHT_THRESHOLD", LUA_NATIVE_HUD_SET_BLIP_EXTENDED_HEIGHT_THRESHOLD);
		HUD.set_function("SET_BLIP_SHORT_HEIGHT_THRESHOLD", LUA_NATIVE_HUD_SET_BLIP_SHORT_HEIGHT_THRESHOLD);
		HUD.set_function("SET_BLIP_USE_HEIGHT_INDICATOR_ON_EDGE", LUA_NATIVE_HUD_SET_BLIP_USE_HEIGHT_INDICATOR_ON_EDGE);
		HUD.set_function("SET_BLIP_AS_MINIMAL_ON_EDGE", LUA_NATIVE_HUD_SET_BLIP_AS_MINIMAL_ON_EDGE);
		HUD.set_function("SET_RADIUS_BLIP_EDGE", LUA_NATIVE_HUD_SET_RADIUS_BLIP_EDGE);
		HUD.set_function("DOES_BLIP_EXIST", LUA_NATIVE_HUD_DOES_BLIP_EXIST);
		HUD.set_function("SET_WAYPOINT_OFF", LUA_NATIVE_HUD_SET_WAYPOINT_OFF);
		HUD.set_function("DELETE_WAYPOINTS_FROM_THIS_PLAYER", LUA_NATIVE_HUD_DELETE_WAYPOINTS_FROM_THIS_PLAYER);
		HUD.set_function("REFRESH_WAYPOINT", LUA_NATIVE_HUD_REFRESH_WAYPOINT);
		HUD.set_function("IS_WAYPOINT_ACTIVE", LUA_NATIVE_HUD_IS_WAYPOINT_ACTIVE);
		HUD.set_function("SET_NEW_WAYPOINT", LUA_NATIVE_HUD_SET_NEW_WAYPOINT);
		HUD.set_function("SET_BLIP_BRIGHT", LUA_NATIVE_HUD_SET_BLIP_BRIGHT);
		HUD.set_function("SET_BLIP_SHOW_CONE", LUA_NATIVE_HUD_SET_BLIP_SHOW_CONE);
		HUD.set_function("REMOVE_COP_BLIP_FROM_PED", LUA_NATIVE_HUD_REMOVE_COP_BLIP_FROM_PED);
		HUD.set_function("SETUP_FAKE_CONE_DATA", LUA_NATIVE_HUD_SETUP_FAKE_CONE_DATA);
		HUD.set_function("REMOVE_FAKE_CONE_DATA", LUA_NATIVE_HUD_REMOVE_FAKE_CONE_DATA);
		HUD.set_function("CLEAR_FAKE_CONE_ARRAY", LUA_NATIVE_HUD_CLEAR_FAKE_CONE_ARRAY);
		HUD.set_function("SET_BLIP_GPS_ROUTE_DISPLAY_DISTANCE_", LUA_NATIVE_HUD_SET_BLIP_GPS_ROUTE_DISPLAY_DISTANCE_);
		HUD.set_function("SET_MINIMAP_COMPONENT", LUA_NATIVE_HUD_SET_MINIMAP_COMPONENT);
		HUD.set_function("SET_MINIMAP_SONAR_SWEEP", LUA_NATIVE_HUD_SET_MINIMAP_SONAR_SWEEP);
		HUD.set_function("SHOW_ACCOUNT_PICKER", LUA_NATIVE_HUD_SHOW_ACCOUNT_PICKER);
		HUD.set_function("GET_MAIN_PLAYER_BLIP_ID", LUA_NATIVE_HUD_GET_MAIN_PLAYER_BLIP_ID);
		HUD.set_function("SET_PM_WARNINGSCREEN_ACTIVE", LUA_NATIVE_HUD_SET_PM_WARNINGSCREEN_ACTIVE);
		HUD.set_function("HIDE_LOADING_ON_FADE_THIS_FRAME", LUA_NATIVE_HUD_HIDE_LOADING_ON_FADE_THIS_FRAME);
		HUD.set_function("SET_RADAR_AS_INTERIOR_THIS_FRAME", LUA_NATIVE_HUD_SET_RADAR_AS_INTERIOR_THIS_FRAME);
		HUD.set_function("SET_INSIDE_VERY_SMALL_INTERIOR", LUA_NATIVE_HUD_SET_INSIDE_VERY_SMALL_INTERIOR);
		HUD.set_function("SET_INSIDE_VERY_LARGE_INTERIOR", LUA_NATIVE_HUD_SET_INSIDE_VERY_LARGE_INTERIOR);
		HUD.set_function("SET_RADAR_AS_EXTERIOR_THIS_FRAME", LUA_NATIVE_HUD_SET_RADAR_AS_EXTERIOR_THIS_FRAME);
		HUD.set_function("SET_FAKE_PAUSEMAP_PLAYER_POSITION_THIS_FRAME", LUA_NATIVE_HUD_SET_FAKE_PAUSEMAP_PLAYER_POSITION_THIS_FRAME);
		HUD.set_function("SET_FAKE_GPS_PLAYER_POSITION_THIS_FRAME", LUA_NATIVE_HUD_SET_FAKE_GPS_PLAYER_POSITION_THIS_FRAME);
		HUD.set_function("IS_PAUSEMAP_IN_INTERIOR_MODE", LUA_NATIVE_HUD_IS_PAUSEMAP_IN_INTERIOR_MODE);
		HUD.set_function("HIDE_MINIMAP_EXTERIOR_MAP_THIS_FRAME", LUA_NATIVE_HUD_HIDE_MINIMAP_EXTERIOR_MAP_THIS_FRAME);
		HUD.set_function("HIDE_MINIMAP_INTERIOR_MAP_THIS_FRAME", LUA_NATIVE_HUD_HIDE_MINIMAP_INTERIOR_MAP_THIS_FRAME);
		HUD.set_function("SET_USE_ISLAND_MAP", LUA_NATIVE_HUD_SET_USE_ISLAND_MAP);
		HUD.set_function("SET_PAUSE_EXTERIOR_RENDERING_WHILE_IN_INTERIOR_", LUA_NATIVE_HUD_SET_PAUSE_EXTERIOR_RENDERING_WHILE_IN_INTERIOR_);
		HUD.set_function("DONT_TILT_MINIMAP_THIS_FRAME", LUA_NATIVE_HUD_DONT_TILT_MINIMAP_THIS_FRAME);
		HUD.set_function("DONT_ZOOM_MINIMAP_WHEN_RUNNING_THIS_FRAME", LUA_NATIVE_HUD_DONT_ZOOM_MINIMAP_WHEN_RUNNING_THIS_FRAME);
		HUD.set_function("DONT_ZOOM_MINIMAP_WHEN_SNIPING_THIS_FRAME", LUA_NATIVE_HUD_DONT_ZOOM_MINIMAP_WHEN_SNIPING_THIS_FRAME);
		HUD.set_function("SET_WIDESCREEN_FORMAT", LUA_NATIVE_HUD_SET_WIDESCREEN_FORMAT);
		HUD.set_function("DISPLAY_AREA_NAME", LUA_NATIVE_HUD_DISPLAY_AREA_NAME);
		HUD.set_function("DISPLAY_CASH", LUA_NATIVE_HUD_DISPLAY_CASH);
		HUD.set_function("USE_FAKE_MP_CASH", LUA_NATIVE_HUD_USE_FAKE_MP_CASH);
		HUD.set_function("CHANGE_FAKE_MP_CASH", LUA_NATIVE_HUD_CHANGE_FAKE_MP_CASH);
		HUD.set_function("DISPLAY_AMMO_THIS_FRAME", LUA_NATIVE_HUD_DISPLAY_AMMO_THIS_FRAME);
		HUD.set_function("DISPLAY_SNIPER_SCOPE_THIS_FRAME", LUA_NATIVE_HUD_DISPLAY_SNIPER_SCOPE_THIS_FRAME);
		HUD.set_function("HIDE_HUD_AND_RADAR_THIS_FRAME", LUA_NATIVE_HUD_HIDE_HUD_AND_RADAR_THIS_FRAME);
		HUD.set_function("ALLOW_DISPLAY_OF_MULTIPLAYER_CASH_TEXT", LUA_NATIVE_HUD_ALLOW_DISPLAY_OF_MULTIPLAYER_CASH_TEXT);
		HUD.set_function("SET_MULTIPLAYER_WALLET_CASH", LUA_NATIVE_HUD_SET_MULTIPLAYER_WALLET_CASH);
		HUD.set_function("REMOVE_MULTIPLAYER_WALLET_CASH", LUA_NATIVE_HUD_REMOVE_MULTIPLAYER_WALLET_CASH);
		HUD.set_function("SET_MULTIPLAYER_BANK_CASH", LUA_NATIVE_HUD_SET_MULTIPLAYER_BANK_CASH);
		HUD.set_function("REMOVE_MULTIPLAYER_BANK_CASH", LUA_NATIVE_HUD_REMOVE_MULTIPLAYER_BANK_CASH);
		HUD.set_function("SET_MULTIPLAYER_HUD_CASH", LUA_NATIVE_HUD_SET_MULTIPLAYER_HUD_CASH);
		HUD.set_function("REMOVE_MULTIPLAYER_HUD_CASH", LUA_NATIVE_HUD_REMOVE_MULTIPLAYER_HUD_CASH);
		HUD.set_function("HIDE_HELP_TEXT_THIS_FRAME", LUA_NATIVE_HUD_HIDE_HELP_TEXT_THIS_FRAME);
		HUD.set_function("IS_IME_IN_PROGRESS", LUA_NATIVE_HUD_IS_IME_IN_PROGRESS);
		HUD.set_function("DISPLAY_HELP_TEXT_THIS_FRAME", LUA_NATIVE_HUD_DISPLAY_HELP_TEXT_THIS_FRAME);
		HUD.set_function("HUD_FORCE_WEAPON_WHEEL", LUA_NATIVE_HUD_HUD_FORCE_WEAPON_WHEEL);
		HUD.set_function("HUD_FORCE_SPECIAL_VEHICLE_WEAPON_WHEEL", LUA_NATIVE_HUD_HUD_FORCE_SPECIAL_VEHICLE_WEAPON_WHEEL);
		HUD.set_function("HUD_SUPPRESS_WEAPON_WHEEL_RESULTS_THIS_FRAME", LUA_NATIVE_HUD_HUD_SUPPRESS_WEAPON_WHEEL_RESULTS_THIS_FRAME);
		HUD.set_function("HUD_GET_WEAPON_WHEEL_CURRENTLY_HIGHLIGHTED", LUA_NATIVE_HUD_HUD_GET_WEAPON_WHEEL_CURRENTLY_HIGHLIGHTED);
		HUD.set_function("HUD_SET_WEAPON_WHEEL_TOP_SLOT", LUA_NATIVE_HUD_HUD_SET_WEAPON_WHEEL_TOP_SLOT);
		HUD.set_function("HUD_GET_WEAPON_WHEEL_TOP_SLOT", LUA_NATIVE_HUD_HUD_GET_WEAPON_WHEEL_TOP_SLOT);
		HUD.set_function("HUD_SHOWING_CHARACTER_SWITCH_SELECTION", LUA_NATIVE_HUD_HUD_SHOWING_CHARACTER_SWITCH_SELECTION);
		HUD.set_function("SET_GPS_FLAGS", LUA_NATIVE_HUD_SET_GPS_FLAGS);
		HUD.set_function("CLEAR_GPS_FLAGS", LUA_NATIVE_HUD_CLEAR_GPS_FLAGS);
		HUD.set_function("SET_RACE_TRACK_RENDER", LUA_NATIVE_HUD_SET_RACE_TRACK_RENDER);
		HUD.set_function("CLEAR_GPS_RACE_TRACK", LUA_NATIVE_HUD_CLEAR_GPS_RACE_TRACK);
		HUD.set_function("START_GPS_CUSTOM_ROUTE", LUA_NATIVE_HUD_START_GPS_CUSTOM_ROUTE);
		HUD.set_function("ADD_POINT_TO_GPS_CUSTOM_ROUTE", LUA_NATIVE_HUD_ADD_POINT_TO_GPS_CUSTOM_ROUTE);
		HUD.set_function("SET_GPS_CUSTOM_ROUTE_RENDER", LUA_NATIVE_HUD_SET_GPS_CUSTOM_ROUTE_RENDER);
		HUD.set_function("CLEAR_GPS_CUSTOM_ROUTE", LUA_NATIVE_HUD_CLEAR_GPS_CUSTOM_ROUTE);
		HUD.set_function("START_GPS_MULTI_ROUTE", LUA_NATIVE_HUD_START_GPS_MULTI_ROUTE);
		HUD.set_function("ADD_POINT_TO_GPS_MULTI_ROUTE", LUA_NATIVE_HUD_ADD_POINT_TO_GPS_MULTI_ROUTE);
		HUD.set_function("SET_GPS_MULTI_ROUTE_RENDER", LUA_NATIVE_HUD_SET_GPS_MULTI_ROUTE_RENDER);
		HUD.set_function("CLEAR_GPS_MULTI_ROUTE", LUA_NATIVE_HUD_CLEAR_GPS_MULTI_ROUTE);
		HUD.set_function("CLEAR_GPS_PLAYER_WAYPOINT", LUA_NATIVE_HUD_CLEAR_GPS_PLAYER_WAYPOINT);
		HUD.set_function("SET_GPS_FLASHES", LUA_NATIVE_HUD_SET_GPS_FLASHES);
		HUD.set_function("SET_PLAYER_ICON_COLOUR", LUA_NATIVE_HUD_SET_PLAYER_ICON_COLOUR);
		HUD.set_function("FLASH_MINIMAP_DISPLAY", LUA_NATIVE_HUD_FLASH_MINIMAP_DISPLAY);
		HUD.set_function("FLASH_MINIMAP_DISPLAY_WITH_COLOR", LUA_NATIVE_HUD_FLASH_MINIMAP_DISPLAY_WITH_COLOR);
		HUD.set_function("TOGGLE_STEALTH_RADAR", LUA_NATIVE_HUD_TOGGLE_STEALTH_RADAR);
		HUD.set_function("SET_MINIMAP_IN_SPECTATOR_MODE", LUA_NATIVE_HUD_SET_MINIMAP_IN_SPECTATOR_MODE);
		HUD.set_function("SET_MISSION_NAME", LUA_NATIVE_HUD_SET_MISSION_NAME);
		HUD.set_function("SET_MISSION_NAME_FOR_UGC_MISSION", LUA_NATIVE_HUD_SET_MISSION_NAME_FOR_UGC_MISSION);
		HUD.set_function("SET_DESCRIPTION_FOR_UGC_MISSION_EIGHT_STRINGS", LUA_NATIVE_HUD_SET_DESCRIPTION_FOR_UGC_MISSION_EIGHT_STRINGS);
		HUD.set_function("SET_MINIMAP_BLOCK_WAYPOINT", LUA_NATIVE_HUD_SET_MINIMAP_BLOCK_WAYPOINT);
		HUD.set_function("SET_MINIMAP_IN_PROLOGUE", LUA_NATIVE_HUD_SET_MINIMAP_IN_PROLOGUE);
		HUD.set_function("SET_MINIMAP_HIDE_FOW", LUA_NATIVE_HUD_SET_MINIMAP_HIDE_FOW);
		HUD.set_function("GET_MINIMAP_FOW_DISCOVERY_RATIO", LUA_NATIVE_HUD_GET_MINIMAP_FOW_DISCOVERY_RATIO);
		HUD.set_function("GET_MINIMAP_FOW_COORDINATE_IS_REVEALED", LUA_NATIVE_HUD_GET_MINIMAP_FOW_COORDINATE_IS_REVEALED);
		HUD.set_function("SET_MINIMAP_FOW_DO_NOT_UPDATE", LUA_NATIVE_HUD_SET_MINIMAP_FOW_DO_NOT_UPDATE);
		HUD.set_function("SET_MINIMAP_FOW_REVEAL_COORDINATE", LUA_NATIVE_HUD_SET_MINIMAP_FOW_REVEAL_COORDINATE);
		HUD.set_function("SET_MINIMAP_GOLF_COURSE", LUA_NATIVE_HUD_SET_MINIMAP_GOLF_COURSE);
		HUD.set_function("SET_MINIMAP_GOLF_COURSE_OFF", LUA_NATIVE_HUD_SET_MINIMAP_GOLF_COURSE_OFF);
		HUD.set_function("LOCK_MINIMAP_ANGLE", LUA_NATIVE_HUD_LOCK_MINIMAP_ANGLE);
		HUD.set_function("UNLOCK_MINIMAP_ANGLE", LUA_NATIVE_HUD_UNLOCK_MINIMAP_ANGLE);
		HUD.set_function("LOCK_MINIMAP_POSITION", LUA_NATIVE_HUD_LOCK_MINIMAP_POSITION);
		HUD.set_function("UNLOCK_MINIMAP_POSITION", LUA_NATIVE_HUD_UNLOCK_MINIMAP_POSITION);
		HUD.set_function("SET_FAKE_MINIMAP_MAX_ALTIMETER_HEIGHT", LUA_NATIVE_HUD_SET_FAKE_MINIMAP_MAX_ALTIMETER_HEIGHT);
		HUD.set_function("SET_HEALTH_HUD_DISPLAY_VALUES", LUA_NATIVE_HUD_SET_HEALTH_HUD_DISPLAY_VALUES);
		HUD.set_function("SET_MAX_HEALTH_HUD_DISPLAY", LUA_NATIVE_HUD_SET_MAX_HEALTH_HUD_DISPLAY);
		HUD.set_function("SET_MAX_ARMOUR_HUD_DISPLAY", LUA_NATIVE_HUD_SET_MAX_ARMOUR_HUD_DISPLAY);
		HUD.set_function("SET_BIGMAP_ACTIVE", LUA_NATIVE_HUD_SET_BIGMAP_ACTIVE);
		HUD.set_function("IS_HUD_COMPONENT_ACTIVE", LUA_NATIVE_HUD_IS_HUD_COMPONENT_ACTIVE);
		HUD.set_function("IS_SCRIPTED_HUD_COMPONENT_ACTIVE", LUA_NATIVE_HUD_IS_SCRIPTED_HUD_COMPONENT_ACTIVE);
		HUD.set_function("HIDE_SCRIPTED_HUD_COMPONENT_THIS_FRAME", LUA_NATIVE_HUD_HIDE_SCRIPTED_HUD_COMPONENT_THIS_FRAME);
		HUD.set_function("SHOW_SCRIPTED_HUD_COMPONENT_THIS_FRAME", LUA_NATIVE_HUD_SHOW_SCRIPTED_HUD_COMPONENT_THIS_FRAME);
		HUD.set_function("IS_SCRIPTED_HUD_COMPONENT_HIDDEN_THIS_FRAME", LUA_NATIVE_HUD_IS_SCRIPTED_HUD_COMPONENT_HIDDEN_THIS_FRAME);
		HUD.set_function("HIDE_HUD_COMPONENT_THIS_FRAME", LUA_NATIVE_HUD_HIDE_HUD_COMPONENT_THIS_FRAME);
		HUD.set_function("SHOW_HUD_COMPONENT_THIS_FRAME", LUA_NATIVE_HUD_SHOW_HUD_COMPONENT_THIS_FRAME);
		HUD.set_function("HIDE_STREET_AND_CAR_NAMES_THIS_FRAME", LUA_NATIVE_HUD_HIDE_STREET_AND_CAR_NAMES_THIS_FRAME);
		HUD.set_function("RESET_RETICULE_VALUES", LUA_NATIVE_HUD_RESET_RETICULE_VALUES);
		HUD.set_function("RESET_HUD_COMPONENT_VALUES", LUA_NATIVE_HUD_RESET_HUD_COMPONENT_VALUES);
		HUD.set_function("SET_HUD_COMPONENT_POSITION", LUA_NATIVE_HUD_SET_HUD_COMPONENT_POSITION);
		HUD.set_function("GET_HUD_COMPONENT_POSITION", LUA_NATIVE_HUD_GET_HUD_COMPONENT_POSITION);
		HUD.set_function("CLEAR_REMINDER_MESSAGE", LUA_NATIVE_HUD_CLEAR_REMINDER_MESSAGE);
		HUD.set_function("GET_HUD_SCREEN_POSITION_FROM_WORLD_POSITION", LUA_NATIVE_HUD_GET_HUD_SCREEN_POSITION_FROM_WORLD_POSITION);
		HUD.set_function("OPEN_REPORTUGC_MENU", LUA_NATIVE_HUD_OPEN_REPORTUGC_MENU);
		HUD.set_function("FORCE_CLOSE_REPORTUGC_MENU", LUA_NATIVE_HUD_FORCE_CLOSE_REPORTUGC_MENU);
		HUD.set_function("IS_REPORTUGC_MENU_OPEN", LUA_NATIVE_HUD_IS_REPORTUGC_MENU_OPEN);
		HUD.set_function("IS_FLOATING_HELP_TEXT_ON_SCREEN", LUA_NATIVE_HUD_IS_FLOATING_HELP_TEXT_ON_SCREEN);
		HUD.set_function("SET_FLOATING_HELP_TEXT_SCREEN_POSITION", LUA_NATIVE_HUD_SET_FLOATING_HELP_TEXT_SCREEN_POSITION);
		HUD.set_function("SET_FLOATING_HELP_TEXT_WORLD_POSITION", LUA_NATIVE_HUD_SET_FLOATING_HELP_TEXT_WORLD_POSITION);
		HUD.set_function("SET_FLOATING_HELP_TEXT_TO_ENTITY", LUA_NATIVE_HUD_SET_FLOATING_HELP_TEXT_TO_ENTITY);
		HUD.set_function("SET_FLOATING_HELP_TEXT_STYLE", LUA_NATIVE_HUD_SET_FLOATING_HELP_TEXT_STYLE);
		HUD.set_function("CLEAR_FLOATING_HELP", LUA_NATIVE_HUD_CLEAR_FLOATING_HELP);
		HUD.set_function("CREATE_MP_GAMER_TAG_WITH_CREW_COLOR", LUA_NATIVE_HUD_CREATE_MP_GAMER_TAG_WITH_CREW_COLOR);
		HUD.set_function("IS_MP_GAMER_TAG_MOVIE_ACTIVE", LUA_NATIVE_HUD_IS_MP_GAMER_TAG_MOVIE_ACTIVE);
		HUD.set_function("CREATE_FAKE_MP_GAMER_TAG", LUA_NATIVE_HUD_CREATE_FAKE_MP_GAMER_TAG);
		HUD.set_function("REMOVE_MP_GAMER_TAG", LUA_NATIVE_HUD_REMOVE_MP_GAMER_TAG);
		HUD.set_function("IS_MP_GAMER_TAG_ACTIVE", LUA_NATIVE_HUD_IS_MP_GAMER_TAG_ACTIVE);
		HUD.set_function("IS_MP_GAMER_TAG_FREE", LUA_NATIVE_HUD_IS_MP_GAMER_TAG_FREE);
		HUD.set_function("SET_MP_GAMER_TAG_VISIBILITY", LUA_NATIVE_HUD_SET_MP_GAMER_TAG_VISIBILITY);
		HUD.set_function("SET_ALL_MP_GAMER_TAGS_VISIBILITY", LUA_NATIVE_HUD_SET_ALL_MP_GAMER_TAGS_VISIBILITY);
		HUD.set_function("SET_MP_GAMER_TAGS_SHOULD_USE_VEHICLE_HEALTH", LUA_NATIVE_HUD_SET_MP_GAMER_TAGS_SHOULD_USE_VEHICLE_HEALTH);
		HUD.set_function("SET_MP_GAMER_TAGS_SHOULD_USE_POINTS_HEALTH", LUA_NATIVE_HUD_SET_MP_GAMER_TAGS_SHOULD_USE_POINTS_HEALTH);
		HUD.set_function("SET_MP_GAMER_TAGS_POINT_HEALTH", LUA_NATIVE_HUD_SET_MP_GAMER_TAGS_POINT_HEALTH);
		HUD.set_function("SET_MP_GAMER_TAG_COLOUR", LUA_NATIVE_HUD_SET_MP_GAMER_TAG_COLOUR);
		HUD.set_function("SET_MP_GAMER_TAG_HEALTH_BAR_COLOUR", LUA_NATIVE_HUD_SET_MP_GAMER_TAG_HEALTH_BAR_COLOUR);
		HUD.set_function("SET_MP_GAMER_TAG_ALPHA", LUA_NATIVE_HUD_SET_MP_GAMER_TAG_ALPHA);
		HUD.set_function("SET_MP_GAMER_TAG_WANTED_LEVEL", LUA_NATIVE_HUD_SET_MP_GAMER_TAG_WANTED_LEVEL);
		HUD.set_function("SET_MP_GAMER_TAG_NUM_PACKAGES", LUA_NATIVE_HUD_SET_MP_GAMER_TAG_NUM_PACKAGES);
		HUD.set_function("SET_MP_GAMER_TAG_NAME", LUA_NATIVE_HUD_SET_MP_GAMER_TAG_NAME);
		HUD.set_function("IS_UPDATING_MP_GAMER_TAG_NAME_AND_CREW_DETAILS", LUA_NATIVE_HUD_IS_UPDATING_MP_GAMER_TAG_NAME_AND_CREW_DETAILS);
		HUD.set_function("SET_MP_GAMER_TAG_BIG_TEXT", LUA_NATIVE_HUD_SET_MP_GAMER_TAG_BIG_TEXT);
		HUD.set_function("GET_CURRENT_WEBPAGE_ID", LUA_NATIVE_HUD_GET_CURRENT_WEBPAGE_ID);
		HUD.set_function("GET_CURRENT_WEBSITE_ID", LUA_NATIVE_HUD_GET_CURRENT_WEBSITE_ID);
		HUD.set_function("GET_GLOBAL_ACTIONSCRIPT_FLAG", LUA_NATIVE_HUD_GET_GLOBAL_ACTIONSCRIPT_FLAG);
		HUD.set_function("RESET_GLOBAL_ACTIONSCRIPT_FLAG", LUA_NATIVE_HUD_RESET_GLOBAL_ACTIONSCRIPT_FLAG);
		HUD.set_function("IS_WARNING_MESSAGE_READY_FOR_CONTROL", LUA_NATIVE_HUD_IS_WARNING_MESSAGE_READY_FOR_CONTROL);
		HUD.set_function("SET_WARNING_MESSAGE", LUA_NATIVE_HUD_SET_WARNING_MESSAGE);
		HUD.set_function("SET_WARNING_MESSAGE_WITH_HEADER", LUA_NATIVE_HUD_SET_WARNING_MESSAGE_WITH_HEADER);
		HUD.set_function("SET_WARNING_MESSAGE_WITH_HEADER_AND_SUBSTRING_FLAGS", LUA_NATIVE_HUD_SET_WARNING_MESSAGE_WITH_HEADER_AND_SUBSTRING_FLAGS);
		HUD.set_function("SET_WARNING_MESSAGE_WITH_HEADER_EXTENDED", LUA_NATIVE_HUD_SET_WARNING_MESSAGE_WITH_HEADER_EXTENDED);
		HUD.set_function("SET_WARNING_MESSAGE_WITH_HEADER_AND_SUBSTRING_FLAGS_EXTENDED", LUA_NATIVE_HUD_SET_WARNING_MESSAGE_WITH_HEADER_AND_SUBSTRING_FLAGS_EXTENDED);
		HUD.set_function("GET_WARNING_SCREEN_MESSAGE_HASH", LUA_NATIVE_HUD_GET_WARNING_SCREEN_MESSAGE_HASH);
		HUD.set_function("SET_WARNING_MESSAGE_OPTION_ITEMS", LUA_NATIVE_HUD_SET_WARNING_MESSAGE_OPTION_ITEMS);
		HUD.set_function("SET_WARNING_MESSAGE_OPTION_HIGHLIGHT", LUA_NATIVE_HUD_SET_WARNING_MESSAGE_OPTION_HIGHLIGHT);
		HUD.set_function("REMOVE_WARNING_MESSAGE_OPTION_ITEMS", LUA_NATIVE_HUD_REMOVE_WARNING_MESSAGE_OPTION_ITEMS);
		HUD.set_function("IS_WARNING_MESSAGE_ACTIVE", LUA_NATIVE_HUD_IS_WARNING_MESSAGE_ACTIVE);
		HUD.set_function("CLEAR_DYNAMIC_PAUSE_MENU_ERROR_MESSAGE", LUA_NATIVE_HUD_CLEAR_DYNAMIC_PAUSE_MENU_ERROR_MESSAGE);
		HUD.set_function("CUSTOM_MINIMAP_SET_ACTIVE", LUA_NATIVE_HUD_CUSTOM_MINIMAP_SET_ACTIVE);
		HUD.set_function("CUSTOM_MINIMAP_SET_BLIP_OBJECT", LUA_NATIVE_HUD_CUSTOM_MINIMAP_SET_BLIP_OBJECT);
		HUD.set_function("CUSTOM_MINIMAP_CREATE_BLIP", LUA_NATIVE_HUD_CUSTOM_MINIMAP_CREATE_BLIP);
		HUD.set_function("CUSTOM_MINIMAP_CLEAR_BLIPS", LUA_NATIVE_HUD_CUSTOM_MINIMAP_CLEAR_BLIPS);
		HUD.set_function("FORCE_SONAR_BLIPS_THIS_FRAME", LUA_NATIVE_HUD_FORCE_SONAR_BLIPS_THIS_FRAME);
		HUD.set_function("GET_NORTH_BLID_INDEX", LUA_NATIVE_HUD_GET_NORTH_BLID_INDEX);
		HUD.set_function("DISPLAY_PLAYER_NAME_TAGS_ON_BLIPS", LUA_NATIVE_HUD_DISPLAY_PLAYER_NAME_TAGS_ON_BLIPS);
		HUD.set_function("DRAW_FRONTEND_BACKGROUND_THIS_FRAME", LUA_NATIVE_HUD_DRAW_FRONTEND_BACKGROUND_THIS_FRAME);
		HUD.set_function("DRAW_HUD_OVER_FADE_THIS_FRAME", LUA_NATIVE_HUD_DRAW_HUD_OVER_FADE_THIS_FRAME);
		HUD.set_function("ACTIVATE_FRONTEND_MENU", LUA_NATIVE_HUD_ACTIVATE_FRONTEND_MENU);
		HUD.set_function("RESTART_FRONTEND_MENU", LUA_NATIVE_HUD_RESTART_FRONTEND_MENU);
		HUD.set_function("GET_CURRENT_FRONTEND_MENU_VERSION", LUA_NATIVE_HUD_GET_CURRENT_FRONTEND_MENU_VERSION);
		HUD.set_function("SET_PAUSE_MENU_ACTIVE", LUA_NATIVE_HUD_SET_PAUSE_MENU_ACTIVE);
		HUD.set_function("DISABLE_FRONTEND_THIS_FRAME", LUA_NATIVE_HUD_DISABLE_FRONTEND_THIS_FRAME);
		HUD.set_function("SUPPRESS_FRONTEND_RENDERING_THIS_FRAME", LUA_NATIVE_HUD_SUPPRESS_FRONTEND_RENDERING_THIS_FRAME);
		HUD.set_function("ALLOW_PAUSE_WHEN_NOT_IN_STATE_OF_PLAY_THIS_FRAME", LUA_NATIVE_HUD_ALLOW_PAUSE_WHEN_NOT_IN_STATE_OF_PLAY_THIS_FRAME);
		HUD.set_function("SET_FRONTEND_ACTIVE", LUA_NATIVE_HUD_SET_FRONTEND_ACTIVE);
		HUD.set_function("IS_PAUSE_MENU_ACTIVE", LUA_NATIVE_HUD_IS_PAUSE_MENU_ACTIVE);
		HUD.set_function("IS_STORE_PENDING_NETWORK_SHUTDOWN_TO_OPEN", LUA_NATIVE_HUD_IS_STORE_PENDING_NETWORK_SHUTDOWN_TO_OPEN);
		HUD.set_function("GET_PAUSE_MENU_STATE", LUA_NATIVE_HUD_GET_PAUSE_MENU_STATE);
		HUD.set_function("GET_PAUSE_MENU_POSITION", LUA_NATIVE_HUD_GET_PAUSE_MENU_POSITION);
		HUD.set_function("IS_PAUSE_MENU_RESTARTING", LUA_NATIVE_HUD_IS_PAUSE_MENU_RESTARTING);
		HUD.set_function("FORCE_SCRIPTED_GFX_WHEN_FRONTEND_ACTIVE", LUA_NATIVE_HUD_FORCE_SCRIPTED_GFX_WHEN_FRONTEND_ACTIVE);
		HUD.set_function("PAUSE_MENUCEPTION_GO_DEEPER", LUA_NATIVE_HUD_PAUSE_MENUCEPTION_GO_DEEPER);
		HUD.set_function("PAUSE_MENUCEPTION_THE_KICK", LUA_NATIVE_HUD_PAUSE_MENUCEPTION_THE_KICK);
		HUD.set_function("PAUSE_TOGGLE_FULLSCREEN_MAP", LUA_NATIVE_HUD_PAUSE_TOGGLE_FULLSCREEN_MAP);
		HUD.set_function("PAUSE_MENU_ACTIVATE_CONTEXT", LUA_NATIVE_HUD_PAUSE_MENU_ACTIVATE_CONTEXT);
		HUD.set_function("PAUSE_MENU_DEACTIVATE_CONTEXT", LUA_NATIVE_HUD_PAUSE_MENU_DEACTIVATE_CONTEXT);
		HUD.set_function("PAUSE_MENU_IS_CONTEXT_ACTIVE", LUA_NATIVE_HUD_PAUSE_MENU_IS_CONTEXT_ACTIVE);
		HUD.set_function("PAUSE_MENU_IS_CONTEXT_MENU_ACTIVE", LUA_NATIVE_HUD_PAUSE_MENU_IS_CONTEXT_MENU_ACTIVE);
		HUD.set_function("PAUSE_MENU_GET_HAIR_COLOUR_INDEX", LUA_NATIVE_HUD_PAUSE_MENU_GET_HAIR_COLOUR_INDEX);
		HUD.set_function("PAUSE_MENU_GET_MOUSE_HOVER_INDEX", LUA_NATIVE_HUD_PAUSE_MENU_GET_MOUSE_HOVER_INDEX);
		HUD.set_function("PAUSE_MENU_GET_MOUSE_HOVER_UNIQUE_ID", LUA_NATIVE_HUD_PAUSE_MENU_GET_MOUSE_HOVER_UNIQUE_ID);
		HUD.set_function("PAUSE_MENU_GET_MOUSE_CLICK_EVENT", LUA_NATIVE_HUD_PAUSE_MENU_GET_MOUSE_CLICK_EVENT);
		HUD.set_function("PAUSE_MENU_REDRAW_INSTRUCTIONAL_BUTTONS", LUA_NATIVE_HUD_PAUSE_MENU_REDRAW_INSTRUCTIONAL_BUTTONS);
		HUD.set_function("PAUSE_MENU_SET_BUSY_SPINNER", LUA_NATIVE_HUD_PAUSE_MENU_SET_BUSY_SPINNER);
		HUD.set_function("PAUSE_MENU_SET_WARN_ON_TAB_CHANGE", LUA_NATIVE_HUD_PAUSE_MENU_SET_WARN_ON_TAB_CHANGE);
		HUD.set_function("IS_FRONTEND_READY_FOR_CONTROL", LUA_NATIVE_HUD_IS_FRONTEND_READY_FOR_CONTROL);
		HUD.set_function("TAKE_CONTROL_OF_FRONTEND", LUA_NATIVE_HUD_TAKE_CONTROL_OF_FRONTEND);
		HUD.set_function("RELEASE_CONTROL_OF_FRONTEND", LUA_NATIVE_HUD_RELEASE_CONTROL_OF_FRONTEND);
		HUD.set_function("CODE_WANTS_SCRIPT_TO_TAKE_CONTROL", LUA_NATIVE_HUD_CODE_WANTS_SCRIPT_TO_TAKE_CONTROL);
		HUD.set_function("GET_SCREEN_CODE_WANTS_SCRIPT_TO_CONTROL", LUA_NATIVE_HUD_GET_SCREEN_CODE_WANTS_SCRIPT_TO_CONTROL);
		HUD.set_function("IS_NAVIGATING_MENU_CONTENT", LUA_NATIVE_HUD_IS_NAVIGATING_MENU_CONTENT);
		HUD.set_function("HAS_MENU_TRIGGER_EVENT_OCCURRED", LUA_NATIVE_HUD_HAS_MENU_TRIGGER_EVENT_OCCURRED);
		HUD.set_function("HAS_MENU_LAYOUT_CHANGED_EVENT_OCCURRED", LUA_NATIVE_HUD_HAS_MENU_LAYOUT_CHANGED_EVENT_OCCURRED);
		HUD.set_function("SET_SAVEGAME_LIST_UNIQUE_ID", LUA_NATIVE_HUD_SET_SAVEGAME_LIST_UNIQUE_ID);
		HUD.set_function("GET_MENU_TRIGGER_EVENT_DETAILS", LUA_NATIVE_HUD_GET_MENU_TRIGGER_EVENT_DETAILS);
		HUD.set_function("GET_MENU_LAYOUT_CHANGED_EVENT_DETAILS", LUA_NATIVE_HUD_GET_MENU_LAYOUT_CHANGED_EVENT_DETAILS);
		HUD.set_function("GET_PM_PLAYER_CREW_COLOR", LUA_NATIVE_HUD_GET_PM_PLAYER_CREW_COLOR);
		HUD.set_function("GET_MENU_PED_INT_STAT", LUA_NATIVE_HUD_GET_MENU_PED_INT_STAT);
		HUD.set_function("GET_CHARACTER_MENU_PED_INT_STAT", LUA_NATIVE_HUD_GET_CHARACTER_MENU_PED_INT_STAT);
		HUD.set_function("GET_MENU_PED_MASKED_INT_STAT", LUA_NATIVE_HUD_GET_MENU_PED_MASKED_INT_STAT);
		HUD.set_function("GET_CHARACTER_MENU_PED_MASKED_INT_STAT", LUA_NATIVE_HUD_GET_CHARACTER_MENU_PED_MASKED_INT_STAT);
		HUD.set_function("GET_MENU_PED_FLOAT_STAT", LUA_NATIVE_HUD_GET_MENU_PED_FLOAT_STAT);
		HUD.set_function("GET_CHARACTER_MENU_PED_FLOAT_STAT", LUA_NATIVE_HUD_GET_CHARACTER_MENU_PED_FLOAT_STAT);
		HUD.set_function("GET_MENU_PED_BOOL_STAT", LUA_NATIVE_HUD_GET_MENU_PED_BOOL_STAT);
		HUD.set_function("CLEAR_PED_IN_PAUSE_MENU", LUA_NATIVE_HUD_CLEAR_PED_IN_PAUSE_MENU);
		HUD.set_function("GIVE_PED_TO_PAUSE_MENU", LUA_NATIVE_HUD_GIVE_PED_TO_PAUSE_MENU);
		HUD.set_function("SET_PAUSE_MENU_PED_LIGHTING", LUA_NATIVE_HUD_SET_PAUSE_MENU_PED_LIGHTING);
		HUD.set_function("SET_PAUSE_MENU_PED_SLEEP_STATE", LUA_NATIVE_HUD_SET_PAUSE_MENU_PED_SLEEP_STATE);
		HUD.set_function("OPEN_ONLINE_POLICIES_MENU", LUA_NATIVE_HUD_OPEN_ONLINE_POLICIES_MENU);
		HUD.set_function("ARE_ONLINE_POLICIES_UP_TO_DATE", LUA_NATIVE_HUD_ARE_ONLINE_POLICIES_UP_TO_DATE);
		HUD.set_function("IS_ONLINE_POLICIES_MENU_ACTIVE", LUA_NATIVE_HUD_IS_ONLINE_POLICIES_MENU_ACTIVE);
		HUD.set_function("OPEN_SOCIAL_CLUB_MENU", LUA_NATIVE_HUD_OPEN_SOCIAL_CLUB_MENU);
		HUD.set_function("CLOSE_SOCIAL_CLUB_MENU", LUA_NATIVE_HUD_CLOSE_SOCIAL_CLUB_MENU);
		HUD.set_function("SET_SOCIAL_CLUB_TOUR", LUA_NATIVE_HUD_SET_SOCIAL_CLUB_TOUR);
		HUD.set_function("IS_SOCIAL_CLUB_ACTIVE", LUA_NATIVE_HUD_IS_SOCIAL_CLUB_ACTIVE);
		HUD.set_function("SET_TEXT_INPUT_BOX_ENABLED", LUA_NATIVE_HUD_SET_TEXT_INPUT_BOX_ENABLED);
		HUD.set_function("FORCE_CLOSE_TEXT_INPUT_BOX", LUA_NATIVE_HUD_FORCE_CLOSE_TEXT_INPUT_BOX);
		HUD.set_function("SET_ALLOW_COMMA_ON_TEXT_INPUT", LUA_NATIVE_HUD_SET_ALLOW_COMMA_ON_TEXT_INPUT);
		HUD.set_function("OVERRIDE_MP_TEXT_CHAT_TEAM_STRING", LUA_NATIVE_HUD_OVERRIDE_MP_TEXT_CHAT_TEAM_STRING);
		HUD.set_function("IS_MP_TEXT_CHAT_TYPING", LUA_NATIVE_HUD_IS_MP_TEXT_CHAT_TYPING);
		HUD.set_function("CLOSE_MP_TEXT_CHAT", LUA_NATIVE_HUD_CLOSE_MP_TEXT_CHAT);
		HUD.set_function("MP_TEXT_CHAT_IS_TEAM_JOB", LUA_NATIVE_HUD_MP_TEXT_CHAT_IS_TEAM_JOB);
		HUD.set_function("OVERRIDE_MP_TEXT_CHAT_COLOR", LUA_NATIVE_HUD_OVERRIDE_MP_TEXT_CHAT_COLOR);
		HUD.set_function("MP_TEXT_CHAT_DISABLE", LUA_NATIVE_HUD_MP_TEXT_CHAT_DISABLE);
		HUD.set_function("FLAG_PLAYER_CONTEXT_IN_TOURNAMENT", LUA_NATIVE_HUD_FLAG_PLAYER_CONTEXT_IN_TOURNAMENT);
		HUD.set_function("SET_PED_HAS_AI_BLIP", LUA_NATIVE_HUD_SET_PED_HAS_AI_BLIP);
		HUD.set_function("SET_PED_HAS_AI_BLIP_WITH_COLOUR", LUA_NATIVE_HUD_SET_PED_HAS_AI_BLIP_WITH_COLOUR);
		HUD.set_function("DOES_PED_HAVE_AI_BLIP", LUA_NATIVE_HUD_DOES_PED_HAVE_AI_BLIP);
		HUD.set_function("SET_PED_AI_BLIP_GANG_ID", LUA_NATIVE_HUD_SET_PED_AI_BLIP_GANG_ID);
		HUD.set_function("SET_PED_AI_BLIP_HAS_CONE", LUA_NATIVE_HUD_SET_PED_AI_BLIP_HAS_CONE);
		HUD.set_function("SET_PED_AI_BLIP_FORCED_ON", LUA_NATIVE_HUD_SET_PED_AI_BLIP_FORCED_ON);
		HUD.set_function("SET_PED_AI_BLIP_NOTICE_RANGE", LUA_NATIVE_HUD_SET_PED_AI_BLIP_NOTICE_RANGE);
		HUD.set_function("SET_PED_AI_BLIP_SPRITE", LUA_NATIVE_HUD_SET_PED_AI_BLIP_SPRITE);
		HUD.set_function("GET_AI_PED_PED_BLIP_INDEX", LUA_NATIVE_HUD_GET_AI_PED_PED_BLIP_INDEX);
		HUD.set_function("GET_AI_PED_VEHICLE_BLIP_INDEX", LUA_NATIVE_HUD_GET_AI_PED_VEHICLE_BLIP_INDEX);
		HUD.set_function("HAS_DIRECTOR_MODE_BEEN_LAUNCHED_BY_CODE", LUA_NATIVE_HUD_HAS_DIRECTOR_MODE_BEEN_LAUNCHED_BY_CODE);
		HUD.set_function("SET_DIRECTOR_MODE_LAUNCHED_BY_SCRIPT", LUA_NATIVE_HUD_SET_DIRECTOR_MODE_LAUNCHED_BY_SCRIPT);
		HUD.set_function("SET_PLAYER_IS_IN_DIRECTOR_MODE", LUA_NATIVE_HUD_SET_PLAYER_IS_IN_DIRECTOR_MODE);
		HUD.set_function("SET_DIRECTOR_MODE_AVAILABLE", LUA_NATIVE_HUD_SET_DIRECTOR_MODE_AVAILABLE);
		HUD.set_function("HIDE_HUDMARKERS_THIS_FRAME", LUA_NATIVE_HUD_HIDE_HUDMARKERS_THIS_FRAME);
	}
}
