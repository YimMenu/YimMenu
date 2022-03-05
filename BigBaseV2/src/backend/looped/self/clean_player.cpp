#include "backend/looped/looped.hpp"
#include "natives.hpp"
#include "util/entity.hpp"

namespace big
{
	void looped::self_clean_player()
	{
		if (g->self.clean_player) {
			entity::clean_ped(PLAYER::PLAYER_PED_ID());
		}
	}
}