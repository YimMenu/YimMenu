#pragma once
#include "invoker.hpp"
#include "lua/lua_module.hpp"

namespace lua::native
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

	uint64_t end_call(uint64_t native_hash);

	static uint64_t get_pointer_value(int pointer_idx)
	{
		if (pointer_idx < pointer_pool.size())
			return pointer_pool[pointer_idx];
		else
			return 0;
	}

	void bind(sol::state& state);
}