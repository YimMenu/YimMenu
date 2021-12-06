#include "gta/joaat.hpp"
#include "hooking.hpp"
#include "natives.hpp"

namespace big
{
	bool hooks::is_dlc_present(Hash dlc_hash)
	{
		switch (dlc_hash)
		{
		case 0x96F02EE6:
			return true;
		}

		return g_hooking->m_is_dlc_present_hook.get_original<decltype(&is_dlc_present)>()(dlc_hash);
	}
}