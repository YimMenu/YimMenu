#include "hooking.hpp"
#include "pointers.hpp"

namespace big
{
	bool hooks::remove_player_from_sender_list(void* list, uint64_t rockstar_id)
	{
		g_pointers->m_gta.m_remove_player_from_sender_list(list, &rockstar_id);
		return true;
	}
}