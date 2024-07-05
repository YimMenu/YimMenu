#include "lua_native_binding.hpp"
#include "natives.hpp"

namespace lua::native
{
	static bool LUA_NATIVE_STATS_STAT_CLEAR_SLOT_FOR_RELOAD(int statSlot)
	{
		auto retval = (bool)STATS::STAT_CLEAR_SLOT_FOR_RELOAD(statSlot);
		return retval;
	}

	static bool LUA_NATIVE_STATS_STAT_LOAD(int statSlot)
	{
		auto retval = (bool)STATS::STAT_LOAD(statSlot);
		return retval;
	}

	static bool LUA_NATIVE_STATS_STAT_SAVE(int p0, bool p1, int p2, bool p3)
	{
		auto retval = (bool)STATS::STAT_SAVE(p0, p1, p2, p3);
		return retval;
	}

	static void LUA_NATIVE_STATS_STAT_SET_OPEN_SAVETYPE_IN_JOB(int p0)
	{
		STATS::STAT_SET_OPEN_SAVETYPE_IN_JOB(p0);
	}

	static bool LUA_NATIVE_STATS_STAT_LOAD_PENDING(int statSlot)
	{
		auto retval = (bool)STATS::STAT_LOAD_PENDING(statSlot);
		return retval;
	}

	static bool LUA_NATIVE_STATS_STAT_SAVE_PENDING()
	{
		auto retval = (bool)STATS::STAT_SAVE_PENDING();
		return retval;
	}

	static bool LUA_NATIVE_STATS_STAT_SAVE_PENDING_OR_REQUESTED()
	{
		auto retval = (bool)STATS::STAT_SAVE_PENDING_OR_REQUESTED();
		return retval;
	}

	static bool LUA_NATIVE_STATS_STAT_DELETE_SLOT(int p0)
	{
		auto retval = (bool)STATS::STAT_DELETE_SLOT(p0);
		return retval;
	}

	static bool LUA_NATIVE_STATS_STAT_SLOT_IS_LOADED(int statSlot)
	{
		auto retval = (bool)STATS::STAT_SLOT_IS_LOADED(statSlot);
		return retval;
	}

	static bool LUA_NATIVE_STATS_STAT_CLOUD_SLOT_LOAD_FAILED(int p0)
	{
		auto retval = (bool)STATS::STAT_CLOUD_SLOT_LOAD_FAILED(p0);
		return retval;
	}

	static int LUA_NATIVE_STATS_STAT_CLOUD_SLOT_LOAD_FAILED_CODE(Any p0)
	{
		auto retval = STATS::STAT_CLOUD_SLOT_LOAD_FAILED_CODE(p0);
		return retval;
	}

	static void LUA_NATIVE_STATS_STAT_SET_BLOCK_SAVES(bool toggle)
	{
		STATS::STAT_SET_BLOCK_SAVES(toggle);
	}

	static bool LUA_NATIVE_STATS_STAT_GET_BLOCK_SAVES()
	{
		auto retval = (bool)STATS::STAT_GET_BLOCK_SAVES();
		return retval;
	}

	static bool LUA_NATIVE_STATS_STAT_CLOUD_SLOT_SAVE_FAILED(Any p0)
	{
		auto retval = (bool)STATS::STAT_CLOUD_SLOT_SAVE_FAILED(p0);
		return retval;
	}

	static void LUA_NATIVE_STATS_STAT_CLEAR_PENDING_SAVES(Any p0)
	{
		STATS::STAT_CLEAR_PENDING_SAVES(p0);
	}

	static bool LUA_NATIVE_STATS_STAT_LOAD_DIRTY_READ_DETECTED()
	{
		auto retval = (bool)STATS::STAT_LOAD_DIRTY_READ_DETECTED();
		return retval;
	}

	static void LUA_NATIVE_STATS_STAT_CLEAR_DIRTY_READ_DETECTED()
	{
		STATS::STAT_CLEAR_DIRTY_READ_DETECTED();
	}

	static bool LUA_NATIVE_STATS_STAT_GET_LOAD_SAFE_TO_PROGRESS_TO_MP_FROM_SP()
	{
		auto retval = (bool)STATS::STAT_GET_LOAD_SAFE_TO_PROGRESS_TO_MP_FROM_SP();
		return retval;
	}

	static Hash LUA_NATIVE_STATS_GET_STAT_HASH_FOR_CHARACTER_STAT_(int dataType, int statIndex, int charSlot)
	{
		auto retval = STATS::_GET_STAT_HASH_FOR_CHARACTER_STAT(dataType, statIndex, charSlot);
		return retval;
	}

	static bool LUA_NATIVE_STATS_STAT_SET_INT(Hash statName, int value, bool save)
	{
		auto retval = (bool)STATS::STAT_SET_INT(statName, value, save);
		return retval;
	}

	static bool LUA_NATIVE_STATS_STAT_SET_FLOAT(Hash statName, float value, bool save)
	{
		auto retval = (bool)STATS::STAT_SET_FLOAT(statName, value, save);
		return retval;
	}

	static bool LUA_NATIVE_STATS_STAT_SET_BOOL(Hash statName, bool value, bool save)
	{
		auto retval = (bool)STATS::STAT_SET_BOOL(statName, value, save);
		return retval;
	}

	static bool LUA_NATIVE_STATS_STAT_SET_GXT_LABEL(Hash statName, sol::stack_object value, bool save)
	{
		auto retval = (bool)STATS::STAT_SET_GXT_LABEL(statName, value.is<const char*>() ? value.as<const char*>() : nullptr, save);
		return retval;
	}

	static bool LUA_NATIVE_STATS_STAT_SET_DATE(Hash statName, uintptr_t value, int numFields, bool save)
	{
		auto retval = (bool)STATS::STAT_SET_DATE(statName, (Any*)value, numFields, save);
		return retval;
	}

	static bool LUA_NATIVE_STATS_STAT_SET_STRING(Hash statName, sol::stack_object value, bool save)
	{
		auto retval = (bool)STATS::STAT_SET_STRING(statName, value.is<const char*>() ? value.as<const char*>() : nullptr, save);
		return retval;
	}

	static bool LUA_NATIVE_STATS_STAT_SET_POS(Hash statName, float x, float y, float z, bool save)
	{
		auto retval = (bool)STATS::STAT_SET_POS(statName, x, y, z, save);
		return retval;
	}

	static bool LUA_NATIVE_STATS_STAT_SET_MASKED_INT(Hash statName, int p1, int p2, int p3, bool save)
	{
		auto retval = (bool)STATS::STAT_SET_MASKED_INT(statName, p1, p2, p3, save);
		return retval;
	}

	static bool LUA_NATIVE_STATS_STAT_SET_USER_ID(Hash statName, sol::stack_object value, bool save)
	{
		auto retval = (bool)STATS::STAT_SET_USER_ID(statName, value.is<const char*>() ? value.as<const char*>() : nullptr, save);
		return retval;
	}

	static bool LUA_NATIVE_STATS_STAT_SET_CURRENT_POSIX_TIME(Hash statName, bool p1)
	{
		auto retval = (bool)STATS::STAT_SET_CURRENT_POSIX_TIME(statName, p1);
		return retval;
	}

	static std::tuple<bool, int> LUA_NATIVE_STATS_STAT_GET_INT(Hash statHash, int outValue, int p2)
	{
		std::tuple<bool, int> return_values;
		std::get<0>(return_values) = (bool)STATS::STAT_GET_INT(statHash, &outValue, p2);
		std::get<1>(return_values) = outValue;

		return return_values;
	}

	static std::tuple<bool, float> LUA_NATIVE_STATS_STAT_GET_FLOAT(Hash statHash, float outValue, Any p2)
	{
		std::tuple<bool, float> return_values;
		std::get<0>(return_values) = (bool)STATS::STAT_GET_FLOAT(statHash, &outValue, p2);
		std::get<1>(return_values) = outValue;

		return return_values;
	}

	static std::tuple<bool, bool> LUA_NATIVE_STATS_STAT_GET_BOOL(Hash statHash, bool outValue, Any p2)
	{
		std::tuple<bool, bool> return_values;
		std::get<0>(return_values) = (bool)STATS::STAT_GET_BOOL(statHash, (BOOL*)&outValue, p2);
		std::get<1>(return_values) = outValue;

		return return_values;
	}

	static bool LUA_NATIVE_STATS_STAT_GET_DATE(Hash statHash, uintptr_t outValue, int numFields, Any p3)
	{
		auto retval = (bool)STATS::STAT_GET_DATE(statHash, (Any*)outValue, numFields, p3);
		return retval;
	}

	static const char* LUA_NATIVE_STATS_STAT_GET_STRING(Hash statHash, int p1)
	{
		auto retval = STATS::STAT_GET_STRING(statHash, p1);
		return retval;
	}

	static std::tuple<bool, float, float, float> LUA_NATIVE_STATS_STAT_GET_POS(Hash statName, float outX, float outY, float outZ, Any p4)
	{
		std::tuple<bool, float, float, float> return_values;
		std::get<0>(return_values) = (bool)STATS::STAT_GET_POS(statName, &outX, &outY, &outZ, p4);
		std::get<1>(return_values) = outX;
		std::get<2>(return_values) = outY;
		std::get<3>(return_values) = outZ;

		return return_values;
	}

	static std::tuple<bool, int> LUA_NATIVE_STATS_STAT_GET_MASKED_INT(Hash statHash, int outValue, int p2, int p3, Any p4)
	{
		std::tuple<bool, int> return_values;
		std::get<0>(return_values) = (bool)STATS::STAT_GET_MASKED_INT(statHash, &outValue, p2, p3, p4);
		std::get<1>(return_values) = outValue;

		return return_values;
	}

	static const char* LUA_NATIVE_STATS_STAT_GET_USER_ID(Hash statHash)
	{
		auto retval = STATS::STAT_GET_USER_ID(statHash);
		return retval;
	}

	static const char* LUA_NATIVE_STATS_STAT_GET_LICENSE_PLATE(Hash statName)
	{
		auto retval = STATS::STAT_GET_LICENSE_PLATE(statName);
		return retval;
	}

	static bool LUA_NATIVE_STATS_STAT_SET_LICENSE_PLATE(Hash statName, sol::stack_object str)
	{
		auto retval = (bool)STATS::STAT_SET_LICENSE_PLATE(statName, str.is<const char*>() ? str.as<const char*>() : nullptr);
		return retval;
	}

	static void LUA_NATIVE_STATS_STAT_INCREMENT(Hash statName, float value)
	{
		STATS::STAT_INCREMENT(statName, value);
	}

	static bool LUA_NATIVE_STATS_STAT_COMMUNITY_START_SYNCH()
	{
		auto retval = (bool)STATS::STAT_COMMUNITY_START_SYNCH();
		return retval;
	}

	static bool LUA_NATIVE_STATS_STAT_COMMUNITY_SYNCH_IS_PENDING()
	{
		auto retval = (bool)STATS::STAT_COMMUNITY_SYNCH_IS_PENDING();
		return retval;
	}

	static std::tuple<bool, float> LUA_NATIVE_STATS_STAT_COMMUNITY_GET_HISTORY(Hash statName, int p1, float outValue)
	{
		std::tuple<bool, float> return_values;
		std::get<0>(return_values) = (bool)STATS::STAT_COMMUNITY_GET_HISTORY(statName, p1, &outValue);
		std::get<1>(return_values) = outValue;

		return return_values;
	}

	static void LUA_NATIVE_STATS_STAT_RESET_ALL_ONLINE_CHARACTER_STATS(int p0)
	{
		STATS::STAT_RESET_ALL_ONLINE_CHARACTER_STATS(p0);
	}

	static void LUA_NATIVE_STATS_STAT_LOCAL_RESET_ALL_ONLINE_CHARACTER_STATS(int p0)
	{
		STATS::STAT_LOCAL_RESET_ALL_ONLINE_CHARACTER_STATS(p0);
	}

	static int LUA_NATIVE_STATS_STAT_GET_NUMBER_OF_DAYS(Hash statName)
	{
		auto retval = STATS::STAT_GET_NUMBER_OF_DAYS(statName);
		return retval;
	}

	static int LUA_NATIVE_STATS_STAT_GET_NUMBER_OF_HOURS(Hash statName)
	{
		auto retval = STATS::STAT_GET_NUMBER_OF_HOURS(statName);
		return retval;
	}

	static int LUA_NATIVE_STATS_STAT_GET_NUMBER_OF_MINUTES(Hash statName)
	{
		auto retval = STATS::STAT_GET_NUMBER_OF_MINUTES(statName);
		return retval;
	}

	static int LUA_NATIVE_STATS_STAT_GET_NUMBER_OF_SECONDS(Hash statName)
	{
		auto retval = STATS::STAT_GET_NUMBER_OF_SECONDS(statName);
		return retval;
	}

	static void LUA_NATIVE_STATS_STAT_SET_PROFILE_SETTING_VALUE(int profileSetting, int value)
	{
		STATS::STAT_SET_PROFILE_SETTING_VALUE(profileSetting, value);
	}

	static void LUA_NATIVE_STATS_STATS_COMPLETED_CHARACTER_CREATION(Any p0)
	{
		STATS::STATS_COMPLETED_CHARACTER_CREATION(p0);
	}

	static int LUA_NATIVE_STATS_PACKED_STAT_GET_INT_STAT_INDEX(int p0)
	{
		auto retval = STATS::PACKED_STAT_GET_INT_STAT_INDEX(p0);
		return retval;
	}

	static Hash LUA_NATIVE_STATS_GET_PACKED_INT_STAT_KEY(int index, bool spStat, bool charStat, int character)
	{
		auto retval = STATS::GET_PACKED_INT_STAT_KEY(index, spStat, charStat, character);
		return retval;
	}

	static Hash LUA_NATIVE_STATS_GET_PACKED_TU_INT_STAT_KEY(int index, bool spStat, bool charStat, int character)
	{
		auto retval = STATS::GET_PACKED_TU_INT_STAT_KEY(index, spStat, charStat, character);
		return retval;
	}

	static Hash LUA_NATIVE_STATS_GET_PACKED_NG_INT_STAT_KEY(int index, bool spStat, bool charStat, int character, sol::stack_object section)
	{
		auto retval = STATS::GET_PACKED_NG_INT_STAT_KEY(index, spStat, charStat, character, section.is<const char*>() ? section.as<const char*>() : nullptr);
		return retval;
	}

	static bool LUA_NATIVE_STATS_GET_PACKED_STAT_BOOL_CODE(int index, int characterSlot)
	{
		auto retval = (bool)STATS::GET_PACKED_STAT_BOOL_CODE(index, characterSlot);
		return retval;
	}

	static int LUA_NATIVE_STATS_GET_PACKED_STAT_INT_CODE(int index, int characterSlot)
	{
		auto retval = STATS::GET_PACKED_STAT_INT_CODE(index, characterSlot);
		return retval;
	}

	static void LUA_NATIVE_STATS_SET_PACKED_STAT_BOOL_CODE(int index, bool value, int characterSlot)
	{
		STATS::SET_PACKED_STAT_BOOL_CODE(index, value, characterSlot);
	}

