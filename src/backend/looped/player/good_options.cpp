#include "backend/looped/looped.hpp"
#include "gta/pickup_rewards.hpp"
#include "services/players/player_service.hpp"
#include "util/globals.hpp"
#include "util/misc.hpp"

namespace big
{
	// rate limit script events to prevent crashes
	static int offRadarPlayer    = 0;
	static int neverWantedPlayer = 0;
	void looped::player_good_options()
	{
		if (!*g_pointers->m_is_session_started)
			return;

		offRadarPlayer++;
		if (offRadarPlayer > 32)
			offRadarPlayer = 0;

		neverWantedPlayer++;
		if (neverWantedPlayer > 32)
			neverWantedPlayer = 0;

		g_player_service->iterate([](const player_entry& entry) {
			if ((g.session.off_radar_all || entry.second->off_radar) && offRadarPlayer == entry.second->id())
				globals::give_remote_otr(entry.second->id());
		});

		g_player_service->iterate([](const player_entry& entry) {
			if ((g.session.never_wanted_all || entry.second->never_wanted)
			    && PLAYER::GET_PLAYER_WANTED_LEVEL(entry.second->id()) > 0 && neverWantedPlayer == entry.second->id())
				globals::clear_wanted_player(entry.second->id());
		});

		if (g.session.semi_godmode_all)
		{
			g_pointers->m_give_pickup_rewards(-1, REWARD_HEALTH);
			g_pointers->m_give_pickup_rewards(-1, REWARD_ARMOUR);
		}
		else
		{
			g_player_service->iterate([](const player_entry& entry) {
				if (entry.second->semi_godmode)
				{
					if (CPed* ped = entry.second->get_ped())
					{
						if (ped->m_maxhealth == 0 || ped->m_health == 0 || misc::has_bit_set((int*)&ped->m_damage_bits, 8))
							return;

						if (ped->m_health < ped->m_maxhealth)
						{
							g_pointers->m_give_pickup_rewards(1 << entry.second->id(), REWARD_HEALTH);
						}

						if (ped->m_armor < 50.0f)
						{
							g_pointers->m_give_pickup_rewards(1 << entry.second->id(), REWARD_ARMOUR);
						}
					}
				}
			});
		}
	}
}
