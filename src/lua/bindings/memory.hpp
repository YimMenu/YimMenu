#pragma once
#include "lua/lua_patch.hpp"
#include "memory/byte_patch.hpp"
#include "memory/module.hpp"
#include "memory/pattern.hpp"

namespace lua::memory
{
	struct handle
	{
	private:
		std::uint64_t m_address;

	public:
		handle(std::uint64_t address) :
		    m_address(address)
		{
		}

		handle add(uint64_t offset)
		{
			return handle(m_address + offset);
		}

		handle sub(uint64_t offset)
		{
			return handle(m_address - offset);
		}

		handle rip()
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
	};

	static handle scan_pattern(const std::string& pattern)
	{
		return handle(::memory::module("GTA5.exe").scan(::memory::pattern(pattern)).as<uint64_t>());
	}

	static void bind(sol::state& state)
	{
		auto ns = state["memory"].get_or_create<sol::table>();

		// clang-format off
		ns.new_usertype<handle>("handle", sol::constructors<handle(std::uint64_t)>(),
			"add", &handle::add, 
			"sub", &handle::sub, 
			"rip", &handle::rip, 
			"get_byte", &handle::get<uint8_t>,
			"get_word", &handle::get<uint16_t>,
			"get_dword", &handle::get<uint32_t>,
			"get_qword", &handle::get<uint64_t>,
			"set_byte", &handle::set<uint8_t>,
			"set_word", &handle::set<uint16_t>,
			"set_dword", &handle::set<uint32_t>,
			"set_qword", &handle::set<uint64_t>,
			"patch_byte", &handle::patch<uint8_t>,
			"patch_word", &handle::patch<uint16_t>,
			"patch_dword", &handle::patch<uint32_t>,
			"patch_qword", &handle::patch<uint64_t>
		);

		ns.new_usertype<big::lua_patch>("patch", sol::no_constructor,
			"apply", &big::lua_patch::apply,
			"restore", &big::lua_patch::restore
		);
		// clang-format on

		ns["scan_pattern"] = scan_pattern;
	}
}