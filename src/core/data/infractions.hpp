#pragma once
#include "gta/joaat.hpp"

namespace big
{
	// Add new values to the bottom
	enum class Infraction
	{
		DESYNC_PROTECTION,
		BREAKUP_KICK_DETECTED,
		LOST_CONNECTION_KICK_DETECTED,
		SPOOFED_ROCKSTAR_ID,
		TRIGGERED_ANTICHEAT,
		TRIED_CRASH_PLAYER,
		TRIED_KICK_PLAYER,
		BLAME_EXPLOSION_DETECTED,
		ATTACKING_WITH_GODMODE
	};

	inline std::unordered_map<Infraction, const char*> infraction_desc = {
	    {Infraction::DESYNC_PROTECTION, "Used desync protections"},
	    {Infraction::BREAKUP_KICK_DETECTED, "Kicked someone using breakup kick"},
	    {Infraction::LOST_CONNECTION_KICK_DETECTED, "Tried to kick someone using lost connection kick"},
	    {Infraction::SPOOFED_ROCKSTAR_ID, "Had spoofed RID"},
	    {Infraction::TRIGGERED_ANTICHEAT, "Triggered Rockstar's anticheat"},
	    {Infraction::TRIED_CRASH_PLAYER, "Tried to crash you"},
	    {Infraction::TRIED_KICK_PLAYER, "Tried to kick you"},
	    {Infraction::BLAME_EXPLOSION_DETECTED, "Tried to blame someone for their explosion"},
	    {Infraction::ATTACKING_WITH_GODMODE, "Attacked someone when using godmode"},
	};
}