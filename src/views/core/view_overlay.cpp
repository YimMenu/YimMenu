#include "views/view.hpp"
#include "pointers.hpp"
#include "gta_util.hpp"
#include "gui.hpp"

namespace big
{
	void view::overlay()
	{
		if (!g.window.ingame_overlay.opened || (g_gui->is_open() && !g.window.ingame_overlay.show_with_menu_opened))
            return;

		ImGui::SetNextWindowPos(ImVec2(10.0f, 10.0f), ImGuiCond_FirstUseEver, ImVec2(0.0f, 0.0f));
		ImGui::SetNextWindowBgAlpha(0.5f);

		if (ImGui::Begin("overlay", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav))
		{
			ImGui::Text("YimMenu");

			ImGui::Separator();

			if (g.window.ingame_overlay.show_fps)
				ImGui::Text("%.0f FPS", ImGui::GetIO().Framerate / 2);

			if (CNetworkPlayerMgr *network_player_mgr = gta_util::get_network_player_mgr(); g.window.ingame_overlay.show_players)
				ImGui::Text(std::format("Players: {}/{}", network_player_mgr->m_player_count, network_player_mgr->m_player_limit).c_str());

			//if (g.window.ingame_overlay.show_time)
			//	ImGui::Text(std::format("Time: {:%d-%m-%Y %H:%M:%OS}", std::chrono::current_zone()->to_local(std::chrono::system_clock::now())).c_str());

			if (auto replay_interface = *g_pointers->m_replay_interface; g.window.ingame_overlay.show_replay_interface)
			{
				ImGui::Separator();

				if(replay_interface->m_ped_interface)
					ImGui::Text(std::format("Ped Pool: {}/{}", replay_interface->m_ped_interface->m_cur_peds, replay_interface->m_ped_interface->m_max_peds).c_str());

				if(replay_interface->m_vehicle_interface)
					ImGui::Text(std::format("Vehicle Pool: {}/{}", replay_interface->m_vehicle_interface->m_cur_vehicles, replay_interface->m_vehicle_interface->m_max_vehicles).c_str());
					
				if(replay_interface->m_object_interface)
					ImGui::Text(std::format("Object Pool: {}/{}", replay_interface->m_object_interface->m_cur_objects, replay_interface->m_object_interface->m_max_objects).c_str());
			}
	
			if (g.window.ingame_overlay.show_game_versions)
			{
				ImGui::Separator();
				ImGui::Text(std::format("Game Version: {}", g_pointers->m_game_version).c_str());
				ImGui::Text(std::format("Online Version: {}", g_pointers->m_online_version).c_str());
			}
		}
		ImGui::End();
	}
}
