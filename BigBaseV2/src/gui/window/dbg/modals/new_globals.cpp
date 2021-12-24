#include "../debug_tabs.hpp"
#include "fiber_pool.hpp"
#include "thread_pool.hpp"
#include "natives.hpp"
#include "script.hpp"

namespace big
{
	void modal_debug::modal_new_global()
	{
		ImGui::SetNextWindowSize({ 520, 325 }, ImGuiCond_FirstUseEver);
		if (ImGui::BeginPopupModal("New Global"))
		{
			static int base_address = 0;
			static bool freeze = false;
			static char name[32] = "";
			static int (*offsets)[2] = nullptr;
			static int offset_count = 0;
			static int previous_offset_count = 0;

			QUEUE_JOB_BEGIN_CLAUSE()
			{
				PAD::DISABLE_ALL_CONTROL_ACTIONS(0);
			}QUEUE_JOB_END_CLAUSE

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
				g_globals_service->m_globals.push_back(global(name, base_address, freeze, offsets, offset_count));

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
	}
}