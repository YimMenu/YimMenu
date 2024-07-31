#include "hooking/hooking.hpp"
#include "gta/script_thread.hpp"

namespace big
{
	GtaThread* hooks::gta_thread_start(unsigned int** a1, unsigned int a2)
	{
		GtaThread* new_thread = g_hooking->get_original<hooks::gta_thread_start>()(a1, a2);

		if (const char* name = new_thread->m_name; strlen(name) > 0)
		{
			if (g.notifications.gta_thread_kill.log)
				LOG(INFO) << "Script Thread '" << name << "' started.";
			if (g.notifications.gta_thread_kill.notify)
				g_notification_service.push("Script Thread Startup", std::format("Script Thread '{}' started.", name));
		}

		return new_thread;
	}
}
