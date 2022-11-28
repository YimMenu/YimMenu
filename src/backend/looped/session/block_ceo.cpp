#include "backend/looped/looped.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "gta_util.hpp"
#include "util/session.hpp"
#include "core/scr_globals.hpp"

namespace big
{
	static bool bLastBlockCeoCreationEnabled = false;

	void looped::session_block_ceo()
	{
		bool ceoCreationUsed = g->session.block_ceo_creation && *g_pointers->m_is_session_started;

		if (!bLastBlockCeoCreationEnabled && ceoCreationUsed)
		{
			if (!STREAMING::IS_PLAYER_SWITCH_IN_PROGRESS() && gta_util::find_script_thread(RAGE_JOAAT("freemode")))
			{
				for (int i = 0; i < *scr_globals::gsbd_fm_events.at(11).at(132).as<int*>(); i++)
				{
					*scr_globals::gsbd_fm_events.at(11).at(132).at(i, 1).as<int*>() = self::id;
				}
				bLastBlockCeoCreationEnabled = true;
			}
		}
		else if (bLastBlockCeoCreationEnabled && !ceoCreationUsed)
		{
			if (*g_pointers->m_is_session_started && !STREAMING::IS_PLAYER_SWITCH_IN_PROGRESS() && gta_util::find_script_thread(RAGE_JOAAT("freemode")))
			{
				for (int i = 0; i < *scr_globals::gsbd_fm_events.at(11).at(132).as<int*>(); i++)
				{
					*scr_globals::gsbd_fm_events.at(11).at(132).at(i, 1).as<int*>() = -1;
				}
			}

			bLastBlockCeoCreationEnabled = false;
		}
	}
}
