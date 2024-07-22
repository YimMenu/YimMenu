#include "hooking/hooking.hpp"
#include "gta/pools.hpp"

namespace big
{
	bool hooks::can_create_vehicle()
	{
		return (**g_pointers->m_gta.m_vehicle_pool)->m_item_count < (**g_pointers->m_gta.m_vehicle_pool)->m_size;
	}
}
