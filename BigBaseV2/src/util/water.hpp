#pragma once

namespace big::water
{
	inline float* get_water_collision_ptr(CNavigation* nav)
	{
		auto nav_addr = (uint64_t)nav;
		return (float*)(*(uint64_t*)(nav_addr + 0x10) + 0x54);
	}

	inline void reset_ped_oxygen_time(CPed* ped)
	{
		auto ped_addr = (uint64_t)ped;
		*(float*)(*(uint64_t*)(ped_addr + 0x10C0) + 0x278) = 0;
	}
}
