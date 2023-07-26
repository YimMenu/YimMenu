#include "backend/command.hpp"
#include "natives.hpp"

namespace big
{
	class clear_wanted : command
	{
		using command::command;

		virtual void execute(const std::vector<uint64_t>&, const std::shared_ptr<command_context> ctx)
		{
			if(g_local_player && g_local_player !=nullptr && !g.self.force_wanted_level)
			{
				g_local_player->m_player_info->m_wanted_level = 0;
				g.self.wanted_level = 0;
				g_local_player->m_player_info->m_is_wanted = false;
			}
		}
	};

	clear_wanted g_clear_wanted("clearwantedlvl", "CLEAR_WANTED_LEVEL", "CLEAR_WANTED_LEVEL_DESC_SELF", 0);
}