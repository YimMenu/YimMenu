#include "invoker.hpp"
#include "crossmap.hpp"
#include "pointers.hpp"

namespace big
{
	void native_invoker::cache_handlers()
	{
		if (m_are_handlers_cached)
			return;

		for (int i = 0; i < g_crossmap.size(); i++)
		{
			m_handlers[i] = g_pointers->m_gta.m_get_native_handler(g_pointers->m_gta.m_native_registration_table, g_crossmap[i]);
		}

		m_are_handlers_cached = true;
	}

	void native_invoker::fix_vectors()
	{
		for (; m_call_context.m_data_count; m_call_context.m_orig[m_call_context.m_data_count][2].Int = m_call_context.m_buffer[m_call_context.m_data_count].z)
		{
			--m_call_context.m_data_count;
			m_call_context.m_orig[m_call_context.m_data_count]->Int   = m_call_context.m_buffer[m_call_context.m_data_count].x;
			m_call_context.m_orig[m_call_context.m_data_count][1].Int = m_call_context.m_buffer[m_call_context.m_data_count].y;
		}
		--m_call_context.m_data_count;
	}
}
