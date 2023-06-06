#pragma once
#include "invoker.hpp"
#include "lua/lua_module.hpp"
#include "lua/natives/natives_data.hpp"
#include "memory.hpp"

namespace lua::native
{
	template<typename T>
	T invoke(sol::variadic_args args)
	{
		big::g_native_invoker.begin_call();

		for (int i = 1; i < args.size(); i++)
		{
			if (args[i].is<memory::pointer>())
				big::g_native_invoker.push_arg(args[i].get<memory::pointer>().get_address());
			else if (args[i].is<int>())
				big::g_native_invoker.push_arg(args[i].get<int>());
			else if (args[i].is<float>())
				big::g_native_invoker.push_arg(args[i].get<float>());
			else if (args[i].is<bool>())
				big::g_native_invoker.push_arg(args[i].get<bool>());
			else if (args[i].is<const char*>())
				big::g_native_invoker.push_arg(args[i].get<const char*>());
			else if (args[i].is<rage::fvector3>())
			{
				auto vec = args[i].get<rage::fvector3>();
				big::g_native_invoker.push_arg(vec.x);
				big::g_native_invoker.push_arg(vec.y);
				big::g_native_invoker.push_arg(vec.z);
			}
			else
			{
				LOG(FATAL) << "Unhandled parameter";
				return T();
			}
		}

		big::g_native_invoker.end_call(args[0].as<std::uint64_t>());

		if constexpr (std::is_same_v<T, std::string>)
		{
			return std::string(big::g_native_invoker.get_return_value<const char*>());
		}
		else if constexpr (std::is_same_v<T, rage::fvector3>)
		{
			auto& vec = big::g_native_invoker.get_return_value<Vector3>();
			return {vec.x, vec.y, vec.z};
		}
		else if constexpr (std::is_same_v<T, memory::pointer>)
		{
			return memory::pointer(big::g_native_invoker.get_return_value<std::uint64_t>());
		}
		else if constexpr (!std::is_void_v<T>)
		{
			return big::g_native_invoker.get_return_value<T>();
		}
	}

	void bind(sol::state& state)
	{
		auto ns            = state["_natives"].get_or_create<sol::table>();
		ns["invoke_void"]  = invoke<void>;
		ns["invoke_int"]   = invoke<int>;
		ns["invoke_float"] = invoke<float>;
		ns["invoke_bool"]  = invoke<bool>;
		ns["invoke_str"]   = invoke<std::string>;
		ns["invoke_vec3"]  = invoke<rage::fvector3>;
		ns["invoke_ptr"]   = invoke<memory::pointer>;

		auto result = state.load_buffer(natives_data, natives_size);
		if (!result.valid())
			LOG(FATAL) << "Failed to load natives data: " << result.get<sol::error>().what();

		result();
	}
}