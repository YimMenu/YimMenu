#pragma once

namespace big
{
	inline std::unordered_map<int, const char*> block_join_reasons = {
	    {1, "None"},
	    {5, "Been Voted Out"},           // You have already been voted out of this game session.
	    {7, "Incompatible Assets"},      // Failed to join session due to incompatible assets.
	    {8, "Session Full"},             // The session you're trying to join is currently full.
	    {9, "Slot Full"},                // The session you're trying to join is currently full of players.
	    {10, "No Title Update"},         // Please make sure all players have the latest Title Update.
	    {12, "Invites Disabled"},        // Invites are currently disabled in the session.
	    {13, "Different Targeting Mode"},// The session you are trying to join is using a different targeting preference. You can change your preference in the Settings tab of the Pause Menu in Grand Theft Auto V. Joining a new GTA Online Session.
	    {14, "Cheater"},// You are classed as a cheat and can only play with other cheats until you are forgiven.
	    {16, "Incompatible DLC"},// Incompatible downloadable content. All players must have the latest compatibility pack.
	    {17, "Crew Only"},       // You are trying to enter a Crew Members only session.
	    {21, "Session No Longer Exists"},// The session you are trying to join no longer exists.
	    {22, "Invite Only"},// The session you are trying to join is private. You will need to be invited to join this session.
	    {26, "Friends Only"},        // The session you are trying to join is friends only.
	    {23, "Different Build Type"},// The session you are trying to join is a different build type.
	    {25, "Different Content"},   // The session you are trying to join is not using the same content.
	    {18, "Bad Sport"},// The session you are trying to join is for people who are not Bad Sports or cheaters - you are a Bad Sport.
	    {19, "Bad Sports Only"},// The session you are trying to join is for Bad Sports only.
	    {20, "Cheaters Only"},  // The session you are trying to join is for cheaters only.
	    {27, "Bad Reputation"}, // Unable to join this session, your account has a bad reputation.
	    {28, "May Not Exist"},  // Unable to connect to session. The session may no longer exist.
	    {29, "Premium Race"},// Unable to Join. The session you are trying to join is a Premium Race. Joining and accepting invites is disabled for this mode.
	};
}