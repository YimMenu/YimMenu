#include "native_hooks.hpp"

namespace big
{
	inline void NETWORK_CAN_BAIL(rage::scrNativeCallContext* src)
	{
		LOG(INFO) << "NATIVE_HOOK => NETWORK_CAN_BAIL : TRIGGERED";

		src->set_return_value<BOOL>(false);
	}
}