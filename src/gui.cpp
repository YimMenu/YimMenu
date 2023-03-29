#include "gui.hpp"

#include "common.hpp"
#include "natives.hpp"
#include "renderer.hpp"
#include "script.hpp"
#include "util/is_key_pressed.hpp"
#include "views/view.hpp"

#include <imgui.h>

namespace big
{
	gui::gui() :
	    m_is_open(false)
	{
		g_renderer->add_dx_callback(view::gta_data, -1);
		g_renderer->add_dx_callback(view::notifications, -2);
		g_renderer->add_dx_callback(view::overlay, -3);
		g_renderer->add_dx_callback(view::cmd_executor, -4);
		g_renderer->add_dx_callback(
		    [this] {
			    dx_on_tick();
		    },
		    -5);

		g_renderer->add_wndproc_callback([this](HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
			wndproc(hwnd, msg, wparam, lparam);
		});

		g_renderer->add_dx_callback(esp::draw, 2); // TODO: move to ESP service
		g_renderer->add_dx_callback(view::context_menu, 1);

		dx_init();

		g_gui = this;
		g_renderer->rescale(g.window.gui_scale);
	}

	gui::~gui()
	{
		g_gui = nullptr;
	}

	bool gui::is_open()
	{
		return m_is_open;
	}

	void gui::toggle(bool toggle)
	{
		m_is_open = toggle;

		toggle_mouse();
	}

