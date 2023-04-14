#include "gui/components/components.hpp"
#include "services/locals/locals_service.hpp"
#include "view_debug.hpp"

namespace big
{

	void render_local_creator_popup_content()
	{
		static int base_address             = 0;
		static bool freeze                  = false;
		static char name[200]               = "";
		static char script_thread_name[200] = "";
		static int(*offsets)[2]             = nullptr;
		static int offset_count             = 0;
		static int previous_offset_count    = 0;
		components::input_text_with_hint("##local_name", "Name", name, sizeof(name));
		components::input_text_with_hint("##local_script_thread_name", "Script thread", script_thread_name, sizeof(script_thread_name));
		ImGui::Text("Base address");
		ImGui::InputInt("##local_base_address", &base_address);
		ImGui::Text("Offsetcount");
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

		static auto reset_values = []() -> void {
			strcpy(name, "");
			freeze = false;
			delete[] offsets;
			offsets               = nullptr;
			offset_count          = 0;
			previous_offset_count = 0;
		};

		if (components::button("CANCEL"_T))
		{
			reset_values();

			ImGui::CloseCurrentPopup();
		}
		ImGui::SameLine();
		if (components::button("SAVE"_T))
		{
			if (locals_service::does_script_exist(script_thread_name))
			{
				auto new_local = local(script_thread_name, name, base_address, freeze, offsets, offset_count);
				g_locals_service.m_locals.push_back(new_local);

				reset_values();

				ImGui::CloseCurrentPopup();
			}
			else
			{
				g_notification_service->push_error("Locals editor", "Script does not exist");
			}
		};
	}

	void debug::locals()
	{
		if (ImGui::BeginTabItem("DEBUG_TAB_LOCALS"_T.data()))
		{
			if (components::button("LOAD"_T))
				g_locals_service.load();
			ImGui::SameLine();
			if (components::button("SAVE"_T))
				g_locals_service.save();

			if (components::button("Add local"))
			{
				ImGui::OpenPopup("##addlocal");
			}

			if (ImGui::BeginPopupModal("##addlocal"))
			{
				render_local_creator_popup_content();

				ImGui::EndPopup();
			}

			for (auto& local_ : g_locals_service.m_locals)
			{
				ImGui::BeginGroup();
				ImGui::PushID(local_.get_id());

				ImGui::Text("%s : %s", local_.m_name, local_.m_script_thread_name);
				if (ImGui::IsItemHovered())
				{
					ImGui::BeginTooltip();
					char offsetschain[200] = "";
					strcat(offsetschain, std::to_string(local_.m_base_address).data());
					for (auto o : local_.m_offsets)
					{
						strcat(offsetschain, std::string(".f_" + std::to_string(o.m_offset)).data());
						if (o.m_size)
							strcat(offsetschain, std::string("/" + std::to_string(o.m_size)).data());
					}
					ImGui::Text(offsetschain);
					ImGui::EndTooltip();
				}

				//Find the thread among the script threads
				if (!local_.m_script_thread)
					local_.m_script_thread = gta_util::find_script_thread(rage::joaat(local_.m_script_thread_name));

				if (local_.m_script_thread && locals_service::is_script_thread_running(local_.m_script_thread))
				{
					//Check whether the address is found
					if (local_.m_internal_address)
					{
						ImGui::Text("Value");
						ImGui::SetNextItemWidth(200);
						if (ImGui::InputInt("##local_value", local_.m_internal_address))
						{
							local_.m_value = *local_.m_internal_address;
						}
						ImGui::SameLine();
						if (ImGui::Checkbox("Freeze", &local_.m_freeze))
							local_.m_freeze_value = *local_.m_internal_address;

						if (local_.m_freeze)
							*local_.m_internal_address = local_.m_freeze_value;
					}
					else
					{
						if (components::button("Fetch"))
						{
							local_.fetch_local_pointer();
						}
					}
				}
				else
				{
					ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
					ImGui::Text("%s isn't running", local_.m_script_thread_name);
					ImGui::PopStyleColor();
				}
				if (components::button("Delete"))
					std::erase_if(g_locals_service.m_locals, [local_](local l) {
						return l.get_id() == local_.get_id();
					});

				ImGui::PopID();
				ImGui::Separator();
				ImGui::EndGroup();
			}

			ImGui::EndTabItem();
		}
	}
}