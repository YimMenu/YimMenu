#include "clean_player.hpp"

#include "natives.hpp"
#include "util/entity.hpp"

namespace big
{
	void clean_player_looped::on_tick()
	{
		entity::clean_ped(self::ped);
	}
}
