#include "hooking/hooking.hpp"
#include "gta/pools.hpp"

namespace big
{
	void* hooks::create_pool_item(GenericPool* pool)
	{
		auto item = g_hooking->get_original<hooks::create_pool_item>()(pool);

		if (!item)
		{
			auto caller_offset = (__int64)_ReturnAddress() - (__int64)GetModuleHandleA(0);
			LOGF(FATAL, "Pool full! Caller: GTA5.exe+0x{:X}, Size: {}", caller_offset, pool->m_item_count);
		}

		return item;
	}
}