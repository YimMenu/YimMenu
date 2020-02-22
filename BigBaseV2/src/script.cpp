#pragma once
#include "common.hpp"
#include "logger.hpp"
#include "script.hpp"

namespace big
{
	void script::script_exception_handler(PEXCEPTION_POINTERS exp)
	{
		HMODULE mod{};
		DWORD64 offset{};
		char buffer[MAX_PATH]{};
		if (GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, (LPCWSTR)exp->ExceptionRecord->ExceptionAddress, &mod) == TRUE && mod != nullptr)
		{
			offset = ((DWORD64)exp->ExceptionRecord->ExceptionAddress - (DWORD64)mod);
			GetModuleFileNameA(mod, buffer, MAX_PATH - 1);
		}
		LOG(FATAL) << "Exception Code: " << HEX_TO_UPPER(exp->ExceptionRecord->ExceptionCode) << " Exception Offset: " << HEX_TO_UPPER(offset) << " Fault Module Name: " << buffer;
	}

	script::script(func_t func, std::optional<std::size_t> stack_size) :
		m_func(func),
		m_script_fiber(nullptr),
		m_main_fiber(nullptr)
	{
		m_script_fiber = CreateFiber(stack_size.has_value() ? stack_size.value() : 0, [](void* param)
		{
			auto this_script = static_cast<script*>(param);
			this_script->fiber_func();
		}, this);
	}

	script::~script()
	{
		if (m_script_fiber)
			DeleteFiber(m_script_fiber);
	}

	void script::tick()
	{
		m_main_fiber = GetCurrentFiber();
		if (!m_wake_time.has_value() || m_wake_time.value() <= std::chrono::high_resolution_clock::now())
		{
			SwitchToFiber(m_script_fiber);
		}
	}

	void script::yield(std::optional<std::chrono::high_resolution_clock::duration> time)
	{
		if (time.has_value())
		{
			m_wake_time = std::chrono::high_resolution_clock::now() + time.value();
		}
		else
		{
			m_wake_time = std::nullopt;
		}

		SwitchToFiber(m_main_fiber);
	}

	script* script::get_current()
	{
		return static_cast<script*>(GetFiberData());
	}

	void script::fiber_func()
	{
		TRY_CLAUSE
		{
			m_func();
		}
			EXCEPT_CLAUSE

			[]() {
			LOG(INFO) << "Script finished!";
		}();

		while (true)
		{
			yield();
		}
	}
}
