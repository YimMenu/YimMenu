#pragma once
#include "common.hpp"
#include "gta/array.hpp"
#include "gta/ped_factory.hpp"
#include "gta/player.hpp"
#include "gta/script_thread.hpp"
#include "gta/tls_context.hpp"
#include "pointers.hpp"

namespace big::gta_util
{
	inline void defuse_event(RockstarEvent e, bool toggle)
	{
		if (g_pointers->m_event_ptr[e] == nullptr) return;

		char* p = (char*)g_pointers->m_event_ptr[e];
		if (toggle)
		{
			if (g_pointers->m_event_restore[e] == 0)
				g_pointers->m_event_restore[e] = p[0];
			*p = (unsigned char)0xC3;
		}
		else if (g_pointers->m_event_restore[e] != 0)
			*p = g_pointers->m_event_restore[e];
	}

	inline CPed *get_local_ped()
	{
		if (auto ped_factory = *g_pointers->m_ped_factory)
		{
			return ped_factory->m_local_ped;
		}

		return nullptr;
	}

	inline CPlayerInfo *get_local_playerinfo()
	{
		if (auto ped_factory = *g_pointers->m_ped_factory)
		{
			if (auto ped = ped_factory->m_local_ped)
			{
				return ped->m_playerinfo;
			}
		}

		return nullptr;
	}

	template <typename F, typename ...Args>
	void execute_as_script(rage::joaat_t script_hash, F &&callback, Args &&...args)
	{
		auto tls_ctx = rage::tlsContext::get();
		for (auto thread : *g_pointers->m_script_threads)
		{
			if (!thread || !thread->m_context.m_thread_id || thread->m_context.m_script_hash != script_hash)
				continue;

			auto og_thread = tls_ctx->m_script_thread;

			tls_ctx->m_script_thread = thread;
			tls_ctx->m_is_script_thread_active = true;

			std::invoke(std::forward<F>(callback), std::forward<Args>(args)...);

			tls_ctx->m_script_thread = og_thread;
			tls_ctx->m_is_script_thread_active = og_thread != nullptr;

			return;
		}
	}
}
