//#include "backend/looped/looped.hpp"
#include "backend/looped_command.hpp"
#include "core/enums.hpp"
#include "core/scr_globals.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "script.hpp"
#include "script_global.hpp"

namespace big
{
	class seamless_join : looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override
		{
			if (g.tunables.seamless_join)
			{
				const auto state = *scr_globals::transition_state.as<eTransitionState*>();

				if (state <= eTransitionState::TRANSITION_STATE_FM_FINAL_SETUP_PLAYER)
				{
					PLAYER::SET_PLAYER_CONTROL(self::id, true, 0);
					if (STREAMING::IS_PLAYER_SWITCH_IN_PROGRESS())
					{
						STREAMING::STOP_PLAYER_SWITCH();
						GRAPHICS::ANIMPOSTFX_STOP_ALL(); // fix Skycam effect
					}
				}
			}
		}
	};

	seamless_join g_seamless_join("seamjoin", "SEAMLESS_JOIN", "SEAMLESS_JOIN_DESC", g.tunables.seamless_join);
}
