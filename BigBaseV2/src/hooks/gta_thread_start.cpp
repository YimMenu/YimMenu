#include "hooking.hpp"
#include "native_hooks/native_hooks.hpp"

namespace big
{
	GtaThread* hooks::gta_thread_start(unsigned int** a1, unsigned int a2)
	{
		GtaThread* new_thread = g_hooking->m_gta_thread_start_hook.get_original<decltype(&hooks::gta_thread_start)>()(a1, a2);

		if (const char* name = new_thread->m_name; strlen(name) > 0)
		{
			if (g->notifications.gta_thread_kill.log)
				LOG(INFO) << "Script Thread '" << name << "' started.";
			if (g->notifications.gta_thread_kill.notify)
				g_notification_service->push("Script Thread Startup", fmt::format("Script Thread '{}' started.", name));
		}

		if (new_thread != nullptr)
			g_native_hooks->check_for_thread(new_thread);

		return new_thread;
	}
}