#include "script_function.hpp"

#include "gta_util.hpp"
#include "pointers.hpp"
#include "util/scripts.hpp"

#include <script/scrProgram.hpp>
#include <script/scrProgramTable.hpp>

namespace big
{
	script_function::script_function(const std::string& name, const rage::joaat_t script, const std::string& pattern, int32_t offset) :
	    m_name(name),
	    m_script(script),
	    m_pattern(pattern),
	    m_offset(offset),
	    m_ip(0)
	{
	}

	void script_function::populate_ip()
	{
		if (m_ip == 0)
		{
			auto program = gta_util::find_script_program(m_script);

			if (!program)
				return;

			auto location = scripts::get_code_location_by_pattern(program, m_pattern);

			if (!location)
				LOG(FATAL) << "Failed to find pattern " << m_name << " in script " << program->m_name;
			else
				LOG(VERBOSE) << "Found pattern " << m_name << " in script " << program->m_name;

			m_ip = location.value() + m_offset;
		}
	}

	void script_function::call(rage::scrThread* thread, rage::scrProgram* program, std::initializer_list<std::uint64_t> args)
	{
		auto tls_ctx   = rage::tlsContext::get();
		auto stack     = (uint64_t*)thread->m_stack;
		auto og_thread = tls_ctx->m_script_thread;

		tls_ctx->m_script_thread           = thread;
		tls_ctx->m_is_script_thread_active = true;

		rage::scrThreadContext ctx = thread->m_context;

		for (auto& arg : args)
			stack[ctx.m_stack_pointer++] = arg;

		stack[ctx.m_stack_pointer++] = 0;
		ctx.m_instruction_pointer    = m_ip;
		ctx.m_state                  = rage::eThreadState::idle;

		g_pointers->m_script_vm(stack, g_pointers->m_script_globals, program, &ctx);

		tls_ctx->m_script_thread           = og_thread;
		tls_ctx->m_is_script_thread_active = og_thread != nullptr;
	}

	void script_function::static_call(std::initializer_list<std::uint64_t> args)
	{
		populate_ip();

		rage::scrThread* thread = (rage::scrThread*)new uint8_t[sizeof(rage::scrThread)];
		memcpy(thread, rage::scrThread::get(), sizeof(rage::scrThread));

		void* stack                       = new uint64_t[25000];
		thread->m_stack                   = stack;
		thread->m_context.m_stack_size    = 25000;
		thread->m_context.m_stack_pointer = 1;

		call(thread, gta_util::find_script_program(m_script), args);

		delete[] stack;
		delete[] (uint8_t*)thread; // without the cast it ends up calling the destructor which leads to some pretty funny crashes
	}

	void script_function::operator()(std::initializer_list<std::uint64_t> args)
	{
		populate_ip();

		if (m_ip == 0)
			return;

		auto thread  = gta_util::find_script_thread(m_script);
		auto program = gta_util::find_script_program(m_script);

		if (thread && program)
		{
			call(thread, program, args);
		}
	}
}