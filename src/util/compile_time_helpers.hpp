#pragma once

namespace big
{
	template<uint32_t hash>
	struct compile_time_helper
	{
		static_assert(hash == -1);
		static constexpr bool print_hash = (hash == -1);
	};

	struct cstxpr_str
	{
		const char* str;
	};
}