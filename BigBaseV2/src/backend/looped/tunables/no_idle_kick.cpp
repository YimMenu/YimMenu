#include "backend/looped/looped.hpp"
#include "script_global.hpp"

namespace big
{
	auto idle_kick_a = script_global(1648034);
	auto idle_kick_b = script_global(262145);

	// ref: https://www.unknowncheats.me/forum/3487508-post22.html#post3487508
	void looped::tunables_no_idle_kick()
	{
		if (g->tunables.no_idle_kick)
		{
			*idle_kick_a.at(1156).as<int*>() = 0; // idle time
			*idle_kick_a.at(1172).as<int*>() = 0;

			*idle_kick_b.at(87).as<int*>() = INT32_MAX; // IDLEKICK_WARNING1
			*idle_kick_b.at(88).as<int*>() = INT32_MAX; // IDLEKICK_WARNING2
			*idle_kick_b.at(89).as<int*>() = INT32_MAX; // IDLEKICK_WARNING3
			*idle_kick_b.at(90).as<int*>() = INT32_MAX; // IDLEKICK_KICK

			*idle_kick_b.at(8248).as<int*>() = INT32_MAX; // ConstrainedKick_Warning1
			*idle_kick_b.at(8249).as<int*>() = INT32_MAX; // ConstrainedKick_Warning2
			*idle_kick_b.at(8250).as<int*>() = INT32_MAX; // ConstrainedKick_Warning3
			*idle_kick_b.at(8251).as<int*>() = INT32_MAX; // ConstrainedKick_Kick
		}
	}
}