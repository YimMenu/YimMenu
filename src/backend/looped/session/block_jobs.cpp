#include "backend/looped/looped.hpp"
#include "core/scr_globals.hpp"
#include "gta_util.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "script_local.hpp"

namespace big
{
	static bool bLastBlockJobsEnabled = false;

	void looped::session_block_jobs()
	{
		bool used = g.session.block_jobs && *g_pointers->m_gta.m_is_session_started;
		if (!bLastBlockJobsEnabled && used)
		{
			if (!STREAMING::IS_PLAYER_SWITCH_IN_PROGRESS() && SCRIPT::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH("maintransition"_J) == 0 && NETWORK::NETWORK_GET_HOST_OF_SCRIPT("fmmc_launcher", -1, 0) == self::id)
			{
				auto fmmc = gta_util::find_script_thread("fmmc_launcher"_J);
				*script_local(fmmc->m_stack, scr_locals::fmmc_launcher::broadcast_idx).at(47).at(7).as<int*>() = (-1 & ~(1 << self::id));
				bLastBlockJobsEnabled                                                                          = true;
			}
		}
		else if (bLastBlockJobsEnabled && !used)
		{
			if (*g_pointers->m_gta.m_is_session_started && !STREAMING::IS_PLAYER_SWITCH_IN_PROGRESS() && gta_util::find_script_thread("fmmc_launcher"_J))
			{
				auto fmmc = gta_util::find_script_thread("fmmc_launcher"_J);
				*script_local(fmmc->m_stack, scr_locals::fmmc_launcher::broadcast_idx).at(47).at(7).as<int*>() = 0;
			}

			bLastBlockJobsEnabled = false;
		}
	}
}
