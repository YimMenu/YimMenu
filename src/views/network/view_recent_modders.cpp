#include "pointers.hpp"
#include "services/recent_modders.cpp"
#include "views/view.hpp"

namespace big
{
	void view::recent_modders()
	{
		static RecentModder* selected;

		components::button("Clear List", [] {
			recent_modders_list.clear();
		});

		if (ImGui::BeginListBox("##recent_modders", {300, static_cast<float>(*g_pointers->m_gta.m_resolution_y * 0.4)}))
		{
			for (auto& pair : recent_modders_list)
				if (ImGui::Selectable(pair.second.name.c_str(), selected && selected->rockstar_id == pair.second.rockstar_id))
					selected = &pair.second;

			ImGui::EndListBox();
		}

		if (selected)
		{
			ImGui::Spacing();
			ImGui::Text("Selected Player - ");
			ImGui::Spacing();
			ImGui::Text(selected->name.c_str());
			ImGui::Text(std::to_string(selected->rockstar_id).c_str());
			ImGui::Checkbox("Block Join", &selected->block_join);
		}
	}
}