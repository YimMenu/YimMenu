#include "backend/looped/looped.hpp"
#include "gta_util.hpp"
#include "script_local.hpp"

namespace big
{
	void looped::tunables_casino_rig()
	{
		if (g.tunables.rig_casino)
		{
			gta_util::execute_as_script(RAGE_JOAAT("CASINO_SLOTS"), [] {
				auto slots_thread = gta_util::find_script_thread(RAGE_JOAAT("CASINO_SLOTS"));
				for (int i = 1; i <= 195; i++) {
					auto local1354 = script_local(slots_thread, 1354).at(1);
					int break_value = *local1354.at(i).as<int*>();
					if (break_value != 64) {
						*local1354.at(i).as<int*>() = 6;
					}
				}
				});
		}
	}
}