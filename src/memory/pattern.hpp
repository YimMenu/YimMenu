#pragma once
#include <cstdint>
#include <optional>
#include <string_view>
#include <vector>
#include "fwddec.hpp"
#include "handle.hpp"

namespace memory
{
	class pattern
	{
		friend pattern_batch;
		friend range;
	public:
		pattern(std::string_view ida_sig);
		explicit pattern(const void *bytes, std::string_view mask);

		inline pattern(const char* ida_sig) :
			pattern(std::string_view(ida_sig))
		{}
	private:
		std::vector<std::optional<std::uint8_t>> m_bytes;
	};
}
