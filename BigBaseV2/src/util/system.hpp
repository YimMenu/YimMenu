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
}