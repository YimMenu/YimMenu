#include "hooking.hpp"
#include "renderer.hpp"
#include "script.hpp"

namespace big
{
	HRESULT hooks::swapchain_present(IDXGISwapChain* this_, UINT sync_interval, UINT flags)
	{
		TRY_CLAUSE
		{
			if (g_running)
			{
				g_renderer->on_present();
			}

			return g_hooking->m_swapchain_hook.get_original<decltype(&swapchain_present)>(swapchain_present_index)(this_, sync_interval, flags);
		}
		EXCEPT_CLAUSE

		return NULL;
	}
}
