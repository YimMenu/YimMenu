#pragma once
#include "crossmap.hpp"

#include <script/scrNativeHandler.hpp>

namespace big
{
	class custom_call_context : public rage::scrNativeCallContext
	{
	public:
		constexpr custom_call_context()
		{
			m_return_value = &m_return_stack[0];
			m_args         = &m_arg_stack[0];
		}

	private:
		uint64_t m_return_stack[10];
		uint64_t m_arg_stack[40];
	};

	class native_invoker
	{
		static inline rage::scrNativeHandler m_handlers[g_crossmap.size()];
		static inline bool m_are_handlers_cached{false};

	public:
		constexpr native_invoker(){};

		constexpr void begin_call()
		{
			m_call_context.reset();
		}

		template<int index, bool should_fix_vectors>
		constexpr void end_call()
		{
			// TODO: try to get rid of this
			[[assume((cache_handlers(), m_are_handlers_cached == true))]]
			if (!m_are_handlers_cached) [[unlikely]]
				cache_handlers();

			m_handlers[index](&m_call_context);
			if constexpr (should_fix_vectors)
				fix_vectors();
		}

		template<typename T>
		constexpr void push_arg(T&& value)
		{
			m_call_context.push_arg(std::forward<T>(value));
		}

		template<typename T>
		constexpr T& get_return_value()
		{
			return *m_call_context.get_return_value<T>();
		}

		void fix_vectors();

	public:
		static void __declspec(noinline) cache_handlers();

		static rage::scrNativeHandler* get_handlers()
		{
			[[assume((cache_handlers(), m_are_handlers_cached == true))]]
			if (!m_are_handlers_cached) [[unlikely]]
				cache_handlers();

			return m_handlers;
		}

		template<int index, bool fix_vectors, typename Ret, typename... Args>
		static constexpr FORCEINLINE Ret invoke(Args&&... args)
		{
			native_invoker invoker{};

			invoker.begin_call();
			(invoker.push_arg(std::forward<Args>(args)), ...);
			invoker.end_call<index, fix_vectors>();

			if constexpr (!std::is_same_v<Ret, void>)
			{
				return invoker.get_return_value<Ret>();
			}
		}

		custom_call_context m_call_context{};
	};
}
