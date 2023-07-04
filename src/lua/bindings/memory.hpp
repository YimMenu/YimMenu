#pragma once
#include "lua/lua_module.hpp"
#include "lua/lua_patch.hpp"
#include "lua/sol.hpp"
#include "memory/byte_patch.hpp"

namespace lua::memory
{
	// Lua API: Class
	// Name: pointer
	// Class representing a 64-bit memory address.

	struct pointer
	{
	private:
		std::uint64_t m_address;

	public:

		// Lua API: Constructor
		// Class: pointer
		// Param: address: integer: Address
		// Returns a memory instance, with the given address.
		explicit pointer(std::uint64_t address) :
		    m_address(address)
		{
		}

		explicit pointer() :
		    m_address(0)
		{
		}

		// Lua API: Function
		// Class: pointer
		// Name: add
		// Param: offset: integer: offset
		// Returns: pointer: new pointer object.
		// Adds an offset to the current memory address and returns a new pointer object.
		pointer add(uint64_t offset)
		{
			return pointer(m_address + offset);
		}

		// Lua API: Function
		// Class: pointer
		// Name: sub
		// Param: offset: integer: offset
		// Returns: pointer: new pointer object.
		// Subs an offset to the current memory address and returns a new pointer object.
		pointer sub(uint64_t offset)
		{
			return pointer(m_address - offset);
		}

		// Lua API: Function
		// Class: pointer
		// Name: rip
		// Param: offset: integer: offset
		// Returns: pointer: new pointer object.
		// Rips the current memory address and returns a new pointer object.
		pointer rip()
		{
			return add(*(std::int32_t*)m_address).add(4);
		}

		// Lua API: Function
		// Class: pointer
		// Name: get_byte
		// Returns: number: the value stored at the memory address as the specified type.
		// Retrieves the value stored at the memory address as the specified type.

		// Lua API: Function
		// Class: pointer
		// Name: get_word
		// Returns: number: the value stored at the memory address as the specified type.
		// Retrieves the value stored at the memory address as the specified type.

		// Lua API: Function
		// Class: pointer
		// Name: get_dword
		// Returns: number: the value stored at the memory address as the specified type.
		// Retrieves the value stored at the memory address as the specified type.

		// Lua API: Function
		// Class: pointer
		// Name: get_float
		// Returns: float: the value stored at the memory address as the specified type.
		// Retrieves the value stored at the memory address as the specified type.

		// Lua API: Function
		// Class: pointer
		// Name: get_qword
		// Returns: number: the value stored at the memory address as the specified type.
		// Retrieves the value stored at the memory address as the specified type.

		template<typename T>
		T get()
		{
			return *(T*)m_address;
		}

		// Lua API: Function
		// Class: pointer
		// Name: set_byte
		// Param: value: number: new value.
		// Sets the value at the memory address to the specified value of the given type.

		// Lua API: Function
		// Class: pointer
		// Name: set_word
		// Param: value: number: new value.
		// Sets the value at the memory address to the specified value of the given type.

		// Lua API: Function
		// Class: pointer
		// Name: set_dword
		// Param: value: number: new value.
		// Sets the value at the memory address to the specified value of the given type.

		// Lua API: Function
		// Class: pointer
		// Name: set_float
		// Param: value: float: new value.
		// Sets the value at the memory address to the specified value of the given type.

		// Lua API: Function
		// Class: pointer
		// Name: set_qword
		// Param: value: number: new value.
		// Sets the value at the memory address to the specified value of the given type.

		template<typename T>
		void set(T value)
		{
			*(T*)m_address = value;
		}

		// Lua API: Function
		// Class: pointer
		// Name: get_string
		// Returns: string: the value stored at the memory address as the specified type.
		// Retrieves the value stored at the memory address as the specified type.
		std::string get_string()
		{
			return std::string((char*)m_address);
		}

		// Lua API: Function
		// Class: pointer
		// Name: set_string
		// Param: value: string: new value.
		// Sets the value at the memory address to the specified value of the given type.
		void set_string(const std::string& string, int max_length)
		{
			strncpy((char*)m_address, string.data(), max_length);
		}

		// Lua API: Function
		// Class: pointer
		// Name: patch_byte
		// Param: value: number: new value.
		// Returns: lua_patch: memory patch instance for modifying the value at the memory address with the specified value. Can call apply / restore on the object.
		// Creates a memory patch for modifying the value at the memory address with the specified value.
		// The modified value is applied when you call the apply function on the lua_patch object.
		// The original value is restored when you call the restore function on the lua_patch object.

		// Lua API: Function
		// Class: pointer
		// Name: patch_word
		// Param: value: number: new value.
		// Returns: lua_patch: memory patch instance for modifying the value at the memory address with the specified value. Can call apply / restore on the object.
		// Creates a memory patch for modifying the value at the memory address with the specified value.
		// The modified value is applied when you call the apply function on the lua_patch object.
		// The original value is restored when you call the restore function on the lua_patch object.

