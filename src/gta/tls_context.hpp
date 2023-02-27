#pragma once
#include "fwddec.hpp"

#include <intrin.h>

namespace rage
{
	class tlsContext
	{
	public:
		char m_padding1[0xB8];         // 0x00
		sysMemAllocator* m_allocator;  // 0xB8
		char m_padding2[0x788];        // 0xD0
		scrThread* m_script_thread;    // 0x848
		bool m_is_script_thread_active;// 0x850

		static tlsContext* get()
		{
			return *reinterpret_cast<tlsContext**>(__readgsqword(0x58));
		}
	};
	static_assert(sizeof(tlsContext) == 0x858);
}
