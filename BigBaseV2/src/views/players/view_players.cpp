#include "pointers.hpp"
#include "services/gui/gui_service.hpp"
#include "services/players/player_service.hpp"
#include "services/anti_cheat/anti_cheat_service.hpp"
#include "views/view.hpp"
#include "fonts/fonts.hpp"
#include "natives.hpp"
#include "fiber_pool.hpp"

#define IMGUI_DEFINE_PLACEMENT_NEW
#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui_internal.h>

namespace big
{
	static void player_button(const player_ptr& plyr)
	{
		bool playerSelected = plyr == g_player_service->get_selected();

		bool isHost = false;
		bool isFriend = false;
		bool isInVehicle = false;
		bool isModder = false;

		if (plyr->is_valid()) {
			isModder = g_anti_cheat_service->is_player_in_moddb(plyr->get_net_data()->m_rockstar_id2);
			isHost = plyr->is_host();
			isFriend = plyr->is_friend();
			isInVehicle = (plyr->get_ped() != nullptr) && 
				(plyr->get_ped()->m_ped_task_flag & (uint8_t)ePedTask::TASK_DRIVING);
		}

		// generate icons string
		std::string playerIcons = std::string(isHost ? FONT_ICON_HOST : "") +
			std::string(isModder ? FONT_ICON_NOTFRIEND : "") +
			std::string(isFriend ? FONT_ICON_FRIEND : "") +
			std::string(isInVehicle ? FONT_ICON_VEHICLE : "");

		const char* playerIconsCStr = playerIcons.c_str();


		// calculate icons width
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		ImGui::PushFont(g->window.font_icon);
		ImVec2 iconsSize = ImGui::CalcTextSize(playerIconsCStr, playerIconsCStr + playerIcons.size());
		ImVec2 iconsPos(window->DC.CursorPos.x + 300.0f - 32.0f - iconsSize.x, window->DC.CursorPos.y + 2.0f);
		ImRect iconsBox(iconsPos, iconsPos + iconsSize);
		ImGui::PopFont();


		if (isModder)
		{
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.9f, 0.f, 0.f, 1.f));
		}

		if (playerSelected)
		{
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.29f, 0.45f, 0.69f, 1.f));
		}

		ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, { 0.0, 0.5 });
		ImGui::PushID(plyr->id());
		if (ImGui::Button(plyr->get_name(), {300.0f - 15.0f - ImGui::GetStyle().ScrollbarSize, 0.f}))
		{
			g_player_service->set_selected(plyr);
			g_gui_service->set_selected(tabs::PLAYER);
			g->window.switched_view = true;
		}
		ImGui::PopID();
		ImGui::PopStyleVar();

		if (playerSelected)
			ImGui::PopStyleColor();

		// render icons on top of the player button
		ImGui::PushFont(g->window.font_icon);
		ImGui::RenderTextWrapped(iconsBox.Min, playerIconsCStr, playerIconsCStr + playerIcons.size(), iconsSize.x);
		ImGui::PopFont();
	}

	void view::players()
	{
		if (!*g_pointers->m_is_session_started) return;

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 2.0f, 2.0f });

		if (ImGui::Begin("playerlist", nullptr, window_flags))
		{

			float window_height = (ImGui::CalcTextSize("A").y + ImGui::GetStyle().ItemInnerSpacing.y * 2 + 6.0f) * 32 + 10.0f;

			ImGui::PushStyleColor(ImGuiCol_FrameBg, { 0.f, 0.f, 0.f, 0.f });
			ImGui::PushStyleColor(ImGuiCol_ScrollbarBg, { 0.f, 0.f, 0.f, 0.f });

			if (ImGui::BeginListBox("##players", { ImGui::GetWindowSize().x - ImGui::GetStyle().WindowPadding.x * 2 , window_height }))
			{
				player_button(g_player_service->get_self());

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
