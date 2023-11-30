#pragma once
#include "memory/byte_patch.hpp"

namespace big
{
	struct explosion_anti_cheat_bypass
	{
		inline static memory::byte_patch* m_can_blame_others;
		inline static memory::byte_patch* m_can_use_blocked_explosions;

		inline static void apply()
		{
			explosion_anti_cheat_bypass::m_can_blame_others->apply();
			explosion_anti_cheat_bypass::m_can_use_blocked_explosions->apply();
		}

		inline static void restore()
		{
			explosion_anti_cheat_bypass::m_can_use_blocked_explosions->restore();
			explosion_anti_cheat_bypass::m_can_blame_others->restore();
		}
	};
}