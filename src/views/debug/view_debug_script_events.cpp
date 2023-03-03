#include "gui/components/components.hpp"
#include "pointers.hpp"
#include "view_debug.hpp"

namespace big
{
	void debug::script_events()
	{
		if (ImGui::BeginTabItem("DEBUG_TAB_SCRIPT_EVENTS"_T.data()))
		{
			static int64_t* args;
			static int event_arg_count = 3;
			static int previous_arg_count;
			static int event_player_bits;
			static bool event_everyone = false;

			ImGui::Text("DEBUG_SCRIPT_EVENT_ARG_COUNT"_T.data());
			ImGui::InputInt("###script_event_arg_count", &event_arg_count);
			if (event_arg_count > 32)
				event_arg_count = 32;
			else if (event_arg_count < 3)
				event_arg_count = 3;

			if (event_arg_count != previous_arg_count)
			{
				int64_t* temp_args = new int64_t[event_arg_count]{0};
				memcpy(temp_args, args, sizeof(int64_t) * std::min(event_arg_count, previous_arg_count));

				delete[] args;
				args = temp_args;

				previous_arg_count = event_arg_count;
			}

			ImGui::Separator();

			for (int i = 0; i < event_arg_count; i++)
			{
				ImGui::PushID(i);
				ImGui::Text("DEBUG_SCRIPT_EVENT_ARG"_T.data(), i);
				ImGui::SameLine();

				ImGui::InputScalar("###input_dynamic_arg", ImGuiDataType_S64, &args[i]);

				ImGui::PopID();
			}

			ImGui::Separator();

			ImGui::Checkbox("DEBUG_SCRIPT_EVENT_EVERYONE"_T.data(), &event_everyone);
			if (!event_everyone)
			{
				ImGui::Text("DEBUG_SCRIPT_EVENT_PLAYER_ID"_T.data());
				ImGui::InputInt("###player_bits", &event_player_bits);
			}

			components::button("DEBUG_SCRIPT_EVENT_SEND_EVENT"_T, [] {
				args[1] = self::id;// prevent detection from AC
				g_pointers->m_trigger_script_event(1, args, event_arg_count, event_everyone ? -1 : 1 << event_player_bits);
			});

			ImGui::EndTabItem();
		}
	}
}