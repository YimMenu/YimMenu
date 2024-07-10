#pragma once
#include "persistent_player.hpp"

#include "core/data/infractions.hpp"

namespace big
{
	static std::unordered_map<Infraction, const char*> infraction_desc = {
	    {Infraction::DESYNC_PROTECTION, "Used desync protections"},
	    {Infraction::BREAKUP_KICK_DETECTED, "Kicked someone using breakup kick"},
	    {Infraction::LOST_CONNECTION_KICK_DETECTED, "Tried to kick someone using lost connection kick"},
	    {Infraction::SPOOFED_ROCKSTAR_ID, "Had spoofed RID"},
	    {Infraction::TRIGGERED_ANTICHEAT, "Triggered Rockstar's anticheat"},
	    {Infraction::TRIED_CRASH_PLAYER, "Tried to crash you"},
	    {Infraction::TRIED_KICK_PLAYER, "Tried to kick you"},
	    {Infraction::BLAME_EXPLOSION_DETECTED, "Tried to blame someone for their explosion"},
	    {Infraction::ATTACKING_WITH_GODMODE, "Attacked someone while using godmode"},
	    {Infraction::ATTACKING_WITH_INVISIBILITY, "Attacked someone while being invisible"},
	    {Infraction::ATTACKING_WHEN_HIDDEN_FROM_PLAYER_LIST, "Attacked someone while being hidden from the player list"},
	    {Infraction::SPOOFED_DATA, "Had spoofed data"},
	    {Infraction::SPOOFED_HOST_TOKEN, "Had spoofed their host token"},
	    {Infraction::INVALID_PLAYER_MODEL, "Had used an invalid player model"},
	    {Infraction::SUPER_JUMP, "Had used super jump"},
	    {Infraction::UNDEAD_OTR, "Had used undead OTR"},
	    {Infraction::CUSTOM_REASON, ""},
	    {Infraction::CHAT_SPAM, "Chat spammer"},
	    {Infraction::SENT_MODDER_BEACONS, "Sent modder beacons"},
	};

	const char* persistent_player::get_infraction_description(int infraction)
	{
		if (static_cast<Infraction>(infraction) == Infraction::CUSTOM_REASON)
		{
			return custom_infraction_reason.c_str();
		}

		return infraction_desc[static_cast<Infraction>(infraction)];
	}

	std::string persistent_player::get_all_infraction_descriptions()
	{
		if (!infractions.size())
		{
			return "";
		}

		constexpr auto separator          = ", ";
		constexpr size_t separator_length = (std::string(separator)).size();

		std::string s;

		for (const auto infr : infractions)
		{
			s += get_infraction_description(infr);
			s += separator;
		}

		// Remove last useless separator
		for (size_t i = 0; i < separator_length; i++)
		{
			s.pop_back();
		}

		return s;
	}
}
