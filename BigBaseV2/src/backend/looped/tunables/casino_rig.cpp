#include "backend/looped/looped.hpp"
#include "gta_util.hpp"
#include "script_local.hpp"
#include "fiber_pool.hpp"
#include "natives.hpp"

namespace big
{
	void looped::tunables_casino_rig()
	{
		if (g->tunables.rig_casino)
		{
			gta_util::execute_as_script(RAGE_JOAAT("CASINO_SLOTS"), [] {
				auto slots_thread = gta_util::find_script_thread(RAGE_JOAAT("CASINO_SLOTS"));
				for (int i = 1; i <= 195; i++) {
					auto local1354 = script_local(slots_thread, 1360).at(1);
					int break_value = *local1354.at(i).as<int*>();
					if (break_value != 64) {
						*local1354.at(i).as<int*>() = 6;
					}
				}
				auto transaction = script_local::script_local(slots_thread, 1650).as<int*>();
				auto checker = *script_local::script_local(slots_thread, 3413).at(PLAYER::PLAYER_ID(), 11).at(10).as<int*>();
				if (checker == 0)
				{
					MISC::SET_BIT(transaction, 3);
				}
				});

		}
	}
}