#include "backend/looped_command.hpp"
#include "natives.hpp"

namespace big
{

	class health_regen_looped : looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override
		{
			PLAYER::SET_PLAYER_HEALTH_RECHARGE_MULTIPLIER(self::ped, g.self.healthregenrate);
			PLAYER::SET_PLAYER_HEALTH_RECHARGE_MAX_PERCENT(self::ped, 99999.0f);
		};
		virtual void on_disable() override
		{
			PLAYER::SET_PLAYER_HEALTH_RECHARGE_MULTIPLIER(self::ped, 1.0f);
			PLAYER::SET_PLAYER_HEALTH_RECHARGE_MAX_PERCENT(self::ped, 1.0f);
		}
	};

	health_regen_looped g_health_regen_looped("healthregen", "HEALTH_REGEN", "HEALTH_REGEN_DESC", g.self.healthregen);
}