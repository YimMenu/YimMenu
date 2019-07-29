#pragma once
#include "common.hpp"
#include "gta/natives.hpp"

namespace big
{
	class native_call_context : public rage::scrNativeCallContext
	{
	public:
		native_call_context();
	private:
		std::uint64_t m_return_stack[10];
		std::uint64_t m_arg_stack[100];
	};

	class native_invoker
	{
	public:
		explicit native_invoker() = default;
		~native_invoker() = default;

		void cache_handlers();

		void begin_call();
		void end_call(rage::scrNativeHash hash);

		template <typename T>
		void push_arg(T &&value)
		{
			m_call_context.push_arg(std::forward<T>(value));
		}

		template <typename T>
		T &get_return_value()
		{
			return *m_call_context.get_return_value<T>();
		}
	private:
		native_call_context m_call_context;
		std::unordered_map<rage::scrNativeHash, rage::scrNativeHandler> m_handler_cache;
	};

	inline native_invoker g_native_invoker;
}
