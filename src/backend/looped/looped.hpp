#pragma once

namespace big
{
	class looped
	{
	public:
		static void hud_transition_state();
		static void hud_disable_input();

		static void player_spectate();

		static void session_force_thunder();

		static void system_self_globals();
		static void system_update_pointers();
		static void system_desync_kick_protection();
		static void system_spoofing();

		static void vehicle_auto_drive();
	};
}
