#pragma once
#include "fiber_pool.hpp"
#include "invoker.hpp"
#include "lua/lua_module.hpp"
#include "lua/natives/natives_data.hpp"
#include "util/toxic.hpp"

namespace lua::natives
{
	inline std::vector<std::array<char, 255>> string_pool;
	inline std::vector<uint64_t> pointer_pool;

	static void begin_call(int num_strings, int num_ptrs)
	{
		if (num_strings)
		{
			string_pool.clear();
			string_pool.reserve(num_strings);
		}

		if (num_ptrs)
		{
			pointer_pool.clear();
			pointer_pool.reserve(num_ptrs);
		}

		big::g_native_invoker.begin_call();
	}

	static void push_arg(uint64_t arg)
	{
		big::g_native_invoker.push_arg(arg);
	}

	static void push_string(const std::string& lua_str)
	{
		strncpy(string_pool.end()->data(), lua_str.data(), 255);
		big::g_native_invoker.push_arg(string_pool.end()->data());
	}

	static void push_pointer(uint64_t initial_value)
	{
		pointer_pool.push_back(initial_value);
		big::g_native_invoker.push_arg(&*pointer_pool.end());
	}

	static void end_call(uint64_t native_hash)
	{
		if (native_hash == 0x172AA1B624FA1013)
		{
			big::toxic::explosion_anti_cheat_bypass::m_can_blame_others->apply();
			big::toxic::explosion_anti_cheat_bypass::m_can_use_blocked_explosions->apply();
		}

		big::g_native_invoker.end_call(native_hash);

		if (native_hash == 0x172AA1B624FA1013)
		{
			big::toxic::explosion_anti_cheat_bypass::m_can_blame_others->restore();
			big::toxic::explosion_anti_cheat_bypass::m_can_use_blocked_explosions->restore();
		}

		if (native_hash == 0xAAA34F8A7CB32098)
		{
			if (auto ped = big::g_pointers->m_gta.m_handle_to_ptr(big::g_native_invoker.m_call_context.get_arg<int>(0)))
				big::g_pointers->m_gta.m_clear_ped_tasks_network((CPed*)ped, true);
		}
	}

	static uint64_t get_pointer_value(int pointer_idx)
	{
		if (pointer_idx < pointer_pool.size())
			return pointer_pool[pointer_idx];
		else
			return 0;
	}

	static void bind(sol::state& state)
	{
		auto ns                 = state["_natives"].get_or_create<sol::table>();
		ns["begin_call"]        = begin_call;
		ns["push_arg"]          = push_arg;
		ns["push_string"]       = push_string;
		ns["push_pointer"]      = push_pointer;
		ns["end_call"]          = end_call;
		ns["get_pointer_value"] = get_pointer_value;

		auto result = state.load_buffer(natives_data, sizeof(natives_data) - 1);
		if (!result.valid())
			LOG(FATAL) << "Failed to load natives data: " << result.get<sol::error>().what();

		result();
	}
}