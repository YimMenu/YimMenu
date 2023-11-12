#include "call_hook.hpp"

namespace
{
	big::call_hook_memory g_call_hook_memory;
}

// https://github.com/martonp96/ClosedIV/blob/master/src/utils/memory.h#L64

namespace big
{
	call_hook_memory::call_hook_memory()
	{ 
		m_memory = VirtualAlloc((void*)((uintptr_t)GetModuleHandle(0) + 0x20000000), 1024, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
		m_offset = 0;
	}

	call_hook_memory::~call_hook_memory()
	{
		VirtualFree(m_memory.as<void*>(), 0, MEM_RELEASE);
	}

	void* call_hook_memory::allocate_jump_sequence(void* func)
	{
		m_offset = m_offset + ((16 - (m_offset % 16)) % 16); // align

		*m_memory.add(m_offset).as<int16_t*>() = 0xB848;
		*m_memory.add(m_offset).add(2).as<void**>() = func;
		*m_memory.add(m_offset).add(10).as<int16_t*>() = 0xE0FF;

		m_offset += 12;

		return m_memory.add(m_offset).sub(12).as<void*>();
	}

	call_hook::call_hook(void* location, void* hook) :
	    m_location(location),
	    m_hook(hook)
	{
		auto seq = g_call_hook_memory.allocate_jump_sequence(hook);
		m_patched_bytes[0] = 0xE8;
		*(int32_t*)&m_patched_bytes[1] = (int32_t)((uint64_t)seq - (uint64_t)location - 5);
		memcpy(m_original_bytes, location, 5);
		m_original_function = memory::handle(location).add(1).rip().as<void*>();
	}

	call_hook::~call_hook()
	{
		disable();
	}

	void call_hook::enable()
	{
		memcpy(m_location, m_patched_bytes, 5);
	}

	void call_hook::disable()
	{
		memcpy(m_location, m_original_bytes, 5);
	}
}