	void gui::dx_init()
	{
		static auto bgColor     = ImVec4(0.09f, 0.094f, 0.129f, .9f);
		static auto primary     = ImVec4(0.172f, 0.380f, 0.909f, 1.f);
		static auto secondary   = ImVec4(0.443f, 0.654f, 0.819f, 1.f);
		static auto whiteBroken = ImVec4(0.792f, 0.784f, 0.827f, 1.f);

		auto& style             = ImGui::GetStyle();
		style.WindowPadding     = ImVec2(15, 15);
		style.WindowRounding    = 10.f;
		style.WindowBorderSize  = 0.f;
		style.FramePadding      = ImVec2(5, 5);
		style.FrameRounding     = 4.0f;
		style.ItemSpacing       = ImVec2(12, 8);
		style.ItemInnerSpacing  = ImVec2(8, 6);
		style.IndentSpacing     = 25.0f;
		style.ScrollbarSize     = 15.0f;
		style.ScrollbarRounding = 9.0f;
		style.GrabMinSize       = 5.0f;
		style.GrabRounding      = 3.0f;
		style.ChildRounding     = 4.0f;

		auto& colors                          = style.Colors;
		colors[ImGuiCol_Text]                 = ImGui::ColorConvertU32ToFloat4(g.window.colortext);
		colors[ImGuiCol_TextDisabled]         = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
		colors[ImGuiCol_WindowBg]             = ImGui::ColorConvertU32ToFloat4(g.window.color);
		colors[ImGuiCol_ChildBg]              = ImGui::ColorConvertU32ToFloat4(g.window.color);
		colors[ImGuiCol_PopupBg]              = ImGui::ColorConvertU32ToFloat4(g.window.colorbg);
		colors[ImGuiCol_Border]               = ImGui::ColorConvertU32ToFloat4(g.window.coloractive);
		colors[ImGuiCol_BorderShadow]         = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
		colors[ImGuiCol_FrameBg]              = ImGui::ColorConvertU32ToFloat4(g.window.colorbg);      //Checkbox background
		colors[ImGuiCol_FrameBgHovered]       = ImGui::ColorConvertU32ToFloat4(g.window.colorhover);   //Checkbox hover
		colors[ImGuiCol_FrameBgActive]        = ImGui::ColorConvertU32ToFloat4(g.window.coloractive);  //Checkbox active
		colors[ImGuiCol_TitleBg]              = ImGui::ColorConvertU32ToFloat4(g.window.colorbg);
		colors[ImGuiCol_TitleBgCollapsed]     = ImGui::ColorConvertU32ToFloat4(g.window.colorbg);
		colors[ImGuiCol_TitleBgActive]        = ImGui::ColorConvertU32ToFloat4(g.window.colorbg);
		colors[ImGuiCol_MenuBarBg]            = ImGui::ColorConvertU32ToFloat4(g.window.colorbg);
		colors[ImGuiCol_ScrollbarBg]          = ImGui::ColorConvertU32ToFloat4(g.window.colorbg);      //Scrollbar background
		colors[ImGuiCol_ScrollbarGrab]        = ImGui::ColorConvertU32ToFloat4(g.window.colorsec);     //Scrollbar handle
		colors[ImGuiCol_ScrollbarGrabHovered] = ImGui::ColorConvertU32ToFloat4(g.window.colorhover);   //Scrollbar handle hover
		colors[ImGuiCol_ScrollbarGrabActive]  = ImGui::ColorConvertU32ToFloat4(g.window.coloractive);  //Scrollbar handle active
		colors[ImGuiCol_CheckMark]            = ImGui::ColorConvertU32ToFloat4(g.window.coloractive);  //Checkmark
		colors[ImGuiCol_SliderGrab]           = ImGui::ColorConvertU32ToFloat4(g.window.colorsec);     //Slider handle
		colors[ImGuiCol_SliderGrabActive]     = ImGui::ColorConvertU32ToFloat4(g.window.coloractive);  //Slider handle active
		colors[ImGuiCol_Button]               = ImGui::ColorConvertU32ToFloat4(g.window.colorsec);
		colors[ImGuiCol_ButtonHovered]        = ImGui::ColorConvertU32ToFloat4(g.window.colorhover);
		colors[ImGuiCol_ButtonActive]         = ImGui::ColorConvertU32ToFloat4(g.window.coloractive);
		colors[ImGuiCol_Header]               = ImGui::ColorConvertU32ToFloat4(g.window.colorsec);
		colors[ImGuiCol_HeaderHovered]        = ImGui::ColorConvertU32ToFloat4(g.window.colorhover);
		colors[ImGuiCol_HeaderActive]         = ImGui::ColorConvertU32ToFloat4(g.window.coloractive);
		colors[ImGuiCol_ResizeGrip]           = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_ResizeGripHovered]    = ImGui::ColorConvertU32ToFloat4(g.window.colorhover);
		colors[ImGuiCol_ResizeGripActive]     = ImGui::ColorConvertU32ToFloat4(g.window.coloractive);
		colors[ImGuiCol_PlotLines]            = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
		colors[ImGuiCol_PlotLinesHovered]     = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
		colors[ImGuiCol_PlotHistogram]        = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
		colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
		colors[ImGuiCol_TextSelectedBg]       = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);

		memcpy(&m_default_config, &ImGui::GetStyle(), sizeof(ImGuiStyle));
	}

	void gui::dx_on_tick()
	{
		if (m_is_open)
		{
			//ImGui::PushStyleColor(ImGuiCol_WindowBg, ImGui::ColorConvertU32ToFloat4(g.window.color));
			//ImGui::PushStyleColor(ImGuiCol_CheckMark, ImGui::ColorConvertU32ToFloat4(g.window.colorsec));

			auto& style = ImGui::GetStyle();

			auto& colors                          = style.Colors;
			colors[ImGuiCol_Text]                 = ImGui::ColorConvertU32ToFloat4(g.window.colortext);
			colors[ImGuiCol_WindowBg]             = ImGui::ColorConvertU32ToFloat4(g.window.color);
			colors[ImGuiCol_ChildBg]              = ImGui::ColorConvertU32ToFloat4(g.window.color);
			colors[ImGuiCol_PopupBg]              = ImGui::ColorConvertU32ToFloat4(g.window.colorbg);
			colors[ImGuiCol_Border]               = ImGui::ColorConvertU32ToFloat4(g.window.coloractive);
			colors[ImGuiCol_FrameBg]              = ImGui::ColorConvertU32ToFloat4(g.window.colorbg);
			colors[ImGuiCol_FrameBgHovered]       = ImGui::ColorConvertU32ToFloat4(g.window.colorhover);
			colors[ImGuiCol_FrameBgActive]        = ImGui::ColorConvertU32ToFloat4(g.window.coloractive);
			colors[ImGuiCol_TitleBg]              = ImGui::ColorConvertU32ToFloat4(g.window.colorbg);
			colors[ImGuiCol_TitleBgCollapsed]     = ImGui::ColorConvertU32ToFloat4(g.window.colorbg);
			colors[ImGuiCol_TitleBgActive]        = ImGui::ColorConvertU32ToFloat4(g.window.colorbg);
			colors[ImGuiCol_MenuBarBg]            = ImGui::ColorConvertU32ToFloat4(g.window.colorbg);
			colors[ImGuiCol_ScrollbarBg]          = ImGui::ColorConvertU32ToFloat4(g.window.colorbg);
			colors[ImGuiCol_ScrollbarGrab]        = ImGui::ColorConvertU32ToFloat4(g.window.colorsec);
			colors[ImGuiCol_ScrollbarGrabHovered] = ImGui::ColorConvertU32ToFloat4(g.window.colorhover);
			colors[ImGuiCol_ScrollbarGrabActive]  = ImGui::ColorConvertU32ToFloat4(g.window.coloractive);
			colors[ImGuiCol_CheckMark]            = ImGui::ColorConvertU32ToFloat4(g.window.coloractive);
			colors[ImGuiCol_SliderGrab]           = ImGui::ColorConvertU32ToFloat4(g.window.colorbg);
			colors[ImGuiCol_SliderGrabActive]     = ImGui::ColorConvertU32ToFloat4(g.window.coloractive);
			colors[ImGuiCol_Button]               = ImGui::ColorConvertU32ToFloat4(g.window.colorsec);
			colors[ImGuiCol_ButtonHovered]        = ImGui::ColorConvertU32ToFloat4(g.window.colorhover);
			colors[ImGuiCol_ButtonActive]         = ImGui::ColorConvertU32ToFloat4(g.window.coloractive);
			colors[ImGuiCol_Header]               = ImGui::ColorConvertU32ToFloat4(g.window.colorsec);
			colors[ImGuiCol_HeaderHovered]        = ImGui::ColorConvertU32ToFloat4(g.window.colorhover);
			colors[ImGuiCol_HeaderActive]         = ImGui::ColorConvertU32ToFloat4(g.window.coloractive);
			colors[ImGuiCol_ResizeGripHovered]    = ImGui::ColorConvertU32ToFloat4(g.window.colorhover);
			colors[ImGuiCol_ResizeGripActive]     = ImGui::ColorConvertU32ToFloat4(g.window.coloractive);

			view::root();
			ImGui::PopStyleColor();
		}
	}

	void gui::restore_default_style()
	{
		memcpy(&ImGui::GetStyle(), &m_default_config, sizeof(ImGuiStyle));
	}

	void gui::script_on_tick()
	{
		if (g_gui->m_is_open)
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

		//wndproc will not work here. the timing here is very difficult. mayby can we hook the creation of the pause menu?
		//this should be improved..
		if (is_key_pressed(VK_ESCAPE) && g.cmd_executor.enabled)
		{
			g_fiber_pool->queue_job([] {
				g.cmd_executor.enabled = false;
				//50 should run stable, IMPROVE THIS!!!
				for (uint8_t i = 0; i <= 50; i++)
				{
					HUD::SET_PAUSE_MENU_ACTIVE(false);
					script::get_current()->yield();
				}
			});
		}
	}

	void gui::script_func()
	{
		while (true)
		{
			g_gui->script_on_tick();
			script::get_current()->yield();
		}
	}

	void gui::wndproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
	{
		if (msg == WM_KEYUP && wparam == g.settings.hotkeys.menu_toggle)
		{
			//Persist and restore the cursor position between menu instances.
			static POINT cursor_coords{};
			if (g_gui->m_is_open)
			{
				GetCursorPos(&cursor_coords);
			}
			else if (cursor_coords.x + cursor_coords.y != 0)
			{
				SetCursorPos(cursor_coords.x, cursor_coords.y);
			}

			toggle(g.settings.hotkeys.editing_menu_toggle || !m_is_open);
			if (g.settings.hotkeys.editing_menu_toggle)
				g.settings.hotkeys.editing_menu_toggle = false;
		}
	}

	void gui::toggle_mouse()
	{
		if (m_is_open)
		{
			ImGui::GetIO().MouseDrawCursor = true;
			ImGui::GetIO().ConfigFlags &= ~ImGuiConfigFlags_NoMouse;
		}
		else
		{
			ImGui::GetIO().MouseDrawCursor = false;
			ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NoMouse;
		}
	}
}
