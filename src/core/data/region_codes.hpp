#pragma once

namespace big
{
	struct RegionType
	{
		uint32_t id;
		const char name[22];
	};

	const RegionType regions[] = {
	    {0, "CIS"},
	    {1, "Africa"},
	    {2, "East"},
	    {3, "Europe"},
	    {4, "China"},
	    {5, "Australia"},
	    {6, "West"},
	    {7, "Japan"},
	    {8, "Unknown"},
	};
}