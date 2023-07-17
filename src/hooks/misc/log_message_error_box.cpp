#include "hooking.hpp"
#include "pointers.hpp"
#include "util/string_conversions.hpp"
#include "logger/stack_trace.hpp"

namespace big
{
	static stack_trace trace;

	static int log_stack_trace_filter(EXCEPTION_POINTERS* ep)
	{
		trace.new_stack_trace(ep);

		LOG(FATAL) << trace;
		Logger::FlushQueue();

		return EXCEPTION_EXECUTE_HANDLER;
	}

	static void log_stack_trace()
	{
#ifndef CROSSCOMPILING
		__try
		{
			// On purpose to print a stack trace.
			*reinterpret_cast<int*>(0xDEAD) = 0;
		}
		__except (log_stack_trace_filter(GetExceptionInformation()))
		{
		}
#endif
	}

	void hooks::log_error_message_box(rage::joaat_t joaated_error_code, char a2)
	{
		LOG(WARNING) << "Error Code: " <<
			string_conversions::utf_16_to_code_page(
				CP_UTF8,
				g_pointers->m_gta.m_get_title_caption_error_message_box(joaated_error_code));

		log_stack_trace();
	}
}
