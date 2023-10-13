#include "pointers.hpp"
#include "services/recent_modders.cpp"
#include "views/view.hpp"

namespace big
{
	void view::recent_modders()
	{
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