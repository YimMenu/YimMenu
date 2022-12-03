#include "script_function.hpp"
#include "pointers.hpp"
#include "gta_util.hpp"
#include <script/scrProgram.hpp>
#include <script/scrProgramTable.hpp>

namespace big
{
	const std::optional<uint32_t> script_function::get_code_location_by_pattern(rage::scrProgram* program, const memory::pattern& pattern)
	{
		std::uint32_t code_size = program->m_code_size;
		for (std::uint32_t i = 0; i < (code_size - pattern.m_bytes.size()); i++)
		{
			for (std::uint32_t j = 0; j < pattern.m_bytes.size(); j++)
				if (pattern.m_bytes[j].has_value())
					if (pattern.m_bytes[j].value() != *program->get_code_address(i + j))
						goto incorrect;

			return i;
incorrect:
			continue;
		}

		return std::nullopt;
	}

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

			auto location = get_code_location_by_pattern(program, m_pattern);
			
			if (!location)
				LOG(FATAL) << "Failed to find pattern " << m_name << " in script " << program->m_name;
			else
				LOG(DEBUG) << "Found pattern " << m_name << " in script " << program->m_name;

			m_ip = location.value() + m_offset;
		}
	}

	void script_function::call(rage::scrThread* thread, rage::scrProgram* program, std::initializer_list<std::uint64_t> args)
	{
		auto tls_ctx = rage::tlsContext::get();
		auto stack = (uint64_t*)thread->m_stack;
		auto og_thread = tls_ctx->m_script_thread;

		tls_ctx->m_script_thread = thread;
		tls_ctx->m_is_script_thread_active = true;

		rage::scrThreadContext ctx = thread->m_context;

		for (auto& arg : args)
			stack[ctx.m_stack_pointer++] = arg;

		stack[ctx.m_stack_pointer++] = 0;
		ctx.m_instruction_pointer = m_ip;
		ctx.m_state = rage::eThreadState::idle;

		g_pointers->m_script_vm(stack, g_pointers->m_script_globals, program, &ctx);

		tls_ctx->m_script_thread = og_thread;
		tls_ctx->m_is_script_thread_active = og_thread != nullptr;
	}

	void script_function::operator()(std::initializer_list<std::uint64_t> args)
	{
		populate_ip();

		if (m_ip == 0)
			return;

		auto thread = gta_util::find_script_thread(m_script);
		auto program = gta_util::find_script_program(m_script);

		if (thread && program)
		{
			call(thread, program, args);
		}
	}
}