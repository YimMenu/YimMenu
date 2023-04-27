#pragma once
#include "lua/lua_module.hpp"
#include "lua/lua_patch.hpp"
#include "lua/sol.hpp"
#include "memory/byte_patch.hpp"

namespace lua::memory
{
	struct pointer
	{
	public:
		std::uint64_t m_address;

		pointer(std::uint64_t address) :
		    m_address(address)
		{
		}

		pointer add(uint64_t offset)
		{
			return pointer(m_address + offset);
		}

		pointer sub(uint64_t offset)
		{
			return pointer(m_address - offset);
		}

		pointer rip()
		{
			return add(*(std::int32_t*)m_address).add(4);
		}

		template<typename T>
		T get()
		{
			return *(T*)m_address;
		}

		template<typename T>
		void set(T value)
		{
			*(T*)m_address = value;
		}

		template<typename T>
		big::lua_patch* patch(T value, sol::this_state state)
		{
			auto module = sol::state_view(state)["!this"].get<big::lua_module*>();
			auto patch  = std::make_shared<big::lua_patch>(::memory::byte_patch::make((T*)m_address, value).get());
			auto raw    = patch.get();
			module->m_registered_patches.push_back(std::move(patch));
			return raw;
		}

		bool is_null()
		{
			return m_address == 0;
		}

		bool is_valid()
		{
			return !is_null();
		}

		pointer deref()
		{
			return pointer(*(uint64_t*)m_address);
		}

		uint64_t get_address()
		{
			return m_address;
		}
	};

	pointer scan_pattern(const std::string& pattern);

	static void bind(sol::state& state)
	{
		auto ns = state["memory"].get_or_create<sol::table>();

		// clang-format off
		ns.new_usertype<pointer>("handle", sol::constructors<pointer(std::uint64_t)>(),
			"add", &pointer::add, 
			"sub", &pointer::sub, 
			"rip", &pointer::rip, 
			"get_byte", &pointer::get<uint8_t>,
			"get_word", &pointer::get<uint16_t>,
			"get_dword", &pointer::get<uint32_t>,
			"get_qword", &pointer::get<uint64_t>,
			"set_byte", &pointer::set<uint8_t>,
			"set_word", &pointer::set<uint16_t>,
			"set_dword", &pointer::set<uint32_t>,
			"set_qword", &pointer::set<uint64_t>,
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

		ns["scan_pattern"] = scan_pattern;
	}
}