#pragma once

namespace big
{
	struct RecentModder
	{
		std::string name;
		uint64_t rockstar_id;
		bool block_join;
	};

	inline std::map<uint64_t, RecentModder> recent_modders_list;
}