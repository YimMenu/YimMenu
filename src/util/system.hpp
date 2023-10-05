#pragma once
#include "crossmap.hpp"
#include "file_manager.hpp"
#include "memory/module.hpp"
#include "pointers.hpp"

namespace big::system
{
	inline uintptr_t get_relative_address(void* ptr)
	{
		uintptr_t base_address = memory::module("GTA5.exe").begin().as<uintptr_t>();

		return (uintptr_t)ptr - base_address;
	}
}