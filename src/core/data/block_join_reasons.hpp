#pragma once

namespace big
{
	enum block_join_reason_t : int32_t
	{
		UNK_0 = 0,

		None = 1,

		UNK_2 = 2,
		UNK_3 = 3,
		UNK_4 = 4,

		// You have already been voted out of this game session.
		BeenVotedOut = 5,

		UNK_6 = 6,

		// Failed to join session due to incompatible assets.
		IncompatibleAssets = 7,

		// The session you're trying to join is currently full.
		SessionFull = 8,

		// The session you're trying to join is currently full of players.
		SlotFull = 9,

		// Please make sure all players have the latest Title Update.
		NoTitleUpdate = 10,

		UNK_11 = 11,

		// Invites are currently disabled in the session.
		InvitesDisabled = 12,

		// The session you are trying to join is using a different targeting preference. You can change your preference in the Settings tab of the Pause Menu in Grand Theft Auto V. Joining a new GTA Online Session.
		DifferentTargetingMode = 13,

		// You are classed as a cheat and can only play with other cheats until you are forgiven.
		Cheater = 14,

		UNK_15 = 15,

		// Incompatible downloadable content. All players must have the latest compatibility pack.
		IncompatibleDLC = 16,

		// You are trying to enter a Crew Members only session.
		CrewOnly = 17,

		// The session you are trying to join is for people who are not Bad Sports or cheaters - you are a Bad Sport.
		BadSport = 18,

		// The session you are trying to join is for Bad Sports only.
		BadSportOnly = 19,

		// The session you are trying to join is for cheaters only.
		CheatersOnly = 20,

		// The session you are trying to join no longer exists.
		SessionNoLongerExists = 21,

		// The session you are trying to join is private. You will need to be invited to join this session.
		InviteOnly = 22,

		// The session you are trying to join is a different build type.
		DifferentBuildType = 23,

		UNK_24 = 24,

		// The session you are trying to join is not using the same content.
		DifferentContent = 25,

		// The session you are trying to join is friends only.
		FriendsOnly = 26,

		// Unable to join this session, your account has a bad reputation.
		BadReputation = 27,

		// Unable to connect to session. The session may no longer exist.
		MayNotExist = 28,

		// Unable to Join. The session you are trying to join is a Premium Race. Joining and accepting invites is disabled for this mode.
		PremiumRace = 29
	};

	inline block_join_reason_t& operator++(block_join_reason_t& reason)
	{
		reason = static_cast<block_join_reason_t>(static_cast<int32_t>(reason) + 1);

		return reason;
	}

	inline block_join_reason_t operator++(block_join_reason_t& reason, int32_t)
	{
		block_join_reason_t a = reason;
		++reason;
		return a;
	}

	inline constexpr auto block_join_reasons = std::to_array({
	    "",                         // 0
	    "None",                     // 1
	    "",                         // 2
	    "",                         // 3
	    "",                         // 4
	    "Been Voted Out",           // 5
	    "",                         // 6
	    "Incompatible Assets",      // 7
	    "Session Full",             // 8
	    "Slot Full",                // 9
	    "No Title Update",          // 10
	    "",                         // 11
	    "Invites Disabled",         // 12
	    "Different Targeting Mode", // 13
	    "Cheater",                  // 14
	    "",                         // 15
	    "Incompatible DLC",         // 16
	    "Crew Only",                // 17
	    "Bad Sport",                // 18
	    "Bad Sports Only",          // 19
	    "Cheaters Only",            // 20
	    "Session No Longer Exists", // 21
	    "Invite Only",              // 22
	    "Different Build Type",     // 23
	    "",                         // 24
	    "Different Content",        // 25
	    "Friends Only",             // 26
	    "Bad Reputation",           // 27
	    "May Not Exist",            // 28
	    "Premium Race"              // 29
	});
}