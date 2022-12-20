#include "hooking.hpp"
#include "network/Network.hpp"
#include "pointers.hpp"

namespace big
{
	bool hooks::read_bitbuffer_gamer_handle(rage::datBitBuffer* buffer, rage::rlGamerHandle* handle)
	{
		bool result = g_hooking->get_original<hooks::read_bitbuffer_gamer_handle>()(buffer, handle);
		if (g.spoofing.should_spoof_rockstar_id && handle->m_rockstar_id == g.spoofing.applied_spoof_rockstar_id)
			handle->m_rockstar_id = g_pointers->m_profile_gamer_info->m_gamer_handle_2.m_rockstar_id;
		return result;
	}
}