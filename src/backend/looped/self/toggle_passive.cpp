#include "backend/looped_command.hpp"
#include "core/scr_globals.hpp"
#include "natives.hpp"
#include "script_global.hpp"
#include "script/globals/GPBD_FM_3.hpp"
#include "gta_util.hpp"

namespace big
{
	class toggle_passive : looped_command
	{
		using looped_command::looped_command;


		virtual void on_tick() override
		{
			if (scr_globals::gpbd_fm_3.as<GPBD_FM_3*>()->Entries[self::id].BossGoon.Boss != -1 || gta_util::find_script_thread(RAGE_JOAAT("fm_mission_controller")) || gta_util::find_script_thread(RAGE_JOAAT("fm_mission_controller_2020")))
			{
				on_disable();
				g.self.passive = false;
				g_notification_service->push_warning("Disabled passive mode", "Disabled passive mode because you started mission / joined CEO/MC");
				return;
			}
			*scr_globals::tuneables.at(27371).as<int*>() = 0; // End Passive Time = 0s
			*script_global(1574582).as<bool*>() = true;
		}

		virtual void on_disable() override
		{
			*script_global(1574582).as<bool*>() = false;
			NETWORK::SET_LOCAL_PLAYER_AS_GHOST(false, false);
			*scr_globals::tuneables.at(27371).as<int*>() = 30000;
			PED::SET_PED_CONFIG_FLAG(self::ped, 342, false); // Disable NotAllowedToJackAnyPlayers
			PED::SET_PED_CONFIG_FLAG(self::ped, 122, false); // Disable DisableMelee
			PLAYER::SET_PLAYER_VEHICLE_DEFENSE_MODIFIER(self::ped, 1.f);
			PED::SET_PED_CAN_BE_DRAGGED_OUT(self::ped, true);
		}
	};

	toggle_passive g_toggle_passive("passive", "PASSIVE", "PASSIVE_DESC", g.self.passive);
}