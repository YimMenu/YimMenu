#include "backend/command.hpp"
#include "backend/context/chat_command_context.hpp"
#include "hooking/hooking.hpp"
#include "services/players/player_service.hpp"
#include "util/chat.hpp"

namespace big
{
	bool hooks::send_chat_message(void* team_mgr, rage::rlGamerInfo* local_gamer_info, char* message, bool is_team)
	{
		if (g.session.chat_commands && message[0] == g.session.chat_command_prefix)
			command::process(std::string(message + 1), std::make_shared<chat_command_context>(g_player_service->get_self()));

		chat::send_message(message, nullptr, false, is_team);

		if (g.session.log_chat_messages)
			chat::log_chat(message, g_player_service->get_self(), SpamReason::NOT_A_SPAMMER, is_team);

		return true;
	}
}