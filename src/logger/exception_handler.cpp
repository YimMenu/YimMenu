#include "exception_handler.hpp"

#include "stack_trace.hpp"

#include <hde64.h>

namespace big
{
	exception_handler::exception_handler()
	{
		m_exception_handler = AddVectoredExceptionHandler(1, &vectored_exception_handler);
	}

	exception_handler::~exception_handler()
	{
		RemoveVectoredExceptionHandler(m_exception_handler);
	}

	inline static stack_trace trace;
	LONG vectored_exception_handler(EXCEPTION_POINTERS* exception_info)
	{
		const auto exception_code = exception_info->ExceptionRecord->ExceptionCode;
		if (exception_code == EXCEPTION_BREAKPOINT || exception_code == DBG_PRINTEXCEPTION_C || exception_code == DBG_PRINTEXCEPTION_WIDE_C)
			return EXCEPTION_CONTINUE_SEARCH;

		trace.new_stack_trace(exception_info);
		LOG(FATAL) << trace;

	
		if (IsBadReadPtr(reinterpret_cast<void*>(exception_info->ContextRecord->Rip), 8))
		{
			auto return_address_ptr = (uint64_t*)exception_info->ContextRecord->Rsp;
			if (IsBadReadPtr(reinterpret_cast<void*>(return_address_ptr), 8))
			{
				LOG(FATAL) << "Cannot resume execution, crashing";
				return EXCEPTION_CONTINUE_SEARCH;
			}
			else
			{
				exception_info->ContextRecord->Rip = *return_address_ptr;
				exception_info->ContextRecord->Rsp += 8;
			}
		}
		else
		{
			hde64s opcode{};
			hde64_disasm(reinterpret_cast<void*>(exception_info->ContextRecord->Rip), &opcode);
			if (opcode.flags & F_ERROR)
			{
				LOG(FATAL) << "Cannot resume execution, crashing";
				return EXCEPTION_CONTINUE_SEARCH;
			}
			exception_info->ContextRecord->Rip += opcode.len;
		}

		return EXCEPTION_CONTINUE_EXECUTION;
	}
}