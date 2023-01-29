#pragma once
#include "core/data/levels.hpp"
#include "gta/joaat.hpp"
#include "natives.hpp"
#include "script_global.hpp"
#include "misc.hpp"

namespace big::local_player
{
	inline void get_active_character_slot(int* character_slot)
	{
		STATS::STAT_GET_INT(RAGE_JOAAT("MPPLY_LAST_MP_CHAR"), character_slot, true);
	}

	inline std::string get_mp_prefix()
	{
		get_active_character_slot(&g.player.character_slot);
		return "MP" + std::to_string(g.player.character_slot) + "_";
	}

	inline void set_player_level(int level)
	{
		STATS::STAT_SET_INT(rage::joaat(get_mp_prefix() + "CHAR_SET_RP_GIFT_ADMIN"), levels[level - 1], 0);
	}

	inline Hash get_text_stat_hash(std::string text)
	{
		std::transform(text.begin(), text.end(), text.begin(), ::tolower);
		if (text[0] == '$')
		{
			auto substr = text.substr(1);
			if (substr.substr(0, 3) == "mpx")
				substr[2] = g.player.character_slot + '0';
			return rage::joaat(substr);
		}
		return misc::get_text_value<Hash>(text);
	}

	inline void stat_set_int(std::string stat, std::string value)
	{
		if (stat == "" || value == "")
			return;
		STATS::STAT_SET_INT(get_text_stat_hash(stat), misc::get_text_value<int>(value), TRUE);
	}

	inline void stat_set_int(std::string stat, int value)
	{
		if (stat == "")
			return;
		STATS::STAT_SET_INT(get_text_stat_hash(stat), value, TRUE);
	}

	inline void stat_set_bool(std::string stat, std::string value)
	{
		if (stat == "" || value == "")
			return;
		STATS::STAT_SET_BOOL(get_text_stat_hash(stat), misc::get_text_value<bool>(value), TRUE);
	}

	inline void stat_set_bool(std::string stat, bool value) { stat_set_bool(stat, std::to_string(value)); }

	inline void stat_set_float(std::string stat, std::string value)
	{
		if (stat == "" || value == "")
			return;
		STATS::STAT_SET_FLOAT(get_text_stat_hash(stat), misc::get_text_value<float>(value), TRUE);
	}

	inline void stat_set_float(std::string stat, float value) { stat_set_float(stat, std::to_string(value)); }

	inline void stat_increment(std::string stat, std::string value)
	{
		if (stat == "" || value == "")
			return;
		STATS::STAT_INCREMENT(get_text_stat_hash(stat), misc::get_text_value<float>(value));
	}

	inline void stat_increment(std::string stat, float value) { stat_increment(stat, std::to_string(value)); }

	inline void stat_set_date(std::string stat, std::string value)
	{
		if (stat == "" || value == "")
			return;
		std::vector<int64_t> strs = misc::split<int64_t>(value, ' ');
		int64_t dates[7]{};
		STATS::STAT_GET_DATE(get_text_stat_hash(stat), (Any*)dates, 7, -1);
		while (strs.size() < 7) //Writing will succeed only when size is greater than or equal to 7
			strs.push_back(dates[strs.size()]);
		STATS::STAT_SET_DATE(get_text_stat_hash(stat), (Any*)strs.data(), strs.size(), TRUE);
	}

	inline void stat_set_string(std::string stat, std::string value)
	{
		if (stat == "")
			return;
		STATS::STAT_SET_STRING(get_text_stat_hash(stat), value.c_str(), TRUE);
	}

	inline void stat_set_label(std::string stat, std::string value)
	{
		if (stat == "")
			return;
		STATS::STAT_SET_GXT_LABEL(get_text_stat_hash(stat), value.c_str(), TRUE);
	}

	inline void stat_set_user_id(std::string stat, std::string value)
	{
		if (stat == "")
			return;
		STATS::STAT_SET_USER_ID(get_text_stat_hash(stat), value.c_str(), TRUE);
	}

	inline int stat_get_int(std::string stat)
	{
		int result = 0;
		if (stat != "")
			STATS::STAT_GET_INT(get_text_stat_hash(stat), &result, -1);
		return result;
	}

