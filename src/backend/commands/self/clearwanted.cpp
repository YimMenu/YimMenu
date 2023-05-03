#include "clearwanted.hpp"

#include "natives.hpp"

namespace big
{
	void clear_wanted::execute(const std::vector<std::uint64_t>&, const std::shared_ptr<command_context> ctx)
	{
		if (g_local_player && !g.self.force_wanted_level)
		{
			g_local_player->m_player_info->m_wanted_level = 0;
			g.self.wanted_level                           = 0;
			g_local_player->m_player_info->m_is_wanted    = false;
		}
	}
}
