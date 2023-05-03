#include "backend/commands/player/toxic/kick_from_vehicle.hpp"
#include "backend/commands/player/troll/boost_vehicle.hpp"
#include "backend/commands/player/troll/burst_tyres.hpp"
#include "backend/commands/player/troll/close_doors.hpp"
#include "backend/commands/player/troll/downgrade_vehicle.hpp"
#include "backend/commands/player/troll/flip_180.hpp"
#include "backend/commands/player/troll/flying_vehicle.hpp"
#include "backend/commands/player/troll/kill_engine.hpp"
#include "backend/commands/player/troll/lock_doors.hpp"
#include "backend/commands/player/troll/open_doors.hpp"
#include "backend/commands/player/troll/remote_control_vehicle.hpp"
#include "backend/commands/player/troll/smash_windows.hpp"
#include "backend/commands/player/troll/stop_vehicle.hpp"
#include "backend/commands/player/troll/unlock_doors.hpp"
#include "backend/commands/player/troll/upgrade_vehicle.hpp"
#include "backend/commands/player/troll/window_tint.hpp"
#include "views/view.hpp"

namespace big
{
	void view::player_vehicle()
	{
		if (ImGui::TreeNode("Vehicle"))
		{
			const auto target = g_player_service->get_selected();

			components::player_command_button(&cmd::g_kick_from_vehicle, target, {});
			ImGui::SameLine();
			components::player_command_button(&cmd::g_flying_vehicle, target, {});

			components::player_command_button(&cmd::g_boost_vehicle, target, {});
			ImGui::SameLine();
			components::player_command_button(&cmd::g_stop_vehicle, target, {});

			components::player_command_button(&cmd::g_flip_180, target, {});
			ImGui::SameLine();
			components::player_command_button(&cmd::g_remote_control_vehicle, target, {});

			components::player_command_button(&cmd::g_kill_engine, target, {});
			ImGui::SameLine();
			components::player_command_button(&cmd::g_burst_tyres, target, {});

			components::player_command_button(&cmd::g_smash_windows, target, {});
			ImGui::SameLine();
			components::player_command_button(&cmd::g_black_tint, target, {});

			components::player_command_button(&cmd::g_lock_vehicle, target, {});
			ImGui::SameLine();
			components::player_command_button(&cmd::g_unlock_vehicle, target, {});

			components::player_command_button(&cmd::g_open_doors, target, {});
			ImGui::SameLine();
			components::player_command_button(&cmd::g_close_doors, target, {});

			components::player_command_button(&cmd::g_upgrade_vehicle, target, {});
			ImGui::SameLine();
			components::player_command_button(&cmd::g_downgrade_vehicle, target, {});

			ImGui::TreePop();
		}
	}
}
