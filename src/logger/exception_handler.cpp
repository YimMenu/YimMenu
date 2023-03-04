#include "exception_handler.hpp"

#include "stack_trace.hpp"

#include <Zydis/Zydis.h>

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

		ZyanU64 opcode_address = exception_info->ContextRecord->Rip;
		ZydisDisassembledInstruction instruction;
		ZydisDisassembleIntel(ZYDIS_MACHINE_MODE_LONG_64, opcode_address, reinterpret_cast<void*>(opcode_address), 32, &instruction);

		exception_info->ContextRecord->Rip += instruction.info.length;

		return EXCEPTION_CONTINUE_EXECUTION;
	}
}