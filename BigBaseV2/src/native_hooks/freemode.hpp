#pragma once

namespace big
{
	namespace freemode
	{
		inline void NETWORK_CAN_BAIL(rage::scrNativeCallContext* src)
		{
			LOG(INFO) << "NATIVE_HOOK => NETWORK_CAN_BAIL : TRIGGERED";

			src->set_return_value<BOOL>(false);
		}
	}

}