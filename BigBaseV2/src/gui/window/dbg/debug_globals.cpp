#include "debug_tabs.hpp"
#include "services/globals_service.hpp"
#include "thread_pool.hpp"

namespace big
{
	void tab_debug::tab_globals()
	{
		if (ImGui::BeginTabItem("Globals"))
		{
			if (ImGui::Checkbox("Enable Freezing", &g_globals_service->m_running) && g_globals_service->m_running)
				g_thread_pool->push([&]() { g_globals_service->loop(); });

			if (ImGui::Button("Load"))
				g_globals_service->load();
			ImGui::SameLine();
			if (ImGui::Button("Save"))
				g_globals_service->save();

			ImGui::SameLine();
			if (ImGui::Button("Add Global"))
			{
				ImGui::OpenPopup("New Global");
			}

			modal_debug::modal_new_global();

			for (auto& global : g_globals_service->m_globals)
			{
				char label[64];

				ImGui::Separator();

				sprintf(label, "Freeze##%d", global.get_id());
				ImGui::Checkbox(label, &global.m_freeze);

				ImGui::BeginGroup();

				ImGui::Text("Name:");
				ImGui::Text("Value:");

				ImGui::EndGroup();

				ImGui::SameLine();

				ImGui::BeginGroup();

				ImGui::Text(global.m_name.c_str());
				
				sprintf(label, "###input_%d", global.get_id());
				ImGui::SetNextItemWidth(200.f);
				ImGui::InputInt(label, global.get());

				ImGui::EndGroup();

				ImGui::SameLine();

				ImGui::BeginGroup();

				sprintf(label, "Delete##%d", global.get_id());
				if (ImGui::Button(label))
				{
					for (int i = 0; i < g_globals_service->m_globals.size(); i++)
						if (auto& it = g_globals_service->m_globals.at(i); it.get_id() == global.get_id())
							g_globals_service->m_globals.erase(g_globals_service->m_globals.begin() + i);

					break;
				}

				sprintf(label, "Write###%d", global.get_id());
				if (ImGui::Button(label))
					global.write();	

				ImGui::EndGroup();
			}

			ImGui::EndTabItem();
		}
	}
}