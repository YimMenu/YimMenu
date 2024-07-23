#include "hooking/hooking.hpp"
#include "security/ObfVar.hpp"
#include <Psapi.h>

namespace big
{
	bool inline is_address_in_game_region(int64_t address)
	{
		if(!address) [[unlikely]]
			return false;
		static int64_t moduleBase = NULL;
		static int64_t moduleSize = NULL;
		if (!moduleBase || !moduleSize) [[unlikely]]
		{
			MODULEINFO info;
			if (!GetModuleInformation(GetCurrentProcess(), GetModuleHandle(0), &info, sizeof(info)))
			{
				LOG(FATAL) << "GetModuleInformation failed!";
				return true;
			}
			else
			{
				moduleBase = (int64_t)GetModuleHandle(0);
				moduleSize = (int64_t)info.SizeOfImage;
			}
		}
		return address > moduleBase && address < (moduleBase + moduleSize);
	}

	struct ac_verifier
	{
		virtual ~ac_verifier() = 0;
		virtual bool run() = 0;
		rage::Obf32 m_last_time; // 0x8 
		rage::Obf32 m_delay; // 0x18
	};

	bool is_unwanted_dependency(int64_t cb)
	{
		int64_t f1 = *reinterpret_cast<int64_t*>(cb + 0x60);
		int64_t f2 = *reinterpret_cast<int64_t*>(cb + 0x100);
		int64_t f3 = *reinterpret_cast<int64_t*>(cb + 0x1A0);

		if (!is_address_in_game_region(f1) || !is_address_in_game_region(f2) || !is_address_in_game_region(f3)) [[likely]]
			return false;

		if(*reinterpret_cast<uint8_t*>(f1) != 0xE9) [[likely]]
			return false;

		return true;
	}

	static bool nullsub()
	{
		return true; // returning false would cause the dependency to requeue
	}

	int hooks::queue_dependency(void* a1, int a2, int64_t dependency)
	{
		if (is_unwanted_dependency(dependency)) [[unlikely]]
		{
			LOG(INFO) << "Blocking AC Verifier " << HEX_TO_UPPER(*reinterpret_cast<int64_t*>(dependency + 0x60) - reinterpret_cast<int64_t>(GetModuleHandle(NULL)));
			ac_verifier* verifier = reinterpret_cast<ac_verifier*>(dependency - 0x30);
			verifier->m_delay = INT_MAX; // makes it so these won't queue in the future
			*reinterpret_cast<void**>(dependency + 0x60) = nullsub;
			*reinterpret_cast<void**>(dependency + 0x100) = nullsub;
			*reinterpret_cast<void**>(dependency + 0x1A0) = nullsub;
		}

		return g_hooking->get_original<hooks::queue_dependency>()(a1, a2, dependency);
	}
}