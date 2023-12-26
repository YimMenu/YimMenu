#include "backend/bool_command.hpp"
#include "memory/byte_patch.hpp"
#include "pointers.hpp"

namespace big
{
	class window_hook : bool_command
	{
		using bool_command::bool_command;

		virtual void refresh() override
		{
			static auto& window_hook_patch = memory::byte_patch::make(g_pointers->m_gta.m_window_hook.as<void*>(), std::to_array({0xC3, 0x90, 0x90, 0x90}));

			if (m_toggle)
			{
				window_hook_patch->apply();
				UnhookWindowsHookEx(*g_pointers->m_gta.m_window_hook.add(45).rip().as<HHOOK*>());
			}
			else
			{
				SetWindowsHookExA(13, g_pointers->m_gta.m_window_hook.add(18).rip().as<HOOKPROC>(), GetModuleHandleA("GTA5.exe"), 0);
				window_hook_patch->restore();
			}
		}
	};

	window_hook g_window_hook("windowhook", "BACKEND_GTA_WINDOW_HOOK", "BACKEND_GTA_WINDOW_HOOK_DESC", g.debug.window_hook);
}
