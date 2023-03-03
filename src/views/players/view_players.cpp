#include "fiber_pool.hpp"
#include "fonts/fonts.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "services/gui/gui_service.hpp"
#include "services/players/player_service.hpp"
#include "views/view.hpp"

#define IMGUI_DEFINE_PLACEMENT_NEW
#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui_internal.h>

namespace big
{
	static void player_button(const player_ptr& plyr)
	{
		bool selected_player = plyr == g_player_service->get_selected();

		// generate icons string
		std::string player_icons;
		if (plyr->is_host())
			player_icons += FONT_ICON_HOST;
		if (plyr->is_friend())
			player_icons += FONT_ICON_FRIEND;
		if (const auto ped = plyr->get_ped(); ped != nullptr && ped->m_ped_task_flag & (uint8_t)ePedTask::TASK_DRIVING)
			player_icons += FONT_ICON_VEHICLE;

		const auto player_iconsc    = player_icons.c_str();
		const auto player_icons_end = player_iconsc + player_icons.size();

		// calculate icons width
		const auto window = ImGui::GetCurrentWindow();
		ImGui::PushFont(g.window.font_icon);
		const auto icons_size = ImGui::CalcTextSize(player_iconsc, player_icons_end);
		const ImVec2 icons_pos(window->DC.CursorPos.x + 300.0f - 32.0f - icons_size.x, window->DC.CursorPos.y + 2.0f);
		const ImRect icons_box(icons_pos, icons_pos + icons_size);
		ImGui::PopFont();

		if (plyr->is_modder)
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.f, 0.1f, 0.1f, 1.f));

		if (selected_player)
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.29f, 0.45f, 0.69f, 1.f));

		ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, {0.0, 0.5});
		ImGui::PushID(plyr->id());
		if (ImGui::Button(plyr->get_name(), {300.0f - ImGui::GetStyle().ScrollbarSize, 0.f}))
		{
			g_player_service->set_selected(plyr);
			g_gui_service->set_selected(tabs::PLAYER);
			g.window.switched_view = true;
		}
		ImGui::PopID();
		ImGui::PopStyleVar();

		if (selected_player)
			ImGui::PopStyleColor();

		if (plyr->is_modder)
			ImGui::PopStyleColor();

		// render icons on top of the player button
		ImGui::PushFont(g.window.font_icon);
		ImGui::RenderTextWrapped(icons_box.Min, player_iconsc, player_icons_end, icons_size.x);
		ImGui::PopFont();
	}

	void view::players()
	{
		const auto player_count = g_player_service->players().size() + 1;

		if (!*g_pointers->m_is_session_started && player_count < 2)
			return;
		float window_pos = 110.f + g_gui_service->nav_ctr * ImGui::CalcTextSize("W").y
		    + g_gui_service->nav_ctr * ImGui::GetStyle().ItemSpacing.y
		    + g_gui_service->nav_ctr * ImGui::GetStyle().ItemInnerSpacing.y + ImGui::GetStyle().WindowPadding.y;

		ImGui::SetNextWindowSize({300.f, 0.f});
		ImGui::SetNextWindowPos({10.f, window_pos});
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, {2.0f, 2.0f});

		if (ImGui::Begin("playerlist", nullptr, window_flags))
		{
			float window_height = (ImGui::CalcTextSize("A").y + ImGui::GetStyle().ItemInnerSpacing.y * 2 + 6.0f) * player_count + 10.0f;
			window_height = window_height + window_pos > (float)*g_pointers->m_resolution_y - 10.f ? (float)*g_pointers->m_resolution_y - (window_pos + 40.f) : window_height;

			ImGui::PushStyleColor(ImGuiCol_FrameBg, {0.f, 0.f, 0.f, 0.f});
			ImGui::PushStyleColor(ImGuiCol_ScrollbarBg, {0.f, 0.f, 0.f, 0.f});

			if (ImGui::BeginListBox("##players", {ImGui::GetWindowSize().x - ImGui::GetStyle().WindowPadding.x * 2, window_height}))
			{
				player_button(g_player_service->get_self());

				if (player_count > 1)
					ImGui::Separator();

				for (const auto& [_, player] : g_player_service->players())
					player_button(player);

				ImGui::EndListBox();
			}
			ImGui::PopStyleColor(2);
		}

		ImGui::PopStyleVar();
		ImGui::End();
	}
}
