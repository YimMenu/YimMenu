#pragma once
#include "file_manager/file.hpp"
#include "services/players/player_service.hpp"
#include "core/enums.hpp"

#include "packet.hpp"
#include "natives.hpp"
#include "script.hpp"
#include "fiber_pool.hpp"
#include "core/scr_globals.hpp"

#include <network/CNetGamePlayer.hpp>
#include <script/HudColor.hpp>
#include <network/ChatData.hpp>
#include <script/globals/GPBD_FM_3.hpp>

namespace
{
	static void gamer_handle_serialize(rage::rlGamerHandle& hnd, rage::datBitBuffer& buf)
	{
		buf.Write<uint8_t>(hnd.m_platform, sizeof(hnd.m_platform) * 8);
		if (hnd.m_platform == rage::rlPlatforms::PC)
		{
			buf.WriteRockstarId(hnd.m_rockstar_id);
			buf.Write<uint8_t>(hnd.m_padding, sizeof(hnd.m_padding) * 8);
		}
	}

	static const char* spam_texts[] = 
	{
	    "qq", //a chinese chat app
	    "QQ",
	    "WWW.",
	    "www.",
	    ".cn",
	    ".CN",
	    ".cc",
	    ".CC",
	    ".TOP",
	    ".COM",
	    ".top",
	    "\xE3\x80\x90", //left bracket in Chinese input method
	    "/Menu",
	    "Money/",
	    "Money\\\\",
	    "Money\\",
	    ".gg",
	    "--->",
	    "shopgta5",
	    "doit#",
	    "krutka#",
	    "<b>",
	    "P888",
	    "gtacash",
	    ".cc",
	    "<font s",
	    "sellix.io",
	    "ezcars",
	    "PLANO INICIAL", // "initial plan"
	    "REP +",
	    "20R$", // Brazil currency?
	    "l55.me",
	    "TRUSTPILOT",
	    "cashlounge",
	    "Fast Delivery",
	    "yosativa",
	    "rich2day",
	    "LevelLifters",
	    ". com",
	    "$1,000,000,000",
	    "Instant Delivery",
	    "0 Ban Risk",
	    "Discord For Cheap Money",
	    "10-30m",
	    "Discord todo",
	    "\xE6\x89\xA3\xE6\x89\xA3",             // QQ
	    "\xE4\xBC\xA0\xE5\xAA\x92",             // AV
	    "\xE8\x96\x87\xE4\xBF\xA1",             // Wechat
	    "\xE7\xBB\xB4\xE4\xBF\xA1",             // Wechat2
	    "\xE9\xA6\x96\xE5\x8D\x95",             // Shop promotion
	    "\xE5\x8C\x85\xE8\xB5\x94",             // Shop promotion
	    "\xE9\x9B\xB6\xE5\xB0\x81",             // Menu promotion
	    "\xE4\xB8\x8D\xE5\xB0\x81",             // Menu promotion
	    "\xE7\x94\xB5\xE7\x8E\xA9",             // Shop
	    "\xE4\xB8\x9A\xE5\x8A\xA1",             // Shop promotion
	    "\xE5\x88\xB7\xE9\x87\x91",             // Shop AD
	    "\xE5\x88\xB7\xE9\x92\xB1",             // Shop AD
	    "\xE9\x87\x91\xE5\xB8\x81",             // Shop AD
	    "\xE9\x87\x91\xE6\x9D\xA1",             // Shop AD
	    "\xE5\x85\x83\xE8\xB5\xB7",             // Shop AD
	    "\xE4\xB8\x8B\xE5\x8D\x95",             // Shop AD
	    "\xE6\x89\x93\xE9\x87\x91",             // Shop AD
	    "\xE5\xA6\xB9\xE5\xAD\x90",             // AV
	    "\xE4\xBD\x8E\xE4\xBB\xB7",             // Menu promotion
	    "\xE9\xAB\x98\xE7\xAB\xAF",             // Menu promotion
	    "\xE8\xA7\x86\xE5\xB1\x8F",             // AV
	    "\xE6\x88\x90\xE5\x85\xA5",             // AV
	    "\xE5\x85\xA8\xE7\xBD\xB1",             // Shop AD
	    "\xE5\x94\xAE\xE5\x90\x8E",             // Shop AD
	    "Q\xE7\xBE\xA4",                        // QQ group
	    "\xE7\xA6\x8F\xE5\x88\xA9",             // AV
	    "\xE6\x8A\x96\xE9\x9F\xB3",             // AV
	    "\xE5\x8A\xA0\xE5\xBE\xAE",             // Wechat
	    "\xE7\xBE\x8E\xE4\xBA\xBA",             // AV
	    "\xE5\xBC\xBA\xE5\xA5\xB8",             // AV
	    "\xE6\xAD\xAA\xE6\xAD\xAA",             // Chat app
	    "\xE5\xB0\x8F\xE7\xA8\x8B\xE5\xBA\x8F", // Wechat miniapp
	    "\xE6\xB7\x98\xE5\xAE\x9D",             // Shop
	    "\xE5\xBA\x97\xE9\x93\xBA",             // Shop
	    "\xE6\x8E\x8F\xE5\xAE\x9D",             // Shop
	    "\xE8\x80\x81\xE5\x93\x88",             // Mod shop
	    "\xE5\xBE\xAE\xE4\xBF\xA1\xE6\x90\x9C", // Wechat search
	    "\xE7\xBE\x8E\xE5\xA5\xB3",             // AV
	    "\xE8\x90\x9D",                         // AV
	    "\xE7\xBD\x91\xE7\xBA\xA2",             // AV
	    "\xE5\x81\xB7\xE6\x8B\x8D",             // AV
	    "\xE4\xBC\xA0\xE7\x85\xA4",             // AV
	    "\xE4\xB9\xB1\xE8\xAE\xBA",             // AV
	};
}

