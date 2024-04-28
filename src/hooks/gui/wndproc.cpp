#include "hooking/hooking.hpp"
#include "renderer/renderer.hpp"
#include "script.hpp"

namespace big
{
	LRESULT hooks::wndproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
	{
		if (g_running) [[likely]]
		{
			g_renderer.wndproc(hwnd, msg, wparam, lparam);
		}

		return CallWindowProcW(g_hooking->m_og_wndproc, hwnd, msg, wparam, lparam);
	}
}
