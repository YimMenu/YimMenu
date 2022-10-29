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

		constexpr size_t name_size = RTL_FIELD_SIZE(rage::rlGamerInfo, m_name);
		static char name[name_size];
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

		components::sub_title("Proofs");
		ImGui::Checkbox("Hide God Mode", &g->spoofing.spoof_hide_god);

		components::sub_title("Crew");

		g_fiber_pool->queue_job([] {
			PAD::DISABLE_ALL_CONTROL_ACTIONS(0);
		});

		ImGui::Checkbox("Spoof Crew", &g->spoofing.spoof_crew_data);

		constexpr size_t crew_tag_size = RTL_FIELD_SIZE(ClanData, m_clan_tag);
		static char crew_tag[crew_tag_size];
		strcpy_s(crew_tag, sizeof(crew_tag), g->spoofing.crew_tag.c_str());

		ImGui::Text("Crew Tag:");
		ImGui::InputText("##crew_tag_input", crew_tag, sizeof(crew_tag));

		if (crew_tag != g->spoofing.crew_tag)
			g->spoofing.crew_tag = std::string(crew_tag);

		ImGui::Checkbox("Is Rockstar Crew", &g->spoofing.rockstar_crew);

		ImGui::Checkbox("Square Crew Tag", &g->spoofing.square_crew_tag);

		components::sub_title("Extra - Only work when Spoofed RID");

		ImGui::Checkbox("Is Cheater", &g->spoofing.spoof_cheater);
		ImGui::Checkbox("Is Rockstar Dev", &g->spoofing.spoof_rockstar_dev);
		ImGui::Checkbox("Is Rockstar QA", &g->spoofing.spoof_rockstar_qa);
	}
}