	inline bool stat_get_bool(std::string stat)
	{
		int result = 0;
		if (stat != "")
			STATS::STAT_GET_BOOL(get_text_stat_hash(stat), &result, -1);
		return result;
	}

	inline float stat_get_float(std::string stat)
	{
		float result = 0;
		if (stat != "")
			STATS::STAT_GET_FLOAT(get_text_stat_hash(stat), &result, -1);
		return result;
	}

	inline std::string stat_get_date(std::string stat)
	{
		int64_t result[7]{};
		if (stat != "")
			STATS::STAT_GET_DATE(get_text_stat_hash(stat), (Any*)&result, 7, -1);
		return std::format("{} {} {} {} {} {} {}", result[0], result[1], result[2], result[3], result[4], result[5], result[6]);
	}

	inline std::string stat_get_string(std::string stat)
	{
		std::string result = "";
		if (stat != "")
			result = STATS::STAT_GET_STRING(get_text_stat_hash(stat), -1);
		return result;
	}

	inline std::string stat_get_user_id(std::string stat)
	{
		std::string result = "";
		if (stat != "")
			result = STATS::STAT_GET_USER_ID(get_text_stat_hash(stat));
		return result;
	}

	template<typename T, typename ...Args>
	inline void stat_set_bits(std::string stat, T arg, Args... args)
	{
		if (stat == "")
			return;

		int value = stat_get_int(stat);
		value |= 1 << arg;

		([&](int tmp) { value |= 1 << tmp; }(args), ...);

		stat_set_int(stat, value);
	}

	template<typename T, typename ...Args>
	inline void stat_clear_bits(std::string stat, T arg, Args... args)
	{
		if (stat == "")
			return;

		int value = stat_get_int(stat);
		value &= ~(1 << arg);

		([&](int tmp) { value &= ~(1 << tmp); }(args), ...);

		stat_set_int(stat, value);
	}

	template<typename T, typename ...Args>
	inline bool stat_bits_test(std::string stat, T arg, Args... args)
	{
		if (stat == "")
			return false;

		int value = 0;
		value |= 1 << arg;

		([&](int tmp) { value |= 1 << tmp; }(args), ...);

		return (stat_get_int(stat) & value) == value;
	}

	inline void packed_stat_set_int(std::string index, std::string value)
	{
		if (index == "" || value == "")
			return;
		std::vector<int> index_v = misc::split<int>(index, ' ');
		int index_min = index_v[0];
		int index_max = index_min;
		if (index_v.size() >= 2)
			index_max = index_v[1];
		int value_n = misc::get_text_value<int>(value);
		for (int i = index_min; i <= index_max; i++)
			STATS::SET_PACKED_STAT_INT_CODE(i, value_n, g.player.character_slot);
	}

	inline void packed_stat_set_int(std::string index, int value) { packed_stat_set_int(index, std::to_string(value)); }

	inline void packed_stat_set_bool(std::string index, std::string value)
	{
		if (index == "" || value == "")
			return;
		std::vector<int> index_v = misc::split<int>(index, ' ');
		int index_min = index_v[0];
		int index_max = index_min;
		if (index_v.size() >= 2)
			index_max = index_v[1];
		int value_b = misc::get_text_value<bool>(value);
		for (int i = index_min; i <= index_max; i++)
			STATS::SET_PACKED_STAT_BOOL_CODE(i, value_b, g.player.character_slot);
	}

	inline void packed_stat_set_bool(std::string index, bool value) { packed_stat_set_bool(index, std::to_string(value)); }

	inline int packed_stat_get_int(std::string index)
	{
		int result = 0;
		std::string str;
		std::stringstream ss(index);
		std::getline(ss, str, ' ');
		if (str != "")
			result = STATS::GET_PACKED_STAT_INT_CODE(misc::get_text_value<int>(str), g.player.character_slot);
		return result;
	}

	inline bool packed_stat_get_bool(std::string index)
	{
		int result = 0;
		std::string str;
		std::stringstream ss(index);
		std::getline(ss, str, ' ');
		if (str != "")
			result = STATS::GET_PACKED_STAT_BOOL_CODE(misc::get_text_value<int>(str), g.player.character_slot);
		return result;
	}
}