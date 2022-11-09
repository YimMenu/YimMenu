#pragma once
#include "crossmap.hpp"
#include "pointers.hpp"
#include "memory/module.hpp"

namespace big::system
{
	inline void dump_entry_points()
	{
		DWORD64 base_address = memory::module(nullptr).begin().as<DWORD64>();

		std::string path = std::getenv("appdata");
		path += "\\BigBaseV2\\entrypoints.txt";

		std::ofstream file;
		file.open(path, std::ios::out |std::ios::trunc);

		for (auto &map : g_crossmap)
		{
			auto address = g_pointers->m_get_native_handler(g_pointers->m_native_registration_table, map.second);

			file << std::hex << std::uppercase << "0x" << map.first << " : GTA5.exe + 0x" << (DWORD64)address - base_address << std::endl;
		}

		file.close();
	}

	inline uintptr_t get_relative_address(void* ptr)
	{
		uintptr_t base_address = memory::module(nullptr).begin().as<uintptr_t>();

		return (uintptr_t)ptr - base_address;
	}

	inline void patch_blame(bool toggle)
	{
		*(unsigned short*)g_pointers->m_blame_explode = toggle ? 0xE990 : 0x850F;
	}
}