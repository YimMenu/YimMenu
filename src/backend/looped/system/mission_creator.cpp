#include "backend/looped/looped.hpp"
#include "core/scr_globals.hpp"
#include "fiber_pool.hpp"
#include "gta_util.hpp"
#include "natives.hpp"
#include "script.hpp"

namespace big
{
	bool bLastMissionCreator = false;
	void looped::system_mission_creator()
	{
		if (g.m_mission_creator_thread)
		{
			*scr_globals::terminate_creator.as<bool*>() = false;

			if (SCRIPT::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH("maintransition"_J) > 0)
			{
				if (g.m_mission_creator_thread)
					g.m_mission_creator_thread->kill();
				g.m_mission_creator_thread = nullptr;
				return;
			}

			bLastMissionCreator = true;
		}
		else if (bLastMissionCreator)
		{
			*scr_globals::switch_struct.at(18).as<int*>() = 0;
			STREAMING::SWITCH_TO_MULTI_SECONDPART(self::ped);
			HUD::DISPLAY_HUD(true);
			HUD::DISPLAY_RADAR(true);
			PLAYER::SET_PLAYER_CONTROL(self::id, true, 0);
			ENTITY::FREEZE_ENTITY_POSITION(self::ped, false);
			ENTITY::SET_ENTITY_COLLISION(self::ped, true, true);
			bLastMissionCreator = false;
		}
	}
}
