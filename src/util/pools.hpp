#pragma once
#include "gta/pools.hpp"

namespace big::pools
{
	inline auto& get_all_peds()
	{
		return **g_pointers->m_gta.m_ped_pool;
	}

	inline auto& get_all_vehicles()
	{
		return ***g_pointers->m_gta.m_vehicle_pool;
	}

	inline auto& get_all_props()
	{
		return **g_pointers->m_gta.m_prop_pool;
	}

	inline auto get_all_peds_array()
	{
		return get_all_peds().to_array();
	}

	inline auto get_all_vehicles_array()
	{
		return get_all_vehicles().to_array();
	}

	inline auto get_all_props_array()
	{
		return get_all_props().to_array();
	}
};