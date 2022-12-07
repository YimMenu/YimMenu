#include "views/view.hpp"
#include "util/teleport.hpp"
#include "util/toxic.hpp"
#include "util/kick.hpp"
#include "util/ped.hpp"
#include "util/vehicle.hpp"

namespace big
{
	void view::view_player_kicks_and_crashes()
	{
		std::string title = std::format("Player Kick and Crash Options: {}", g_player_service->get_selected()->get_name());
		ImGui::Text(title.c_str());

		if (ImGui::TreeNode("Kicks")) 
		{
			components::button("Desync", [] { kick::desync_kick(g_player_service->get_selected()); });
			ImGui::SameLine(); components::help_marker("Removes this player from your player manager.\nWill kick them if you are a host.\nOtherwise will just remove them localy.\nUntested.");

			components::button("Breakup Kick", [] { kick::breakup_kick(g_player_service->get_selected()); });
			ImGui::SameLine(); components::help_marker("Removes this player from everyones player manager. \nCan be detected by anyone in session. \nUnblockable.");

			components::button("Lost Connection Kick", [] { kick::lost_connection_kick(g_player_service->get_selected()); });

			components::button("Bail Kick", [] { kick::bail_kick(g_player_service->get_selected()); });

			components::button("Null Function Kick", [] { kick::null_function_kick(g_player_service->get_selected()); });

			components::button("OOM Kick", [] { kick::oom_kick(g_player_service->get_selected()); });

			components::button("Script Host Kick", [] { kick::kick_player_script_host(g_player_service->get_selected()); });

			components::button("End Session Kick", [] { kick::end_session_kick(g_player_service->get_selected()); });
			ImGui::SameLine(); components::help_marker("The kick can take around 10 seconds to work");

			components::button("Host Kick", [] { kick::host_kick(g_player_service->get_selected()); });
			ImGui::SameLine(); components::help_marker("Removes this player hosts player manager and adds them to session blacklist. \nBlacklist can be bypassed by RID spoofing. \nBlockable by some menus.");

			components::button("Complaint Kick", [] { kick::complaint_kick(g_player_service->get_selected()); });
			ImGui::SameLine(); components::help_marker("The kick can take around 10 seconds to work");
		}

		if (ImGui::TreeNode("Crashes (shit)")) 
		{
			components::button("Ped Crash", [] {
				Ped ped = ped::spawn(ePedType::PED_TYPE_PROSTITUTE, rage::joaat("slod_human"), 0, misc::fvector3_to_Vector3(*g_player_service->get_selected()->get_ped()->get_position()), 0);
				script::get_current()->yield(3s);
				entity::delete_entity_notp(ped);
			});
			ImGui::SameLine(); components::help_marker("Spawns 'slod_human' ped near player wich crashes them. \nBlocked by most internal menus.\nUntested.");

			components::button("Vehicle Crash", [] {
				Vehicle veh = vehicle::spawn(rage::joaat("arbitergt"), misc::fvector3_to_Vector3(*g_player_service->get_selected()->get_ped()->get_position()), 0.f);
				script::get_current()->yield(3s);
				entity::delete_entity_notp(veh);
			});
			ImGui::SameLine(); components::help_marker("Spawns next_gen vehicle: 'arbitergt' near player wich crashes them. \nBlocked by most internal menus.\nUntested.");
			ImGui::SameLine();

			components::button("TSE Crash", [] {
				toxic::tse_crash(g_player_service->get_selected());
			});
			ImGui::SameLine(); components::help_marker("Sends crash script events to the player. \nBlocked by most internal menus.");
			ImGui::TreePop();
		}
	}
}