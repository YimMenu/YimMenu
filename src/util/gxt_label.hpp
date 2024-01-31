#pragma once
#include "pointers.hpp"

namespace big
{
	inline std::string get_gxt_label(const std::string& key)
	{
		const auto gxt_via_string{g_pointers->m_gta.m_get_gxt_label_from_table(g_pointers->m_gta.g_gxt_labels, key.c_str())};
		if (!gxt_via_string)
		{
			const auto gxt_via_joaat{g_pointers->m_gta.m_get_joaated_gxt_label_from_table(g_pointers->m_gta.g_gxt_labels, rage::joaat(key))};
			if (!gxt_via_string)
			{
				return key;
			}
			return gxt_via_joaat;
		}
		return gxt_via_string;
	}
}
