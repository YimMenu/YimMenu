#include "gui/components/components.hpp"
#include "services/locals/locals_service.hpp"
#include "view_debug.hpp"
#include "widgets/imgui_bitfield.hpp"

namespace big
{

	void render_local_creator_popup_content()
	{
		static int base_address             = 0;
		static bool freeze                  = false;
		static char name[200]               = "";
		static char script_thread_name[200] = "";
		static int offsets[10][2]           = {};
		static int offset_count             = 0;
		static int previous_offset_count    = 0;
		components::input_text("Name", name, sizeof(name));
		components::input_text("Script Name", script_thread_name, sizeof(script_thread_name));
		ImGui::Text("Base address");
		ImGui::InputInt("##local_base_address", &base_address);
		ImGui::Text("Offsetcount");
		ImGui::InputInt("##modal_offset_count", &offset_count);

		offset_count = std::clamp(offset_count, 0, 10);

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
			freeze                = false;
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
				if (std::string(name).empty())
					strcpy(name, new_local.get_local_chain_text());
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

			if (components::button("Add Local"))
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
				ImGui::SetNextItemOpen(true, ImGuiCond_FirstUseEver);
				if (ImGui::TreeNode(strcmp(local_.m_name, "") == 0 ? 
					std::string(local_.m_script_thread_name + std::string(" ")).append(local_.get_local_chain_text()).data(): local_.m_name))
				{
					ImGui::Text("%s : %s", local_.m_script_thread_name, local_.m_name);
					if (ImGui::IsItemHovered())
					{
						ImGui::BeginTooltip();
						ImGui::Text(local_.get_local_chain_text());
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
							if (ImGui::RadioButton("Int", local_.m_edit_mode == 0))
								local_.m_edit_mode = 0;
							ImGui::SameLine();
							if (ImGui::RadioButton("Float", local_.m_edit_mode == 1))
								local_.m_edit_mode = 1;
							ImGui::SameLine();
							if (ImGui::RadioButton("Bitfield", local_.m_edit_mode == 2))
								local_.m_edit_mode = 2;
							ImGui::SameLine();
							if (ImGui::RadioButton("Vector3", local_.m_edit_mode == 3))
								local_.m_edit_mode = 3;


							ImGui::LabelText(local_.get_local_chain_text(), "Value");

							ImGui::SetNextItemWidth(200);

							switch (local_.m_edit_mode)
							{
							case 0:

								if (ImGui::InputInt("##local_value",
								        local_.m_freeze ? &local_.m_freeze_value_int : local_.m_internal_address))
								{
									local_.m_value = *local_.m_internal_address;
								}

								if (local_.m_freeze)
								{
									*local_.m_internal_address = local_.m_freeze_value_int;
								}
								break;
							case 1:

								if (ImGui::InputFloat("##local_value",
								        local_.m_freeze ? &local_.m_freeze_value_float : (float*)local_.m_internal_address))
								{
									local_.m_value = *local_.m_internal_address;
								}

								if (local_.m_freeze)
								{
									*(float*)local_.m_internal_address = local_.m_freeze_value_float;
								}
								break;
							case 2:

								if (ImGui::Bitfield("##local_value",
								        local_.m_freeze ? &local_.m_freeze_value_int : local_.m_internal_address))
								{
									local_.m_value = *local_.m_internal_address;
								}

								if (local_.m_freeze)
								{
									*local_.m_internal_address = local_.m_freeze_value_int;
								}
								break;

							case 3:
								ImGui::SetNextItemWidth(300);
								if (ImGui::InputFloat3("##local_value",
								        local_.m_freeze ? (float*)&local_.m_freeze_value_vector3 : (float*)local_.m_internal_address))
								{
									local_.m_value = *local_.m_internal_address;
								}

								if (local_.m_freeze)
								{
									*local_.m_internal_address_vector3 = local_.m_freeze_value_vector3;
								}
								break;
							}

							ImGui::SameLine();
							if (ImGui::Checkbox("Freeze", &local_.m_freeze))
							{
								local_.m_freeze_value_int     = *local_.m_internal_address;
								local_.m_freeze_value_float   = *reinterpret_cast<float*>(local_.m_internal_address);
								local_.m_freeze_value_vector3 = *local_.m_internal_address_vector3;
							}
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

					ImGui::TreePop();
				}
				ImGui::EndGroup();
			}

			ImGui::EndTabItem();
		}
	}
}