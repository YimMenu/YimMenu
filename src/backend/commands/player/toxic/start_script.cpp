#include "backend/player_command.hpp"
#include "core/scr_globals.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "script.hpp"

#include <script/globals/GPBD_FM_3.hpp>

namespace big
{
	template<int scriptId, int arg19 = 0>
	class start_script : player_command
	{
		using player_command::player_command;

		virtual CommandAccessLevel get_access_level() override
		{
			return CommandAccessLevel::AGGRESSIVE;
		}

		virtual void execute(player_ptr player, const command_arguments& _args, const std::shared_ptr<command_context> ctx) override
		{
			const size_t arg_count  = 27;
			int64_t args[arg_count] = {(int64_t)eRemoteEvent::StartScriptBegin, (int64_t)self::id, 1 << player->id()};

			args[3] = scriptId;
			strcpy((char*)&args[2 + 3], "0");
			args[3 + 16] = -1;
			args[3 + 17] = 1337;
			args[3 + 19] = arg19;
			args[25] = scr_globals::gpbd_fm_3.as<GPBD_FM_3*>()->Entries[player->id()].ScriptEventReplayProtectionCounter;

			g_pointers->m_gta.m_trigger_script_event(1, args, arg_count, 1 << player->id(), (int)eRemoteEvent::StartScriptBegin);

			for (int i = 0; i < 2; i++)
			{
				const size_t arg_count_2    = 27;
				int64_t args_2[arg_count_2] = {(int64_t)eRemoteEvent::StartScriptProceed, (int64_t)self::id, 1 << player->id()};
				args_2[3 + 17]              = 1337;
				g_pointers->m_gta.m_trigger_script_event(1, args_2, arg_count_2, 1 << player->id(), (int)eRemoteEvent::StartScriptProceed);

				script::get_current()->yield(20ms);
			}
		}
	};

	start_script<20> g_start_tutorial("tutorial", "BACKEND_START_SCRIPT_START_TUTORIAL", "BACKEND_START_SCRIPT_START_TUTORIAL_DESC", 0);
	start_script<200> g_start_golf("golf", "BACKEND_START_SCRIPT_START_GOLF", "BACKEND_START_SCRIPT_START_GOLF_DESC", 0);
	start_script<203> g_start_flight_school("flightschool", "BACKEND_START_SCRIPT_START_FLIGHT_SCHOOL", "BACKEND_START_SCRIPT_START_FLIGHT_SCHOOL_DESC", 0);
	start_script<9> g_start_darts("darts", "BACKEND_START_SCRIPT_START_DARTS", "BACKEND_START_SCRIPT_START_DARTS_DESC", 0);
	start_script<218> g_start_badlands("badlands", "BACKEND_START_SCRIPT_START_BADLANDS_REVENGE_II", "BACKEND_START_SCRIPT_START_BADLANDS_REVENGE_II_DESC", 0);
	start_script<223> g_start_space_monkey("spacemonkey", "BACKEND_START_SCRIPT_START_SPACE_MONKEY", "BACKEND_START_SCRIPT_START_SPACE_MONKEY_DESC", 0);
	start_script<219> g_start_wizards_ruin("wizard", "BACKEND_START_SCRIPT_START_WIZARD", "BACKEND_START_SCRIPT_START_WIZARD_DESC", 0);
	start_script<224> g_start_qub3d("qub3d", "BACKEND_START_SCRIPT_START_QUB3D", "BACKEND_START_SCRIPT_START_QUB3D_DESC", 0);
	start_script<225> g_start_camhedz("camhedz", "BACKEND_START_SCRIPT_START_CAMHEDZ", "BACKEND_START_SCRIPT_START_CAMHEDZ_DESC", 0);
}