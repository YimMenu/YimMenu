#include "views/view.hpp"
#include "services/globals_service.hpp"
#include "thread_pool.hpp"
#include "fiber_pool.hpp"
#include "pointers.hpp"
#include "script.hpp"
#include "util/system.hpp"
#include "natives.hpp"

namespace big
{
	void view::debug() {
		components::small_text("Globals");

		if (ImGui::Checkbox("Enable Freezing", &g_globals_service->m_running) && g_globals_service->m_running)
			g_thread_pool->push([&]() { g_globals_service->loop(); });

		if (ImGui::Button("Load"))
			g_globals_service->load();
		ImGui::SameLine();
		if (ImGui::Button("Save"))
			g_globals_service->save();

		components::button("Network Bail", []
		{
			NETWORK::NETWORK_BAIL(16, 0, 0);
		});

		ImGui::SameLine();
		if (ImGui::Button("Add Global"))
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

			g_fiber_pool->queue_job([] {
				PAD::DISABLE_ALL_CONTROL_ACTIONS(0);
			});

			ImGui::Text("Name:");
			ImGui::InputText("##modal_global_name", name, sizeof(name));
			ImGui::Text("Base Address:");
			ImGui::InputInt("##modal_global_base_addr", &base_address);
			ImGui::Text("Freeze:");
			ImGui::Checkbox("##modal_global_freeze", &freeze);
			ImGui::Text("Number of Offsets:");
			ImGui::InputInt("##modal_offset_count", &offset_count);

			if (offset_count < 0) offset_count;
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
				char id[32];

				ImGui::Separator();

				ImGui::Text("Offset: %d", i + 1);

				sprintf(id, "##offset_%d", i);
				ImGui::InputInt(id, &offsets[i][0]);

				ImGui::Text("Size:");
				ImGui::SameLine();
				sprintf(id, "##size_%d", i);
				ImGui::InputInt(id, &offsets[i][1]);
			}
			ImGui::PopItemWidth();

			if (ImGui::Button("Cancel"))
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
			if (ImGui::Button("Save"))
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

		components::small_text("Scripting Events");

		static int64_t* args;
		static int event_arg_count = 1;
		static int previous_arg_count;
		static int event_player_bits;
		static bool event_everyone = false;

		ImGui::Text("Script Argument Count:");
		ImGui::InputInt("###script_event_arg_count", &event_arg_count);
		if (event_arg_count > 32)
			event_arg_count = 32;
		else if (event_arg_count < 1)
			event_arg_count = 1;

		if (event_arg_count != previous_arg_count)
		{
			int64_t* temp_args = new int64_t[event_arg_count]{ 0 };
			memcpy(temp_args, args, sizeof(int64_t) * std::min(event_arg_count, previous_arg_count));

			delete[] args;
			args = temp_args;

			previous_arg_count = event_arg_count;
		}

		ImGui::Separator();

		for (int i = 0; i < event_arg_count; i++)
		{
			ImGui::Text("Arg[%d]", i);
			ImGui::SameLine();

			char input_arg_name[20];
			sprintf(input_arg_name, "###input_dynamic_arg_%d", i);
			ImGui::InputScalar(input_arg_name, ImGuiDataType_S64, &args[i]);
		}

		ImGui::Separator();

		ImGui::Checkbox("Send to everyone", &event_everyone);
		if (!event_everyone)
		{
			ImGui::Text("Player ID:");
			ImGui::InputInt("###player_bits", &event_player_bits);
		}

		components::button("Send Event", [] {
			args[1] = self::id; // prevent detection from AC
			g_pointers->m_trigger_script_event(1, args, event_arg_count, event_everyone ? -1 : 1 << event_player_bits);
		});

		components::small_text("Debug");

		ImGui::Checkbox("Script Event Logging", &g->debug.script_event_logging);

		if (ImGui::Button("Dump entrypoints"))
		{
			system::dump_entry_points();
		}
	}
}