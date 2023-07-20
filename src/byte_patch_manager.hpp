#pragma once

extern "C" uint64_t g_sound_overload_ret_addr;

namespace big
{
	class byte_patch_manager
	{
	public:
		byte_patch_manager();
		~byte_patch_manager();
	};

	inline byte_patch_manager* g_byte_patch_manager;
}
