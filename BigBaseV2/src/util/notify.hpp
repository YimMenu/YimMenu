#pragma once
#include "CNetGamePlayer.hpp"
#include "natives.hpp"
#include "script.hpp"

namespace big::notify
{
	inline void above_map(const char* text)
	{
		HUD::SET_TEXT_OUTLINE();
		HUD::BEGIN_TEXT_COMMAND_THEFEED_POST("STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
		HUD::END_TEXT_COMMAND_THEFEED_POST_TICKER(false, false);
	}
	inline void above_map(std::string text) { above_map(text.c_str()); }

	// deprecated/unused
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

	// Shows a busy spinner till the value at the address equals the value passed or if timeout is hit
	inline void busy_spinner(const char* text, int* address, int value, int timeout = 15)
	{
		HUD::BEGIN_TEXT_COMMAND_BUSYSPINNER_ON("STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
		HUD::END_TEXT_COMMAND_BUSYSPINNER_ON(3);

		for (size_t i = 0; *address != value && i < (size_t)timeout * 100; i++)
			script::get_current()->yield(10ms);
		
		HUD::BUSYSPINNER_OFF();
	}

	inline void display_help_text(const char* text)
	{
		HUD::BEGIN_TEXT_COMMAND_DISPLAY_HELP("STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
		HUD::END_TEXT_COMMAND_DISPLAY_HELP(0, 0, 1, -1);
	}

	inline void player_joined(CNetGamePlayer* net_game_player)
	{
		above_map(
			fmt::format("<C>{}</C> joined.", net_game_player->get_name())
		);
	}
}