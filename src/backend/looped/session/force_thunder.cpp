#include "backend/looped/looped.hpp"
#include "gta_util.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "util/session.hpp"

namespace big
{
	static bool bLastForceThunderEnabled = false;

	void looped::session_force_thunder()
	{
		bool used = g.session.force_thunder && *g_pointers->m_is_session_started;
		if (!bLastForceThunderEnabled && used)
		{
			if (!STREAMING::IS_PLAYER_SWITCH_IN_PROGRESS() && gta_util::find_script_thread(RAGE_JOAAT("freemode")) && SCRIPT::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH(RAGE_JOAAT("maintransition")) == 0)
			{
				session::set_fm_event_index(9);
				session::set_fm_event_index(10);
				session::set_fm_event_index(11);
				bLastForceThunderEnabled = true;
			}
		}
		else if (bLastForceThunderEnabled && !used)
		{
			if (*g_pointers->m_is_session_started && !STREAMING::IS_PLAYER_SWITCH_IN_PROGRESS() && gta_util::find_script_thread(RAGE_JOAAT("freemode")))
			{
				session::clear_fm_event_index(9);
				session::clear_fm_event_index(10);
				session::clear_fm_event_index(11);
			}

			bLastForceThunderEnabled = false;
		}
	}
}
