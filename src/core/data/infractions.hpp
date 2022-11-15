#pragma once
#include "gta/joaat.hpp"

namespace big
{
    inline std::unordered_map<rage::joaat_t, const char*> infractions =
	{
		{RAGE_JOAAT("desync_protection"), "Used desync protections"},
		{RAGE_JOAAT("breakup_detected"), "Kicked someone using breakup kick"},
		{RAGE_JOAAT("lost_connection_kick"), "Tried to kick someone using lost connection kick"},
		{RAGE_JOAAT("spoofing_rid"), "Had spoofed RID"},
		{RAGE_JOAAT("trigger_ac"), "Triggered Rockstar's anticheat"},
		{RAGE_JOAAT("crashed_player"), "Tried to crash you"},
		{RAGE_JOAAT("kicked_player"), "Tried to kick you"}
	};
}