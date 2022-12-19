#include "backend/looped/looped.hpp"
#include "fiber_pool.hpp"
#include "natives.hpp"
#include "script.hpp"
#include "pointers.hpp"

namespace big
{
	bool bLastAutoTP = false;
	void looped::system_auto_tp()
	{
		bool temp_disable_tp = (!*g_pointers->m_is_session_started) && CUTSCENE::IS_CUTSCENE_ACTIVE();

		if ((!g.self.auto_tp || temp_disable_tp) && bLastAutoTP)
		{
			MISC::USING_MISSION_CREATOR(false);
			MISC::ALLOW_MISSION_CREATOR_WARP(false);
		}

		if (g.self.auto_tp && !temp_disable_tp)
		{
			MISC::USING_MISSION_CREATOR(true);
			MISC::ALLOW_MISSION_CREATOR_WARP(true);
		}

		bLastAutoTP = g.self.auto_tp;
	}
}