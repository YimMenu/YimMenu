#include "backend/command.hpp"
#include "natives.hpp"

namespace big
{
	class clear_wanted : command
	{
		using command::command;

		virtual void execute(const std::vector<std::uint64_t>&, const std::shared_ptr<command_context> ctx)
		{
			if(g_local_player && g_local_player !=nullptr && !g.self.force_wanted_level)
			{
				g.self.wanted_level = 0;
				g_local_player->m_player_info->m_is_wanted = false;
			}
		}
	};

	clear_wanted g_clear_wanted("clearwantedlvl", "Clear Wanted Level", "Clears your wanted level", 0);
}