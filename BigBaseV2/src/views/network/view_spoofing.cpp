#include "views/view.hpp"
#include "fiber_pool.hpp"
#include "util/teleport.hpp"
#include "core/data/region_codes.hpp"
#include "core/data/pool_types.hpp"

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

		ImGui::Separator();

		components::sub_title("Region Spoof");

		if (ImGui::BeginCombo("Region", region_codes[g->spoofing.region_code]))
		{
			for (int i = 0; i < region_codes.size(); i++)
			{
				if (ImGui::Selectable(region_codes[i], g->spoofing.region_code == i))
				{
					g->spoofing.region_code = i;
					*g_pointers->m_region_code = i;
				};
			}
			ImGui::EndCombo();
		}

		ImGui::Separator();

		components::sub_title("Session Pool Spoof");

		if (ImGui::BeginCombo("Pools", pool_types[g->spoofing.pool_type]))
		{
			for (int i = 0; i < pool_types.size(); i++)
			{
				if (ImGui::Selectable(pool_types[i], g->spoofing.pool_type == i))
				{
					g->spoofing.pool_type = i;
				};
			}
			ImGui::EndCombo();
		}
	}
}
