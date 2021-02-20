#include "features/self.hpp"
#include "gta_util.hpp"

namespace big
{
	static bool bLastGodMode = false;

	void self::god_mode()
	{
		bool bGodMode = g_settings.options["god_mode"].get<bool>();

		if (bGodMode || (!bGodMode && bGodMode != bLastGodMode))
		{
			g_local_ped->m_godmode = bGodMode ? 0x1 : 0x0;

			//ENTITY::SET_ENTITY_INVINCIBLE(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(g_player.id), bGodMode);

			bLastGodMode = bGodMode;
		}
	}
}