#include "backend/looped/looped.hpp"
#include "script_global.hpp"
#include "natives.hpp"

namespace big
{
	void looped::tunables_phone_anim()
	{
		int view = CAM::GET_FOLLOW_PED_CAM_VIEW_MODE();
		if (g->tunables.phone_anim)
		{
			if (view != 4)
			{
				PED::SET_PED_CONFIG_FLAG(self::ped, 244, false);
				PED::SET_PED_CONFIG_FLAG(self::ped, 243, false);
				PED::SET_PED_CONFIG_FLAG(self::ped, 242, false);
			}
		}
		else 
		{
			PED::SET_PED_CONFIG_FLAG(self::ped, 244, true);
			PED::SET_PED_CONFIG_FLAG(self::ped, 243, true);
			PED::SET_PED_CONFIG_FLAG(self::ped, 242, true);
		}
	}
}

//false-> open
//true-> close
