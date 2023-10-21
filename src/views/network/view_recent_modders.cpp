#include "pointers.hpp"
#include "services/api/api_service.hpp"
#include "services/notifications/notification_service.hpp"
#include "services/recent_modders.cpp"
#include "thread_pool.hpp"
#include "views/view.hpp"

namespace big
{
	void view::recent_modders()
	{
		static char player_name[64];

		ImGui::SetNextItemWidth(300);
		components::input_text("Player Name", player_name, sizeof(player_name));
		components::button("Add to block list", [] {
			g_thread_pool->push([] {
				uint64_t rockstar_id;

				if (!g_api_service->get_rid_from_username(player_name, rockstar_id))
					g_notification_service->push_error("New Player Entry", "User could not be found.");
				else
					recent_modders_nm::recent_modders_list[rockstar_id] = {player_name, rockstar_id, true};
			});
		});

		static recent_modders_nm::recent_modder* selected;
		ImGui::NewLine();
		ImGui::BeginGroup();
		{
			ImGui::Text("Joins Not blocked -");
			if (ImGui::BeginListBox("##recent_modders", {300, static_cast<float>(*g_pointers->m_gta.m_resolution_y * 0.3)}))
			{
				for (auto& pair : recent_modders_nm::recent_modders_list)
					if (!pair.second.block_join
					    && ImGui::Selectable(pair.second.name.c_str(), selected && selected->rockstar_id == pair.second.rockstar_id))
						selected = &pair.second;

				ImGui::EndListBox();
			}
		}
		ImGui::EndGroup();
		ImGui::SameLine();
		ImGui::BeginGroup();
		{
			ImGui::Text("Joins blocked -");
			if (ImGui::BeginListBox("##recent_modders_blocked", {300, static_cast<float>(*g_pointers->m_gta.m_resolution_y * 0.3)}))
			{
				for (auto& pair : recent_modders_nm::recent_modders_list)
					if (pair.second.block_join
					    && ImGui::Selectable(pair.second.name.c_str(), selected && selected->rockstar_id == pair.second.rockstar_id))
						selected = &pair.second;

				ImGui::EndListBox();
			}
		}
		ImGui::EndGroup();

		components::button("Reset Non Blocked List", [] {
			selected = nullptr;
			for (auto it = recent_modders_nm::recent_modders_list.begin(); it != recent_modders_nm::recent_modders_list.end();)
			{
				if (!it->second.block_join)
					it = recent_modders_nm::recent_modders_list.erase(it);
				else
					++it;
			}
		});
		components::button("Reset All", [] {
			selected = nullptr;
			recent_modders_nm::load_blocked_list();
		});

		ImGui::Spacing();

		if (selected)
		{
			ImGui::Spacing();
			ImGui::Text("Selected Player - ");
			ImGui::Spacing();
			ImGui::Text(selected->name.c_str());
			ImGui::Text(std::to_string(selected->rockstar_id).c_str());
			if (ImGui::Checkbox("Block Join", &selected->block_join))
				recent_modders_nm::save_blocked_list();
		}
	}
}