		// Lua API: Function
		// Class: pointer
		// Name: patch_dword
		// Param: value: number: new value.
		// Returns: lua_patch: memory patch instance for modifying the value at the memory address with the specified value. Can call apply / restore on the object.
		// Creates a memory patch for modifying the value at the memory address with the specified value.
		// The modified value is applied when you call the apply function on the lua_patch object.
		// The original value is restored when you call the restore function on the lua_patch object.

		// Lua API: Function
		// Class: pointer
		// Name: patch_qword
		// Param: value: number: new value.
		// Returns: lua_patch: memory patch instance for modifying the value at the memory address with the specified value. Can call apply / restore on the object.
		// Creates a memory patch for modifying the value at the memory address with the specified value.
		// The modified value is applied when you call the apply function on the lua_patch object.
		// The original value is restored when you call the restore function on the lua_patch object.

		template<typename T>
		big::lua_patch* patch(T value, sol::this_state state)
		{
			auto module = sol::state_view(state)["!this"].get<big::lua_module*>();
			auto patch  = std::make_shared<big::lua_patch>(::memory::byte_patch::make((T*)m_address, value).get());
			auto raw    = patch.get();
			module->m_registered_patches.push_back(std::move(patch));
			return raw;
		}

		// Lua API: Function
		// Class: pointer
		// Name: is_null
		// Returns: boolean: Returns true if the address is null.
		bool is_null()
		{
			return m_address == 0;
		}

		// Lua API: Function
		// Class: pointer
		// Name: is_valid
		// Returns: boolean: Returns true if the address is not null.
		bool is_valid()
		{
			return !is_null();
		}

		// Lua API: Function
		// Class: pointer
		// Name: deref
		// Returns: pointer: A new pointer object pointing to the value at that address.
		// Dereferences the memory address and returns a new pointer object pointing to the value at that address.
		pointer deref()
		{
			return pointer(*(uint64_t*)m_address);
		}

		// Lua API: Function
		// Class: pointer
		// Name: get_address
		// Returns: number: The memory address stored in the pointer object as a number.
		// Retrieves the memory address stored in the pointer object.
		uint64_t get_address() const
		{
			return m_address;
		}
	};

	// Lua API: Table
	// Name: memory
	// Table containing helper functions related to process memory.

	// Lua API: Function
	// Table: memory
	// Name: scan_pattern
	// Param: pattern: string: byte pattern (IDA format)
	// Returns: pointer: A pointer to the found address.
	// Scans the specified memory pattern within the "GTA5.exe" module and returns a pointer to the found address.
	pointer scan_pattern(const std::string& pattern);

	// Lua API: Function
	// Table: memory
	// Name: handle_to_ptr
	// Param: entity: number: script game entity handle
	// Returns: pointer: A rage::CDynamicEntity pointer to the script game entity handle
	pointer handle_to_ptr(int entity);

	// Lua API: Function
	// Table: memory
	// Name: ptr_to_handle
	// Param: mem_addr: pointer: A rage::CDynamicEntity pointer.
	// Returns: number: The script game entity handle linked to the given rage::CDynamicEntity pointer.
	int ptr_to_handle(pointer mem_addr);

	// Lua API: Function
	// Table: memory
	// Name: allocate
	// Param: size: integer: The number of bytes to allocate on the heap.
	// Returns: pointer: A pointer to the newly allocated memory.
	pointer allocate(int size, sol::this_state state);

	// Lua API: Function
	// Table: memory
	// Name: free
	// Param: ptr: pointer: The pointer that must be freed.
	void free(pointer ptr, sol::this_state state);

	static void bind(sol::state& state)
	{
		auto ns = state["memory"].get_or_create<sol::table>();

		// clang-format off
		ns.new_usertype<pointer>("pointer", sol::constructors<pointer(std::uint64_t)>(),
			"add", &pointer::add, 
			"sub", &pointer::sub, 
			"rip", &pointer::rip, 
			"get_byte", &pointer::get<uint8_t>,
			"get_word", &pointer::get<uint16_t>,
			"get_dword", &pointer::get<uint32_t>,
			"get_float", &pointer::get<float>,
			"get_qword", &pointer::get<uint64_t>,
			"get_string", &pointer::get_string,
			"set_byte", &pointer::set<uint8_t>,
			"set_word", &pointer::set<uint16_t>,
			"set_dword", &pointer::set<uint32_t>,
			"set_float", &pointer::set<float>,
			"set_qword", &pointer::set<uint64_t>,
			"set_string", &pointer::set_string,
			"patch_byte", &pointer::patch<uint8_t>,
			"patch_word", &pointer::patch<uint16_t>,
			"patch_dword", &pointer::patch<uint32_t>,
			"patch_qword", &pointer::patch<uint64_t>,
			"is_null", &pointer::is_null,
			"is_valid", &pointer::is_valid,
			"deref", &pointer::deref,
			"get_address", &pointer::get_address
		);

		ns.new_usertype<big::lua_patch>("patch", sol::no_constructor,
			"apply", &big::lua_patch::apply,
			"restore", &big::lua_patch::restore
		);
		// clang-format on

		ns["scan_pattern"]  = scan_pattern;
		ns["handle_to_ptr"] = handle_to_ptr;
		ns["ptr_to_handle"] = ptr_to_handle;
		ns["allocate"]      = allocate;
		ns["free"]          = free;
	}
}