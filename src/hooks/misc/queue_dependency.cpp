#include "hooking.hpp"
#include "pointers.hpp"

#include <Psapi.h>

namespace big
{
	bool inline is_address_in_game_region(uint64_t address)
	{
		static uint64_t moduleBase = NULL;
		static uint64_t moduleSize = NULL;
		if ((!moduleBase) || (!moduleSize))
		{
			MODULEINFO info;
			if (!GetModuleInformation(GetCurrentProcess(), GetModuleHandle(0), &info, sizeof(info)))
			{
				LOG(FATAL) << "GetModuleInformation failed!";
				return true;
			}
			else
			{
				moduleBase = (uint64_t)GetModuleHandle(0);
				moduleSize = (uint64_t)info.SizeOfImage;
			}
		}
		return address > moduleBase && address < (moduleBase + moduleSize);
	}

	bool is_jump(__int64 fptr)
	{
		if (!is_address_in_game_region(fptr))
			return false;

		auto value = *(uint8_t*)(fptr);
		return value == 0xE9;
	}

	bool is_unwanted_dependency(__int64 cb, uint64_t caller_addr_offset)
	{
		auto f1 = *(__int64*)(cb + 0x60);
		auto f2 = *(__int64*)(cb + 0x100);

		if (!is_address_in_game_region(f1) || (f2 && !is_address_in_game_region(f2)))
			return false;

		// These must run, otherwise we'll at some point run out of sysMemSimpleAllocator memory.
		if (caller_addr_offset == 0xAA03D4 || caller_addr_offset == 0xAA0A21 || caller_addr_offset == 0xAA0902)
		{
			return false;
		}

		return is_jump(f1) || is_jump(f2);
	}

	void hooks::queue_dependency(void* dependency)
	{
		uint64_t caller_addr_offset = (uint64_t)_ReturnAddress();

		static auto module_base = (uint64_t)GetModuleHandle(0);

		caller_addr_offset -= module_base;

		if (is_unwanted_dependency((__int64)dependency, caller_addr_offset))
		{
			return;
		}

		return g_hooking->get_original<hooks::queue_dependency>()(dependency);
	}
}