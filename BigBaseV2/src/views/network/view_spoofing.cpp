#include "views/view.hpp"
#include "fiber_pool.hpp"
#include "util/teleport.hpp"

namespace big
{
	void view::spoofing()
	{ 
		components::small_text("To spoof any of the below credentials you need to reconnect with the lobby.");

		components::sub_title("Username");

		g_fiber_pool->queue_job([] {
			PAD::DISABLE_ALL_CONTROL_ACTIONS(0);
		});

		ImGui::Checkbox("Spoof Username", &g->spoofing.spoof_username);

		static char name[20];
		strcpy_s(name, sizeof(name), g->spoofing.username.c_str());

		ImGui::Text("Username:");
		ImGui::InputText("##username_input", name, sizeof(name));

		if (name != g->spoofing.username)
			g->spoofing.username = std::string(name);

		ImGui::Separator();

		components::sub_title("IP Address");

		g_fiber_pool->queue_job([] {
			PAD::DISABLE_ALL_CONTROL_ACTIONS(0);
		});

		ImGui::Checkbox("Spoof IP", &g->spoofing.spoof_ip);

		ImGui::Text("IP Address:");
		ImGui::DragInt4("##ip_fields", g->spoofing.ip_address, 0, 255);

		ImGui::Separator();

		components::sub_title("Rockstar ID");

		g_fiber_pool->queue_job([] {
			PAD::DISABLE_ALL_CONTROL_ACTIONS(0);
		});

		ImGui::Checkbox("Spoof Rockstar ID", &g->spoofing.spoof_rockstar_id);

		ImGui::Text("Rockstar ID:");
		ImGui::InputScalar("##rockstar_id_input", ImGuiDataType_U64, &g->spoofing.rockstar_id);
	}
}
