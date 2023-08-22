#include "backend/looped_command.hpp"
#include "services/tunables/tunables_service.hpp"
#include "core/scr_globals.hpp"
#include "natives.hpp"

namespace big
{
	class no_idle_kick : looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override
		{
			*scr_globals::session_info.at(1155).as<PINT>() = -1;
			*scr_globals::session_info.at(1171).as<PINT>() = -1;
			CAM::INVALIDATE_IDLE_CAM();
			CAM::INVALIDATE_CINEMATIC_VEHICLE_IDLE_MODE();
		}
	};

	no_idle_kick g_no_idle_kick("noidlekick", "NO_IDLE_KICK", "Prevents you from being kicked while idling.", g.tunables.no_idle_kick);
}
