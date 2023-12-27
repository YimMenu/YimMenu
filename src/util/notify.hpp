#pragma once
#include "gta/enums.hpp"
#include "natives.hpp"
#include "network/CNetGamePlayer.hpp"
#include "network/ChatData.hpp"
#include "pointers.hpp"
#include "script.hpp"
#include "services/players/player_service.hpp"
#include "fiber_pool.hpp"
#include "hooking/hooking.hpp"

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

	inline void draw_chat(const char* msg, const char* player_name, bool is_team)
	{
		int scaleform = GRAPHICS::REQUEST_SCALEFORM_MOVIE("MULTIPLAYER_CHAT");

		while (!GRAPHICS::HAS_SCALEFORM_MOVIE_LOADED(scaleform))
			script::get_current()->yield();

		GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(scaleform, "ADD_MESSAGE");
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_PLAYER_NAME_STRING(player_name); // player name
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_LITERAL_STRING(msg);             // content
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_TEXTURE_NAME_STRING(HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(is_team ? "MP_CHAT_TEAM" : "MP_CHAT_ALL")); // scope
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_BOOL(false);                               // teamOnly
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT((int)HudColor::HUD_COLOUR_PURE_WHITE); // eHudColour
		GRAPHICS::END_SCALEFORM_MOVIE_METHOD();

		GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(scaleform, "SET_FOCUS");
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(1);                                    // VISIBLE_STATE_DEFAULT
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(0);                                    // scopeType (unused)
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(0);                                    // scope (unused)
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_PLAYER_NAME_STRING(player_name);           // player
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT((int)HudColor::HUD_COLOUR_PURE_WHITE); // eHudColour
		GRAPHICS::END_SCALEFORM_MOVIE_METHOD();

		GRAPHICS::DRAW_SCALEFORM_MOVIE_FULLSCREEN(scaleform, 255, 255, 255, 255, 0);

		// fix broken scaleforms, when chat alrdy opened
		if (const auto chat_data = *g_pointers->m_gta.m_chat_data; chat_data && (chat_data->m_chat_open || chat_data->m_timer_two))
			HUD::CLOSE_MP_TEXT_CHAT();
	}

	inline void crash_blocked(CNetGamePlayer* player, const char* crash)
	{
		if (player)
		{
			if ((g_player_service->get_by_id(player->m_player_id)->is_friend() && g.session.trust_friends)
			    || g_player_service->get_by_id(player->m_player_id)->is_trusted
			    || g.session.trust_session)
				return;

			if (g.reactions.crash.notify)
				g_notification_service->push_error("Protections", std::format("Blocked {} crash from {}", crash, player->get_name()));

			if (g.reactions.crash.log)
				LOG(WARNING) << "Blocked " << crash << " crash from " << player->get_name() << " ("
				             << (player->get_net_data() ? player->get_net_data()->m_gamer_handle.m_rockstar_id : 0) << ")";
			
			if (g.reactions.crash.announce_in_chat)
			{
				g_fiber_pool->queue_job([player, crash] {
					auto chat = std::vformat("NOTIFICATION_CRASH_TYPE_BLOCKED"_T, std::make_format_args(player->get_name(), crash));
					chat = std::format("{} {}", g.session.chat_output_prefix, chat);

					if (g_hooking->get_original<hooks::send_chat_message>()(*g_pointers->m_gta.m_send_chat_ptr,
					        g_player_service->get_self()->get_net_data(),
					        chat.data(),
					        g.reactions.crash.is_team_only))
						draw_chat(chat.c_str(), g_player_service->get_self()->get_name(), g.reactions.crash.is_team_only);
				});
			}

			g.reactions.crash.process_common(g_player_service->get_by_id(player->m_player_id));
		}
		else
		{
			if (g.reactions.crash.notify)
				g_notification_service->push_error("Protections", std::format("Blocked {} crash from unknown player", crash));
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

	inline void show_subtitle(std::string_view text, int ms = 2000)
	{
		HUD::BEGIN_TEXT_COMMAND_PRINT("STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text.data());
		HUD::END_TEXT_COMMAND_PRINT(ms, 1);
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

}