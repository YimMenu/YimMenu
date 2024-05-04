#pragma once
#include "file_manager.hpp"
#include "memory/module.hpp"
#include "pointers.hpp"

namespace big::system
{
    inline void dump_entry_points()
    {
        const auto file_path = g_file_manager.get_project_file("./entrypoints.txt");
        std::ofstream file(file_path.get_path(), std::ios::out | std::ios::trunc);

        const uintptr_t base_address = memory::module("GTA5.exe").begin().as<uintptr_t>();

        for (const auto& [key, value] : g_crossmap)
        {
            const auto address = g_pointers->m_gta.m_get_native_handler(g_pointers->m_gta.m_native_registration_table, value);
            file << std::hex << std::uppercase << "0x" << key << " : GTA5.exe + 0x" << get_relative_address(address) << std::endl;
        }
    }

    inline uintptr_t get_relative_address(void* ptr)
    {
        const uintptr_t base_address = memory::module("GTA5.exe").begin().as<uintptr_t>();
        return (uintptr_t)ptr - base_address;
    }
}
