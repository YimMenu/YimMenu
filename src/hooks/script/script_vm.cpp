#include "hooking.hpp"
#include <script/scrProgram.hpp>

#include "services/script_patcher/script_patcher_service.hpp"

namespace big
{
	rage::eThreadState hooks::script_vm(uint64_t* start_stack, uint64_t** scr_globals, rage::scrProgram* program, rage::scrThreadContext* ctx)
	{
		uint8_t** orig_bytecode = program->m_code_blocks;

		if (auto bytecode = g_script_patcher_service.get_script_bytecode(program->m_name_hash))
			program->m_code_blocks = bytecode;

		auto ret = g_hooking->get_original<hooks::script_vm>()(start_stack, scr_globals, program, ctx);

		program->m_code_blocks = orig_bytecode;
		return ret;
	}
}