#include "backend/looped/looped.hpp"
#include "natives.hpp"
#include "services/players/player_service.hpp"

namespace big
{
	void looped::tunables_ignoreplayer() {
		if (g->tunables.ignoreplayer) {
			PLAYER::SET_EVERYONE_IGNORE_PLAYER(self::id, 1);
		}
		else
			PLAYER::SET_EVERYONE_IGNORE_PLAYER(self::id, 0);
	}
}