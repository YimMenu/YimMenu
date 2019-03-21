#include "../common.hpp"
#include "module.hpp"

namespace memory
{
	module::module(HMODULE mod) :
		range(mod, 0)
	{
		auto dosHeader = m_base.as<IMAGE_DOS_HEADER*>();
		auto ntHeader = m_base.add(dosHeader->e_lfanew).as<IMAGE_NT_HEADERS*>();
		m_size = ntHeader->OptionalHeader.SizeOfImage;
	}

	module::module(std::nullptr_t) :
		module(GetModuleHandle(nullptr))
	{
	}

	module::module(std::string_view name) :
		module(GetModuleHandleA(name.data()))
	{
	}

	module::module(std::wstring_view name) :
		module(GetModuleHandleW(name.data()))
	{
	}

	handle module::get_export(std::string_view symbol_name)
	{
		return GetProcAddress(m_base.as<HMODULE>(), symbol_name.data());
	}
}
