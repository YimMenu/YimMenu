#include "backend/looped/looped.hpp"
#include "natives.hpp"

namespace big
{
	void looped::self_clean_player()
	{
		auto const player_ped = PLAYER::PLAYER_PED_ID();

		if (g->self.clean_player) {
			PED::CLEAR_PED_BLOOD_DAMAGE(player_ped);
			PED::CLEAR_PED_WETNESS(player_ped);
			PED::CLEAR_PED_ENV_DIRT(player_ped);
			PED::RESET_PED_VISIBLE_DAMAGE(player_ped);
		}

	}
}