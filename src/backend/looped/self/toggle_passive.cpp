#include "backend/looped_command.hpp"
#include "core/scr_globals.hpp"
#include "natives.hpp"
#include "script_global.hpp"
#include "script/globals/GPBD_FM_3.hpp"
#include "gta_util.hpp"
#include "services/tunables/tunables_service.hpp"

namespace big
{
	class toggle_passive : looped_command
	{
		using looped_command::looped_command;


		virtual void on_tick() override
		{
			if (scr_globals::gpbd_fm_3.as<GPBD_FM_3*>()->Entries[self::id].BossGoon.Boss != -1 || gta_util::find_script_thread("fm_mission_controller"_J) || gta_util::find_script_thread("fm_mission_controller_2020"_J)) [[unlikely]]
			{
				on_disable();
				g.self.passive = false;
				g_notification_service.push_warning("PASSIVE"_T.data(), "BACKEND_LOOPED_SELF_TOGGLE_PASSIVE_DISABLED_PASSIVE_MODE_MESSAGE"_T.data());
				return;
			}
			*g_tunables_service->get_tunable<int*>("VC_PASSIVE_TIME_AFTER_DISABLE"_J) = 0; // End Passive Time = 0s
			*scr_globals::passive.as<PBOOL>() = TRUE;
		}

		virtual void on_disable() override
		{
			*scr_globals::passive.as<PBOOL>() = FALSE;
			NETWORK::SET_LOCAL_PLAYER_AS_GHOST(false, false);
			*g_tunables_service->get_tunable<int*>("VC_PASSIVE_TIME_AFTER_DISABLE"_J) = 30000;
			PED::SET_PED_CONFIG_FLAG(self::ped, 342, false); // Disable NotAllowedToJackAnyPlayers
			PED::SET_PED_CONFIG_FLAG(self::ped, 122, false); // Disable DisableMelee
			PLAYER::SET_PLAYER_VEHICLE_DEFENSE_MODIFIER(self::ped, 1.f);
			PED::SET_PED_CAN_BE_DRAGGED_OUT(self::ped, true);
		}
	};

	toggle_passive g_toggle_passive("passive", "PASSIVE", "PASSIVE_DESC", g.self.passive);
}
