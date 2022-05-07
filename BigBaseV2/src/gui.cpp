#include "common.hpp"
#include "fiber_pool.hpp"
#include "gta/player.hpp"
#include "gta_util.hpp"
#include "gui.hpp"
#include "logger.hpp"
#include "memory/module.hpp"
#include "memory/pattern.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "renderer.hpp"
#include "script.hpp"


#include <imgui.h>
#include "widgets/imgui_hotkey.hpp"

#include "views/view.hpp"
#include "services/notification_service.hpp"

namespace big
{
	void gui::dx_init()
	{
		static ImVec4 bgColor = ImVec4(0.09f, 0.094f, 0.129f, .9f);
		static ImVec4 primary = ImVec4(0.172f, 0.380f, 0.909f, 1.f);
		static ImVec4 secondary = ImVec4(0.443f, 0.654f, 0.819f, 1.f);
		static ImVec4 whiteBroken = ImVec4(0.792f, 0.784f, 0.827f, 1.f);

		auto& style = ImGui::GetStyle();
		style.WindowPadding = ImVec2(15, 15);
		style.WindowRounding = 10.f;
		style.WindowBorderSize = 0.f;
		style.FramePadding = ImVec2(5, 5);
		style.FrameRounding = 4.0f;
		style.ItemSpacing = ImVec2(12, 8);
		style.ItemInnerSpacing = ImVec2(8, 6);
		style.IndentSpacing = 25.0f;
		style.ScrollbarSize = 15.0f;
		style.ScrollbarRounding = 9.0f;
		style.GrabMinSize = 5.0f;
		style.GrabRounding = 3.0f;
		style.ChildRounding = 4.0f;

		auto& colors = style.Colors;
		colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.00f);
		colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
		colors[ImGuiCol_WindowBg] = ImGui::ColorConvertU32ToFloat4(g->window.color);
		colors[ImGuiCol_ChildBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
		colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
		colors[ImGuiCol_Border] = ImVec4(0.80f, 0.80f, 0.83f, 0.88f);
		colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
		colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
		colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
		colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
		colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
		colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
		colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
		colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
		colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
		colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
		colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
		colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
		colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
		colors[ImGuiCol_Button] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
		colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
		colors[ImGuiCol_ButtonActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
		colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
		colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
		colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
		colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
		colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
		colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
		colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
		colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
		colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
		colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
	}

	void gui::dx_on_tick()
	{
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImGui::ColorConvertU32ToFloat4(g->window.color));
		view::root();
		ImGui::PopStyleColor();
	}

	void gui::always_draw()
	{
		view::always();
	}

	void gui::script_init()
	{
		g_notification_service->push("Welcome", fmt::format("Loaded YimMenu. Press {} to open", ImGui::key_names[g->settings.hotkeys.menu_toggle]));	
	}

	void gui::script_on_tick()
	{
		TRY_CLAUSE
		{
			if (g_gui.m_opened)
			{
				for (uint8_t i = 0; i <= 6; i++)
					PAD::DISABLE_CONTROL_ACTION(2, i, true);
				PAD::DISABLE_CONTROL_ACTION(2, 106, true);
				PAD::DISABLE_CONTROL_ACTION(2, 329, true);
				PAD::DISABLE_CONTROL_ACTION(2, 330, true);

				PAD::DISABLE_CONTROL_ACTION(2, 14, true);
				PAD::DISABLE_CONTROL_ACTION(2, 15, true);
				PAD::DISABLE_CONTROL_ACTION(2, 16, true);
				PAD::DISABLE_CONTROL_ACTION(2, 17, true);
				PAD::DISABLE_CONTROL_ACTION(2, 24, true);
				PAD::DISABLE_CONTROL_ACTION(2, 69, true);
				PAD::DISABLE_CONTROL_ACTION(2, 70, true);
				PAD::DISABLE_CONTROL_ACTION(2, 84, true);
				PAD::DISABLE_CONTROL_ACTION(2, 85, true);
				PAD::DISABLE_CONTROL_ACTION(2, 99, true);
				PAD::DISABLE_CONTROL_ACTION(2, 92, true);
				PAD::DISABLE_CONTROL_ACTION(2, 100, true);
				PAD::DISABLE_CONTROL_ACTION(2, 114, true);
				PAD::DISABLE_CONTROL_ACTION(2, 115, true);
				PAD::DISABLE_CONTROL_ACTION(2, 121, true);
				PAD::DISABLE_CONTROL_ACTION(2, 142, true);
				PAD::DISABLE_CONTROL_ACTION(2, 241, true);
				PAD::DISABLE_CONTROL_ACTION(2, 261, true);
				PAD::DISABLE_CONTROL_ACTION(2, 257, true);
				PAD::DISABLE_CONTROL_ACTION(2, 262, true);
				PAD::DISABLE_CONTROL_ACTION(2, 331, true);
			}
		}
		EXCEPT_CLAUSE
	}

	void gui::script_func()
	{
		g_gui.script_init();
		while (true)
		{
			g_gui.script_on_tick();
			script::get_current()->yield();
		}
	}
}
