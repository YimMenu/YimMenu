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

		bool mouse_override() const
		{
			return m_override_mouse;
		}
		/**
		 * @brief Forces the mouse to draw and disable camera controls of the game
		 * This function works for now but might start causing issues when more features start relying on it.
		 */
		void override_mouse(bool override);

		void dx_init();
		void dx_on_tick();

		void save_default_style();
		void restore_default_style();

		void push_theme_colors();
		void pop_theme_colors();

		void script_on_tick();
		static void script_func();

		void wndproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

	private:
		void toggle_mouse();

	private:
		bool m_is_open;
		bool m_override_mouse;

		ImGuiStyle m_default_config;
	};

	inline gui* g_gui;
}
