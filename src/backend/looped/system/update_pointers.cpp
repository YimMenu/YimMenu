#include "backend/looped/looped.hpp"
#include "gta_util.hpp"

namespace big
{
	void looped::system_update_pointers()
	{
		g_local_player = gta_util::get_local_ped();
	}
}