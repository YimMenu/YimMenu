#include "hooking.hpp"
#include "network/Network.hpp"
#include "pointers.hpp"

namespace big
{
	bool hooks::write_bitbuffer_gamer_handle(rage::datBitBuffer* buffer, rage::rlGamerHandle* handle)
	{
		bool restore = false;

		if (g.spoofing.should_spoof_rockstar_id && handle->m_rockstar_id == g_pointers->m_profile_gamer_info->m_gamer_handle_2.m_rockstar_id)
		{
			handle->m_rockstar_id = g.spoofing.applied_spoof_rockstar_id;
			restore = true;
		}

		bool result = g_hooking->get_original<hooks::write_bitbuffer_gamer_handle>()(buffer, handle);

		if (restore)
			handle->m_rockstar_id = g_pointers->m_profile_gamer_info->m_gamer_handle_2.m_rockstar_id;
		return result;
	}
}