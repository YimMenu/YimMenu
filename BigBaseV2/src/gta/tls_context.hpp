#pragma once
#include <intrin.h>
#include "fwddec.hpp"

namespace rage
{
	class tlsContext
	{
	public:
		char m_padding1[0xC8]; // 0x00
		sysMemAllocator* m_allocator; // 0xC8
		char m_padding2[0x758]; // 0xD0
		scrThread* m_script_thread; // 0x828
		bool m_is_script_thread_active; // 0x830

		static tlsContext* get()
		{
			return *reinterpret_cast<tlsContext**>(__readgsqword(0x58));
		}
	};
	static_assert(sizeof(tlsContext) == 0x838);
}
