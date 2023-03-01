#pragma once
#include "crossmap.hpp"
#include "file_manager.hpp"
#include "memory/module.hpp"
#include "pointers.hpp"

namespace big::system
{
	inline void dump_entry_points()
	{
		DWORD64 base_address = memory::module("GTA5.exe").begin().as<DWORD64>();

		const auto file_path = g_file_manager->get_project_file("./entrypoints.txt");
		auto file            = std::ofstream(file_path.get_path(), std::ios::out | std::ios::trunc);

		for (auto& map : g_crossmap)
		{
			auto address = g_pointers->m_get_native_handler(g_pointers->m_native_registration_table, map.second);

			file << std::hex << std::uppercase << "0x" << map.first << " : GTA5.exe + 0x" << (DWORD64)address - base_address << std::endl;
		}

		file.close();
	}

	inline uintptr_t get_relative_address(void* ptr)
	{
		uintptr_t base_address = memory::module("GTA5.exe").begin().as<uintptr_t>();

		return (uintptr_t)ptr - base_address;
	}
}