#include "pointers.hpp"
#include "services/gui/gui_service.hpp"
#include "services/players/player_service.hpp"
#include "views/view.hpp"
#include "fonts/fonts.hpp"
#include <renderer.hpp>
#include <natives.hpp>

namespace big
{
	static void player_button(const player_ptr& plyr)
	{
		bool playerSelected = plyr == g_player_service->get_selected();

		bool isHost = false;
		bool isInVehicle = false;

		if (plyr->is_valid()) {
			isHost = plyr->is_host();
			isInVehicle = plyr->get_current_vehicle() != nullptr;

			/*Entity plyrPed = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(plyr->id());
			if (ENTITY::DOES_ENTITY_EXIST(plyrPed)) {
				if (PED::IS_PED_IN_ANY_VEHICLE(plyrPed, true)) {
					isInVehicle = true;
				}
			}*/
		}

		std::string playerIcons = std::string(isHost ? FONT_ICON_HOST : FONT_ICON_CLIENT) +
			std::string(isInVehicle ? FONT_ICON_VEHICLE : FONT_ICON_WALK);

		ImGui::PushFont(g_renderer->m_font_icons);
		ImGui::Text(playerIcons.c_str());
		ImGui::PopFont();
		ImGui::SameLine();


		if (playerSelected)
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.29f, 0.45f, 0.69f, 1.f));

		ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, { 0.0, 0.5 });
		ImGui::PushID(plyr->id());
		if (ImGui::Button(plyr->get_name(), { ImGui::GetWindowSize().x - 70.f, 0.f }))
		{
			g_player_service->set_selected(plyr);
			g_gui_service->set_selected(tabs::PLAYER);
			g->window.switched_view = true;
		}
		ImGui::PopID();
		ImGui::PopStyleVar();

		if (playerSelected)
			ImGui::PopStyleColor();
	}

	void view::players()
	{
		float window_pos = 110.f + g_gui_service->nav_ctr * ImGui::CalcTextSize("W").y + g_gui_service->nav_ctr * ImGui::GetStyle().ItemSpacing.y + g_gui_service->nav_ctr * ImGui::GetStyle().ItemInnerSpacing.y + ImGui::GetStyle().WindowPadding.y;

		ImGui::SetNextWindowSize({ 300.f, 0.f });
		ImGui::SetNextWindowPos({ 10.f, window_pos });
		if (ImGui::Begin("playerlist", nullptr, window_flags))
		{
			const auto player_count = g_player_service->players().size() + 1;

			float window_height = (ImGui::CalcTextSize("A").y + ImGui::GetStyle().ItemInnerSpacing.y * 2 + 8.5f) * player_count;
			window_height = window_height + window_pos > (float)*g_pointers->m_resolution_y - 10.f ? (float)*g_pointers->m_resolution_y - (window_pos + 40.f) : window_height;

			ImGui::PushStyleColor(ImGuiCol_FrameBg, { 0.f, 0.f, 0.f, 0.f });
			ImGui::PushStyleColor(ImGuiCol_ScrollbarBg, { 0.f, 0.f, 0.f, 0.f });

			if (ImGui::BeginListBox("##players", { 300.f - ImGui::GetStyle().WindowPadding.x * 2 , window_height }))
			{
				player_button(g_player_service->get_self());

				ImGui::Separator();

				for (const auto& [_, player] : g_player_service->players())
					player_button(player);

				ImGui::EndListBox();
			}
			ImGui::PopStyleColor(2);
		}
		ImGui::End();
	}
}
