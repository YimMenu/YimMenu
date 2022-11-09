#include "common.hpp"
#include "pointers.hpp"
#include "script_local.hpp"
#include "gta\script_thread.hpp"

namespace big
{
	script_local::script_local(rage::scrThread* thread, std::size_t index) :
		m_index(index), m_stack(thread->m_stack)
	{
	}
	script_local::script_local(PVOID stack, std::size_t index) :
		m_index(index), m_stack(stack)
	{
	}

	script_local script_local::at(std::ptrdiff_t index)
	{
		return script_local(m_stack, m_index + index);
	}

	script_local script_local::at(std::ptrdiff_t index, std::size_t size)
	{
		return script_local(m_stack, m_index + 1 + (index * size));
	}

	void *script_local::get()
	{
		return reinterpret_cast<uintptr_t*>((uintptr_t)m_stack + (m_index * sizeof(uintptr_t)));
	}
}
