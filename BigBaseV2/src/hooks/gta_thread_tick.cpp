#include "hooking.hpp"
#include "gta/script_thread.hpp"

namespace big
{
	static char struct_backup[sizeof(GtaThread)];
	static char stack_buffer[0xFFFF];

	rage::eThreadState hooks::gta_thread_tick(GtaThread* thread, unsigned int a2)
	{
		rage::eThreadState state = thread->m_context.m_state;

		if (thread->m_script_hash == RAGE_JOAAT("freemode") && state == rage::eThreadState::running && !g->protections.freemode_terminated)
		{
			memcpy(struct_backup, (void*)thread, sizeof(GtaThread));
			if (thread->m_stack)
				memcpy(stack_buffer, thread->m_stack, thread->m_context.m_stack_size);
		}

		rage::eThreadState result = g_hooking->m_gta_thread_tick_hook.get_original<decltype(&gta_thread_tick)>()(thread, a2);

		if (thread->m_script_hash == RAGE_JOAAT("freemode"))
		{
			if (result == rage::eThreadState::killed && state == rage::eThreadState::running && !g->protections.freemode_terminated)
			{
				LOG(INFO) << "Freemode script crashed, attempting recovery...";

				result = rage::eThreadState::running;

				memcpy(thread, struct_backup, sizeof(GtaThread));
				if (thread->m_stack)
					memcpy(thread->m_stack, stack_buffer, thread->m_context.m_stack_size);
			}

			if (g->protections.freemode_terminated) g->protections.freemode_terminated = !(result == rage::eThreadState::running);
		}

		return result;
	}
}