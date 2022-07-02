#include "backend/looped/looped.hpp"
#include "natives.hpp"

namespace big
{
	static bool bLastGodMode = false;

	void looped::self_godmode()
	{
		bool bGodMode = g->self.godmode;

		if (bGodMode || (!bGodMode && bGodMode != bLastGodMode))
		{
			ENTITY::SET_ENTITY_INVINCIBLE(self::ped, g->self.godmode);

			bLastGodMode = g->self.godmode;
		}

		if (g_local_player != nullptr)
		{
			g_local_player->m_damage_bits = g->self.proof_mask;
		}
	}
}