namespace big::chat
{
	inline SpamReason is_text_spam(const char* text, player_ptr player)
	{
		if ((player->is_trusted || (g.session.trust_friends && player->is_friend())))
			return SpamReason::NOT_A_SPAMMER; // don't filter messages from friends

		if (g.session.use_spam_timer)
		{
			if (player->last_message_time.has_value())
			{
				auto currentTime = std::chrono::steady_clock::now();
				auto diff = std::chrono::duration_cast<std::chrono::seconds>(currentTime - player->last_message_time.value());
				player->last_message_time.emplace(currentTime);

				if (strlen(text) > g.session.spam_length && diff.count() <= g.session.spam_timer)
					return SpamReason::TIMER_DETECTION;
			}
			else
			{
				player->last_message_time.emplace(std::chrono::steady_clock::now());
			}
		}
		for (auto e : spam_texts)
			if (strstr(text, e) != 0)
				return SpamReason::STATIC_DETECTION;

		return SpamReason::NOT_A_SPAMMER;
	}

	inline void log_chat(char* msg, player_ptr player, SpamReason spam_reason, bool is_team)
	{
		std::ofstream log(
		    g_file_manager.get_project_file(spam_reason != SpamReason::NOT_A_SPAMMER ? "./spam.log" : "./chat.log").get_path(),
		    std::ios::app);

		auto& data = *player->get_net_data();
		auto ip    = player->get_ip_address();

		auto now        = std::chrono::system_clock::now();
		auto ms         = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
		auto timer      = std::chrono::system_clock::to_time_t(now);
		auto local_time = *std::localtime(&timer);

		std::string spam_reason_str = "";

		switch (spam_reason)
		{
		case SpamReason::STATIC_DETECTION: spam_reason_str = "(Static Detection) "; break;
		case SpamReason::TIMER_DETECTION: spam_reason_str = "(Timer Detection) "; break;
		}

		log << spam_reason_str << "[" << std::put_time(&local_time, "%m/%d/%Y %I:%M:%S") << ":" << std::setfill('0') << std::setw(3) << ms.count() << " " << std::put_time(&local_time, "%p") << "] ";

		if (ip)
			log << player->get_name() << " (" << data.m_gamer_handle.m_rockstar_id << ") <" << (int)ip.value().m_field1 << "."
			    << (int)ip.value().m_field2 << "." << (int)ip.value().m_field3 << "." << (int)ip.value().m_field4 << "> " << ((is_team == true) ? "[TEAM]: " : "[ALL]: ") << msg << std::endl;
		else
			log << player->get_name() << " (" << data.m_gamer_handle.m_rockstar_id << ") <UNKNOWN> " << ((is_team == true) ? "[TEAM]: " : "[ALL]: ") << msg << std::endl;

		log.close();
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

	inline bool is_on_same_team(CNetGamePlayer* player)
	{
		auto target_id = player->m_player_id;

		if (NETWORK::NETWORK_IS_ACTIVITY_SESSION())
		{
			// mission
			return PLAYER::GET_PLAYER_TEAM(target_id) == PLAYER::GET_PLAYER_TEAM(self::id);
		}
		else
		{
			auto boss_goon = &scr_globals::gpbd_fm_3.as<GPBD_FM_3*>()->Entries[self::id].BossGoon;

			if (boss_goon->Boss == target_id)
				return true;

			if (boss_goon->Boss == -1)
				return false;

			if (boss_goon->Boss != self::id)
				boss_goon = &scr_globals::gpbd_fm_3.as<GPBD_FM_3*>()->Entries[boss_goon->Boss].BossGoon; // get their structure

			// bypass some P2Cs
			for (int i = 0; i < boss_goon->Goons.Size; i++)
			{
				if (boss_goon->Goons[i] == target_id)
				{
					return true;
				}
			}

			return false;
		}
	}

	// set target to send to a specific player
	inline void send_message(const std::string& message, player_ptr target = nullptr, bool draw = true, bool is_team = false)
	{
		if (!*g_pointers->m_gta.m_is_session_started)
			return;

		packet msg{};
		msg.write_message(rage::eNetMessage::MsgTextMessage);
		msg.m_buffer.WriteString(message.c_str(), 256);
		gamer_handle_serialize(g_player_service->get_self()->get_net_data()->m_gamer_handle, msg.m_buffer);
		msg.write<bool>(is_team, 1);


		for (auto& player : g_player_service->players())
		{
			if (player.second && player.second->is_valid())
			{
				if (target && player.second != target)
					continue;

				if (!target && is_team && !is_on_same_team(player.second->get_net_game_player()))
					continue;

				msg.send(player.second->get_net_game_player()->m_msg_id);
			}
		}

		if (draw)
			if (rage::tlsContext::get()->m_is_script_thread_active)
				draw_chat(message.c_str(), g_player_service->get_self()->get_name(), is_team);
			else
				g_fiber_pool->queue_job([message, target, is_team] {
					draw_chat(message.c_str(), g_player_service->get_self()->get_name(), is_team);
				});
	}
}
