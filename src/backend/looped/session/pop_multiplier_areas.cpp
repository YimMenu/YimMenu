#include "backend/looped/looped.hpp"
#include "gta_util.hpp"
#include "natives.hpp"
#include "pointers.hpp"

namespace big
{
	static bool bLastPopMultiplierAreasEnabled = false;
	static bool bLastBlockPeds                 = false;
	static bool bLastBlockVehs                 = false;
	static int pop_multiplier_id               = -1;

	void looped::session_pop_multiplier_areas()
	{
		bool used = (g.session.disable_traffic || g.session.disable_peds) && *g_pointers->m_gta.m_is_session_started;
		if (!bLastPopMultiplierAreasEnabled && used)
		{
			if (!STREAMING::IS_PLAYER_SWITCH_IN_PROGRESS() && gta_util::find_script_thread("freemode"_J) && SCRIPT::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH("maintransition"_J) == 0)
			{
				gta_util::execute_as_script("freemode"_J, [] {
					pop_multiplier_id = MISC::ADD_POP_MULTIPLIER_SPHERE(1.1f,
					    1.1f,
					    1.1f,
					    15000.0f,
					    g.session.disable_peds ? 0.0f : 1.0f,
					    g.session.disable_traffic ? 0.0f : 1.0f,
					    false,
					    true);

					bLastBlockPeds                 = g.session.disable_peds;
					bLastBlockVehs                 = g.session.disable_traffic;
					bLastPopMultiplierAreasEnabled = true;

					MISC::CLEAR_AREA(1.1f, 1.1f, 1.1f, 19999.9f, true, false, false, true);
				});
			}
		}
		else if (bLastPopMultiplierAreasEnabled && (g.session.disable_traffic != bLastBlockVehs || g.session.disable_peds != bLastBlockPeds))
		{
			bLastBlockPeds = g.session.disable_peds;
			bLastBlockVehs = g.session.disable_traffic;
			used           = false;
		}

		if (bLastPopMultiplierAreasEnabled && !used)
		{
			if (gta_util::find_script_thread("freemode"_J))
			{
				gta_util::execute_as_script("freemode"_J, [] {
					MISC::REMOVE_POP_MULTIPLIER_SPHERE(pop_multiplier_id, false);
				});
			}

			bLastPopMultiplierAreasEnabled = false;
			pop_multiplier_id              = -1;
		}
	}
}
