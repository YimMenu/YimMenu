#pragma once
#include "common.hpp"

namespace big
{
	class gui
	{
	public:
		gui();
		virtual ~gui();
		gui(const gui&)                = delete;
		gui(gui&&) noexcept            = delete;
		gui& operator=(const gui&)     = delete;
		gui& operator=(gui&&) noexcept = delete;

		bool is_open();
		void toggle(bool toggle);

		void dx_init();
		void dx_on_tick();

		void restore_default_style();

		void script_on_tick();
		static void script_func();

		void wndproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

	private:
		void toggle_mouse();

	private:
		bool m_is_open;
		ImGuiStyle m_default_config;
	};

	inline gui* g_gui;
}
