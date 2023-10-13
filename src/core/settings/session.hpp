#pragma once
#include <rage/rlSessionInfo.hpp>
#include "core/enums.hpp"

namespace big
{
	inline struct g_session_t
	{
		bool log_chat_messages                 = false;
		bool decloak_players                   = false;
		bool force_session_host                = false;
		bool force_script_host                 = false;
		bool lock_session                      = false;
		bool allow_friends_into_locked_session = true;

		CommandAccessLevel chat_command_default_access_level = CommandAccessLevel::FRIENDLY;

		bool force_thunder = false;

		bool join_queued = false;
		rage::rlSessionInfo info;

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(g_session_t, log_chat_messages)
	} g_session{};
}