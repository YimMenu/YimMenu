#pragma once
#include "gta/joaat.hpp"

namespace big
{
	// Add new values to the bottom
	enum class Infraction
	{
		NONE,
		TRIGGERED_ANTICHEAT,
		TRIED_CRASH_PLAYER,
		TRIED_KICK_PLAYER,
		ATTACKING_WITH_GODMODE,
		ATTACKING_WITH_INVISIBILITY,
		ATTACKING_WHEN_HIDDEN_FROM_PLAYER_LIST,
		SPOOFED_DATA,
		SPOOFED_HOST_TOKEN,
		INVALID_PLAYER_MODEL,
		SUPER_JUMP,
		UNDEAD_OTR,
		TSE_FREEZE,
		TSE_SENDER_MISMATCH,
		PLAYED_YOU_POS,
		PLAYED_YOU_NEG,
		GIVE_COLLECTIBLE,
		CASH_SPAWN,
		REPORT,
		VOTE_KICK,
		REMOVE_WEAPON
	};

	inline std::unordered_map<Infraction, const char*> infraction_desc = {
	    {Infraction::TRIGGERED_ANTICHEAT, "Triggered Rockstar's anticheat"},
	    {Infraction::TRIED_CRASH_PLAYER, "Tried to crash you"},
	    {Infraction::TRIED_KICK_PLAYER, "Tried to kick you"},
	    {Infraction::ATTACKING_WITH_GODMODE, "Attacked someone while using godmode"},
	    {Infraction::ATTACKING_WITH_INVISIBILITY, "Attacked someone while being invisible"},
	    {Infraction::ATTACKING_WHEN_HIDDEN_FROM_PLAYER_LIST, "Attacked someone while hidden in player list"},
	    {Infraction::SPOOFED_DATA, "Had spoofed data"},
	    {Infraction::SPOOFED_HOST_TOKEN, "Had spoofed their host token"},
	    {Infraction::INVALID_PLAYER_MODEL, "Had used an invalid player model"},
	    {Infraction::SUPER_JUMP, "Had used super jump"},
	    {Infraction::UNDEAD_OTR, "Had used undead OTR"},
	    {Infraction::TSE_FREEZE, "Tried TSE freeze you"},
	    {Infraction::TSE_SENDER_MISMATCH, "Sent TSE sender mismatch"},
	    {Infraction::PLAYED_YOU_POS, "Played with you positive"},
	    {Infraction::PLAYED_YOU_NEG, "Played with you negative"},
	    {Infraction::GIVE_COLLECTIBLE, "Tried to give collectible"},
	    {Infraction::CASH_SPAWN, "Spawning cash"},
	    {Infraction::REPORT, "Reported you"},
	    {Infraction::VOTE_KICK, "Trying to vote kick you"},
	    {Infraction::REMOVE_WEAPON, "Tried to remove weapon"},
	};
}