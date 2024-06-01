#include "notify.hpp"
#include "chat.hpp"
#include "fiber_pool.hpp"
#include "gta/enums.hpp"
#include "hooking/hooking.hpp"
#include "natives.hpp"
#include "network/CNetGamePlayer.hpp"
#include "network/ChatData.hpp"
#include "pointers.hpp"
#include "script.hpp"
#include "services/players/player_service.hpp"

namespace big::notify
{
	void above_map(std::string_view text)
	{
		HUD::SET_TEXT_OUTLINE();
		HUD::BEGIN_TEXT_COMMAND_THEFEED_POST("STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text.data());
		HUD::END_TEXT_COMMAND_THEFEED_POST_TICKER(false, false);
	}

	void crash_blocked(CNetGamePlayer* player, const char* crash)
	{
		if (player && g_player_service->get_by_id(player->m_player_id))
		{
			if ((g_player_service->get_by_id(player->m_player_id)->is_friend() && g.session.trust_friends)
			    || g_player_service->get_by_id(player->m_player_id)->is_trusted || g.session.trust_session)
				return;

			if (g.reactions.crash.notify)
				g_notification_service.push_error("Protections", std::format("Blocked {} crash from {}", crash, player->get_name()));

			if (g.reactions.crash.log)
				LOG(WARNING) << "Blocked " << crash << " crash from " << player->get_name() << " ("
				             << (player->get_net_data() ? player->get_net_data()->m_gamer_handle.m_rockstar_id : 0) << ")";

			if (g.reactions.crash.announce_in_chat)
			{
				auto p_name = player->get_name();

				auto msg = std::vformat("NOTIFICATION_CRASH_TYPE_BLOCKED"_T, std::make_format_args(p_name, crash));
				msg = std::format("{} {}", g.session.chat_output_prefix, msg);
				
				chat::send_message(msg);
			}

			g.reactions.crash.process_common(g_player_service->get_by_id(player->m_player_id));
		}
		else
		{
			if (g.reactions.crash.notify)
				g_notification_service.push_error("Protections", std::format("Blocked {} crash from unknown player", crash));
		}
	}

	// Shows a busy spinner till the value at the address equals the value passed or if timeout is hit
	void busy_spinner(std::string_view text, int* address, int value, int timeout)
	{
		HUD::BEGIN_TEXT_COMMAND_BUSYSPINNER_ON("STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text.data());
		HUD::END_TEXT_COMMAND_BUSYSPINNER_ON(3);

		for (size_t i = 0; *address != value && i < (size_t)timeout * 100; i++)
			script::get_current()->yield(10ms);

		HUD::BUSYSPINNER_OFF();
	}

	void show_subtitle(std::string_view text, int ms)
	{
		HUD::BEGIN_TEXT_COMMAND_PRINT("STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text.data());
		HUD::END_TEXT_COMMAND_PRINT(ms, 1);
	}

	void display_help_text(std::string_view text)
	{
		HUD::BEGIN_TEXT_COMMAND_DISPLAY_HELP("STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text.data());
		HUD::END_TEXT_COMMAND_DISPLAY_HELP(0, 0, 1, -1);
	}

	void player_joined(CNetGamePlayer* net_game_player)
	{
		above_map(std::format("<C>{}</C> joined.", net_game_player->get_name()));
	}
}