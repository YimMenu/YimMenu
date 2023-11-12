#pragma once
#include "core/enums.hpp"

#include <rage/rlSessionInfo.hpp>

namespace big
{
	inline struct g_session_t
	{
		bool log_chat_messages_to_file    = false;
		bool log_chat_messages_to_textbox = false;

		bool decloak_players    = false;
		bool force_session_host = false;
		bool force_script_host  = false;
		bool lock_session       = false;

		CommandAccessLevel chat_command_default_access_level = CommandAccessLevel::FRIENDLY;

		bool force_thunder = false;

		bool join_queued = false;
		rage::rlSessionInfo info;

		bool spoof_hide_spectate = true;
		bool spoof_hide_god      = true;

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(g_session_t, log_chat_messages_to_file, log_chat_messages_to_textbox)
	} g_session{};
}