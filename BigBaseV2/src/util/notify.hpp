#pragma once
#include "natives.hpp"

namespace big::notify
{
	inline void above_map(const char* text)
	{
		HUD::SET_TEXT_OUTLINE();
		HUD::BEGIN_TEXT_COMMAND_THEFEED_POST("STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
		HUD::END_TEXT_COMMAND_THEFEED_POST_TICKER(false, false);
	}

	inline void blocked_event(const char* name, Player player)
	{
		char msg[128];

		strcpy(msg, "~g~BLOCKED RECEIVED EVENT~s~\n~b~");
		strcat(msg, name);
		strcat(msg, "~s~\nFrom: <C>");
		strcat(msg, PLAYER::GET_PLAYER_NAME(player));
		strcat(msg, "</C>");

		above_map(msg);
	}

	inline void display_help_text(const char* text)
	{
		HUD::BEGIN_TEXT_COMMAND_DISPLAY_HELP("STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
		HUD::END_TEXT_COMMAND_DISPLAY_HELP(0, 0, 1, -1);
	}

	inline void player_joined(CPlayer player)
	{
		char msg[64];

		strcpy(msg, "<C>");
		strcat(msg, player.name);
		strcat(msg, "</C>");
		strcat(msg, " joined.");

		above_map(msg);
	}
}