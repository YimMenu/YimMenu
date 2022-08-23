#pragma once
#include "native_hooks.hpp"
#include "core/globals.hpp"
#include "natives.hpp"

namespace big
{
	namespace maintransition
	{
		inline void NETWORK_SESSION_HOST(rage::scrNativeCallContext* src)
		{
			if (g->session.session_join_queued)
			{
				g_pointers->m_join_session_by_info(*g_pointers->m_network, &g->session.session_info, 0, 0, nullptr, 0);
				g->session.session_join_queued = false;
				src->set_return_value<BOOL>(TRUE);
			}
			else
			{
				src->set_return_value<BOOL>(NETWORK::NETWORK_SESSION_HOST(src->get_arg<int>(0), src->get_arg<int>(1), src->get_arg<BOOL>(2)));
			}
		};
	}
}