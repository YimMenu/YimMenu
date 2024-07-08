#include "memory.hpp"

#include "lua/lua_manager.hpp"
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

	value_wrapper_t::value_wrapper_t(char* val, type_info_t type)
	{
		m_value = val;
		m_type  = type;
	}

	sol::object value_wrapper_t::get(sol::this_state state_)
	{
		if (m_type == type_info_t::boolean_)
		{
			return sol::make_object(state_, *(bool*)m_value);
		}
		else if (m_type == type_info_t::string_)
		{
			return sol::make_object(state_, *(const char**)m_value);
		}
		else if (m_type == type_info_t::integer_)
		{
			return sol::make_object(state_, *(int64_t*)m_value);
		}
		else if (m_type == type_info_t::float_)
		{
			return sol::make_object(state_, *(float*)m_value);
		}
		else if (m_type == type_info_t::double_)
		{
			return sol::make_object(state_, *(double*)m_value);
		}
		else
		{
			return sol::nil;
		}
	}

	void value_wrapper_t::set(sol::object new_val, sol::this_state state_)
	{
		if (m_type == type_info_t::boolean_ && new_val.is<bool>())
		{
			*(bool*)m_value = new_val.as<bool>();
		}
		else if (m_type == type_info_t::string_ && new_val.is<const char*>())
		{
			*(const char**)m_value = new_val.as<const char*>();
		}
		else if (m_type == type_info_t::integer_ && new_val.is<int64_t>())
		{
			*(int64_t*)m_value = new_val.as<int64_t>();
		}
		else if (m_type == type_info_t::float_ && new_val.is<float>())
		{
			*(float*)m_value = new_val.as<float>();
		}
		else if (m_type == type_info_t::double_ && new_val.is<double>())
		{
			*(double*)m_value = new_val.as<double>();
		}
	}

	static std::unordered_map<uintptr_t, std::unique_ptr<runtime_func_t>> target_func_ptr_to_hook;

	static bool pre_callback(const runtime_func_t::parameters_t* params, const uint8_t param_count, runtime_func_t::return_value_t* return_value, const uintptr_t target_func_ptr)
	{
		const auto& dyn_hook = target_func_ptr_to_hook[target_func_ptr];
		return big::g_lua_manager
		    ->dynamic_hook_pre_callbacks(target_func_ptr, dyn_hook->m_return_type, return_value, dyn_hook->m_param_types, params, param_count);
	}

	static void post_callback(const runtime_func_t::parameters_t* params, const uint8_t param_count, runtime_func_t::return_value_t* return_value, const uintptr_t target_func_ptr)
	{
		const auto& dyn_hook = target_func_ptr_to_hook[target_func_ptr];
		big::g_lua_manager->dynamic_hook_post_callbacks(target_func_ptr, dyn_hook->m_return_type, return_value, dyn_hook->m_param_types, params, param_count);
	}

	// Lua API: Function
	// Table: memory
	// Name: dynamic_hook
	// Param: hook_name: string: The name of the hook.
	// Param: return_type: string: Type of the return value of the detoured function.
	// Param: param_types: table<string>: Types of the parameters of the detoured function.
	// Param: target_func_ptr: memory.pointer: The pointer to the function to detour.
	// Param: pre_callback: function: The function that will be called before the original function is about to be called. The callback must match the following signature: ( return_value (value_wrapper), arg1 (value_wrapper), arg2 (value_wrapper), ... ) -> Returns true or false (boolean) depending on whether you want the original function to be called.
	// Param: post_callback: function: The function that will be called after the original function is called (or just after the pre callback is called, if the original function was skipped). The callback must match the following signature: ( return_value (value_wrapper), arg1 (value_wrapper), arg2 (value_wrapper), ... ) -> void
	// **Example Usage:**
	// ```lua
	// local ptr = memory.scan_pattern("some ida sig")
	// memory.dynamic_hook("test_hook", "float", {"const char*"}, ptr,
	// function(ret_val, str)
	//
	//     --str:set("replaced str")
	//     ret_val:set(69.69)
	//     log.info("pre callback from lua", ret_val:get(), str:get())
	//
	//     -- false for skipping the original function call
	//     return false
	// end,
	// function(ret_val, str)
	//     log.info("post callback from lua 1", ret_val:get(), str:get())
	//     ret_val:set(79.69)
	//     log.info("post callback from lua 2", ret_val:get(), str:get())
	// end)
	// ```
	static void dynamic_hook(const std::string& hook_name, const std::string& return_type, sol::table param_types_table, lua::memory::pointer& target_func_ptr_obj, sol::protected_function pre_lua_callback, sol::protected_function post_lua_callback, sol::this_state state_)
	{
		const auto target_func_ptr = target_func_ptr_obj.get_address();
		if (!target_func_ptr_to_hook.contains(target_func_ptr))
		{
			std::vector<std::string> param_types;
			for (const auto& [k, v] : param_types_table)
			{
				if (v.is<const char*>())
				{
					param_types.push_back(v.as<const char*>());
				}
			}

			std::unique_ptr<runtime_func_t> runtime_func = std::make_unique<runtime_func_t>();
			const auto jitted_func = runtime_func->make_jit_func(return_type, param_types, asmjit::Arch::kHost, pre_callback, post_callback, target_func_ptr);

			target_func_ptr_to_hook.emplace(target_func_ptr, std::move(runtime_func));

			// TODO: The detour_hook is never cleaned up on menu unload.
			target_func_ptr_to_hook[target_func_ptr]->create_and_enable_hook(hook_name, target_func_ptr, jitted_func);
		}

		big::lua_module* module = sol::state_view(state_)["!this"];
		if (!module)
		{
			return;
		}
		if (pre_lua_callback.valid())
		{
			module->m_dynamic_hook_pre_callbacks[target_func_ptr].push_back(pre_lua_callback);
		}
		if (post_lua_callback.valid())
		{
			module->m_dynamic_hook_post_callbacks[target_func_ptr].push_back(post_lua_callback);
		}
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

		ns.new_usertype<value_wrapper_t>("value_wrapper", "get", &value_wrapper_t::get, "set", &value_wrapper_t::set);
		ns["dynamic_hook"] = dynamic_hook;
	}
}