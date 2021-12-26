#include "main_tabs.hpp"
#include "fiber_pool.hpp"
#include "util/teleport.hpp"

namespace big
{
	void tab_main::tab_spoofing()
	{
		if (ImGui::BeginTabItem("Spoofing"))
		{
			ImGui::Text("To spoof any of the below credentials you need to reconnect with the lobby.");

			if (ImGui::TreeNode("Username"))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					PAD::DISABLE_ALL_CONTROL_ACTIONS(0);
				}QUEUE_JOB_END_CLAUSE

				ImGui::Checkbox("Spoof Username", &g.spoofing.spoof_username);

				static char name[20];
				strcpy_s(name, sizeof(name), g.spoofing.username.c_str());

				ImGui::Text("Username:");
				ImGui::InputText("##username_input", name, sizeof(name));

				if (name != g.spoofing.username)
					g.spoofing.username = std::string(name);

				ImGui::TreePop();
			}

			if (ImGui::TreeNode("IP Address"))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					PAD::DISABLE_ALL_CONTROL_ACTIONS(0);
				}QUEUE_JOB_END_CLAUSE

				ImGui::Checkbox("Spoof IP", &g.spoofing.spoof_ip);

				ImGui::Text("IP Address:");
				ImGui::DragInt4("##ip_fields", g.spoofing.ip_address, 0, 255);

				ImGui::TreePop();
			}

			if (ImGui::TreeNode("Rockstar ID"))
			{
				QUEUE_JOB_BEGIN_CLAUSE()
				{
					PAD::DISABLE_ALL_CONTROL_ACTIONS(0);
				}QUEUE_JOB_END_CLAUSE

				ImGui::Checkbox("Spoof Rockstar ID", &g.spoofing.spoof_rockstar_id);

				ImGui::Text("Rockstar ID:");
				ImGui::InputScalar("##rockstar_id_input", ImGuiDataType_U64, &g.spoofing.rockstar_id);

				ImGui::TreePop();
			}

			ImGui::EndTabItem();
		}
	}
}
