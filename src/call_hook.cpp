#include "common.hpp"
#include "call_hook.hpp"
#include "memory/handle.hpp"

namespace
{
	big::call_hook_memory g_call_hook_memory;
}

// https://github.com/martonp96/ClosedIV/blob/master/src/utils/memory.h#L64

namespace big
{
	call_hook_memory::call_hook_memory()
	{ 
		m_memory = (uint8_t*)VirtualAlloc((void*)((uintptr_t)GetModuleHandle(0) + 0x20000000), 1024, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
		m_offset = 0;
	}

	call_hook_memory::~call_hook_memory()
	{
		VirtualFree(m_memory, 0, MEM_RELEASE);
	}

	void* call_hook_memory::allocate_jump_sequence(void* func)
	{
		m_offset = m_offset + ((16 - (m_offset % 16)) % 16); // align

		*(int16_t*)&m_memory[m_offset] = 0xB848;
		*(uint64_t*)&m_memory[m_offset+2] = (uint64_t)func;
		*(int16_t*)&m_memory[m_offset+10] = 0xE0FF;

		m_offset += 12;
		return &m_memory[m_offset - 12];
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
