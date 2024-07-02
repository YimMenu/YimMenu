#pragma once
#include "services/tunables/tunables_service.hpp"
#include "natives.hpp"

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

		inline void _NETWORK_GET_TUNABLES_REGISTRATION_INT(rage::scrNativeCallContext* src)
		{
			if (g_tunables_service->caching_tunables())
			{
				g_tunables_service->m_junk_values.emplace(g_tunables_service->m_current_junk_val, src->get_arg<Hash>(0));
				src->set_return_value<int>(g_tunables_service->m_current_junk_val++);
				return;
			}
			src->set_return_value<int>(NETWORK::_NETWORK_GET_TUNABLES_REGISTRATION_INT(src->get_arg<Hash>(0), src->get_arg<int>(1)));
		};

		inline void _NETWORK_GET_TUNABLES_REGISTRATION_BOOL(rage::scrNativeCallContext* src)
		{
			if (g_tunables_service->caching_tunables())
			{
				g_tunables_service->m_junk_values.emplace(g_tunables_service->m_current_junk_val, src->get_arg<Hash>(0));
				src->set_return_value<int>(g_tunables_service->m_current_junk_val++);
				return;
			}
			src->set_return_value<BOOL>(NETWORK::_NETWORK_GET_TUNABLES_REGISTRATION_BOOL(src->get_arg<Hash>(0), src->get_arg<BOOL>(1)));
		};

		inline void _NETWORK_GET_TUNABLES_REGISTRATION_FLOAT(rage::scrNativeCallContext* src)
		{
			if (g_tunables_service->caching_tunables())
			{
				g_tunables_service->m_junk_values.emplace(g_tunables_service->m_current_junk_val, src->get_arg<Hash>(0));
				src->set_return_value<int>(g_tunables_service->m_current_junk_val++);
				return;
			}
			src->set_return_value<float>(NETWORK::_NETWORK_GET_TUNABLES_REGISTRATION_FLOAT(src->get_arg<Hash>(0), src->get_arg<float>(1)));
		};
	}
}