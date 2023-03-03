#include "backend/command.hpp"
#include "backend/context/chat_command_context.hpp"
#include "gta_util.hpp"
#include "hooking.hpp"
#include "services/players/player_service.hpp"

namespace big
{
	bool hooks::send_chat_message(void* team_mgr, rage::rlGamerInfo* local_gamer_info, char* message, bool is_team)
	{
		if (g.session.chat_commands && message[0] == g.session.chat_command_prefix)
			command::process(std::string(message + 1), std::make_shared<chat_command_context>(g_player_service->get_self()));

		return g_hooking->get_original<hooks::send_chat_message>()(team_mgr, local_gamer_info, message, is_team);
	}
}