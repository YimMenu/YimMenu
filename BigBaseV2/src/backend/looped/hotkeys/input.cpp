#include "backend/looped/looped.hpp"

namespace big
{
	bool IsGameWindowFocussed()
	{
		if (GetForegroundWindow() == g_hwnd)
		{
			return true;
		}
		return false;
	}
	bool IsKeyCurrentlyPressed(int vKey)
	{
		if (IsGameWindowFocussed())
		{
			if (GetAsyncKeyState(vKey) & 0x8000)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		return false;
	}
	void looped::hotkeys_input()
	{
		g->settings.hotkeys.teleport_waypoint_triggered = IsKeyCurrentlyPressed(g->settings.hotkeys.teleport_waypoint);
		g->settings.hotkeys.teleport_objective_triggered = IsKeyCurrentlyPressed(g->settings.hotkeys.teleport_objective);
	}
}