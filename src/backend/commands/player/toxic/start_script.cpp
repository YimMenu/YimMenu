#include "backend/player_command.hpp"
#include "util/scripts.hpp"

namespace big
{
	template<rage::joaat_t script_hash>
	class start_script : player_command
	{
		using player_command::player_command;

		virtual CommandAccessLevel get_access_level() override
		{
			return CommandAccessLevel::AGGRESSIVE;
		}

		virtual void execute(player_ptr player, const command_arguments& _args, const std::shared_ptr<command_context> ctx) override
		{
			scripts::force_script_on_player(player, script_hash);
		}
	};

	start_script<"fm_intro"_J> g_start_tutorial("tutorial", "BACKEND_START_SCRIPT_START_TUTORIAL", "BACKEND_START_SCRIPT_START_TUTORIAL_DESC", 0);
	start_script<"golf_mp"_J> g_start_golf("golf", "BACKEND_START_SCRIPT_START_GOLF", "BACKEND_START_SCRIPT_START_GOLF_DESC", 0);
	start_script<"Pilot_School_MP"_J> g_start_flight_school("flightschool", "BACKEND_START_SCRIPT_START_FLIGHT_SCHOOL", "BACKEND_START_SCRIPT_START_FLIGHT_SCHOOL_DESC", 0);
	start_script<"AM_Darts"_J> g_start_darts("darts", "BACKEND_START_SCRIPT_START_DARTS", "BACKEND_START_SCRIPT_START_DARTS_DESC", 0);
	start_script<"gunslinger_arcade"_J> g_start_badlands("badlands", "BACKEND_START_SCRIPT_START_BADLANDS_REVENGE_II", "BACKEND_START_SCRIPT_START_BADLANDS_REVENGE_II_DESC", 0);
	start_script<"ggsm_arcade"_J> g_start_space_monkey("spacemonkey", "BACKEND_START_SCRIPT_START_SPACE_MONKEY", "BACKEND_START_SCRIPT_START_SPACE_MONKEY_DESC", 0);
	start_script<"wizard_arcade"_J> g_start_wizards_ruin("wizard", "BACKEND_START_SCRIPT_START_WIZARD", "BACKEND_START_SCRIPT_START_WIZARD_DESC", 0);
	start_script<"puzzle"_J> g_start_qub3d("qub3d", "BACKEND_START_SCRIPT_START_QUB3D", "BACKEND_START_SCRIPT_START_QUB3D_DESC", 0);
	start_script<"camhedz_arcade"_J> g_start_camhedz("camhedz", "BACKEND_START_SCRIPT_START_CAMHEDZ", "BACKEND_START_SCRIPT_START_CAMHEDZ_DESC", 0);
}