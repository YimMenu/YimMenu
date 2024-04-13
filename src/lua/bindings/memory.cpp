#include "memory.hpp"

#include "memory/module.hpp"
#include "memory/pattern.hpp"
#include "pointers.hpp"

namespace lua::memory
{
	pointer::pointer(uint64_t address) :
	    m_address(address)
	{
	}

	pointer::pointer() :
	    m_address(0)
	{
	}

	pointer pointer::add(uint64_t offset)
	{
		return pointer(m_address + offset);
	}

	pointer pointer::sub(uint64_t offset)
	{
		return pointer(m_address - offset);
	}

	pointer pointer::rip()
	{
		return add(*(std::int32_t*)m_address).add(4);
	}

	std::string pointer::get_string()
	{
		return std::string((char*)m_address);
	}

	void pointer::set_string(const std::string& string, int max_length)
	{
		strncpy((char*)m_address, string.data(), max_length);
	}

	bool pointer::is_null()
	{
		return m_address == 0;
	}

	bool pointer::is_valid()
	{
		return !is_null();
	}

	pointer pointer::deref()
	{
		return pointer(*(uint64_t*)m_address);
	}

	uint64_t pointer::get_address() const
	{
		return m_address;
	}

	// Lua API: Table
	// Name: memory
	// Table containing helper functions related to process memory.

	// Lua API: Function
	// Table: memory
	// Name: scan_pattern
	// Param: pattern: string: byte pattern (IDA format)
	// Returns: pointer: A pointer to the found address.
	// Scans the specified memory pattern within the "GTA5.exe" module and returns a pointer to the found address.
	static pointer scan_pattern(const std::string& pattern)
	{
		return pointer(::memory::module("GTA5.exe").scan(::memory::pattern(pattern)).value().as<uint64_t>());
	}

	// Lua API: Function
	// Table: memory
	// Name: handle_to_ptr
	// Param: entity: number: script game entity handle
	// Returns: pointer: A rage::CDynamicEntity pointer to the script game entity handle
	static pointer handle_to_ptr(int entity)
	{
		auto ptr = big::g_pointers->m_gta.m_handle_to_ptr(entity);
		return pointer((uint64_t)ptr);
	}

	// Lua API: Function
	// Table: memory
	// Name: ptr_to_handle
	// Param: mem_addr: pointer: A rage::CDynamicEntity pointer.
	// Returns: number: The script game entity handle linked to the given rage::CDynamicEntity pointer.
	static int ptr_to_handle(pointer mem_addr)
	{
		if (mem_addr.is_null())
			return 0;

		return big::g_pointers->m_gta.m_ptr_to_handle((void*)mem_addr.get_address());
	}

	// Lua API: Function
	// Table: memory
	// Name: allocate
	// Param: size: integer: The number of bytes to allocate on the heap.
	// Returns: pointer: A pointer to the newly allocated memory.
	static pointer allocate(int size, sol::this_state state)
	{
		void* mem = new uint8_t[size]();

		big::lua_module* module = sol::state_view(state)["!this"];
		module->m_allocated_memory.push_back(mem);

		return pointer((uint64_t)mem);
	}

	// Lua API: Function
	// Table: memory
	// Name: free
	// Param: ptr: pointer: The pointer that must be freed.
	static void free(pointer ptr, sol::this_state state)
	{
		delete[] (void*)ptr.get_address();

		big::lua_module* module = sol::state_view(state)["!this"];

		std::erase_if(module->m_allocated_memory, [ptr](void* addr) {
			return ptr.get_address() == (uint64_t)addr;
		});
	}

	void bind(sol::state& state)
	{
		auto ns = state["memory"].get_or_create<sol::table>();

		auto pointer_ut = ns.new_usertype<pointer>("pointer", sol::constructors<pointer(uint64_t)>());

		pointer_ut["add"]         = &pointer::add;
		pointer_ut["sub"]         = &pointer::sub;
		pointer_ut["rip"]         = &pointer::rip;
		pointer_ut["get_byte"]    = &pointer::get<uint8_t>;
		pointer_ut["get_word"]    = &pointer::get<uint16_t>;
		pointer_ut["get_dword"]   = &pointer::get<uint32_t>;
		pointer_ut["get_qword"]   = &pointer::get<uint64_t>;
		pointer_ut["get_float"]   = &pointer::get<float>;
		pointer_ut["get_string"]  = &pointer::get_string;
		pointer_ut["set_byte"]    = &pointer::set<uint8_t>;
		pointer_ut["set_word"]    = &pointer::set<uint16_t>;
		pointer_ut["set_dword"]   = &pointer::set<uint32_t>;
		pointer_ut["set_qword"]   = &pointer::set<uint64_t>;
		pointer_ut["set_float"]   = &pointer::set<float>;
		pointer_ut["set_string"]  = &pointer::set_string;
		pointer_ut["patch_byte"]  = &pointer::patch<uint8_t>;
		pointer_ut["patch_word"]  = &pointer::patch<uint16_t>;
		pointer_ut["patch_dword"] = &pointer::patch<uint32_t>;
		pointer_ut["patch_qword"] = &pointer::patch<uint64_t>;
		pointer_ut["is_null"]     = &pointer::is_null;
		pointer_ut["is_valid"]    = &pointer::is_valid;
		pointer_ut["deref"]       = &pointer::deref;
		pointer_ut["get_address"] = &pointer::get_address;

		auto patch_ut       = ns.new_usertype<big::lua_patch>("patch", sol::no_constructor);
		patch_ut["apply"]   = &big::lua_patch::apply;
		patch_ut["restore"] = &big::lua_patch::restore;

		ns["scan_pattern"]  = scan_pattern;
		ns["handle_to_ptr"] = handle_to_ptr;
		ns["ptr_to_handle"] = ptr_to_handle;
		ns["allocate"]      = allocate;
		ns["free"]          = free;
	}
}