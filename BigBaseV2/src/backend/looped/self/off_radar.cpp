#include "backend/looped/looped.hpp"
#include "pointers.hpp"
#include "natives.hpp"
#include "script_global.hpp"

namespace big
{
	void looped::self_off_radar()
	{
		if (g.self.off_radar)
		{
			/*Player playerId = PLAYER::PLAYER_ID();
			
			int off_radar[] = {
				(int)RemoteEvent::RemoteOffradar,
				playerId,
				NETWORK::GET_NETWORK_TIME(),
				0,
				0,
				0,
				*script_global(1630816).at(playerId, 597).at(508).as<int*>()
			};

			g_pointers->m_trigger_script_event(1, off_radar, 7, 1 << playerId);*/
			//SCRIPT::TRIGGER_SCRIPT_EVENT(1, off_radar, 7, 1 << playerId);

			*script_global(2426865).at(PLAYER::PLAYER_ID(), 449).at(209).as<bool*>() = true;
			*script_global(2441237).at(70).as<int*>() = NETWORK::GET_NETWORK_TIME() + 1;
		}
	}
}