#pragma once
#include "rage/joaat.hpp"

#include <cstddef>
#include <cstdint>
#include <string_view>
#include <type_traits>

inline consteval char consteval_to_lower(char c)
{
	return c >= 'A' && c <= 'Z' ? c | 1 << 5 : c;
}

namespace rage
{
	inline constexpr joaat_t constexpr_joaat(const std::string_view s)
	{	
		joaat_t result = 0;

		for (std::size_t i = 0; i < s.size(); i++)
		{
			result += joaat_to_lower(s[i]);
			result += (result << 10);
			result ^= (result >> 6);
		}

		result += (result << 3);
		result ^= (result >> 11);
		result += (result << 15);

		return result;
	}
}

inline consteval rage::joaat_t operator""_J(const char* s, std::size_t n)
{	
	rage::joaat_t result = 0;

	for (std::size_t i = 0; i < n; i++)
	{
		result += consteval_to_lower(s[i]);
		result += (result << 10);
		result ^= (result >> 6);
	}

	result += (result << 3);
	result ^= (result >> 11);
	result += (result << 15);

	return result;
}
static_assert("test"_J == 0x3f75ccc1);
