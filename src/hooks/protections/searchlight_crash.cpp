#include "hooking/hooking.hpp"
#include "pointers.hpp"

namespace big
{
	void hooks::searchlight_crash(void* a1, CPed* ped)
	{
		if (!ped || !g_pointers->m_gta.m_get_searchlight(ped)) [[unlikely]]
			return;

		return g_hooking->get_original<hooks::searchlight_crash>()(a1, ped);
	}
}