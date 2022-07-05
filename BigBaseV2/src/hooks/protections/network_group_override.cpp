#include "hooking.hpp"

namespace big
{
	// thanks ellisdudes :P
	void hooks::network_group_override(std::int64_t a1, std::int64_t a2, std::int64_t a3)
	{
		if (a2 == 0 && (a3 == 103 || a3 == 0))
		{
			LOG(WARNING) << "Received SCRIPT_WORLD_STATE_EVENT crash from unknown attacker...";

			return;
		}
		// original

		return g_hooking->m_network_group_override.get_original<decltype(&network_group_override)>()(a1, a2, a3);
	}
}