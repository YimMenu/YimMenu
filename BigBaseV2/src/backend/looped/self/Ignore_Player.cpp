#include "backend/looped/looped.hpp"
#include "natives.hpp"
#include "services/players/player_service.hpp"

namespace big
{
	void looped::self_ignoreplayer() {
		if (g->self.ignoreplayer) {
			PLAYER::SET_EVERYONE_IGNORE_PLAYER(self::id, 1);
		}
		else
			PLAYER::SET_EVERYONE_IGNORE_PLAYER(self::id, 0);
	}
}