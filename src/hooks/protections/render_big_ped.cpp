#include "hooking/hooking.hpp"
#include "pointers.hpp"

namespace big
{
	__int64 hooks::render_big_ped(__int64 renderer, CPed* ped, __int64 a3, __int64 a4)
	{
		if (*(int*)(((__int64)(*g_pointers->m_gta.m_draw_handler_mgr) + 0x14730)) >= 512) [[unlikely]]
		{
			*(int*)(a4 + 4) = -2;
			return a4 + 0x14;
		}
		else [[likely]]
		{
			return g_hooking->get_original<hooks::render_big_ped>()(renderer, ped, a3, a4);
		}
	}
}