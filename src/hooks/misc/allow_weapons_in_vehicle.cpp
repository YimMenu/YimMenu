#include "hooking.hpp"

namespace big
{
	bool hooks::allow_weapons_in_vehicle(int64_t unk, int weaponinfo_group)
	{
		if (g.vehicle.unlimited_weapons)
		{
			if (weaponinfo_group == RAGE_JOAAT("GROUP_THROWN")) // Because the thrower can be used without bypassing, we let the game decide the return value, since this function has multiple xrefs, it may be necessary to return 0 at some point
				return g_hooking->get_original<allow_weapons_in_vehicle>()(unk, weaponinfo_group);
			return true;
		}
		return g_hooking->get_original<allow_weapons_in_vehicle>()(unk, weaponinfo_group);
	}
}