#pragma once
#include "script.hpp"

namespace big
{
	script::script(const func_t func, const std::string& name, const bool toggleable, const std::optional<std::size_t> stack_size) :
	    script(func, stack_size)
	{
		m_name       = name;
		m_toggleable = toggleable;
	}

	script::script(const func_t func, const std::optional<std::size_t> stack_size) :
	    m_enabled(true),
	    m_toggleable(false),
	    m_script_fiber(nullptr),
	    m_main_fiber(nullptr),
	    m_func(func),
	    m_done(false)
	{
		m_script_fiber = CreateFiber(
		    stack_size.has_value() ? stack_size.value() : 0,
		    [](void* param) {
			    auto this_script = static_cast<script*>(param);
			    this_script->fiber_func();
		    },
		    this);
	}

	script::~script()
	{
		if (m_script_fiber)
			DeleteFiber(m_script_fiber);
	}

	const char* script::name() const
	{
		return m_name.data();
	}

	bool script::is_enabled() const
	{
		return m_enabled;
	}

	void script::set_enabled(const bool toggle)
	{
		if (m_toggleable)
			m_enabled = toggle;
	}

	bool* script::toggle_ptr()
	{
		return &m_enabled;
	}

	bool script::is_toggleable() const
	{
		return m_toggleable;
	}

	bool script::is_done() const
	{
		return m_done;
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
		m_func();

		m_done = true;

		while (true)
		{
			yield();
		}
	}
}