	static void LUA_NATIVE_STATS_SET_PACKED_STAT_INT_CODE(int index, int value, int characterSlot)
	{
		STATS::SET_PACKED_STAT_INT_CODE(index, value, characterSlot);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_BACKGROUND_SCRIPT_ACTION(sol::stack_object action, int value)
	{
		STATS::PLAYSTATS_BACKGROUND_SCRIPT_ACTION(action.is<const char*>() ? action.as<const char*>() : nullptr, value);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_FLOW_LOW_(float posX, float posY, float posZ, sol::stack_object p3, Any p4, int amount)
	{
		STATS::_PLAYSTATS_FLOW_LOW(posX, posY, posZ, p3.is<const char*>() ? p3.as<const char*>() : nullptr, p4, amount);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_FLOW_MEDIUM_(float x, float y, float z, sol::stack_object interiorAction, int p4, Hash p5)
	{
		STATS::_PLAYSTATS_FLOW_MEDIUM(x, y, z, interiorAction.is<const char*>() ? interiorAction.as<const char*>() : nullptr, p4, p5);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_NPC_INVITE(sol::stack_object p0)
	{
		STATS::PLAYSTATS_NPC_INVITE(p0.is<const char*>() ? p0.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_AWARD_XP(int amount, Hash type, Hash category)
	{
		STATS::PLAYSTATS_AWARD_XP(amount, type, category);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_RANK_UP(int rank)
	{
		STATS::PLAYSTATS_RANK_UP(rank);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_STARTED_SESSION_IN_OFFLINEMODE()
	{
		STATS::PLAYSTATS_STARTED_SESSION_IN_OFFLINEMODE();
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_ACTIVITY_DONE(int p0, int activityId, Any p2)
	{
		STATS::PLAYSTATS_ACTIVITY_DONE(p0, activityId, p2);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_LEAVE_JOB_CHAIN(Any p0, Any p1, Any p2, Any p3, Any p4)
	{
		STATS::PLAYSTATS_LEAVE_JOB_CHAIN(p0, p1, p2, p3, p4);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_MISSION_STARTED(sol::stack_object p0, Any p1, Any p2, bool p3)
	{
		STATS::PLAYSTATS_MISSION_STARTED(p0.is<const char*>() ? p0.as<const char*>() : nullptr, p1, p2, p3);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_MISSION_OVER(sol::stack_object p0, Any p1, Any p2, bool p3, bool p4, bool p5)
	{
		STATS::PLAYSTATS_MISSION_OVER(p0.is<const char*>() ? p0.as<const char*>() : nullptr, p1, p2, p3, p4, p5);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_MISSION_CHECKPOINT(sol::stack_object p0, Any p1, Any p2, Any p3)
	{
		STATS::PLAYSTATS_MISSION_CHECKPOINT(p0.is<const char*>() ? p0.as<const char*>() : nullptr, p1, p2, p3);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_RANDOM_MISSION_DONE(sol::stack_object name, Any p1, Any p2, Any p3)
	{
		STATS::PLAYSTATS_RANDOM_MISSION_DONE(name.is<const char*>() ? name.as<const char*>() : nullptr, p1, p2, p3);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_ROS_BET(int amount, int act, Player player, float cm)
	{
		STATS::PLAYSTATS_ROS_BET(amount, act, player, cm);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_RACE_CHECKPOINT(Vehicle p0, Any p1, int p2, int p3, Any p4)
	{
		STATS::PLAYSTATS_RACE_CHECKPOINT(p0, p1, p2, p3, p4);
	}

	static std::tuple<bool, int, int> LUA_NATIVE_STATS_PLAYSTATS_CREATE_MATCH_HISTORY_ID_2(int playerAccountId, int posixTime)
	{
		std::tuple<bool, int, int> return_values;
		std::get<0>(return_values) = (bool)STATS::PLAYSTATS_CREATE_MATCH_HISTORY_ID_2(&playerAccountId, &posixTime);
		std::get<1>(return_values) = playerAccountId;
		std::get<2>(return_values) = posixTime;

		return return_values;
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_MATCH_STARTED(Any p0, Any p1, Any p2)
	{
		STATS::PLAYSTATS_MATCH_STARTED(p0, p1, p2);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_SHOP_ITEM(Any p0, Any p1, Any p2, Any p3, Any p4)
	{
		STATS::PLAYSTATS_SHOP_ITEM(p0, p1, p2, p3, p4);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_CRATE_DROP_MISSION_DONE(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7)
	{
		STATS::PLAYSTATS_CRATE_DROP_MISSION_DONE(p0, p1, p2, p3, p4, p5, p6, p7);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_CRATE_CREATED(float p0, float p1, float p2)
	{
		STATS::PLAYSTATS_CRATE_CREATED(p0, p1, p2);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_HOLD_UP_MISSION_DONE(Any p0, Any p1, Any p2, Any p3)
	{
		STATS::PLAYSTATS_HOLD_UP_MISSION_DONE(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_IMPORT_EXPORT_MISSION_DONE(Any p0, Any p1, Any p2, Any p3)
	{
		STATS::PLAYSTATS_IMPORT_EXPORT_MISSION_DONE(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_RACE_TO_POINT_MISSION_DONE(int p0, Any p1, Any p2, Any p3)
	{
		STATS::PLAYSTATS_RACE_TO_POINT_MISSION_DONE(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_ACQUIRED_HIDDEN_PACKAGE(Any p0)
	{
		STATS::PLAYSTATS_ACQUIRED_HIDDEN_PACKAGE(p0);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_WEBSITE_VISITED(Hash scaleformHash, int p1)
	{
		STATS::PLAYSTATS_WEBSITE_VISITED(scaleformHash, p1);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_FRIEND_ACTIVITY(int p0, bool p1)
	{
		STATS::PLAYSTATS_FRIEND_ACTIVITY(p0, p1);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_ODDJOB_DONE(int totalTimeMs, int p1, bool p2)
	{
		STATS::PLAYSTATS_ODDJOB_DONE(totalTimeMs, p1, p2);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_PROP_CHANGE(Ped p0, int p1, int p2, int p3)
	{
		STATS::PLAYSTATS_PROP_CHANGE(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_CLOTH_CHANGE(Ped p0, Any p1, Any p2, Any p3, Any p4)
	{
		STATS::PLAYSTATS_CLOTH_CHANGE(p0, p1, p2, p3, p4);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_WEAPON_MODE_CHANGE(Hash weaponHash, Hash componentHashTo, Hash componentHashFrom)
	{
		STATS::PLAYSTATS_WEAPON_MODE_CHANGE(weaponHash, componentHashTo, componentHashFrom);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_CHEAT_APPLIED(sol::stack_object cheat)
	{
		STATS::PLAYSTATS_CHEAT_APPLIED(cheat.is<const char*>() ? cheat.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_JOB_ACTIVITY_END(uintptr_t p0, uintptr_t p1, uintptr_t p2, uintptr_t p3)
	{
		STATS::PLAYSTATS_JOB_ACTIVITY_END((Any*)p0, (Any*)p1, (Any*)p2, (Any*)p3);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_JOB_BEND(uintptr_t p0, uintptr_t p1, uintptr_t p2, uintptr_t p3)
	{
		STATS::PLAYSTATS_JOB_BEND((Any*)p0, (Any*)p1, (Any*)p2, (Any*)p3);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_JOB_LTS_END(uintptr_t p0, uintptr_t p1, uintptr_t p2, uintptr_t p3)
	{
		STATS::PLAYSTATS_JOB_LTS_END((Any*)p0, (Any*)p1, (Any*)p2, (Any*)p3);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_JOB_LTS_ROUND_END(uintptr_t p0, uintptr_t p1, uintptr_t p2, uintptr_t p3)
	{
		STATS::PLAYSTATS_JOB_LTS_ROUND_END((Any*)p0, (Any*)p1, (Any*)p2, (Any*)p3);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_QUICKFIX_TOOL(int element, sol::stack_object item)
	{
		STATS::PLAYSTATS_QUICKFIX_TOOL(element, item.is<const char*>() ? item.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_IDLE_KICK(int msStoodIdle)
	{
		STATS::PLAYSTATS_IDLE_KICK(msStoodIdle);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_SET_JOIN_TYPE(int joinType)
	{
		STATS::PLAYSTATS_SET_JOIN_TYPE(joinType);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_HEIST_SAVE_CHEAT(Hash hash, int p1)
	{
		STATS::PLAYSTATS_HEIST_SAVE_CHEAT(hash, p1);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_APPEND_DIRECTOR_METRIC(uintptr_t p0)
	{
		STATS::PLAYSTATS_APPEND_DIRECTOR_METRIC((Any*)p0);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_AWARD_BAD_SPORT(int id)
	{
		STATS::PLAYSTATS_AWARD_BAD_SPORT(id);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_PEGASUS_AS_PERSONAL_AIRCRAFT(Hash modelHash)
	{
		STATS::PLAYSTATS_PEGASUS_AS_PERSONAL_AIRCRAFT(modelHash);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_SHOPMENU_NAV_(Any p0, Any p1, Any p2, Any p3)
	{
		STATS::_PLAYSTATS_SHOPMENU_NAV(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_FM_EVENT_CHALLENGES(Any p0)
	{
		STATS::PLAYSTATS_FM_EVENT_CHALLENGES(p0);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_FM_EVENT_VEHICLETARGET(Any p0)
	{
		STATS::PLAYSTATS_FM_EVENT_VEHICLETARGET(p0);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_FM_EVENT_URBANWARFARE(Any p0)
	{
		STATS::PLAYSTATS_FM_EVENT_URBANWARFARE(p0);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_FM_EVENT_CHECKPOINTCOLLECTION(Any p0)
	{
		STATS::PLAYSTATS_FM_EVENT_CHECKPOINTCOLLECTION(p0);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_FM_EVENT_ATOB(Any p0)
	{
		STATS::PLAYSTATS_FM_EVENT_ATOB(p0);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_FM_EVENT_PENNEDIN(Any p0)
	{
		STATS::PLAYSTATS_FM_EVENT_PENNEDIN(p0);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_FM_EVENT_PASSTHEPARCEL(Any p0)
	{
		STATS::PLAYSTATS_FM_EVENT_PASSTHEPARCEL(p0);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_FM_EVENT_HOTPROPERTY(Any p0)
	{
		STATS::PLAYSTATS_FM_EVENT_HOTPROPERTY(p0);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_FM_EVENT_DEADDROP(Any p0)
	{
		STATS::PLAYSTATS_FM_EVENT_DEADDROP(p0);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_FM_EVENT_KINGOFTHECASTLE(Any p0)
	{
		STATS::PLAYSTATS_FM_EVENT_KINGOFTHECASTLE(p0);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_FM_EVENT_CRIMINALDAMAGE(Any p0)
	{
		STATS::PLAYSTATS_FM_EVENT_CRIMINALDAMAGE(p0);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_FM_EVENT_COMPETITIVEURBANWARFARE(Any p0)
	{
		STATS::PLAYSTATS_FM_EVENT_COMPETITIVEURBANWARFARE(p0);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_FM_EVENT_HUNTBEAST(Any p0)
	{
		STATS::PLAYSTATS_FM_EVENT_HUNTBEAST(p0);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_PIMENU_HIDE_OPTIONS(uintptr_t data)
	{
		STATS::PLAYSTATS_PIMENU_HIDE_OPTIONS((Any*)data);
	}

	static int LUA_NATIVE_STATS_LEADERBOARDS_GET_NUMBER_OF_COLUMNS(int p0, Any p1)
	{
		auto retval = STATS::LEADERBOARDS_GET_NUMBER_OF_COLUMNS(p0, p1);
		return retval;
	}

	static int LUA_NATIVE_STATS_LEADERBOARDS_GET_COLUMN_ID(int p0, int p1, int p2)
	{
		auto retval = STATS::LEADERBOARDS_GET_COLUMN_ID(p0, p1, p2);
		return retval;
	}

	static int LUA_NATIVE_STATS_LEADERBOARDS_GET_COLUMN_TYPE(int p0, Any p1, Any p2)
	{
		auto retval = STATS::LEADERBOARDS_GET_COLUMN_TYPE(p0, p1, p2);
		return retval;
	}

	static int LUA_NATIVE_STATS_LEADERBOARDS_READ_CLEAR_ALL()
	{
		auto retval = STATS::LEADERBOARDS_READ_CLEAR_ALL();
		return retval;
	}

	static int LUA_NATIVE_STATS_LEADERBOARDS_READ_CLEAR(Any p0, Any p1, Any p2)
	{
		auto retval = STATS::LEADERBOARDS_READ_CLEAR(p0, p1, p2);
		return retval;
	}

	static bool LUA_NATIVE_STATS_LEADERBOARDS_READ_PENDING(Any p0, Any p1, Any p2)
	{
		auto retval = (bool)STATS::LEADERBOARDS_READ_PENDING(p0, p1, p2);
		return retval;
	}

	static bool LUA_NATIVE_STATS_LEADERBOARDS_READ_ANY_PENDING()
	{
		auto retval = (bool)STATS::LEADERBOARDS_READ_ANY_PENDING();
		return retval;
	}

	static bool LUA_NATIVE_STATS_LEADERBOARDS_READ_SUCCESSFUL(Any p0, Any p1, Any p2)
	{
		auto retval = (bool)STATS::LEADERBOARDS_READ_SUCCESSFUL(p0, p1, p2);
		return retval;
	}

	static bool LUA_NATIVE_STATS_LEADERBOARDS2_READ_FRIENDS_BY_ROW(uintptr_t p0, uintptr_t p1, Any p2, bool p3, Any p4, Any p5)
	{
		auto retval = (bool)STATS::LEADERBOARDS2_READ_FRIENDS_BY_ROW((Any*)p0, (Any*)p1, p2, p3, p4, p5);
		return retval;
	}

	static bool LUA_NATIVE_STATS_LEADERBOARDS2_READ_BY_HANDLE(uintptr_t p0, uintptr_t p1)
	{
		auto retval = (bool)STATS::LEADERBOARDS2_READ_BY_HANDLE((Any*)p0, (Any*)p1);
		return retval;
	}

	static bool LUA_NATIVE_STATS_LEADERBOARDS2_READ_BY_RANK(uintptr_t p0, Any p1, Any p2)
	{
		auto retval = (bool)STATS::LEADERBOARDS2_READ_BY_RANK((Any*)p0, p1, p2);
		return retval;
	}

	static bool LUA_NATIVE_STATS_LEADERBOARDS2_READ_BY_RADIUS(uintptr_t p0, Any p1, uintptr_t p2)
	{
		auto retval = (bool)STATS::LEADERBOARDS2_READ_BY_RADIUS((Any*)p0, p1, (Any*)p2);
		return retval;
	}

	static bool LUA_NATIVE_STATS_LEADERBOARDS2_READ_BY_SCORE_INT(uintptr_t p0, Any p1, Any p2)
	{
		auto retval = (bool)STATS::LEADERBOARDS2_READ_BY_SCORE_INT((Any*)p0, p1, p2);
		return retval;
	}

	static bool LUA_NATIVE_STATS_LEADERBOARDS2_READ_BY_SCORE_FLOAT(uintptr_t p0, float p1, Any p2)
	{
		auto retval = (bool)STATS::LEADERBOARDS2_READ_BY_SCORE_FLOAT((Any*)p0, p1, p2);
		return retval;
	}

	static bool LUA_NATIVE_STATS_LEADERBOARDS2_READ_RANK_PREDICTION(uintptr_t p0, uintptr_t p1, uintptr_t p2)
	{
		auto retval = (bool)STATS::LEADERBOARDS2_READ_RANK_PREDICTION((Any*)p0, (Any*)p1, (Any*)p2);
		return retval;
	}

	static bool LUA_NATIVE_STATS_LEADERBOARDS2_READ_BY_PLAFORM(uintptr_t p0, sol::stack_object gamerHandleCsv, sol::stack_object platformName)
	{
		auto retval = (bool)STATS::LEADERBOARDS2_READ_BY_PLAFORM((Any*)p0, gamerHandleCsv.is<const char*>() ? gamerHandleCsv.as<const char*>() : nullptr, platformName.is<const char*>() ? platformName.as<const char*>() : nullptr);
		return retval;
	}

	static bool LUA_NATIVE_STATS_LEADERBOARDS2_READ_GET_ROW_DATA_START(uintptr_t p0)
	{
		auto retval = (bool)STATS::LEADERBOARDS2_READ_GET_ROW_DATA_START((Any*)p0);
		return retval;
	}

	static void LUA_NATIVE_STATS_LEADERBOARDS2_READ_GET_ROW_DATA_END()
	{
		STATS::LEADERBOARDS2_READ_GET_ROW_DATA_END();
	}

	static bool LUA_NATIVE_STATS_LEADERBOARDS2_READ_GET_ROW_DATA_INFO(Any p0, uintptr_t p1)
	{
		auto retval = (bool)STATS::LEADERBOARDS2_READ_GET_ROW_DATA_INFO(p0, (Any*)p1);
		return retval;
	}

	static int LUA_NATIVE_STATS_LEADERBOARDS2_READ_GET_ROW_DATA_INT(Any p0, Any p1)
	{
		auto retval = STATS::LEADERBOARDS2_READ_GET_ROW_DATA_INT(p0, p1);
		return retval;
	}

	static float LUA_NATIVE_STATS_LEADERBOARDS2_READ_GET_ROW_DATA_FLOAT(Any p0, Any p1)
	{
		auto retval = STATS::LEADERBOARDS2_READ_GET_ROW_DATA_FLOAT(p0, p1);
		return retval;
	}

	static bool LUA_NATIVE_STATS_LEADERBOARDS2_WRITE_DATA(uintptr_t p0)
	{
		auto retval = (bool)STATS::LEADERBOARDS2_WRITE_DATA((Any*)p0);
		return retval;
	}

	static void LUA_NATIVE_STATS_LEADERBOARDS_WRITE_ADD_COLUMN(Any p0, Any p1, float p2)
	{
		STATS::LEADERBOARDS_WRITE_ADD_COLUMN(p0, p1, p2);
	}

	static void LUA_NATIVE_STATS_LEADERBOARDS_WRITE_ADD_COLUMN_LONG(Any p0, Any p1, Any p2)
	{
		STATS::LEADERBOARDS_WRITE_ADD_COLUMN_LONG(p0, p1, p2);
	}

	static bool LUA_NATIVE_STATS_LEADERBOARDS_CACHE_DATA_ROW(uintptr_t p0)
	{
		auto retval = (bool)STATS::LEADERBOARDS_CACHE_DATA_ROW((Any*)p0);
		return retval;
	}

	static void LUA_NATIVE_STATS_LEADERBOARDS_CLEAR_CACHE_DATA()
	{
		STATS::LEADERBOARDS_CLEAR_CACHE_DATA();
	}

	static void LUA_NATIVE_STATS_LEADERBOARDS_CLEAR_CACHE_DATA_ID(Any p0)
	{
		STATS::LEADERBOARDS_CLEAR_CACHE_DATA_ID(p0);
	}

	static bool LUA_NATIVE_STATS_LEADERBOARDS_GET_CACHE_EXISTS(Any p0)
	{
		auto retval = (bool)STATS::LEADERBOARDS_GET_CACHE_EXISTS(p0);
		return retval;
	}

	static int LUA_NATIVE_STATS_LEADERBOARDS_GET_CACHE_TIME(Any p0)
	{
		auto retval = STATS::LEADERBOARDS_GET_CACHE_TIME(p0);
		return retval;
	}

	static int LUA_NATIVE_STATS_LEADERBOARDS_GET_CACHE_NUMBER_OF_ROWS(Any p0)
	{
		auto retval = STATS::LEADERBOARDS_GET_CACHE_NUMBER_OF_ROWS(p0);
		return retval;
	}

	static bool LUA_NATIVE_STATS_LEADERBOARDS_GET_CACHE_DATA_ROW(Any p0, Any p1, uintptr_t p2)
	{
		auto retval = (bool)STATS::LEADERBOARDS_GET_CACHE_DATA_ROW(p0, p1, (Any*)p2);
		return retval;
	}

	static void LUA_NATIVE_STATS_PRESENCE_EVENT_UPDATESTAT_INT(Hash statHash, int value, int p2)
	{
		STATS::PRESENCE_EVENT_UPDATESTAT_INT(statHash, value, p2);
	}

	static void LUA_NATIVE_STATS_PRESENCE_EVENT_UPDATESTAT_FLOAT(Hash statHash, float value, int p2)
	{
		STATS::PRESENCE_EVENT_UPDATESTAT_FLOAT(statHash, value, p2);
	}

	static void LUA_NATIVE_STATS_PRESENCE_EVENT_UPDATESTAT_INT_WITH_STRING(Hash statHash, int value, int p2, sol::stack_object string)
	{
		STATS::PRESENCE_EVENT_UPDATESTAT_INT_WITH_STRING(statHash, value, p2, string.is<const char*>() ? string.as<const char*>() : nullptr);
	}

	static bool LUA_NATIVE_STATS_GET_PLAYER_HAS_DRIVEN_ALL_VEHICLES()
	{
		auto retval = (bool)STATS::GET_PLAYER_HAS_DRIVEN_ALL_VEHICLES();
		return retval;
	}

	static void LUA_NATIVE_STATS_SET_HAS_POSTED_ALL_VEHICLES_DRIVEN()
	{
		STATS::SET_HAS_POSTED_ALL_VEHICLES_DRIVEN();
	}

	static void LUA_NATIVE_STATS_SET_PROFILE_SETTING_PROLOGUE_COMPLETE()
	{
		STATS::SET_PROFILE_SETTING_PROLOGUE_COMPLETE();
	}

	static void LUA_NATIVE_STATS_SET_PROFILE_SETTING_SP_CHOP_MISSION_COMPLETE()
	{
		STATS::SET_PROFILE_SETTING_SP_CHOP_MISSION_COMPLETE();
	}

	static void LUA_NATIVE_STATS_SET_PROFILE_SETTING_CREATOR_RACES_DONE(int value)
	{
		STATS::SET_PROFILE_SETTING_CREATOR_RACES_DONE(value);
	}

	static void LUA_NATIVE_STATS_SET_PROFILE_SETTING_CREATOR_DM_DONE(int value)
	{
		STATS::SET_PROFILE_SETTING_CREATOR_DM_DONE(value);
	}

	static void LUA_NATIVE_STATS_SET_PROFILE_SETTING_CREATOR_CTF_DONE(int value)
	{
		STATS::SET_PROFILE_SETTING_CREATOR_CTF_DONE(value);
	}

	static void LUA_NATIVE_STATS_SET_JOB_ACTIVITY_ID_STARTED(Any p0, int characterSlot)
	{
		STATS::SET_JOB_ACTIVITY_ID_STARTED(p0, characterSlot);
	}

	static void LUA_NATIVE_STATS_SET_FREEMODE_PROLOGUE_DONE(Any p0, int characterSlot)
	{
		STATS::SET_FREEMODE_PROLOGUE_DONE(p0, characterSlot);
	}

	static void LUA_NATIVE_STATS_SET_FREEMODE_STRAND_PROGRESSION_STATUS(int profileSetting, int settingValue)
	{
		STATS::SET_FREEMODE_STRAND_PROGRESSION_STATUS(profileSetting, settingValue);
	}

	static void LUA_NATIVE_STATS_STAT_NETWORK_INCREMENT_ON_SUICIDE(Any p0, float p1)
	{
		STATS::STAT_NETWORK_INCREMENT_ON_SUICIDE(p0, p1);
	}

	static void LUA_NATIVE_STATS_STAT_SET_CHEAT_IS_ACTIVE()
	{
		STATS::STAT_SET_CHEAT_IS_ACTIVE();
	}

	static bool LUA_NATIVE_STATS_LEADERBOARDS2_WRITE_DATA_FOR_EVENT_TYPE(uintptr_t p0, uintptr_t p1)
	{
		auto retval = (bool)STATS::LEADERBOARDS2_WRITE_DATA_FOR_EVENT_TYPE((Any*)p0, (Any*)p1);
		return retval;
	}

	static void LUA_NATIVE_STATS_FORCE_CLOUD_MP_STATS_DOWNLOAD_AND_OVERWRITE_LOCAL_SAVE()
	{
		STATS::FORCE_CLOUD_MP_STATS_DOWNLOAD_AND_OVERWRITE_LOCAL_SAVE();
	}

	static void LUA_NATIVE_STATS_STAT_MIGRATE_CLEAR_FOR_RESTART()
	{
		STATS::STAT_MIGRATE_CLEAR_FOR_RESTART();
	}

	static bool LUA_NATIVE_STATS_STAT_MIGRATE_SAVEGAME_START(sol::stack_object platformName)
	{
		auto retval = (bool)STATS::STAT_MIGRATE_SAVEGAME_START(platformName.is<const char*>() ? platformName.as<const char*>() : nullptr);
		return retval;
	}

	static int LUA_NATIVE_STATS_STAT_MIGRATE_SAVEGAME_GET_STATUS()
	{
		auto retval = STATS::STAT_MIGRATE_SAVEGAME_GET_STATUS();
		return retval;
	}

	static bool LUA_NATIVE_STATS_STAT_MIGRATE_CHECK_ALREADY_DONE()
	{
		auto retval = (bool)STATS::STAT_MIGRATE_CHECK_ALREADY_DONE();
		return retval;
	}

	static bool LUA_NATIVE_STATS_STAT_MIGRATE_CHECK_START()
	{
		auto retval = (bool)STATS::STAT_MIGRATE_CHECK_START();
		return retval;
	}

	static int LUA_NATIVE_STATS_STAT_MIGRATE_CHECK_GET_IS_PLATFORM_AVAILABLE(int p0)
	{
		auto retval = STATS::STAT_MIGRATE_CHECK_GET_IS_PLATFORM_AVAILABLE(p0);
		return retval;
	}

	static int LUA_NATIVE_STATS_STAT_MIGRATE_CHECK_GET_PLATFORM_STATUS(int p0, uintptr_t p1)
	{
		auto retval = STATS::STAT_MIGRATE_CHECK_GET_PLATFORM_STATUS(p0, (Any*)p1);
		return retval;
	}

	static int LUA_NATIVE_STATS_STAT_GET_SAVE_MIGRATION_STATUS(uintptr_t data)
	{
		auto retval = STATS::STAT_GET_SAVE_MIGRATION_STATUS((Any*)data);
		return retval;
	}

	static bool LUA_NATIVE_STATS_STAT_SAVE_MIGRATION_CANCEL_PENDING_OPERATION()
	{
		auto retval = (bool)STATS::STAT_SAVE_MIGRATION_CANCEL_PENDING_OPERATION();
		return retval;
	}

	static int LUA_NATIVE_STATS_STAT_GET_CANCEL_SAVE_MIGRATION_STATUS()
	{
		auto retval = STATS::STAT_GET_CANCEL_SAVE_MIGRATION_STATUS();
		return retval;
	}

	static bool LUA_NATIVE_STATS_STAT_SAVE_MIGRATION_CONSUME_CONTENT(Hash contentId, sol::stack_object srcPlatform, sol::stack_object srcGamerHandle)
	{
		auto retval = (bool)STATS::STAT_SAVE_MIGRATION_CONSUME_CONTENT(contentId, srcPlatform.is<const char*>() ? srcPlatform.as<const char*>() : nullptr, srcGamerHandle.is<const char*>() ? srcGamerHandle.as<const char*>() : nullptr);
		return retval;
	}

	static std::tuple<int, int> LUA_NATIVE_STATS_STAT_GET_SAVE_MIGRATION_CONSUME_CONTENT_STATUS(int p0)
	{
		std::tuple<int, int> return_values;
		std::get<0>(return_values) = STATS::STAT_GET_SAVE_MIGRATION_CONSUME_CONTENT_STATUS(&p0);
		std::get<1>(return_values) = p0;

		return return_values;
	}

	static void LUA_NATIVE_STATS_STAT_ENABLE_STATS_TRACKING()
	{
		STATS::STAT_ENABLE_STATS_TRACKING();
	}

	static void LUA_NATIVE_STATS_STAT_DISABLE_STATS_TRACKING()
	{
		STATS::STAT_DISABLE_STATS_TRACKING();
	}

	static bool LUA_NATIVE_STATS_STAT_IS_STATS_TRACKING_ENABLED()
	{
		auto retval = (bool)STATS::STAT_IS_STATS_TRACKING_ENABLED();
		return retval;
	}

	static bool LUA_NATIVE_STATS_STAT_START_RECORD_STAT(int statType, int valueType)
	{
		auto retval = (bool)STATS::STAT_START_RECORD_STAT(statType, valueType);
		return retval;
	}

	static bool LUA_NATIVE_STATS_STAT_STOP_RECORD_STAT()
	{
		auto retval = (bool)STATS::STAT_STOP_RECORD_STAT();
		return retval;
	}

	static std::tuple<bool, float> LUA_NATIVE_STATS_STAT_GET_RECORDED_VALUE(float value)
	{
		std::tuple<bool, float> return_values;
		std::get<0>(return_values) = (bool)STATS::STAT_GET_RECORDED_VALUE(&value);
		std::get<1>(return_values) = value;

		return return_values;
	}

	static bool LUA_NATIVE_STATS_STAT_IS_RECORDING_STAT()
	{
		auto retval = (bool)STATS::STAT_IS_RECORDING_STAT();
		return retval;
	}

	static int LUA_NATIVE_STATS_STAT_GET_CURRENT_NEAR_MISS_NOCRASH_PRECISE()
	{
		auto retval = STATS::STAT_GET_CURRENT_NEAR_MISS_NOCRASH_PRECISE();
		return retval;
	}

	static float LUA_NATIVE_STATS_STAT_GET_CURRENT_REAR_WHEEL_DISTANCE()
	{
		auto retval = STATS::STAT_GET_CURRENT_REAR_WHEEL_DISTANCE();
		return retval;
	}

	static float LUA_NATIVE_STATS_STAT_GET_CURRENT_FRONT_WHEEL_DISTANCE()
	{
		auto retval = STATS::STAT_GET_CURRENT_FRONT_WHEEL_DISTANCE();
		return retval;
	}

	static float LUA_NATIVE_STATS_STAT_GET_CURRENT_JUMP_DISTANCE()
	{
		auto retval = STATS::STAT_GET_CURRENT_JUMP_DISTANCE();
		return retval;
	}

	static float LUA_NATIVE_STATS_STAT_GET_CURRENT_DRIVE_NOCRASH_DISTANCE()
	{
		auto retval = STATS::STAT_GET_CURRENT_DRIVE_NOCRASH_DISTANCE();
		return retval;
	}

	static float LUA_NATIVE_STATS_STAT_GET_CURRENT_SPEED()
	{
		auto retval = STATS::STAT_GET_CURRENT_SPEED();
		return retval;
	}

	static float LUA_NATIVE_STATS_STAT_GET_CURRENT_DRIVING_REVERSE_DISTANCE()
	{
		auto retval = STATS::STAT_GET_CURRENT_DRIVING_REVERSE_DISTANCE();
		return retval;
	}

	static float LUA_NATIVE_STATS_STAT_GET_CURRENT_SKYDIVING_DISTANCE()
	{
		auto retval = STATS::STAT_GET_CURRENT_SKYDIVING_DISTANCE();
		return retval;
	}

	static float LUA_NATIVE_STATS_STAT_GET_CHALLENGE_FLYING_DIST()
	{
		auto retval = STATS::STAT_GET_CHALLENGE_FLYING_DIST();
		return retval;
	}

	static std::tuple<bool, float> LUA_NATIVE_STATS_STAT_GET_FLYING_ALTITUDE(float outValue)
	{
		std::tuple<bool, float> return_values;
		std::get<0>(return_values) = (bool)STATS::STAT_GET_FLYING_ALTITUDE(&outValue);
		std::get<1>(return_values) = outValue;

		return return_values;
	}

	static bool LUA_NATIVE_STATS_STAT_IS_PLAYER_VEHICLE_ABOVE_OCEAN()
	{
		auto retval = (bool)STATS::STAT_IS_PLAYER_VEHICLE_ABOVE_OCEAN();
		return retval;
	}

	static float LUA_NATIVE_STATS_STAT_GET_VEHICLE_BAIL_DISTANCE()
	{
		auto retval = STATS::STAT_GET_VEHICLE_BAIL_DISTANCE();
		return retval;
	}

	static bool LUA_NATIVE_STATS_STAT_ROLLBACK_SAVE_MIGRATION()
	{
		auto retval = (bool)STATS::STAT_ROLLBACK_SAVE_MIGRATION();
		return retval;
	}

	static void LUA_NATIVE_STATS_SET_HAS_SPECIALEDITION_CONTENT(int value)
	{
		STATS::SET_HAS_SPECIALEDITION_CONTENT(value);
	}

	static void LUA_NATIVE_STATS_SET_SAVE_MIGRATION_TRANSACTION_ID_WARNING(int transactionId)
	{
		STATS::SET_SAVE_MIGRATION_TRANSACTION_ID_WARNING(transactionId);
	}

	static void LUA_NATIVE_STATS_GET_BOSS_GOON_UUID(int characterSlot, Any p1, Any p2)
	{
		STATS::GET_BOSS_GOON_UUID(characterSlot, p1, p2);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_BW_BOSSONBOSSDEATHMATCH(Any p0)
	{
		STATS::PLAYSTATS_BW_BOSSONBOSSDEATHMATCH(p0);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_BW_YATCHATTACK(Any p0)
	{
		STATS::PLAYSTATS_BW_YATCHATTACK(p0);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_BW_HUNT_THE_BOSS(Any p0)
	{
		STATS::PLAYSTATS_BW_HUNT_THE_BOSS(p0);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_BW_SIGHTSEER(Any p0)
	{
		STATS::PLAYSTATS_BW_SIGHTSEER(p0);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_BW_ASSAULT(Any p0)
	{
		STATS::PLAYSTATS_BW_ASSAULT(p0);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_BW_BELLY_OF_THE_BEAST(Any p0)
	{
		STATS::PLAYSTATS_BW_BELLY_OF_THE_BEAST(p0);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_BW_HEAD_HUNTER(Any p0)
	{
		STATS::PLAYSTATS_BW_HEAD_HUNTER(p0);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_BW_FRAGILE_GOODS(Any p0)
	{
		STATS::PLAYSTATS_BW_FRAGILE_GOODS(p0);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_BW_AIR_FREIGHT(Any p0)
	{
		STATS::PLAYSTATS_BW_AIR_FREIGHT(p0);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_BC_CAR_JACKING(Any p0)
	{
		STATS::PLAYSTATS_BC_CAR_JACKING(p0);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_BC_SMASH_AND_GRAB(Any p0)
	{
		STATS::PLAYSTATS_BC_SMASH_AND_GRAB(p0);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_BC_PROTECTION_RACKET(Any p0)
	{
		STATS::PLAYSTATS_BC_PROTECTION_RACKET(p0);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_BC_MOST_WANTED(Any p0)
	{
		STATS::PLAYSTATS_BC_MOST_WANTED(p0);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_BC_FINDERS_KEEPERS(Any p0)
	{
		STATS::PLAYSTATS_BC_FINDERS_KEEPERS(p0);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_BC_POINT_TO_POINT(Any p0)
	{
		STATS::PLAYSTATS_BC_POINT_TO_POINT(p0);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_BC_CASHING(Any p0)
	{
		STATS::PLAYSTATS_BC_CASHING(p0);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_BC_SALVAGE(Any p0)
	{
		STATS::PLAYSTATS_BC_SALVAGE(p0);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_SPENT_PI_CUSTOM_LOADOUT(int amount)
	{
		STATS::PLAYSTATS_SPENT_PI_CUSTOM_LOADOUT(amount);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_BUY_CONTRABAND_MISSION(uintptr_t data)
	{
		STATS::PLAYSTATS_BUY_CONTRABAND_MISSION((Any*)data);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_SELL_CONTRABAND_MISSION(uintptr_t data)
	{
		STATS::PLAYSTATS_SELL_CONTRABAND_MISSION((Any*)data);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_DEFEND_CONTRABAND_MISSION(uintptr_t data)
	{
		STATS::PLAYSTATS_DEFEND_CONTRABAND_MISSION((Any*)data);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_RECOVER_CONTRABAND_MISSION(uintptr_t data)
	{
		STATS::PLAYSTATS_RECOVER_CONTRABAND_MISSION((Any*)data);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_HIT_CONTRABAND_DESTROY_LIMIT(Any p0)
	{
		STATS::PLAYSTATS_HIT_CONTRABAND_DESTROY_LIMIT(p0);
	}

	static void LUA_NATIVE_STATS_START_BEING_BOSS(Any p0, Any p1, Any p2)
	{
		STATS::START_BEING_BOSS(p0, p1, p2);
	}

	static void LUA_NATIVE_STATS_START_BEING_GOON(Any p0, Any p1, Any p2)
	{
		STATS::START_BEING_GOON(p0, p1, p2);
	}

	static void LUA_NATIVE_STATS_END_BEING_BOSS(Any p0, Any p1, Any p2)
	{
		STATS::END_BEING_BOSS(p0, p1, p2);
	}

	static void LUA_NATIVE_STATS_END_BEING_GOON(Any p0, Any p1, Any p2, Any p3, Any p4)
	{
		STATS::END_BEING_GOON(p0, p1, p2, p3, p4);
	}

	static void LUA_NATIVE_STATS_HIRED_LIMO(Any p0, Any p1)
	{
		STATS::HIRED_LIMO(p0, p1);
	}

	static void LUA_NATIVE_STATS_ORDER_BOSS_VEHICLE(Any p0, Any p1, Hash vehicleHash)
	{
		STATS::ORDER_BOSS_VEHICLE(p0, p1, vehicleHash);
	}

	static void LUA_NATIVE_STATS_CHANGE_UNIFORM(Any p0, Any p1, Any p2)
	{
		STATS::CHANGE_UNIFORM(p0, p1, p2);
	}

	static void LUA_NATIVE_STATS_CHANGE_GOON_LOOKING_FOR_WORK(Any p0)
	{
		STATS::CHANGE_GOON_LOOKING_FOR_WORK(p0);
	}

	static void LUA_NATIVE_STATS_SEND_METRIC_GHOSTING_TO_PLAYER(Any p0)
	{
		STATS::SEND_METRIC_GHOSTING_TO_PLAYER(p0);
	}

	static void LUA_NATIVE_STATS_SEND_METRIC_VIP_POACH(Any p0, Any p1, Any p2)
	{
		STATS::SEND_METRIC_VIP_POACH(p0, p1, p2);
	}

	static void LUA_NATIVE_STATS_SEND_METRIC_PUNISH_BODYGUARD(Any p0)
	{
		STATS::SEND_METRIC_PUNISH_BODYGUARD(p0);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_START_TRACKING_STUNTS()
	{
		STATS::PLAYSTATS_START_TRACKING_STUNTS();
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_STOP_TRACKING_STUNTS()
	{
		STATS::PLAYSTATS_STOP_TRACKING_STUNTS();
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_MISSION_ENDED(Any p0)
	{
		STATS::PLAYSTATS_MISSION_ENDED(p0);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_IMPEXP_MISSION_ENDED(Any p0)
	{
		STATS::PLAYSTATS_IMPEXP_MISSION_ENDED(p0);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_CHANGE_MC_ROLE(Any p0, Any p1, Any p2, Any p3, int role, int p5, Any p6)
	{
		STATS::PLAYSTATS_CHANGE_MC_ROLE(p0, p1, p2, p3, role, p5, p6);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_CHANGE_MC_OUTFIT(Any p0, Any p1, Any p2, Any p3, Any p4)
	{
		STATS::PLAYSTATS_CHANGE_MC_OUTFIT(p0, p1, p2, p3, p4);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_SWITCH_MC_EMBLEM(Any p0, Any p1, Any p2, Any p3, Any p4)
	{
		STATS::PLAYSTATS_SWITCH_MC_EMBLEM(p0, p1, p2, p3, p4);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_MC_REQUEST_BIKE(Any p0, Any p1, Any p2, Any p3, Any p4)
	{
		STATS::PLAYSTATS_MC_REQUEST_BIKE(p0, p1, p2, p3, p4);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_MC_KILLED_RIVAL_MC_MEMBER(Any p0, Any p1, Any p2, Any p3, Any p4)
	{
		STATS::PLAYSTATS_MC_KILLED_RIVAL_MC_MEMBER(p0, p1, p2, p3, p4);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_ABANDONED_MC(Any p0, Any p1, Any p2, Any p3, Any p4)
	{
		STATS::PLAYSTATS_ABANDONED_MC(p0, p1, p2, p3, p4);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_EARNED_MC_POINTS(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5)
	{
		STATS::PLAYSTATS_EARNED_MC_POINTS(p0, p1, p2, p3, p4, p5);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_MC_FORMATION_ENDS(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6)
	{
		STATS::PLAYSTATS_MC_FORMATION_ENDS(p0, p1, p2, p3, p4, p5, p6);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_MC_CLUBHOUSE_ACTIVITY(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7)
	{
		STATS::PLAYSTATS_MC_CLUBHOUSE_ACTIVITY(p0, p1, p2, p3, p4, p5, p6, p7);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_RIVAL_BEHAVIOR(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9)
	{
		STATS::PLAYSTATS_RIVAL_BEHAVIOR(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_COPY_RANK_INTO_NEW_SLOT(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6)
	{
		STATS::PLAYSTATS_COPY_RANK_INTO_NEW_SLOT(p0, p1, p2, p3, p4, p5, p6);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_DUPE_DETECTED(uintptr_t data)
	{
		STATS::PLAYSTATS_DUPE_DETECTED((Any*)data);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_BAN_ALERT(int p0)
	{
		STATS::PLAYSTATS_BAN_ALERT(p0);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_GUNRUNNING_MISSION_ENDED(uintptr_t data)
	{
		STATS::PLAYSTATS_GUNRUNNING_MISSION_ENDED((Any*)data);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_GUNRUNNING_RND(Any p0)
	{
		STATS::PLAYSTATS_GUNRUNNING_RND(p0);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_BUSINESS_BATTLE_ENDED(Any p0)
	{
		STATS::PLAYSTATS_BUSINESS_BATTLE_ENDED(p0);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_WAREHOUSE_MISSION_ENDED(Any p0)
	{
		STATS::PLAYSTATS_WAREHOUSE_MISSION_ENDED(p0);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_NIGHTCLUB_MISSION_ENDED(Any p0)
	{
		STATS::PLAYSTATS_NIGHTCLUB_MISSION_ENDED(p0);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_DJ_USAGE(Any p0, Any p1)
	{
		STATS::PLAYSTATS_DJ_USAGE(p0, p1);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_MINIGAME_USAGE(Any p0, Any p1, Any p2)
	{
		STATS::PLAYSTATS_MINIGAME_USAGE(p0, p1, p2);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_STONE_HATCHET_ENDED(uintptr_t data)
	{
		STATS::PLAYSTATS_STONE_HATCHET_ENDED((Any*)data);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_SMUGGLER_MISSION_ENDED(uintptr_t data)
	{
		STATS::PLAYSTATS_SMUGGLER_MISSION_ENDED((Any*)data);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_FM_HEIST_PREP_ENDED(uintptr_t data)
	{
		STATS::PLAYSTATS_FM_HEIST_PREP_ENDED((Any*)data);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_INSTANCED_HEIST_ENDED(uintptr_t data, Any p1, Any p2, Any p3)
	{
		STATS::PLAYSTATS_INSTANCED_HEIST_ENDED((Any*)data, p1, p2, p3);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_DAR_CHECKPOINT(uintptr_t data)
	{
		STATS::PLAYSTATS_DAR_CHECKPOINT((Any*)data);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_ENTER_SESSION_PACK(uintptr_t data)
	{
		STATS::PLAYSTATS_ENTER_SESSION_PACK((Any*)data);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_DRONE_USAGE(int p0, int p1, int p2)
	{
		STATS::PLAYSTATS_DRONE_USAGE(p0, p1, p2);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_SPIN_WHEEL(int p0, int p1, int p2, int p3)
	{
		STATS::PLAYSTATS_SPIN_WHEEL(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_ARENA_WARS_SPECTATOR(int p0, int p1, int p2, int p3, int p4)
	{
		STATS::PLAYSTATS_ARENA_WARS_SPECTATOR(p0, p1, p2, p3, p4);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_ARENA_WARS_ENDED(uintptr_t data)
	{
		STATS::PLAYSTATS_ARENA_WARS_ENDED((Any*)data);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_SWITCH_PASSIVE_MODE(bool p0, int p1, int p2, int p3)
	{
		STATS::PLAYSTATS_SWITCH_PASSIVE_MODE(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_COLLECTIBLE_PICKED_UP(int p0, Hash objectHash, Any p2, Any p3, int moneyAmount, int rpAmount, int chipsAmount, Any p7, int p8, Any p9, Any p10)
	{
		STATS::PLAYSTATS_COLLECTIBLE_PICKED_UP(p0, objectHash, p2, p3, moneyAmount, rpAmount, chipsAmount, p7, p8, p9, p10);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_CASINO_STORY_MISSION_ENDED(Any p0, Any p1)
	{
		STATS::PLAYSTATS_CASINO_STORY_MISSION_ENDED(p0, p1);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_CASINO_CHIP(Any p0)
	{
		STATS::PLAYSTATS_CASINO_CHIP(p0);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_CASINO_ROULETTE(Any p0)
	{
		STATS::PLAYSTATS_CASINO_ROULETTE(p0);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_CASINO_BLACKJACK(Any p0)
	{
		STATS::PLAYSTATS_CASINO_BLACKJACK(p0);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_CASINO_THREE_CARD_POKER(Any p0)
	{
		STATS::PLAYSTATS_CASINO_THREE_CARD_POKER(p0);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_CASINO_SLOT_MACHINE(Any p0)
	{
		STATS::PLAYSTATS_CASINO_SLOT_MACHINE(p0);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_CASINO_INSIDE_TRACK(Any p0)
	{
		STATS::PLAYSTATS_CASINO_INSIDE_TRACK(p0);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_CASINO_LUCKY_SEVEN(Any p0)
	{
		STATS::PLAYSTATS_CASINO_LUCKY_SEVEN(p0);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_CASINO_ROULETTE_LIGHT(Any p0)
	{
		STATS::PLAYSTATS_CASINO_ROULETTE_LIGHT(p0);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_CASINO_BLACKJACK_LIGHT(Any p0)
	{
		STATS::PLAYSTATS_CASINO_BLACKJACK_LIGHT(p0);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_CASINO_THREE_CARD_POKER_LIGHT(Any p0)
	{
		STATS::PLAYSTATS_CASINO_THREE_CARD_POKER_LIGHT(p0);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_CASINO_SLOT_MACHINE_LIGHT(Any p0)
	{
		STATS::PLAYSTATS_CASINO_SLOT_MACHINE_LIGHT(p0);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_CASINO_INSIDE_TRACK_LIGHT(Any p0)
	{
		STATS::PLAYSTATS_CASINO_INSIDE_TRACK_LIGHT(p0);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_ARCADE_GAME(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6)
	{
		STATS::PLAYSTATS_ARCADE_GAME(p0, p1, p2, p3, p4, p5, p6);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_ARCADE_LOVE_MATCH(Any p0, Any p1)
	{
		STATS::PLAYSTATS_ARCADE_LOVE_MATCH(p0, p1);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_FREEMODE_CASINO_MISSION_ENDED(uintptr_t data)
	{
		STATS::PLAYSTATS_FREEMODE_CASINO_MISSION_ENDED((Any*)data);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_HEIST3_DRONE(Any p0)
	{
		STATS::PLAYSTATS_HEIST3_DRONE(p0);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_HEIST3_HACK(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5)
	{
		STATS::PLAYSTATS_HEIST3_HACK(p0, p1, p2, p3, p4, p5);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_NPC_PHONE(uintptr_t p0)
	{
		STATS::PLAYSTATS_NPC_PHONE((Any*)p0);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_ARCADE_CABINET(Any p0)
	{
		STATS::PLAYSTATS_ARCADE_CABINET(p0);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_HEIST3_FINALE(Any p0)
	{
		STATS::PLAYSTATS_HEIST3_FINALE(p0);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_HEIST3_PREP(Any p0)
	{
		STATS::PLAYSTATS_HEIST3_PREP(p0);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_MASTER_CONTROL(Any p0, Any p1, Any p2, Any p3)
	{
		STATS::PLAYSTATS_MASTER_CONTROL(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_QUIT_MODE(Any p0, Any p1, Any p2, Any p3, Any p4)
	{
		STATS::PLAYSTATS_QUIT_MODE(p0, p1, p2, p3, p4);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_MISSION_VOTE(Any p0)
	{
		STATS::PLAYSTATS_MISSION_VOTE(p0);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_NJVS_VOTE(Any p0)
	{
		STATS::PLAYSTATS_NJVS_VOTE(p0);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_FM_MISSION_END(Any p0, Any p1, Any p2, Any p3)
	{
		STATS::PLAYSTATS_FM_MISSION_END(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_HEIST4_PREP(Any p0)
	{
		STATS::PLAYSTATS_HEIST4_PREP(p0);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_HEIST4_FINALE(Any p0)
	{
		STATS::PLAYSTATS_HEIST4_FINALE(p0);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_HEIST4_HACK(Any p0, Any p1, Any p2, Any p3, Any p4)
	{
		STATS::PLAYSTATS_HEIST4_HACK(p0, p1, p2, p3, p4);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_SUB_WEAP(Any p0, Any p1, Any p2, Any p3)
	{
		STATS::PLAYSTATS_SUB_WEAP(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_FAST_TRVL(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8, Any p9, Any p10)
	{
		STATS::PLAYSTATS_FAST_TRVL(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_HUB_ENTRY(Any p0)
	{
		STATS::PLAYSTATS_HUB_ENTRY(p0);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_DJ_MISSION_ENDED(Any p0)
	{
		STATS::PLAYSTATS_DJ_MISSION_ENDED(p0);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_ROBBERY_PREP(Any p0)
	{
		STATS::PLAYSTATS_ROBBERY_PREP(p0);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_ROBBERY_FINALE(Any p0)
	{
		STATS::PLAYSTATS_ROBBERY_FINALE(p0);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_EXTRA_EVENT(Any p0)
	{
		STATS::PLAYSTATS_EXTRA_EVENT(p0);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_CARCLUB_POINTS(Any p0)
	{
		STATS::PLAYSTATS_CARCLUB_POINTS(p0);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_CARCLUB_CHALLENGE(Any p0, Any p1, Any p2, Any p3)
	{
		STATS::PLAYSTATS_CARCLUB_CHALLENGE(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_CARCLUB_PRIZE(int p0, Hash vehicleModel)
	{
		STATS::PLAYSTATS_CARCLUB_PRIZE(p0, vehicleModel);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_AWARD_NAV(Any p0, Any p1, Any p2, Any p3)
	{
		STATS::PLAYSTATS_AWARD_NAV(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_INST_MISSION_END(Any p0)
	{
		STATS::PLAYSTATS_INST_MISSION_END(p0);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_HUB_EXIT(Any p0)
	{
		STATS::PLAYSTATS_HUB_EXIT(p0);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_VEH_DEL(int bossId1, int bossId2, int bossType, int vehicleID, int reason)
	{
		STATS::PLAYSTATS_VEH_DEL(bossId1, bossId2, bossType, vehicleID, reason);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_INVENTORY(Any p0)
	{
		STATS::PLAYSTATS_INVENTORY(p0);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_ACID_MISSION_END_(Any p0)
	{
		STATS::_PLAYSTATS_ACID_MISSION_END(p0);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_ACID_RND_(Any p0)
	{
		STATS::_PLAYSTATS_ACID_RND(p0);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_IDLE_(Any p0, Any p1, Any p2)
	{
		STATS::_PLAYSTATS_IDLE(p0, p1, p2);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_PLAYER_STYLE_(Any p0)
	{
		STATS::_PLAYSTATS_PLAYER_STYLE(p0);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_RANDOM_EVENT_(Any p0)
	{
		STATS::_PLAYSTATS_RANDOM_EVENT(p0);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_ALERT_(uintptr_t data)
	{
		STATS::_PLAYSTATS_ALERT((Any*)data);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_ATTRITION_STAGE_END_(Any p0)
	{
		STATS::_PLAYSTATS_ATTRITION_STAGE_END(p0);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_SHOWROOM_NAV_(Any p0, Any p1, Hash entity)
	{
		STATS::_PLAYSTATS_SHOWROOM_NAV(p0, p1, entity);
	}

	static void LUA_NATIVE_STATS_PLAYSTATS_SHOWROOM_OVERVIEW_(uintptr_t data)
	{
		STATS::_PLAYSTATS_SHOWROOM_OVERVIEW((Any*)data);
	}

	void init_native_binding_STATS(sol::state& L)
	{
		auto STATS = L["STATS"].get_or_create<sol::table>();
		STATS.set_function("STAT_CLEAR_SLOT_FOR_RELOAD", LUA_NATIVE_STATS_STAT_CLEAR_SLOT_FOR_RELOAD);
		STATS.set_function("STAT_LOAD", LUA_NATIVE_STATS_STAT_LOAD);
		STATS.set_function("STAT_SAVE", LUA_NATIVE_STATS_STAT_SAVE);
		STATS.set_function("STAT_SET_OPEN_SAVETYPE_IN_JOB", LUA_NATIVE_STATS_STAT_SET_OPEN_SAVETYPE_IN_JOB);
		STATS.set_function("STAT_LOAD_PENDING", LUA_NATIVE_STATS_STAT_LOAD_PENDING);
		STATS.set_function("STAT_SAVE_PENDING", LUA_NATIVE_STATS_STAT_SAVE_PENDING);
		STATS.set_function("STAT_SAVE_PENDING_OR_REQUESTED", LUA_NATIVE_STATS_STAT_SAVE_PENDING_OR_REQUESTED);
		STATS.set_function("STAT_DELETE_SLOT", LUA_NATIVE_STATS_STAT_DELETE_SLOT);
		STATS.set_function("STAT_SLOT_IS_LOADED", LUA_NATIVE_STATS_STAT_SLOT_IS_LOADED);
		STATS.set_function("STAT_CLOUD_SLOT_LOAD_FAILED", LUA_NATIVE_STATS_STAT_CLOUD_SLOT_LOAD_FAILED);
		STATS.set_function("STAT_CLOUD_SLOT_LOAD_FAILED_CODE", LUA_NATIVE_STATS_STAT_CLOUD_SLOT_LOAD_FAILED_CODE);
		STATS.set_function("STAT_SET_BLOCK_SAVES", LUA_NATIVE_STATS_STAT_SET_BLOCK_SAVES);
		STATS.set_function("STAT_GET_BLOCK_SAVES", LUA_NATIVE_STATS_STAT_GET_BLOCK_SAVES);
		STATS.set_function("STAT_CLOUD_SLOT_SAVE_FAILED", LUA_NATIVE_STATS_STAT_CLOUD_SLOT_SAVE_FAILED);
		STATS.set_function("STAT_CLEAR_PENDING_SAVES", LUA_NATIVE_STATS_STAT_CLEAR_PENDING_SAVES);
		STATS.set_function("STAT_LOAD_DIRTY_READ_DETECTED", LUA_NATIVE_STATS_STAT_LOAD_DIRTY_READ_DETECTED);
		STATS.set_function("STAT_CLEAR_DIRTY_READ_DETECTED", LUA_NATIVE_STATS_STAT_CLEAR_DIRTY_READ_DETECTED);
		STATS.set_function("STAT_GET_LOAD_SAFE_TO_PROGRESS_TO_MP_FROM_SP", LUA_NATIVE_STATS_STAT_GET_LOAD_SAFE_TO_PROGRESS_TO_MP_FROM_SP);
		STATS.set_function("GET_STAT_HASH_FOR_CHARACTER_STAT_", LUA_NATIVE_STATS_GET_STAT_HASH_FOR_CHARACTER_STAT_);
		STATS.set_function("STAT_SET_INT", LUA_NATIVE_STATS_STAT_SET_INT);
		STATS.set_function("STAT_SET_FLOAT", LUA_NATIVE_STATS_STAT_SET_FLOAT);
		STATS.set_function("STAT_SET_BOOL", LUA_NATIVE_STATS_STAT_SET_BOOL);
		STATS.set_function("STAT_SET_GXT_LABEL", LUA_NATIVE_STATS_STAT_SET_GXT_LABEL);
		STATS.set_function("STAT_SET_DATE", LUA_NATIVE_STATS_STAT_SET_DATE);
		STATS.set_function("STAT_SET_STRING", LUA_NATIVE_STATS_STAT_SET_STRING);
		STATS.set_function("STAT_SET_POS", LUA_NATIVE_STATS_STAT_SET_POS);
		STATS.set_function("STAT_SET_MASKED_INT", LUA_NATIVE_STATS_STAT_SET_MASKED_INT);
		STATS.set_function("STAT_SET_USER_ID", LUA_NATIVE_STATS_STAT_SET_USER_ID);
		STATS.set_function("STAT_SET_CURRENT_POSIX_TIME", LUA_NATIVE_STATS_STAT_SET_CURRENT_POSIX_TIME);
		STATS.set_function("STAT_GET_INT", LUA_NATIVE_STATS_STAT_GET_INT);
		STATS.set_function("STAT_GET_FLOAT", LUA_NATIVE_STATS_STAT_GET_FLOAT);
		STATS.set_function("STAT_GET_BOOL", LUA_NATIVE_STATS_STAT_GET_BOOL);
		STATS.set_function("STAT_GET_DATE", LUA_NATIVE_STATS_STAT_GET_DATE);
		STATS.set_function("STAT_GET_STRING", LUA_NATIVE_STATS_STAT_GET_STRING);
		STATS.set_function("STAT_GET_POS", LUA_NATIVE_STATS_STAT_GET_POS);
		STATS.set_function("STAT_GET_MASKED_INT", LUA_NATIVE_STATS_STAT_GET_MASKED_INT);
		STATS.set_function("STAT_GET_USER_ID", LUA_NATIVE_STATS_STAT_GET_USER_ID);
		STATS.set_function("STAT_GET_LICENSE_PLATE", LUA_NATIVE_STATS_STAT_GET_LICENSE_PLATE);
		STATS.set_function("STAT_SET_LICENSE_PLATE", LUA_NATIVE_STATS_STAT_SET_LICENSE_PLATE);
		STATS.set_function("STAT_INCREMENT", LUA_NATIVE_STATS_STAT_INCREMENT);
		STATS.set_function("STAT_COMMUNITY_START_SYNCH", LUA_NATIVE_STATS_STAT_COMMUNITY_START_SYNCH);
		STATS.set_function("STAT_COMMUNITY_SYNCH_IS_PENDING", LUA_NATIVE_STATS_STAT_COMMUNITY_SYNCH_IS_PENDING);
		STATS.set_function("STAT_COMMUNITY_GET_HISTORY", LUA_NATIVE_STATS_STAT_COMMUNITY_GET_HISTORY);
		STATS.set_function("STAT_RESET_ALL_ONLINE_CHARACTER_STATS", LUA_NATIVE_STATS_STAT_RESET_ALL_ONLINE_CHARACTER_STATS);
		STATS.set_function("STAT_LOCAL_RESET_ALL_ONLINE_CHARACTER_STATS", LUA_NATIVE_STATS_STAT_LOCAL_RESET_ALL_ONLINE_CHARACTER_STATS);
		STATS.set_function("STAT_GET_NUMBER_OF_DAYS", LUA_NATIVE_STATS_STAT_GET_NUMBER_OF_DAYS);
		STATS.set_function("STAT_GET_NUMBER_OF_HOURS", LUA_NATIVE_STATS_STAT_GET_NUMBER_OF_HOURS);
		STATS.set_function("STAT_GET_NUMBER_OF_MINUTES", LUA_NATIVE_STATS_STAT_GET_NUMBER_OF_MINUTES);
		STATS.set_function("STAT_GET_NUMBER_OF_SECONDS", LUA_NATIVE_STATS_STAT_GET_NUMBER_OF_SECONDS);
		STATS.set_function("STAT_SET_PROFILE_SETTING_VALUE", LUA_NATIVE_STATS_STAT_SET_PROFILE_SETTING_VALUE);
		STATS.set_function("STATS_COMPLETED_CHARACTER_CREATION", LUA_NATIVE_STATS_STATS_COMPLETED_CHARACTER_CREATION);
		STATS.set_function("PACKED_STAT_GET_INT_STAT_INDEX", LUA_NATIVE_STATS_PACKED_STAT_GET_INT_STAT_INDEX);
		STATS.set_function("GET_PACKED_INT_STAT_KEY", LUA_NATIVE_STATS_GET_PACKED_INT_STAT_KEY);
		STATS.set_function("GET_PACKED_TU_INT_STAT_KEY", LUA_NATIVE_STATS_GET_PACKED_TU_INT_STAT_KEY);
		STATS.set_function("GET_PACKED_NG_INT_STAT_KEY", LUA_NATIVE_STATS_GET_PACKED_NG_INT_STAT_KEY);
		STATS.set_function("GET_PACKED_STAT_BOOL_CODE", LUA_NATIVE_STATS_GET_PACKED_STAT_BOOL_CODE);
		STATS.set_function("GET_PACKED_STAT_INT_CODE", LUA_NATIVE_STATS_GET_PACKED_STAT_INT_CODE);
		STATS.set_function("SET_PACKED_STAT_BOOL_CODE", LUA_NATIVE_STATS_SET_PACKED_STAT_BOOL_CODE);
		STATS.set_function("SET_PACKED_STAT_INT_CODE", LUA_NATIVE_STATS_SET_PACKED_STAT_INT_CODE);
		STATS.set_function("PLAYSTATS_BACKGROUND_SCRIPT_ACTION", LUA_NATIVE_STATS_PLAYSTATS_BACKGROUND_SCRIPT_ACTION);
		STATS.set_function("PLAYSTATS_FLOW_LOW_", LUA_NATIVE_STATS_PLAYSTATS_FLOW_LOW_);
		STATS.set_function("PLAYSTATS_FLOW_MEDIUM_", LUA_NATIVE_STATS_PLAYSTATS_FLOW_MEDIUM_);
		STATS.set_function("PLAYSTATS_NPC_INVITE", LUA_NATIVE_STATS_PLAYSTATS_NPC_INVITE);
		STATS.set_function("PLAYSTATS_AWARD_XP", LUA_NATIVE_STATS_PLAYSTATS_AWARD_XP);
		STATS.set_function("PLAYSTATS_RANK_UP", LUA_NATIVE_STATS_PLAYSTATS_RANK_UP);
		STATS.set_function("PLAYSTATS_STARTED_SESSION_IN_OFFLINEMODE", LUA_NATIVE_STATS_PLAYSTATS_STARTED_SESSION_IN_OFFLINEMODE);
		STATS.set_function("PLAYSTATS_ACTIVITY_DONE", LUA_NATIVE_STATS_PLAYSTATS_ACTIVITY_DONE);
		STATS.set_function("PLAYSTATS_LEAVE_JOB_CHAIN", LUA_NATIVE_STATS_PLAYSTATS_LEAVE_JOB_CHAIN);
		STATS.set_function("PLAYSTATS_MISSION_STARTED", LUA_NATIVE_STATS_PLAYSTATS_MISSION_STARTED);
		STATS.set_function("PLAYSTATS_MISSION_OVER", LUA_NATIVE_STATS_PLAYSTATS_MISSION_OVER);
		STATS.set_function("PLAYSTATS_MISSION_CHECKPOINT", LUA_NATIVE_STATS_PLAYSTATS_MISSION_CHECKPOINT);
		STATS.set_function("PLAYSTATS_RANDOM_MISSION_DONE", LUA_NATIVE_STATS_PLAYSTATS_RANDOM_MISSION_DONE);
		STATS.set_function("PLAYSTATS_ROS_BET", LUA_NATIVE_STATS_PLAYSTATS_ROS_BET);
		STATS.set_function("PLAYSTATS_RACE_CHECKPOINT", LUA_NATIVE_STATS_PLAYSTATS_RACE_CHECKPOINT);
		STATS.set_function("PLAYSTATS_CREATE_MATCH_HISTORY_ID_2", LUA_NATIVE_STATS_PLAYSTATS_CREATE_MATCH_HISTORY_ID_2);
		STATS.set_function("PLAYSTATS_MATCH_STARTED", LUA_NATIVE_STATS_PLAYSTATS_MATCH_STARTED);
		STATS.set_function("PLAYSTATS_SHOP_ITEM", LUA_NATIVE_STATS_PLAYSTATS_SHOP_ITEM);
		STATS.set_function("PLAYSTATS_CRATE_DROP_MISSION_DONE", LUA_NATIVE_STATS_PLAYSTATS_CRATE_DROP_MISSION_DONE);
		STATS.set_function("PLAYSTATS_CRATE_CREATED", LUA_NATIVE_STATS_PLAYSTATS_CRATE_CREATED);
		STATS.set_function("PLAYSTATS_HOLD_UP_MISSION_DONE", LUA_NATIVE_STATS_PLAYSTATS_HOLD_UP_MISSION_DONE);
		STATS.set_function("PLAYSTATS_IMPORT_EXPORT_MISSION_DONE", LUA_NATIVE_STATS_PLAYSTATS_IMPORT_EXPORT_MISSION_DONE);
		STATS.set_function("PLAYSTATS_RACE_TO_POINT_MISSION_DONE", LUA_NATIVE_STATS_PLAYSTATS_RACE_TO_POINT_MISSION_DONE);
		STATS.set_function("PLAYSTATS_ACQUIRED_HIDDEN_PACKAGE", LUA_NATIVE_STATS_PLAYSTATS_ACQUIRED_HIDDEN_PACKAGE);
		STATS.set_function("PLAYSTATS_WEBSITE_VISITED", LUA_NATIVE_STATS_PLAYSTATS_WEBSITE_VISITED);
		STATS.set_function("PLAYSTATS_FRIEND_ACTIVITY", LUA_NATIVE_STATS_PLAYSTATS_FRIEND_ACTIVITY);
		STATS.set_function("PLAYSTATS_ODDJOB_DONE", LUA_NATIVE_STATS_PLAYSTATS_ODDJOB_DONE);
		STATS.set_function("PLAYSTATS_PROP_CHANGE", LUA_NATIVE_STATS_PLAYSTATS_PROP_CHANGE);
		STATS.set_function("PLAYSTATS_CLOTH_CHANGE", LUA_NATIVE_STATS_PLAYSTATS_CLOTH_CHANGE);
		STATS.set_function("PLAYSTATS_WEAPON_MODE_CHANGE", LUA_NATIVE_STATS_PLAYSTATS_WEAPON_MODE_CHANGE);
		STATS.set_function("PLAYSTATS_CHEAT_APPLIED", LUA_NATIVE_STATS_PLAYSTATS_CHEAT_APPLIED);
		STATS.set_function("PLAYSTATS_JOB_ACTIVITY_END", LUA_NATIVE_STATS_PLAYSTATS_JOB_ACTIVITY_END);
		STATS.set_function("PLAYSTATS_JOB_BEND", LUA_NATIVE_STATS_PLAYSTATS_JOB_BEND);
		STATS.set_function("PLAYSTATS_JOB_LTS_END", LUA_NATIVE_STATS_PLAYSTATS_JOB_LTS_END);
		STATS.set_function("PLAYSTATS_JOB_LTS_ROUND_END", LUA_NATIVE_STATS_PLAYSTATS_JOB_LTS_ROUND_END);
		STATS.set_function("PLAYSTATS_QUICKFIX_TOOL", LUA_NATIVE_STATS_PLAYSTATS_QUICKFIX_TOOL);
		STATS.set_function("PLAYSTATS_IDLE_KICK", LUA_NATIVE_STATS_PLAYSTATS_IDLE_KICK);
		STATS.set_function("PLAYSTATS_SET_JOIN_TYPE", LUA_NATIVE_STATS_PLAYSTATS_SET_JOIN_TYPE);
		STATS.set_function("PLAYSTATS_HEIST_SAVE_CHEAT", LUA_NATIVE_STATS_PLAYSTATS_HEIST_SAVE_CHEAT);
		STATS.set_function("PLAYSTATS_APPEND_DIRECTOR_METRIC", LUA_NATIVE_STATS_PLAYSTATS_APPEND_DIRECTOR_METRIC);
		STATS.set_function("PLAYSTATS_AWARD_BAD_SPORT", LUA_NATIVE_STATS_PLAYSTATS_AWARD_BAD_SPORT);
		STATS.set_function("PLAYSTATS_PEGASUS_AS_PERSONAL_AIRCRAFT", LUA_NATIVE_STATS_PLAYSTATS_PEGASUS_AS_PERSONAL_AIRCRAFT);
		STATS.set_function("PLAYSTATS_SHOPMENU_NAV_", LUA_NATIVE_STATS_PLAYSTATS_SHOPMENU_NAV_);
		STATS.set_function("PLAYSTATS_FM_EVENT_CHALLENGES", LUA_NATIVE_STATS_PLAYSTATS_FM_EVENT_CHALLENGES);
		STATS.set_function("PLAYSTATS_FM_EVENT_VEHICLETARGET", LUA_NATIVE_STATS_PLAYSTATS_FM_EVENT_VEHICLETARGET);
		STATS.set_function("PLAYSTATS_FM_EVENT_URBANWARFARE", LUA_NATIVE_STATS_PLAYSTATS_FM_EVENT_URBANWARFARE);
		STATS.set_function("PLAYSTATS_FM_EVENT_CHECKPOINTCOLLECTION", LUA_NATIVE_STATS_PLAYSTATS_FM_EVENT_CHECKPOINTCOLLECTION);
		STATS.set_function("PLAYSTATS_FM_EVENT_ATOB", LUA_NATIVE_STATS_PLAYSTATS_FM_EVENT_ATOB);
		STATS.set_function("PLAYSTATS_FM_EVENT_PENNEDIN", LUA_NATIVE_STATS_PLAYSTATS_FM_EVENT_PENNEDIN);
		STATS.set_function("PLAYSTATS_FM_EVENT_PASSTHEPARCEL", LUA_NATIVE_STATS_PLAYSTATS_FM_EVENT_PASSTHEPARCEL);
		STATS.set_function("PLAYSTATS_FM_EVENT_HOTPROPERTY", LUA_NATIVE_STATS_PLAYSTATS_FM_EVENT_HOTPROPERTY);
		STATS.set_function("PLAYSTATS_FM_EVENT_DEADDROP", LUA_NATIVE_STATS_PLAYSTATS_FM_EVENT_DEADDROP);
		STATS.set_function("PLAYSTATS_FM_EVENT_KINGOFTHECASTLE", LUA_NATIVE_STATS_PLAYSTATS_FM_EVENT_KINGOFTHECASTLE);
		STATS.set_function("PLAYSTATS_FM_EVENT_CRIMINALDAMAGE", LUA_NATIVE_STATS_PLAYSTATS_FM_EVENT_CRIMINALDAMAGE);
		STATS.set_function("PLAYSTATS_FM_EVENT_COMPETITIVEURBANWARFARE", LUA_NATIVE_STATS_PLAYSTATS_FM_EVENT_COMPETITIVEURBANWARFARE);
		STATS.set_function("PLAYSTATS_FM_EVENT_HUNTBEAST", LUA_NATIVE_STATS_PLAYSTATS_FM_EVENT_HUNTBEAST);
		STATS.set_function("PLAYSTATS_PIMENU_HIDE_OPTIONS", LUA_NATIVE_STATS_PLAYSTATS_PIMENU_HIDE_OPTIONS);
		STATS.set_function("LEADERBOARDS_GET_NUMBER_OF_COLUMNS", LUA_NATIVE_STATS_LEADERBOARDS_GET_NUMBER_OF_COLUMNS);
		STATS.set_function("LEADERBOARDS_GET_COLUMN_ID", LUA_NATIVE_STATS_LEADERBOARDS_GET_COLUMN_ID);
		STATS.set_function("LEADERBOARDS_GET_COLUMN_TYPE", LUA_NATIVE_STATS_LEADERBOARDS_GET_COLUMN_TYPE);
		STATS.set_function("LEADERBOARDS_READ_CLEAR_ALL", LUA_NATIVE_STATS_LEADERBOARDS_READ_CLEAR_ALL);
		STATS.set_function("LEADERBOARDS_READ_CLEAR", LUA_NATIVE_STATS_LEADERBOARDS_READ_CLEAR);
		STATS.set_function("LEADERBOARDS_READ_PENDING", LUA_NATIVE_STATS_LEADERBOARDS_READ_PENDING);
		STATS.set_function("LEADERBOARDS_READ_ANY_PENDING", LUA_NATIVE_STATS_LEADERBOARDS_READ_ANY_PENDING);
		STATS.set_function("LEADERBOARDS_READ_SUCCESSFUL", LUA_NATIVE_STATS_LEADERBOARDS_READ_SUCCESSFUL);
		STATS.set_function("LEADERBOARDS2_READ_FRIENDS_BY_ROW", LUA_NATIVE_STATS_LEADERBOARDS2_READ_FRIENDS_BY_ROW);
		STATS.set_function("LEADERBOARDS2_READ_BY_HANDLE", LUA_NATIVE_STATS_LEADERBOARDS2_READ_BY_HANDLE);
		STATS.set_function("LEADERBOARDS2_READ_BY_RANK", LUA_NATIVE_STATS_LEADERBOARDS2_READ_BY_RANK);
		STATS.set_function("LEADERBOARDS2_READ_BY_RADIUS", LUA_NATIVE_STATS_LEADERBOARDS2_READ_BY_RADIUS);
		STATS.set_function("LEADERBOARDS2_READ_BY_SCORE_INT", LUA_NATIVE_STATS_LEADERBOARDS2_READ_BY_SCORE_INT);
		STATS.set_function("LEADERBOARDS2_READ_BY_SCORE_FLOAT", LUA_NATIVE_STATS_LEADERBOARDS2_READ_BY_SCORE_FLOAT);
		STATS.set_function("LEADERBOARDS2_READ_RANK_PREDICTION", LUA_NATIVE_STATS_LEADERBOARDS2_READ_RANK_PREDICTION);
		STATS.set_function("LEADERBOARDS2_READ_BY_PLAFORM", LUA_NATIVE_STATS_LEADERBOARDS2_READ_BY_PLAFORM);
		STATS.set_function("LEADERBOARDS2_READ_GET_ROW_DATA_START", LUA_NATIVE_STATS_LEADERBOARDS2_READ_GET_ROW_DATA_START);
		STATS.set_function("LEADERBOARDS2_READ_GET_ROW_DATA_END", LUA_NATIVE_STATS_LEADERBOARDS2_READ_GET_ROW_DATA_END);
		STATS.set_function("LEADERBOARDS2_READ_GET_ROW_DATA_INFO", LUA_NATIVE_STATS_LEADERBOARDS2_READ_GET_ROW_DATA_INFO);
		STATS.set_function("LEADERBOARDS2_READ_GET_ROW_DATA_INT", LUA_NATIVE_STATS_LEADERBOARDS2_READ_GET_ROW_DATA_INT);
		STATS.set_function("LEADERBOARDS2_READ_GET_ROW_DATA_FLOAT", LUA_NATIVE_STATS_LEADERBOARDS2_READ_GET_ROW_DATA_FLOAT);
		STATS.set_function("LEADERBOARDS2_WRITE_DATA", LUA_NATIVE_STATS_LEADERBOARDS2_WRITE_DATA);
		STATS.set_function("LEADERBOARDS_WRITE_ADD_COLUMN", LUA_NATIVE_STATS_LEADERBOARDS_WRITE_ADD_COLUMN);
		STATS.set_function("LEADERBOARDS_WRITE_ADD_COLUMN_LONG", LUA_NATIVE_STATS_LEADERBOARDS_WRITE_ADD_COLUMN_LONG);
		STATS.set_function("LEADERBOARDS_CACHE_DATA_ROW", LUA_NATIVE_STATS_LEADERBOARDS_CACHE_DATA_ROW);
		STATS.set_function("LEADERBOARDS_CLEAR_CACHE_DATA", LUA_NATIVE_STATS_LEADERBOARDS_CLEAR_CACHE_DATA);
		STATS.set_function("LEADERBOARDS_CLEAR_CACHE_DATA_ID", LUA_NATIVE_STATS_LEADERBOARDS_CLEAR_CACHE_DATA_ID);
		STATS.set_function("LEADERBOARDS_GET_CACHE_EXISTS", LUA_NATIVE_STATS_LEADERBOARDS_GET_CACHE_EXISTS);
		STATS.set_function("LEADERBOARDS_GET_CACHE_TIME", LUA_NATIVE_STATS_LEADERBOARDS_GET_CACHE_TIME);
		STATS.set_function("LEADERBOARDS_GET_CACHE_NUMBER_OF_ROWS", LUA_NATIVE_STATS_LEADERBOARDS_GET_CACHE_NUMBER_OF_ROWS);
		STATS.set_function("LEADERBOARDS_GET_CACHE_DATA_ROW", LUA_NATIVE_STATS_LEADERBOARDS_GET_CACHE_DATA_ROW);
		STATS.set_function("PRESENCE_EVENT_UPDATESTAT_INT", LUA_NATIVE_STATS_PRESENCE_EVENT_UPDATESTAT_INT);
		STATS.set_function("PRESENCE_EVENT_UPDATESTAT_FLOAT", LUA_NATIVE_STATS_PRESENCE_EVENT_UPDATESTAT_FLOAT);
		STATS.set_function("PRESENCE_EVENT_UPDATESTAT_INT_WITH_STRING", LUA_NATIVE_STATS_PRESENCE_EVENT_UPDATESTAT_INT_WITH_STRING);
		STATS.set_function("GET_PLAYER_HAS_DRIVEN_ALL_VEHICLES", LUA_NATIVE_STATS_GET_PLAYER_HAS_DRIVEN_ALL_VEHICLES);
		STATS.set_function("SET_HAS_POSTED_ALL_VEHICLES_DRIVEN", LUA_NATIVE_STATS_SET_HAS_POSTED_ALL_VEHICLES_DRIVEN);
		STATS.set_function("SET_PROFILE_SETTING_PROLOGUE_COMPLETE", LUA_NATIVE_STATS_SET_PROFILE_SETTING_PROLOGUE_COMPLETE);
		STATS.set_function("SET_PROFILE_SETTING_SP_CHOP_MISSION_COMPLETE", LUA_NATIVE_STATS_SET_PROFILE_SETTING_SP_CHOP_MISSION_COMPLETE);
		STATS.set_function("SET_PROFILE_SETTING_CREATOR_RACES_DONE", LUA_NATIVE_STATS_SET_PROFILE_SETTING_CREATOR_RACES_DONE);
		STATS.set_function("SET_PROFILE_SETTING_CREATOR_DM_DONE", LUA_NATIVE_STATS_SET_PROFILE_SETTING_CREATOR_DM_DONE);
		STATS.set_function("SET_PROFILE_SETTING_CREATOR_CTF_DONE", LUA_NATIVE_STATS_SET_PROFILE_SETTING_CREATOR_CTF_DONE);
		STATS.set_function("SET_JOB_ACTIVITY_ID_STARTED", LUA_NATIVE_STATS_SET_JOB_ACTIVITY_ID_STARTED);
		STATS.set_function("SET_FREEMODE_PROLOGUE_DONE", LUA_NATIVE_STATS_SET_FREEMODE_PROLOGUE_DONE);
		STATS.set_function("SET_FREEMODE_STRAND_PROGRESSION_STATUS", LUA_NATIVE_STATS_SET_FREEMODE_STRAND_PROGRESSION_STATUS);
		STATS.set_function("STAT_NETWORK_INCREMENT_ON_SUICIDE", LUA_NATIVE_STATS_STAT_NETWORK_INCREMENT_ON_SUICIDE);
		STATS.set_function("STAT_SET_CHEAT_IS_ACTIVE", LUA_NATIVE_STATS_STAT_SET_CHEAT_IS_ACTIVE);
		STATS.set_function("LEADERBOARDS2_WRITE_DATA_FOR_EVENT_TYPE", LUA_NATIVE_STATS_LEADERBOARDS2_WRITE_DATA_FOR_EVENT_TYPE);
		STATS.set_function("FORCE_CLOUD_MP_STATS_DOWNLOAD_AND_OVERWRITE_LOCAL_SAVE", LUA_NATIVE_STATS_FORCE_CLOUD_MP_STATS_DOWNLOAD_AND_OVERWRITE_LOCAL_SAVE);
		STATS.set_function("STAT_MIGRATE_CLEAR_FOR_RESTART", LUA_NATIVE_STATS_STAT_MIGRATE_CLEAR_FOR_RESTART);
		STATS.set_function("STAT_MIGRATE_SAVEGAME_START", LUA_NATIVE_STATS_STAT_MIGRATE_SAVEGAME_START);
		STATS.set_function("STAT_MIGRATE_SAVEGAME_GET_STATUS", LUA_NATIVE_STATS_STAT_MIGRATE_SAVEGAME_GET_STATUS);
		STATS.set_function("STAT_MIGRATE_CHECK_ALREADY_DONE", LUA_NATIVE_STATS_STAT_MIGRATE_CHECK_ALREADY_DONE);
		STATS.set_function("STAT_MIGRATE_CHECK_START", LUA_NATIVE_STATS_STAT_MIGRATE_CHECK_START);
		STATS.set_function("STAT_MIGRATE_CHECK_GET_IS_PLATFORM_AVAILABLE", LUA_NATIVE_STATS_STAT_MIGRATE_CHECK_GET_IS_PLATFORM_AVAILABLE);
		STATS.set_function("STAT_MIGRATE_CHECK_GET_PLATFORM_STATUS", LUA_NATIVE_STATS_STAT_MIGRATE_CHECK_GET_PLATFORM_STATUS);
		STATS.set_function("STAT_GET_SAVE_MIGRATION_STATUS", LUA_NATIVE_STATS_STAT_GET_SAVE_MIGRATION_STATUS);
		STATS.set_function("STAT_SAVE_MIGRATION_CANCEL_PENDING_OPERATION", LUA_NATIVE_STATS_STAT_SAVE_MIGRATION_CANCEL_PENDING_OPERATION);
		STATS.set_function("STAT_GET_CANCEL_SAVE_MIGRATION_STATUS", LUA_NATIVE_STATS_STAT_GET_CANCEL_SAVE_MIGRATION_STATUS);
		STATS.set_function("STAT_SAVE_MIGRATION_CONSUME_CONTENT", LUA_NATIVE_STATS_STAT_SAVE_MIGRATION_CONSUME_CONTENT);
		STATS.set_function("STAT_GET_SAVE_MIGRATION_CONSUME_CONTENT_STATUS", LUA_NATIVE_STATS_STAT_GET_SAVE_MIGRATION_CONSUME_CONTENT_STATUS);
		STATS.set_function("STAT_ENABLE_STATS_TRACKING", LUA_NATIVE_STATS_STAT_ENABLE_STATS_TRACKING);
		STATS.set_function("STAT_DISABLE_STATS_TRACKING", LUA_NATIVE_STATS_STAT_DISABLE_STATS_TRACKING);
		STATS.set_function("STAT_IS_STATS_TRACKING_ENABLED", LUA_NATIVE_STATS_STAT_IS_STATS_TRACKING_ENABLED);
		STATS.set_function("STAT_START_RECORD_STAT", LUA_NATIVE_STATS_STAT_START_RECORD_STAT);
		STATS.set_function("STAT_STOP_RECORD_STAT", LUA_NATIVE_STATS_STAT_STOP_RECORD_STAT);
		STATS.set_function("STAT_GET_RECORDED_VALUE", LUA_NATIVE_STATS_STAT_GET_RECORDED_VALUE);
		STATS.set_function("STAT_IS_RECORDING_STAT", LUA_NATIVE_STATS_STAT_IS_RECORDING_STAT);
		STATS.set_function("STAT_GET_CURRENT_NEAR_MISS_NOCRASH_PRECISE", LUA_NATIVE_STATS_STAT_GET_CURRENT_NEAR_MISS_NOCRASH_PRECISE);
		STATS.set_function("STAT_GET_CURRENT_REAR_WHEEL_DISTANCE", LUA_NATIVE_STATS_STAT_GET_CURRENT_REAR_WHEEL_DISTANCE);
		STATS.set_function("STAT_GET_CURRENT_FRONT_WHEEL_DISTANCE", LUA_NATIVE_STATS_STAT_GET_CURRENT_FRONT_WHEEL_DISTANCE);
		STATS.set_function("STAT_GET_CURRENT_JUMP_DISTANCE", LUA_NATIVE_STATS_STAT_GET_CURRENT_JUMP_DISTANCE);
		STATS.set_function("STAT_GET_CURRENT_DRIVE_NOCRASH_DISTANCE", LUA_NATIVE_STATS_STAT_GET_CURRENT_DRIVE_NOCRASH_DISTANCE);
		STATS.set_function("STAT_GET_CURRENT_SPEED", LUA_NATIVE_STATS_STAT_GET_CURRENT_SPEED);
		STATS.set_function("STAT_GET_CURRENT_DRIVING_REVERSE_DISTANCE", LUA_NATIVE_STATS_STAT_GET_CURRENT_DRIVING_REVERSE_DISTANCE);
		STATS.set_function("STAT_GET_CURRENT_SKYDIVING_DISTANCE", LUA_NATIVE_STATS_STAT_GET_CURRENT_SKYDIVING_DISTANCE);
		STATS.set_function("STAT_GET_CHALLENGE_FLYING_DIST", LUA_NATIVE_STATS_STAT_GET_CHALLENGE_FLYING_DIST);
		STATS.set_function("STAT_GET_FLYING_ALTITUDE", LUA_NATIVE_STATS_STAT_GET_FLYING_ALTITUDE);
		STATS.set_function("STAT_IS_PLAYER_VEHICLE_ABOVE_OCEAN", LUA_NATIVE_STATS_STAT_IS_PLAYER_VEHICLE_ABOVE_OCEAN);
		STATS.set_function("STAT_GET_VEHICLE_BAIL_DISTANCE", LUA_NATIVE_STATS_STAT_GET_VEHICLE_BAIL_DISTANCE);
		STATS.set_function("STAT_ROLLBACK_SAVE_MIGRATION", LUA_NATIVE_STATS_STAT_ROLLBACK_SAVE_MIGRATION);
		STATS.set_function("SET_HAS_SPECIALEDITION_CONTENT", LUA_NATIVE_STATS_SET_HAS_SPECIALEDITION_CONTENT);
		STATS.set_function("SET_SAVE_MIGRATION_TRANSACTION_ID_WARNING", LUA_NATIVE_STATS_SET_SAVE_MIGRATION_TRANSACTION_ID_WARNING);
		STATS.set_function("GET_BOSS_GOON_UUID", LUA_NATIVE_STATS_GET_BOSS_GOON_UUID);
		STATS.set_function("PLAYSTATS_BW_BOSSONBOSSDEATHMATCH", LUA_NATIVE_STATS_PLAYSTATS_BW_BOSSONBOSSDEATHMATCH);
		STATS.set_function("PLAYSTATS_BW_YATCHATTACK", LUA_NATIVE_STATS_PLAYSTATS_BW_YATCHATTACK);
		STATS.set_function("PLAYSTATS_BW_HUNT_THE_BOSS", LUA_NATIVE_STATS_PLAYSTATS_BW_HUNT_THE_BOSS);
		STATS.set_function("PLAYSTATS_BW_SIGHTSEER", LUA_NATIVE_STATS_PLAYSTATS_BW_SIGHTSEER);
		STATS.set_function("PLAYSTATS_BW_ASSAULT", LUA_NATIVE_STATS_PLAYSTATS_BW_ASSAULT);
		STATS.set_function("PLAYSTATS_BW_BELLY_OF_THE_BEAST", LUA_NATIVE_STATS_PLAYSTATS_BW_BELLY_OF_THE_BEAST);
		STATS.set_function("PLAYSTATS_BW_HEAD_HUNTER", LUA_NATIVE_STATS_PLAYSTATS_BW_HEAD_HUNTER);
		STATS.set_function("PLAYSTATS_BW_FRAGILE_GOODS", LUA_NATIVE_STATS_PLAYSTATS_BW_FRAGILE_GOODS);
		STATS.set_function("PLAYSTATS_BW_AIR_FREIGHT", LUA_NATIVE_STATS_PLAYSTATS_BW_AIR_FREIGHT);
		STATS.set_function("PLAYSTATS_BC_CAR_JACKING", LUA_NATIVE_STATS_PLAYSTATS_BC_CAR_JACKING);
		STATS.set_function("PLAYSTATS_BC_SMASH_AND_GRAB", LUA_NATIVE_STATS_PLAYSTATS_BC_SMASH_AND_GRAB);
		STATS.set_function("PLAYSTATS_BC_PROTECTION_RACKET", LUA_NATIVE_STATS_PLAYSTATS_BC_PROTECTION_RACKET);
		STATS.set_function("PLAYSTATS_BC_MOST_WANTED", LUA_NATIVE_STATS_PLAYSTATS_BC_MOST_WANTED);
		STATS.set_function("PLAYSTATS_BC_FINDERS_KEEPERS", LUA_NATIVE_STATS_PLAYSTATS_BC_FINDERS_KEEPERS);
		STATS.set_function("PLAYSTATS_BC_POINT_TO_POINT", LUA_NATIVE_STATS_PLAYSTATS_BC_POINT_TO_POINT);
		STATS.set_function("PLAYSTATS_BC_CASHING", LUA_NATIVE_STATS_PLAYSTATS_BC_CASHING);
		STATS.set_function("PLAYSTATS_BC_SALVAGE", LUA_NATIVE_STATS_PLAYSTATS_BC_SALVAGE);
		STATS.set_function("PLAYSTATS_SPENT_PI_CUSTOM_LOADOUT", LUA_NATIVE_STATS_PLAYSTATS_SPENT_PI_CUSTOM_LOADOUT);
		STATS.set_function("PLAYSTATS_BUY_CONTRABAND_MISSION", LUA_NATIVE_STATS_PLAYSTATS_BUY_CONTRABAND_MISSION);
		STATS.set_function("PLAYSTATS_SELL_CONTRABAND_MISSION", LUA_NATIVE_STATS_PLAYSTATS_SELL_CONTRABAND_MISSION);
		STATS.set_function("PLAYSTATS_DEFEND_CONTRABAND_MISSION", LUA_NATIVE_STATS_PLAYSTATS_DEFEND_CONTRABAND_MISSION);
		STATS.set_function("PLAYSTATS_RECOVER_CONTRABAND_MISSION", LUA_NATIVE_STATS_PLAYSTATS_RECOVER_CONTRABAND_MISSION);
		STATS.set_function("PLAYSTATS_HIT_CONTRABAND_DESTROY_LIMIT", LUA_NATIVE_STATS_PLAYSTATS_HIT_CONTRABAND_DESTROY_LIMIT);
		STATS.set_function("START_BEING_BOSS", LUA_NATIVE_STATS_START_BEING_BOSS);
		STATS.set_function("START_BEING_GOON", LUA_NATIVE_STATS_START_BEING_GOON);
		STATS.set_function("END_BEING_BOSS", LUA_NATIVE_STATS_END_BEING_BOSS);
		STATS.set_function("END_BEING_GOON", LUA_NATIVE_STATS_END_BEING_GOON);
		STATS.set_function("HIRED_LIMO", LUA_NATIVE_STATS_HIRED_LIMO);
		STATS.set_function("ORDER_BOSS_VEHICLE", LUA_NATIVE_STATS_ORDER_BOSS_VEHICLE);
		STATS.set_function("CHANGE_UNIFORM", LUA_NATIVE_STATS_CHANGE_UNIFORM);
		STATS.set_function("CHANGE_GOON_LOOKING_FOR_WORK", LUA_NATIVE_STATS_CHANGE_GOON_LOOKING_FOR_WORK);
		STATS.set_function("SEND_METRIC_GHOSTING_TO_PLAYER", LUA_NATIVE_STATS_SEND_METRIC_GHOSTING_TO_PLAYER);
		STATS.set_function("SEND_METRIC_VIP_POACH", LUA_NATIVE_STATS_SEND_METRIC_VIP_POACH);
		STATS.set_function("SEND_METRIC_PUNISH_BODYGUARD", LUA_NATIVE_STATS_SEND_METRIC_PUNISH_BODYGUARD);
		STATS.set_function("PLAYSTATS_START_TRACKING_STUNTS", LUA_NATIVE_STATS_PLAYSTATS_START_TRACKING_STUNTS);
		STATS.set_function("PLAYSTATS_STOP_TRACKING_STUNTS", LUA_NATIVE_STATS_PLAYSTATS_STOP_TRACKING_STUNTS);
		STATS.set_function("PLAYSTATS_MISSION_ENDED", LUA_NATIVE_STATS_PLAYSTATS_MISSION_ENDED);
		STATS.set_function("PLAYSTATS_IMPEXP_MISSION_ENDED", LUA_NATIVE_STATS_PLAYSTATS_IMPEXP_MISSION_ENDED);
		STATS.set_function("PLAYSTATS_CHANGE_MC_ROLE", LUA_NATIVE_STATS_PLAYSTATS_CHANGE_MC_ROLE);
		STATS.set_function("PLAYSTATS_CHANGE_MC_OUTFIT", LUA_NATIVE_STATS_PLAYSTATS_CHANGE_MC_OUTFIT);
		STATS.set_function("PLAYSTATS_SWITCH_MC_EMBLEM", LUA_NATIVE_STATS_PLAYSTATS_SWITCH_MC_EMBLEM);
		STATS.set_function("PLAYSTATS_MC_REQUEST_BIKE", LUA_NATIVE_STATS_PLAYSTATS_MC_REQUEST_BIKE);
		STATS.set_function("PLAYSTATS_MC_KILLED_RIVAL_MC_MEMBER", LUA_NATIVE_STATS_PLAYSTATS_MC_KILLED_RIVAL_MC_MEMBER);
		STATS.set_function("PLAYSTATS_ABANDONED_MC", LUA_NATIVE_STATS_PLAYSTATS_ABANDONED_MC);
		STATS.set_function("PLAYSTATS_EARNED_MC_POINTS", LUA_NATIVE_STATS_PLAYSTATS_EARNED_MC_POINTS);
		STATS.set_function("PLAYSTATS_MC_FORMATION_ENDS", LUA_NATIVE_STATS_PLAYSTATS_MC_FORMATION_ENDS);
		STATS.set_function("PLAYSTATS_MC_CLUBHOUSE_ACTIVITY", LUA_NATIVE_STATS_PLAYSTATS_MC_CLUBHOUSE_ACTIVITY);
		STATS.set_function("PLAYSTATS_RIVAL_BEHAVIOR", LUA_NATIVE_STATS_PLAYSTATS_RIVAL_BEHAVIOR);
		STATS.set_function("PLAYSTATS_COPY_RANK_INTO_NEW_SLOT", LUA_NATIVE_STATS_PLAYSTATS_COPY_RANK_INTO_NEW_SLOT);
		STATS.set_function("PLAYSTATS_DUPE_DETECTED", LUA_NATIVE_STATS_PLAYSTATS_DUPE_DETECTED);
		STATS.set_function("PLAYSTATS_BAN_ALERT", LUA_NATIVE_STATS_PLAYSTATS_BAN_ALERT);
		STATS.set_function("PLAYSTATS_GUNRUNNING_MISSION_ENDED", LUA_NATIVE_STATS_PLAYSTATS_GUNRUNNING_MISSION_ENDED);
		STATS.set_function("PLAYSTATS_GUNRUNNING_RND", LUA_NATIVE_STATS_PLAYSTATS_GUNRUNNING_RND);
		STATS.set_function("PLAYSTATS_BUSINESS_BATTLE_ENDED", LUA_NATIVE_STATS_PLAYSTATS_BUSINESS_BATTLE_ENDED);
		STATS.set_function("PLAYSTATS_WAREHOUSE_MISSION_ENDED", LUA_NATIVE_STATS_PLAYSTATS_WAREHOUSE_MISSION_ENDED);
		STATS.set_function("PLAYSTATS_NIGHTCLUB_MISSION_ENDED", LUA_NATIVE_STATS_PLAYSTATS_NIGHTCLUB_MISSION_ENDED);
		STATS.set_function("PLAYSTATS_DJ_USAGE", LUA_NATIVE_STATS_PLAYSTATS_DJ_USAGE);
		STATS.set_function("PLAYSTATS_MINIGAME_USAGE", LUA_NATIVE_STATS_PLAYSTATS_MINIGAME_USAGE);
		STATS.set_function("PLAYSTATS_STONE_HATCHET_ENDED", LUA_NATIVE_STATS_PLAYSTATS_STONE_HATCHET_ENDED);
		STATS.set_function("PLAYSTATS_SMUGGLER_MISSION_ENDED", LUA_NATIVE_STATS_PLAYSTATS_SMUGGLER_MISSION_ENDED);
		STATS.set_function("PLAYSTATS_FM_HEIST_PREP_ENDED", LUA_NATIVE_STATS_PLAYSTATS_FM_HEIST_PREP_ENDED);
		STATS.set_function("PLAYSTATS_INSTANCED_HEIST_ENDED", LUA_NATIVE_STATS_PLAYSTATS_INSTANCED_HEIST_ENDED);
		STATS.set_function("PLAYSTATS_DAR_CHECKPOINT", LUA_NATIVE_STATS_PLAYSTATS_DAR_CHECKPOINT);
		STATS.set_function("PLAYSTATS_ENTER_SESSION_PACK", LUA_NATIVE_STATS_PLAYSTATS_ENTER_SESSION_PACK);
		STATS.set_function("PLAYSTATS_DRONE_USAGE", LUA_NATIVE_STATS_PLAYSTATS_DRONE_USAGE);
		STATS.set_function("PLAYSTATS_SPIN_WHEEL", LUA_NATIVE_STATS_PLAYSTATS_SPIN_WHEEL);
		STATS.set_function("PLAYSTATS_ARENA_WARS_SPECTATOR", LUA_NATIVE_STATS_PLAYSTATS_ARENA_WARS_SPECTATOR);
		STATS.set_function("PLAYSTATS_ARENA_WARS_ENDED", LUA_NATIVE_STATS_PLAYSTATS_ARENA_WARS_ENDED);
		STATS.set_function("PLAYSTATS_SWITCH_PASSIVE_MODE", LUA_NATIVE_STATS_PLAYSTATS_SWITCH_PASSIVE_MODE);
		STATS.set_function("PLAYSTATS_COLLECTIBLE_PICKED_UP", LUA_NATIVE_STATS_PLAYSTATS_COLLECTIBLE_PICKED_UP);
		STATS.set_function("PLAYSTATS_CASINO_STORY_MISSION_ENDED", LUA_NATIVE_STATS_PLAYSTATS_CASINO_STORY_MISSION_ENDED);
		STATS.set_function("PLAYSTATS_CASINO_CHIP", LUA_NATIVE_STATS_PLAYSTATS_CASINO_CHIP);
		STATS.set_function("PLAYSTATS_CASINO_ROULETTE", LUA_NATIVE_STATS_PLAYSTATS_CASINO_ROULETTE);
		STATS.set_function("PLAYSTATS_CASINO_BLACKJACK", LUA_NATIVE_STATS_PLAYSTATS_CASINO_BLACKJACK);
		STATS.set_function("PLAYSTATS_CASINO_THREE_CARD_POKER", LUA_NATIVE_STATS_PLAYSTATS_CASINO_THREE_CARD_POKER);
		STATS.set_function("PLAYSTATS_CASINO_SLOT_MACHINE", LUA_NATIVE_STATS_PLAYSTATS_CASINO_SLOT_MACHINE);
		STATS.set_function("PLAYSTATS_CASINO_INSIDE_TRACK", LUA_NATIVE_STATS_PLAYSTATS_CASINO_INSIDE_TRACK);
		STATS.set_function("PLAYSTATS_CASINO_LUCKY_SEVEN", LUA_NATIVE_STATS_PLAYSTATS_CASINO_LUCKY_SEVEN);
		STATS.set_function("PLAYSTATS_CASINO_ROULETTE_LIGHT", LUA_NATIVE_STATS_PLAYSTATS_CASINO_ROULETTE_LIGHT);
		STATS.set_function("PLAYSTATS_CASINO_BLACKJACK_LIGHT", LUA_NATIVE_STATS_PLAYSTATS_CASINO_BLACKJACK_LIGHT);
		STATS.set_function("PLAYSTATS_CASINO_THREE_CARD_POKER_LIGHT", LUA_NATIVE_STATS_PLAYSTATS_CASINO_THREE_CARD_POKER_LIGHT);
		STATS.set_function("PLAYSTATS_CASINO_SLOT_MACHINE_LIGHT", LUA_NATIVE_STATS_PLAYSTATS_CASINO_SLOT_MACHINE_LIGHT);
		STATS.set_function("PLAYSTATS_CASINO_INSIDE_TRACK_LIGHT", LUA_NATIVE_STATS_PLAYSTATS_CASINO_INSIDE_TRACK_LIGHT);
		STATS.set_function("PLAYSTATS_ARCADE_GAME", LUA_NATIVE_STATS_PLAYSTATS_ARCADE_GAME);
		STATS.set_function("PLAYSTATS_ARCADE_LOVE_MATCH", LUA_NATIVE_STATS_PLAYSTATS_ARCADE_LOVE_MATCH);
		STATS.set_function("PLAYSTATS_FREEMODE_CASINO_MISSION_ENDED", LUA_NATIVE_STATS_PLAYSTATS_FREEMODE_CASINO_MISSION_ENDED);
		STATS.set_function("PLAYSTATS_HEIST3_DRONE", LUA_NATIVE_STATS_PLAYSTATS_HEIST3_DRONE);
		STATS.set_function("PLAYSTATS_HEIST3_HACK", LUA_NATIVE_STATS_PLAYSTATS_HEIST3_HACK);
		STATS.set_function("PLAYSTATS_NPC_PHONE", LUA_NATIVE_STATS_PLAYSTATS_NPC_PHONE);
		STATS.set_function("PLAYSTATS_ARCADE_CABINET", LUA_NATIVE_STATS_PLAYSTATS_ARCADE_CABINET);
		STATS.set_function("PLAYSTATS_HEIST3_FINALE", LUA_NATIVE_STATS_PLAYSTATS_HEIST3_FINALE);
		STATS.set_function("PLAYSTATS_HEIST3_PREP", LUA_NATIVE_STATS_PLAYSTATS_HEIST3_PREP);
		STATS.set_function("PLAYSTATS_MASTER_CONTROL", LUA_NATIVE_STATS_PLAYSTATS_MASTER_CONTROL);
		STATS.set_function("PLAYSTATS_QUIT_MODE", LUA_NATIVE_STATS_PLAYSTATS_QUIT_MODE);
		STATS.set_function("PLAYSTATS_MISSION_VOTE", LUA_NATIVE_STATS_PLAYSTATS_MISSION_VOTE);
		STATS.set_function("PLAYSTATS_NJVS_VOTE", LUA_NATIVE_STATS_PLAYSTATS_NJVS_VOTE);
		STATS.set_function("PLAYSTATS_FM_MISSION_END", LUA_NATIVE_STATS_PLAYSTATS_FM_MISSION_END);
		STATS.set_function("PLAYSTATS_HEIST4_PREP", LUA_NATIVE_STATS_PLAYSTATS_HEIST4_PREP);
		STATS.set_function("PLAYSTATS_HEIST4_FINALE", LUA_NATIVE_STATS_PLAYSTATS_HEIST4_FINALE);
		STATS.set_function("PLAYSTATS_HEIST4_HACK", LUA_NATIVE_STATS_PLAYSTATS_HEIST4_HACK);
		STATS.set_function("PLAYSTATS_SUB_WEAP", LUA_NATIVE_STATS_PLAYSTATS_SUB_WEAP);
		STATS.set_function("PLAYSTATS_FAST_TRVL", LUA_NATIVE_STATS_PLAYSTATS_FAST_TRVL);
		STATS.set_function("PLAYSTATS_HUB_ENTRY", LUA_NATIVE_STATS_PLAYSTATS_HUB_ENTRY);
		STATS.set_function("PLAYSTATS_DJ_MISSION_ENDED", LUA_NATIVE_STATS_PLAYSTATS_DJ_MISSION_ENDED);
		STATS.set_function("PLAYSTATS_ROBBERY_PREP", LUA_NATIVE_STATS_PLAYSTATS_ROBBERY_PREP);
		STATS.set_function("PLAYSTATS_ROBBERY_FINALE", LUA_NATIVE_STATS_PLAYSTATS_ROBBERY_FINALE);
		STATS.set_function("PLAYSTATS_EXTRA_EVENT", LUA_NATIVE_STATS_PLAYSTATS_EXTRA_EVENT);
		STATS.set_function("PLAYSTATS_CARCLUB_POINTS", LUA_NATIVE_STATS_PLAYSTATS_CARCLUB_POINTS);
		STATS.set_function("PLAYSTATS_CARCLUB_CHALLENGE", LUA_NATIVE_STATS_PLAYSTATS_CARCLUB_CHALLENGE);
		STATS.set_function("PLAYSTATS_CARCLUB_PRIZE", LUA_NATIVE_STATS_PLAYSTATS_CARCLUB_PRIZE);
		STATS.set_function("PLAYSTATS_AWARD_NAV", LUA_NATIVE_STATS_PLAYSTATS_AWARD_NAV);
		STATS.set_function("PLAYSTATS_INST_MISSION_END", LUA_NATIVE_STATS_PLAYSTATS_INST_MISSION_END);
		STATS.set_function("PLAYSTATS_HUB_EXIT", LUA_NATIVE_STATS_PLAYSTATS_HUB_EXIT);
		STATS.set_function("PLAYSTATS_VEH_DEL", LUA_NATIVE_STATS_PLAYSTATS_VEH_DEL);
		STATS.set_function("PLAYSTATS_INVENTORY", LUA_NATIVE_STATS_PLAYSTATS_INVENTORY);
		STATS.set_function("PLAYSTATS_ACID_MISSION_END_", LUA_NATIVE_STATS_PLAYSTATS_ACID_MISSION_END_);
		STATS.set_function("PLAYSTATS_ACID_RND_", LUA_NATIVE_STATS_PLAYSTATS_ACID_RND_);
		STATS.set_function("PLAYSTATS_IDLE_", LUA_NATIVE_STATS_PLAYSTATS_IDLE_);
		STATS.set_function("PLAYSTATS_PLAYER_STYLE_", LUA_NATIVE_STATS_PLAYSTATS_PLAYER_STYLE_);
		STATS.set_function("PLAYSTATS_RANDOM_EVENT_", LUA_NATIVE_STATS_PLAYSTATS_RANDOM_EVENT_);
		STATS.set_function("PLAYSTATS_ALERT_", LUA_NATIVE_STATS_PLAYSTATS_ALERT_);
		STATS.set_function("PLAYSTATS_ATTRITION_STAGE_END_", LUA_NATIVE_STATS_PLAYSTATS_ATTRITION_STAGE_END_);
		STATS.set_function("PLAYSTATS_SHOWROOM_NAV_", LUA_NATIVE_STATS_PLAYSTATS_SHOWROOM_NAV_);
		STATS.set_function("PLAYSTATS_SHOWROOM_OVERVIEW_", LUA_NATIVE_STATS_PLAYSTATS_SHOWROOM_OVERVIEW_);
	}
}
