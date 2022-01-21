#include "hooking.hpp"
#include "native_hooks/native_hooks.hpp"

namespace big
{
	GtaThread* hooks::gta_thread_start(unsigned int** a1, unsigned int a2)
	{
		GtaThread* new_thread = g_hooking->m_gta_thread_start_hook.get_original<decltype(&hooks::gta_thread_start)>()(a1, a2);

		if (new_thread != nullptr)
			g_native_hooks->check_for_thread(new_thread);

		return new_thread;
	}
}