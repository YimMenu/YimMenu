#include "hooking.hpp"

#include <network/Network.hpp>

namespace big
{
	// true => e1 > e2
	// false => e1 < e2
	bool hooks::sort_session_details(SessionSortEntry* e1, SessionSortEntry* e2)
	{
		return g_hooking->get_original<hooks::sort_session_details>()(e1, e2);
	}
}