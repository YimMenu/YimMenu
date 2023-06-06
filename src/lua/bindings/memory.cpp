#include "memory.hpp"

#include "memory/module.hpp"
#include "memory/pattern.hpp"
#include "pointers.hpp"

namespace lua::memory
{
	pointer scan_pattern(const std::string& pattern)
	{
		return pointer(::memory::module("GTA5.exe").scan(::memory::pattern(pattern)).value().as<uint64_t>());
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

		return big::g_pointers->m_gta.m_ptr_to_handle((void*)mem_addr.get_address());
	}

	pointer allocate(int size, sol::this_state state)
	{
		void* mem   = new uint8_t[](size);
		auto module = sol::state_view(state)["!this"].get<big::lua_module*>();
		module->m_allocated_memory.push_back(mem);
		return pointer((uint64_t)mem);
	}

	void free(pointer ptr, sol::this_state state)
	{
		delete[] (void*)ptr.get_address();
		auto module = sol::state_view(state)["!this"].get<big::lua_module*>();
		std::erase_if(module->m_allocated_memory, [ptr](void* addr) {
			return ptr.get_address() == (uint64_t)addr;
		});
	}
}