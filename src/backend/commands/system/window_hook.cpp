#include "backend/looped_command.hpp"
#include "memory/byte_patch.hpp"
#include "pointers.hpp"

namespace big
{
	class window_hook : looped_command
	{
		using looped_command::looped_command;

		memory::byte_patch* m_window_hook_patch;

		virtual void on_enable() override
		{
			static auto patch = (m_window_hook_patch = memory::byte_patch::make(g_pointers->m_gta.m_window_hook.as<void*>(), std::to_array({0xC3, 0x90, 0x90, 0x90}))
			                                               .get(),
			    true);

			m_window_hook_patch->apply();
			UnhookWindowsHookEx(*g_pointers->m_gta.m_window_hook.add(45).rip().as<HHOOK*>());
		}

		virtual void on_tick() override
		{
		}

		virtual void on_disable() override
		{
			SetWindowsHookExA(13, g_pointers->m_gta.m_window_hook.add(18).rip().as<HOOKPROC>(), GetModuleHandleA("GTA5.exe"), 0);
			m_window_hook_patch->restore();
		}
	};

	window_hook g_window_hook("windowhook", "GTA Window Hook", "Only enable this if you know what you are doing, this will prevent AHK scripts from working.",
	    g.debug.window_hook);
}
