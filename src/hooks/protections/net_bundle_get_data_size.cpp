#include "hooking/hooking.hpp"
#include "util/notify.hpp"

namespace big
{
	uint32_t hooks::net_bundle_get_data_size(__int64 _this)
	{
		uint32_t ret = g_hooking->get_original<hooks::net_bundle_get_data_size>()(_this);

		auto return_address = static_cast<uint8_t*>(_ReturnAddress());

		if (return_address[0] == 0x33 && ret > 128)
		{
			notify::crash_blocked(nullptr, "out of bounds error packet data size");
			return 0;
		}

		return ret;
	}
}