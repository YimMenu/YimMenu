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

	bool is_unwanted_dependency(__int64 cb)
	{
		auto f1 = *(__int64*)(cb + 0x60);
		auto f2 = *(__int64*)(cb + 0x100);

		if (!is_address_in_game_region(f1) || (f2 && !is_address_in_game_region(f2)))
			return false;

		return is_jump(f1) || is_jump(f2);
	}

	static bool nullsub()
	{
		return true; // returning false would cause the dependency to requeue
	}

	int hooks::queue_dependency(void* a1, int a2, void* dependency)
	{
		if (is_unwanted_dependency((__int64)dependency))
		{
			*(void**)((__int64)dependency + 0x60) = nullsub;
			*(void**)((__int64)dependency + 0x100) = nullsub;
		}

		return g_hooking->get_original<hooks::queue_dependency>()(a1, a2, dependency);
	}
}