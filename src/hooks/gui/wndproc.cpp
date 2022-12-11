#include "hooking.hpp"
#include "renderer.hpp"
#include "script.hpp"
#include "services/hotkey/hotkey_service.hpp"

namespace big
{
	LRESULT hooks::wndproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
	{
		TRY_CLAUSE
		{
			if (g_running)
			{
				g_renderer->wndproc(hwnd, msg, wparam, lparam);
				g_hotkey_service->wndproc(static_cast<eKeyState>(msg), wparam);
			}

			return CallWindowProcW(g_hooking->m_og_wndproc, hwnd, msg, wparam, lparam);
		} EXCEPT_CLAUSE

		return NULL;
	}
}
