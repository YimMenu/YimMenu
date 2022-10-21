#include "gui/components/components.hpp"
#include "services/globals/globals_service.hpp"
#include "thread_pool.hpp"
#include "view_debug.hpp"

namespace big
{
	void debug::globals()
	{
		if (ImGui::BeginTabItem("Globals"))
		{
			if (ImGui::Checkbox("Enable Freezing", &g_globals_service->m_running) && g_globals_service->m_running)
				g_thread_pool->push([&]() { g_globals_service->loop(); });

			if (components::button("Load"))
				g_globals_service->load();
			ImGui::SameLine();
			if (components::button("Save"))
				g_globals_service->save();


			ImGui::SameLine();
			if (components::button("Add Global"))
			{
				ImGui::OpenPopup("New Global");
			}

			if (ImGui::BeginPopupModal("New Global"))
			{
				static int base_address = 0;
				static bool freeze = false;
				static char name[32] = "";
				static int(*offsets)[2] = nullptr;
				static int offset_count = 0;
				static int previous_offset_count = 0;

				ImGui::Text("Name:");
				components::input_text_with_hint("##global_name", "Name", name, sizeof(name));
				ImGui::Text("Base Address:");
				ImGui::InputInt("##modal_global_base_addr", &base_address);
				ImGui::Text("Freeze:");
				ImGui::Checkbox("##modal_global_freeze", &freeze);
				ImGui::Text("Number of Offsets:");
				ImGui::InputInt("##modal_offset_count", &offset_count);

				if (offset_count < 0) offset_count = 0;
				else if (offset_count > 10) offset_count = 10;

				if (offset_count != previous_offset_count)
				{
					int(*new_offsets)[2] = new int[offset_count][2]{ 0 };
					memcpy(new_offsets, offsets, sizeof(int) * std::min(offset_count, previous_offset_count) * 2);

					delete[] offsets;
					offsets = new_offsets;

					previous_offset_count = offset_count;
				}

				ImGui::PushItemWidth(320.f);
				for (int i = 0; i < offset_count; i++)
				{
					ImGui::PushID(i);

					ImGui::Separator();

					ImGui::Text("Offset: %d", i + 1);
					ImGui::InputInt("##offset", &offsets[i][0]);

					ImGui::Text("Size:");
					ImGui::SameLine();
					ImGui::InputInt("##size", &offsets[i][1]);

					ImGui::PopID();
				}
				ImGui::PopItemWidth();

				if (components::button("Cancel"))
				{
					strcpy(name, "");
					freeze = false;
					delete[] offsets;
					offsets = nullptr;
					offset_count = 0;
					previous_offset_count = 0;

					ImGui::CloseCurrentPopup();
				}
				ImGui::SameLine();
				if (components::button("Save"))
				{
					auto new_global = global(name, base_address, freeze, offsets, offset_count);
					new_global.build_cache();

					g_globals_service->m_globals.push_back(new_global);

					strcpy(name, "");
					freeze = false;
					delete[] offsets;
					offsets = nullptr;
					offset_count = 0;
					previous_offset_count = 0;

					ImGui::CloseCurrentPopup();
				}

				ImGui::EndPopup();
			}

			for (auto& global : g_globals_service->m_globals)
			{
				char label[64];

				ImGui::Separator();

				ImGui::PushID(global.get_id());
				ImGui::Checkbox("Freeze", &global.m_freeze);

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

				if (components::button("Delete"))
				{
					for (int i = 0; i < g_globals_service->m_globals.size(); i++)
						if (auto& it = g_globals_service->m_globals.at(i); it.get_id() == global.get_id())
							g_globals_service->m_globals.erase(g_globals_service->m_globals.begin() + i);

					break;
				}

				if (components::button("Write"))
					global.write();

				ImGui::PopID();
				ImGui::EndGroup();
			}

			ImGui::EndTabItem();
		}
	}
}