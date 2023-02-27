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

		virtual CommandAccessLevel get_access_level()
		{
			return CommandAccessLevel::AGGRESSIVE;
		}

		virtual void execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx)
		{
			const size_t arg_count  = 25;
			int64_t args[arg_count] = {(int64_t)eRemoteEvent::StartScriptBegin, (int64_t)self::id};

			args[2] = scriptId;
			strcpy((char*)&args[2 + 3], "0");
			args[2 + 16] = -1;
			args[2 + 17] = 1337;
			args[2 + 19] = arg19;
			args[24] = scr_globals::gpbd_fm_3.as<GPBD_FM_3*>()->Entries[player->id()].ScriptEventReplayProtectionCounter;

			g_pointers->m_trigger_script_event(1, args, arg_count, 1 << player->id());

			for (int i = 0; i < 2; i++)
			{
				const size_t arg_count_2    = 25;
				int64_t args_2[arg_count_2] = {(int64_t)eRemoteEvent::StartScriptProceed, (int64_t)self::id};
				args_2[2 + 17]              = 1337;
				g_pointers->m_trigger_script_event(1, args_2, arg_count_2, 1 << player->id());

				script::get_current()->yield(20ms);
			}
		}
	};

	start_script<20> g_start_tutorial("tutorial", "Start Tutorial", "Plays that unskippable cutscene used in the tutorial", 0);
	start_script<193> g_start_golf("golf", "Start Golf", "Starts golf", 0);
	start_script<196> g_start_flight_school("flightschool", "Start Flight School", "Teleports player to the airport and starts flight school", 0);
	start_script<192> g_start_darts("darts", "Start Darts", "Starts darts in a Sandy Shores bar", 0);
	start_script<211> g_start_badlands("badlands", "Start Badlands Revenge II", "Starts the arcade game Badlands Revenge II in fullscreen", 0);
	start_script<216> g_start_space_monkey("spacemonkey", "Start Space Monkey 3", "Starts the arcade game Space Monkey 3 in fullscreen", 0);
	start_script<216> g_start_wizards_ruin("wizard", "Start The Wizard's Ruin", "Starts the arcade game The Wizard's Ruin in fullscreen", 0);
	start_script<217> g_start_qub3d("qub3d", "Start Qub3D", "Starts the arcade game Qub3D in fullscreen", 0);
	start_script<218> g_start_camhedz("camhedz", "Start Camhedz", "Starts the arcade game Camhedz in fullscreen", 0);
}