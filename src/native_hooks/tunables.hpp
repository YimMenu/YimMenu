#pragma once
#include "services/tunables/tunables_service.hpp"

namespace big
{
	namespace tunables
	{
		inline void WAIT(rage::scrNativeCallContext* src)
		{
			if (g_tunables_service && g_tunables_service->caching_tunables())
				return; // speed things up

			SYSTEM::WAIT(src->get_arg<int>(0));
		}

		inline void NETWORK_ACCESS_TUNABLE_INT_HASH(rage::scrNativeCallContext* src)
		{
			g_tunables_service->register_tunable(src->get_arg<Hash>(1), src->get_arg<int*>(2));
			src->set_return_value<BOOL>(NETWORK::NETWORK_ACCESS_TUNABLE_INT_HASH(src->get_arg<Hash>(0), src->get_arg<Hash>(1), src->get_arg<int*>(2)));
		};

		inline void NETWORK_ACCESS_TUNABLE_BOOL_MODIFICATION_DETECTION_REGISTRATION_HASH(rage::scrNativeCallContext* src)
		{
			g_tunables_service->register_tunable(src->get_arg<Hash>(1), src->get_arg<bool*>(2));
			src->set_return_value<BOOL>(NETWORK::NETWORK_ACCESS_TUNABLE_BOOL_MODIFICATION_DETECTION_REGISTRATION_HASH(src->get_arg<Hash>(0), src->get_arg<Hash>(1), src->get_arg<BOOL*>(2)));
		};

		inline void NETWORK_ACCESS_TUNABLE_FLOAT_HASH(rage::scrNativeCallContext* src)
		{
			g_tunables_service->register_tunable(src->get_arg<Hash>(1), src->get_arg<float*>(2));
			src->set_return_value<BOOL>(NETWORK::NETWORK_ACCESS_TUNABLE_FLOAT_HASH(src->get_arg<Hash>(0), src->get_arg<Hash>(1), src->get_arg<float*>(2)));
		};
	}
}