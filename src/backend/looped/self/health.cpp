#include "health.hpp"

#include "gta/enums.hpp"
#include "natives.hpp"

namespace big
{
	void health_regen_looped::on_tick()
	{
		PLAYER::SET_PLAYER_HEALTH_RECHARGE_MULTIPLIER(self::ped, g.self.healthregenrate);
		PLAYER::SET_PLAYER_HEALTH_RECHARGE_MAX_PERCENT(self::ped, 99999.0f);
	}

	void health_regen_looped::on_disable()
	{
		PLAYER::SET_PLAYER_HEALTH_RECHARGE_MULTIPLIER(self::ped, 1.0f);
		PLAYER::SET_PLAYER_HEALTH_RECHARGE_MAX_PERCENT(self::ped, 1.0f);
	}
}
