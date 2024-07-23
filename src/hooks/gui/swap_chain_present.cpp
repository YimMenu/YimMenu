#include "hooking/hooking.hpp"
#include "renderer/renderer.hpp"

namespace big
{
	HRESULT hooks::swapchain_present(IDXGISwapChain* this_, UINT sync_interval, UINT flags)
	{
		if (g_running && ((flags & (UINT)DXGI_PRESENT_TEST) != (UINT)DXGI_PRESENT_TEST))
		{
			g_renderer.on_present();
		}

		return g_hooking->m_swapchain_hook.get_original<decltype(&swapchain_present)>(swapchain_present_index)(this_, sync_interval, flags);
	}
}
