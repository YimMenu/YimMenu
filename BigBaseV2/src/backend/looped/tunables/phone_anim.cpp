#include "backend/looped/looped.hpp"
#include "script_global.hpp"
#include "natives.hpp"

namespace big
{
	void looped::tunables_disable_phone()
	{
		if(g->tunables.phone_anim)
		{
			/*PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), 244, false);
			PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), 243, false);
			PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), 242, false);

			TASK::TASK_USE_MOBILE_PHONE(PLAYER::PLAYER_PED_ID(), 1, 1);*/
		}
	}
}