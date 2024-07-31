#include "backend/looped/looped.hpp"
#include "core/scr_globals.hpp"
#include "gta_util.hpp"
#include "natives.hpp"
#include "util/math.hpp"

#include <network/CCommunications.hpp>
#include <network/Network.hpp>
#include <script/globals/GPBD_FM.hpp>
#include <script/globals/GlobalPlayerBD.hpp>

namespace big
{
	static bool bLastForceHost = false;
	void looped::system_spoofing()
	{
		if (*g_pointers->m_gta.m_is_session_started)
		{
			gta_util::execute_as_script("freemode"_J, [] {
				if (NETWORK::NETWORK_GET_THIS_SCRIPT_IS_NETWORK_SCRIPT() && NETWORK::NETWORK_GET_SCRIPT_STATUS() == 2)
				{
					if (g.spoofing.spoof_rank)
						scr_globals::gpbd_fm_1.as<GPBD_FM*>()->Entries[self::id].PlayerStats.Rank = g.spoofing.rank;

					if (g.spoofing.spoof_job_points)
						scr_globals::gpbd_fm_1.as<GPBD_FM*>()->Entries[self::id].JobPoints = g.spoofing.job_points;

					if (g.spoofing.spoof_kd_ratio)
						scr_globals::gpbd_fm_1.as<GPBD_FM*>()->Entries[self::id].PlayerStats.KdRatio = g.spoofing.kd_ratio;

					if (g.spoofing.spoof_blip)
					{
						if (g.spoofing.blip_type == 0)// random
							scr_globals::globalplayer_bd.as<GlobalPlayerBD*>()->Entries[self::id].PlayerBlip.PlayerVehicleBlipType = (eBlipType)(rand() % 90);
						else
							scr_globals::globalplayer_bd.as<GlobalPlayerBD*>()->Entries[self::id].PlayerBlip.PlayerVehicleBlipType =
							    (eBlipType)(g.spoofing.blip_type - 1);
					}
				}
			});
		}
	}
}
