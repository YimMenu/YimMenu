#include "backend/looped/looped.hpp"
#include "util/teleport.hpp"

namespace big
{
	void looped::hotkey_tp_waypoint()
	{
		if (GetAsyncKeyState(g->settings.hotkeys.teleport_waypoint)) {
			teleport::to_waypoint();
			script::get_current()->yield(300ms);
		}
	}
}