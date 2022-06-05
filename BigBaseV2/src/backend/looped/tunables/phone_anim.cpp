#include "backend/looped/looped.hpp"
#include "script_global.hpp"
#include "natives.hpp"

namespace big
{
	void looped::phone_anim()
	{
		if(g->tunables.phone_anim)
		{
			if (!PED::GET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), 244, false))
			{
				PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), 244, false);
				PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), 243, false);
				PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), 242, false);
			}
		}
	}
}