#include "backend/bool_command.hpp"
#include "backend/looped_command.hpp"
#include "core/scr_globals.hpp"
#include "core/settings.hpp"
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
				MISC::SET_BIT(scr_globals::freemode_global.at(4667).as<int*>(), 2);
			scr_globals::globalplayer_bd.as<GlobalPlayerBD*>()->Entries[self::id].OffRadarActive = true;
			*scr_globals::freemode_properties.at(57).as<int*>() = NETWORK::GET_NETWORK_TIME() + 1;
		}

		virtual void on_disable() override
		{
			if (!g.self.ghost_org)
				MISC::CLEAR_BIT(scr_globals::freemode_global.at(4667).as<int*>(), 2);
			scr_globals::globalplayer_bd.as<GlobalPlayerBD*>()->Entries[self::id].OffRadarActive = false;
		}
	};

	off_radar g_off_radar("otr", "Off Radar", "Hides your blip from other players", g.self.off_radar);
	bool_command ghost_org("ghostorg", "Ghost Org", "Use Ghost Organization instead of standard off radar.", g.self.ghost_org);
}
