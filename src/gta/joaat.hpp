#pragma once
#include <cstddef>
#include <cstdint>
#include <string_view>
#include <type_traits>

#include "rage/joaat.hpp"

namespace rage
{
	inline consteval joaat_t consteval_joaat(const std::span<const char>& data)
	{
		joaat_t hash = 0;

		for (std::size_t i = 0; i < data.size() - 1; ++i)
		{
			hash += joaat_to_lower(data[i]);
			hash += (hash << 10);
			hash ^= (hash >> 6);
		}

		hash += (hash << 3);
		hash ^= (hash >> 11);
		hash += (hash << 15);

		return hash;
	}
	static_assert(consteval_joaat("test") == 0x3f75ccc1);
}

inline consteval rage::joaat_t operator""_j(const char* s, std::size_t n)
{
	rage::joaat_t result = 0;

	for (std::size_t i = 0; i < n; i++)
	{            
		result += rage::joaat_to_lower(s[i]);
		result += (result << 10);
		result ^= (result >> 6);
	}
	
	result += (result << 3);
	result ^= (result >> 11);
	result += (result << 15);

	return result;
}

#define RAGE_JOAAT_IMPL(str) (::rage::consteval_joaat(str))
#define RAGE_JOAAT(str) (std::integral_constant<rage::joaat_t, RAGE_JOAAT_IMPL(str)>::value)