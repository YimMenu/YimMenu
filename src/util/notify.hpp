#pragma once
#include "gta/enums.hpp"
#include "natives.hpp"
#include "network/CNetGamePlayer.hpp"
#include "script.hpp"
#include "session.hpp"

#include <script/HudColor.hpp>

namespace big::notify
{
	inline void above_map(std::string_view text)
	{
		HUD::SET_TEXT_OUTLINE();
		HUD::BEGIN_TEXT_COMMAND_THEFEED_POST("STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text.data());
		HUD::END_TEXT_COMMAND_THEFEED_POST_TICKER(false, false);
	}

	inline void crash_blocked(CNetGamePlayer* player, const char* crash)
	{
		if (player)
		{
			g_notification_service->push_error("Protections", std::format("Blocked {} crash from {}", crash, player->get_name()));
			LOG(WARNING) << "Blocked " << crash << " crash from " << player->get_name() << " ("
			             << (player->get_net_data() ? player->get_net_data()->m_gamer_handle.m_rockstar_id : 0) << ")";
		}
		else
		{
			g_notification_service->push_error("Protections", std::format("Blocked {} crash from unknown player", crash));
		}

		if (player)
		{
			if (auto plyr = g_player_service->get_by_id(player->m_player_id))
			{
				session::add_infraction(plyr, Infraction::TRIED_CRASH_PLAYER);
			}
		}
	}

	// Shows a busy spinner till the value at the address equals the value passed or if timeout is hit
	inline void busy_spinner(std::string_view text, int* address, int value, int timeout = 15)
	{
		HUD::BEGIN_TEXT_COMMAND_BUSYSPINNER_ON("STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text.data());
		HUD::END_TEXT_COMMAND_BUSYSPINNER_ON(3);

		for (size_t i = 0; *address != value && i < (size_t)timeout * 100; i++)
			script::get_current()->yield(10ms);

		HUD::BUSYSPINNER_OFF();
	}

	inline void display_help_text(std::string_view text)
	{
		HUD::BEGIN_TEXT_COMMAND_DISPLAY_HELP("STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text.data());
		HUD::END_TEXT_COMMAND_DISPLAY_HELP(0, 0, 1, -1);
	}

	inline void player_joined(CNetGamePlayer* net_game_player)
	{
		above_map(std::format("<C>{}</C> joined.", net_game_player->get_name()));
	}

	inline void draw_chat(char* msg, const char* player_name, bool is_team)
	{
		int scaleform = GRAPHICS::REQUEST_SCALEFORM_MOVIE("MULTIPLAYER_CHAT");
		GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(scaleform, "ADD_MESSAGE");
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_PLAYER_NAME_STRING(player_name);// player name
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_LITERAL_STRING(msg);            // content
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_TEXTURE_NAME_STRING(HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(is_team ? "MP_CHAT_TEAM" : "MP_CHAT_ALL"));// scope
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_BOOL(false);                              // teamOnly
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT((int)HudColor::HUD_COLOUR_PURE_WHITE);// eHudColour
		GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
		GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(scaleform, "SET_FOCUS");
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(1);                                   // VISIBLE_STATE_DEFAULT
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(0);                                   // scopeType (unused)
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(0);                                   // scope (unused)
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_PLAYER_NAME_STRING(player_name);          // player
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT((int)HudColor::HUD_COLOUR_PURE_WHITE);// eHudColour
		GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
		GRAPHICS::DRAW_SCALEFORM_MOVIE_FULLSCREEN(scaleform, 255, 255, 255, 255, 0);
	}
}