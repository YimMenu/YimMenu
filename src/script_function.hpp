#pragma once

#include "gta_util.hpp"
#include "pointers.hpp"
#include "util/scripts.hpp"

#include <script/scrProgram.hpp>

namespace big
{
	class script_function
	{
		rage::joaat_t m_script;
		const memory::pattern m_pattern;
		int32_t m_ip;
		std::string m_name;

	public:
		script_function(const std::string& name, const rage::joaat_t script, const std::string& pattern);	
		void populate_ip();

		template<typename Arg>
		void push_arg(uint64_t* stack, uint32_t& stack_pointer, Arg&& value)
		{
			*reinterpret_cast<std::remove_cv_t<std::remove_reference_t<Arg>>*>(reinterpret_cast<uint64_t*>(stack) + (stack_pointer++)) = std::forward<Arg>(value);
		}

		template<typename Ret, typename... Args>
		Ret call(Args... args)
		{
			auto thread  = gta_util::find_script_thread(m_script);
			auto program = gta_util::find_script_program(m_script);
			populate_ip();

			if (!thread || !program || !m_ip)
				return Ret();

			auto tls_ctx                       = rage::tlsContext::get();
			auto stack                         = (uint64_t*)thread->m_stack;
			auto og_thread                     = tls_ctx->m_script_thread;
			tls_ctx->m_script_thread           = thread;
			tls_ctx->m_is_script_thread_active = true;
			rage::scrThreadContext ctx         = thread->m_context;
			auto top_stack                     = ctx.m_stack_pointer; // This will be the top item in the stack after the args and return address are cleaned off

			(push_arg(stack, ctx.m_stack_pointer, std::forward<Args>(args)), ...);

			stack[ctx.m_stack_pointer++] = 0;
			ctx.m_instruction_pointer    = m_ip;
			ctx.m_state                  = rage::eThreadState::idle;

			g_pointers->m_gta.m_script_vm(stack, g_pointers->m_gta.m_script_globals, program, &ctx);

			tls_ctx->m_script_thread           = og_thread;
			tls_ctx->m_is_script_thread_active = og_thread != nullptr;

			if constexpr (!std::is_same_v<Ret, void>)
			{
				return *reinterpret_cast<Ret*>(stack + top_stack);
			}
		}

		template<typename Ret, typename... Args>
		Ret call(rage::joaat_t script, uint32_t ip, Args... args)
		{
			auto thread  = gta_util::find_script_thread(script);
			auto program = gta_util::find_script_program(script);

			if (!thread || !program)
				return Ret();

			auto tls_ctx                       = rage::tlsContext::get();
			auto stack                         = (uint64_t*)thread->m_stack;
			auto og_thread                     = tls_ctx->m_script_thread;
			tls_ctx->m_script_thread           = thread;
			tls_ctx->m_is_script_thread_active = true;
			rage::scrThreadContext ctx         = thread->m_context;
			auto top_stack                     = ctx.m_stack_pointer;

			(push_arg(stack, ctx.m_stack_pointer, std::forward<Args>(args)), ...);

			stack[ctx.m_stack_pointer++] = 0;
			ctx.m_instruction_pointer    = ip;
			ctx.m_state                  = rage::eThreadState::idle;

			g_pointers->m_gta.m_script_vm(stack, g_pointers->m_gta.m_script_globals, program, &ctx);

			tls_ctx->m_script_thread           = og_thread;
			tls_ctx->m_is_script_thread_active = og_thread != nullptr;

			if constexpr (!std::is_same_v<Ret, void>)
			{
				return *reinterpret_cast<Ret*>(stack + top_stack);
			}
		}
	};

	static inline script_function set_as_ceo("SAC", "freemode"_J, "2D 04 1D 00 00 5D");
	static inline script_function set_freemode_session_active("SFSA", "freemode"_J, "2D 00 02 00 00 75 5D ? ? ? 50");
	static inline script_function save_to_datafile("STD", "fm_race_creator"_J, "2D 01 03 00 00 71 2C");
	static inline script_function load_from_datafile("LFD", "fm_race_creator"_J, "2D 04 0D 00 00 71 2C");
	static inline script_function reset_session_data("RSD", "pausemenu_multiplayer"_J, "2D 02 7D 00 00");
	static inline script_function add_clan_logo_to_vehicle("ACLTV", "main_persistent"_J, "2D 02 04 00 00 5D ? ? ? 61");
}