#include "backend/looped/looped.hpp"
#include "gta/enums.hpp"
#include "gta/joaat.hpp"
#include "natives.hpp"
#include "util/entity.hpp"

namespace big
{
	void looped::vehicle_chaff()
	{
		if (!g->vehicle.chaff) return;

		if (PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_SCRIPTED_FLY_ZDOWN) && self::veh)
		{
			STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_sm_counter");
			if (STREAMING::HAS_NAMED_PTFX_ASSET_LOADED("scr_sm_counter"))
			{
				AUDIO::PLAY_SOUND_FROM_ENTITY(-1, "chaff_released", self::veh, "DLC_SM_Countermeasures_Sounds", true, 0);
				GRAPHICS::USE_PARTICLE_FX_ASSET("scr_sm_counter");
				GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_AT_COORD("scr_sm_counter_chaff", self::pos.x, self::pos.y, self::pos.z, 0, 0, 0, 2, false, false, false, false);
				if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(self::veh))
				{
					VEHICLE::SET_VEHICLE_ALLOW_HOMING_MISSLE_LOCKON_SYNCED(self::veh, false, true);
				}
			}
		}
	}
}