#include "backend/looped/looped.hpp"
#include "natives.hpp"
#include "util/entity.hpp"

namespace big
{
	void looped::tunables_clean_player()
	{
		if (g->tunables.clean_player) {
			entity::clean_ped(self::ped);
		}
	}
}