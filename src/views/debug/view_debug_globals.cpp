#include "gui/components/components.hpp"
#include "services/globals/globals_service.hpp"
#include "thread_pool.hpp"
#include "view_debug.hpp"

namespace big
{
	void debug::globals()
	{
		if (ImGui::BeginTabItem("DEBUG_TAB_GLOBALS"_T.data()))
		{
			if (ImGui::Checkbox("DEBUG_GLOBALS_ENABLE_FREEZING"_T.data(), &g_globals_service->m_running)
			    && g_globals_service->m_running)
				g_thread_pool->push([&]() {
					g_globals_service->loop();
				});

			if (components::button("LOAD"_T))
				g_globals_service->load();
			ImGui::SameLine();
			if (components::button("SAVE"_T))
				g_globals_service->save();


			ImGui::SameLine();
			if (components::button("DEBUG_GLOBALS_ADD"_T))
			{
				ImGui::OpenPopup("DEBUG_GLOBALS_NEW"_T.data());
			}

			if (ImGui::BeginPopupModal("DEBUG_GLOBALS_NEW"_T.data()))
			{
				static int base_address          = 0;
				static bool freeze               = false;
				static char name[32]             = "";
				static int(*offsets)[2]          = nullptr;
				static int offset_count          = 0;
				static int previous_offset_count = 0;

				ImGui::Text("DEBUG_GLOBALS_NAME"_T.data());
				components::input_text_with_hint("##global_name", "Name", name, sizeof(name));
				ImGui::Text("DEBUG_GLOBALS_BASE_ADDRESS"_T.data());
				ImGui::InputInt("##modal_global_base_addr", &base_address);
				ImGui::Text("DEBUG_GLOBAL_FREEZE"_T.data());
				ImGui::Checkbox("##modal_global_freeze", &freeze);
				ImGui::Text("DEBUG_GLOBAL_OFFSET_COUNT"_T.data());
				ImGui::InputInt("##modal_offset_count", &offset_count);

				if (offset_count < 0)
					offset_count = 0;
				else if (offset_count > 10)
					offset_count = 10;

				if (offset_count != previous_offset_count)
				{
					int(*new_offsets)[2] = new int[offset_count][2]{0};
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

					ImGui::Text("DEBUG_GLOBAL_OFFSET"_T.data(), i + 1);
					ImGui::InputInt("##offset", &offsets[i][0]);

					ImGui::Text("DEBUG_GLOBAL_SIZE"_T.data());
					ImGui::SameLine();
					ImGui::InputInt("##size", &offsets[i][1]);

					ImGui::PopID();
				}
				ImGui::PopItemWidth();

				if (components::button("CANCEL"_T))
				{
					strcpy(name, "");
					freeze = false;
					delete[] offsets;
					offsets               = nullptr;
					offset_count          = 0;
					previous_offset_count = 0;

					ImGui::CloseCurrentPopup();
				}
				ImGui::SameLine();
				if (components::button("SAVE"_T))
				{
					auto new_global = global(name, base_address, freeze, offsets, offset_count);
					new_global.build_cache();

					g_globals_service->m_globals.push_back(new_global);

					strcpy(name, "");
					freeze = false;
					delete[] offsets;
					offsets               = nullptr;
					offset_count          = 0;
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
				ImGui::Checkbox("DEBUG_GLOBAL_FREEZE_TOGGLE"_T.data(), &global.m_freeze);

				ImGui::BeginGroup();

				ImGui::Text("DEBUG_GLOBALS_NAME"_T.data());
				ImGui::Text("DEBUG_GLOBALS_VALUE"_T.data());

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

				if (components::button("DELETE"_T))
				{
					for (int i = 0; i < g_globals_service->m_globals.size(); i++)
						if (auto& it = g_globals_service->m_globals.at(i); it.get_id() == global.get_id())
							g_globals_service->m_globals.erase(g_globals_service->m_globals.begin() + i);

					break;
				}

				if (components::button("WRITE"_T))
					global.write();

				ImGui::PopID();
				ImGui::EndGroup();
			}

			ImGui::EndTabItem();
		}
	}
}