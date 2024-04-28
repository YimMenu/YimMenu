#include "hooking/hooking.hpp"
#include "pointers.hpp"

namespace big
{
	void hooks::render_entity(__int64 renderer, rage::fwEntity* entity, int unk, bool a4)
	{
		if (*(int*)(((__int64)(*g_pointers->m_gta.m_draw_handler_mgr) + 0x14730)) >= 512) [[unlikely]]
		{
			*(int*)(renderer + 4) &= ~0x80000000;
			*(int*)(renderer + 4) &= ~0x40000000;
			*(int*)(renderer + 4) |= (a4 & 1) << 30;
			*(int*)renderer = -2;
		}
		else [[likely]]
		{
			g_hooking->get_original<hooks::render_entity>()(renderer, entity, unk, a4);
		}
	}
}