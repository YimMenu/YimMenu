#include "notify.hpp"
#include "natives.hpp"

namespace big
{
	void notify::above_map(const char* text)
	{
		HUD::SET_TEXT_OUTLINE();
		HUD::BEGIN_TEXT_COMMAND_THEFEED_POST("STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
		HUD::END_TEXT_COMMAND_THEFEED_POST_TICKER(false, false);
	}

	void notify::blocked_event(const char* name, Player player)
	{
		char msg[128];

		strcpy(msg, "~g~BLOCKED RECEIVED EVENT~s~\n~b~");
		strcat(msg, name);
		strcat(msg, "~s~\nFrom: <C>");
		strcat(msg, PLAYER::GET_PLAYER_NAME(player));
		strcat(msg, "</C>");

		above_map(msg);
	}
}