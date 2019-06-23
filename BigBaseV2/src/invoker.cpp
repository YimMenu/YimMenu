#include "common.hpp"
#include "crossmap.hpp"
#include "invoker.hpp"
#include "logger.hpp"
#include "pointers.hpp"

namespace big
{
	native_call_context::native_call_context()
	{
		m_return_value = &m_return_stack[0];
		m_args = &m_arg_stack[0];
	}

	bool native_invoker::map_native(rage::scrNativeHash *hash)
	{
		for (auto const &mapping : g_crossmap)
		{
			if (mapping.first == *hash)
			{
				*hash = mapping.second;
				return true;
			}
		}

		return false;
	}

	void native_invoker::begin_call()
	{
		m_call_context.reset();
	}

	void native_invoker::end_call(rage::scrNativeHash hash)
	{
		map_native(&hash);
		if (auto handler = g_pointers->m_get_native_handler(g_pointers->m_native_registration_table, hash))
		{
			__try
			{
				handler(&m_call_context);
				g_pointers->m_fix_vectors(&m_call_context);
			}
			__except (EXCEPTION_EXECUTE_HANDLER)
			{
				LOG_ERROR("Exception caught while trying to call 0x{:X} native.", hash);
			}
		}
		else
		{
			LOG_ERROR("Failed to find 0x{:X} native's handler.", hash);
		}
	}
}
