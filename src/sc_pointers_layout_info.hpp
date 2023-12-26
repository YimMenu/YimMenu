#pragma once
#include "pointers.hpp"

namespace big
{
	struct sc_pointers_layout_info
	{
		// get the beginning and the end of what we need to save / load
		inline static constexpr size_t offset_of_cache_begin_field = offsetof(big::pointers, m_sc);
		inline static constexpr size_t offset_of_cache_end_field = offsetof(big::pointers, m_sc) + sizeof(socialclub_pointers);
		inline static constexpr size_t field_count = (offset_of_cache_end_field - offset_of_cache_begin_field) / sizeof(void*);
	};
}
