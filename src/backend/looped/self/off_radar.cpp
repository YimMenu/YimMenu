#include "backend/looped_command.hpp"
#include "backend/bool_command.hpp"
#include "core/scr_globals.hpp"
#include "natives.hpp"

#include <script/globals/GlobalPlayerBD.hpp>

namespace big
{
	class off_radar : looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override
		{
			if (g.self.ghost_org)
				MISC::SET_BIT(script_global(2794162).at(4667).as<int*>(), 2);
			*scr_globals::globalplayer_bd.at(PLAYER::PLAYER_ID(), 463).at(210).as<bool*>() = true;
			*script_global(2672505).at(57).as<int*>() = NETWORK::GET_NETWORK_TIME() + 1;
		}

		virtual void on_disable() override
		{
			if (!g.self.ghost_org)
				MISC::CLEAR_BIT(script_global(2794162).at(4667).as<int*>(), 2);
			*scr_globals::globalplayer_bd.at(PLAYER::PLAYER_ID(), 463).at(210).as<bool*>() = false;
		}
	};

	off_radar g_off_radar("otr", "OFF_RADAR", "OFF_RADAR_DESC", g.self.off_radar);
	bool_command ghost_org("ghostorg", "Ghost Org", "Ghost Organization for free.", g.self.ghost_org);
}
