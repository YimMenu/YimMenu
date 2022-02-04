#include "debug_tabs.hpp"
#include "fiber_pool.hpp"
#include "pointers.hpp"
#include "script.hpp"

namespace big
{
	void tab_debug::tab_script_events()
	{
		if (ImGui::BeginTabItem("Script Events"))
		{
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
				int64_t* temp_args = new int64_t[event_arg_count] {0};
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

			if (ImGui::Button("Send Event"))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					g_pointers->m_trigger_script_event(1, args, event_arg_count, event_everyone ? -1 : 1 << event_player_bits);
				}QUEUE_JOB_END_CLAUSE
			}

			ImGui::EndTabItem();
		}
	}
}