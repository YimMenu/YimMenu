#include "hooking.hpp"

namespace big
{
	int hooks::join_player(__int64 a1, int a2, __int64* a3, int a4)
	{
        if (g->session.joiner)
        {
            if (a3 == 0)
            {
                return g_hooking->m_join_pattern.get_original<decltype(&hooks::join_player)>()(a1, a2, a3, a4);
            }
            *a3 = g->session.rid_to_join;

        }

        return g_hooking->m_join_pattern.get_original<decltype(&hooks::join_player)>()(a1, a2, a3, a4);
    }
}