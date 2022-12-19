#include "backend/looped/looped.hpp"

namespace big
{
	void looped::self_unlimited_oxygen()
	{
		if (g_local_player == nullptr) return;

		if (g.self.unlimited_oxygen)
			g_local_player->m_oxygen_info->m_oxygen_time = 0;
	}
}