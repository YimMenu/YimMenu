#pragma once

namespace big
{
	// Lua API: Infraction
	enum class Infraction
	{
		// Add new values to the bottom (for serialization)

		DESYNC_PROTECTION,
		BREAKUP_KICK_DETECTED,         // do not use
		LOST_CONNECTION_KICK_DETECTED, // do not use
		SPOOFED_ROCKSTAR_ID,           // do not use
		TRIGGERED_ANTICHEAT,
		TRIED_CRASH_PLAYER,
		TRIED_KICK_PLAYER,
		BLAME_EXPLOSION_DETECTED, // do not use (for now)
		ATTACKING_WITH_GODMODE,
		ATTACKING_WITH_INVISIBILITY,
		ATTACKING_WHEN_HIDDEN_FROM_PLAYER_LIST,
		SPOOFED_DATA,
		SPOOFED_HOST_TOKEN,
		INVALID_PLAYER_MODEL,
		SUPER_JUMP,
		UNDEAD_OTR,
		// So that lua scripts can add a custom runtime reason.
		CUSTOM_REASON,
		CHAT_SPAM,
		SENT_MODDER_BEACONS
	};
}