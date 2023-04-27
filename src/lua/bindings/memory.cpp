#include "memory.hpp"

#include "memory/module.hpp"
#include "memory/pattern.hpp"
#include "pointers.hpp"

namespace lua::memory
{
	pointer scan_pattern(const std::string& pattern)
	{
		return pointer(::memory::module("GTA5.exe").scan(::memory::pattern(pattern)).as<uint64_t>());
	}

	pointer handle_to_ptr(int entity)
	{
		auto ptr = big::g_pointers->m_gta.m_handle_to_ptr(entity);
		return pointer((uint64_t)ptr);
	}

	int ptr_to_handle(pointer mem_addr)
	{
		if (mem_addr.is_null())
			return 0;

		return big::g_pointers->m_gta.m_ptr_to_handle((void*)mem_addr.m_address);
	}
}