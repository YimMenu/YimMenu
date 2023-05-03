#include "off_radar.hpp"

#include "core/scr_globals.hpp"
#include "natives.hpp"

namespace big
{
	void off_radar::on_tick()
	{
		*scr_globals::globalplayer_bd.at(PLAYER::GET_PLAYER_INDEX(), scr_globals::size::globalplayer_bd).at(210).as<int*>() = true;
		*script_global(2672505).at(57).as<int*>() = NETWORK::GET_NETWORK_TIME() + 1;
	}

	void off_radar::on_disable()
	{
		*scr_globals::globalplayer_bd.at(PLAYER::GET_PLAYER_INDEX(), scr_globals::size::globalplayer_bd).at(210).as<int*>() = false;
	}
}
