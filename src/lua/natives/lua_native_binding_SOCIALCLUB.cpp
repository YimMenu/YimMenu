#include "lua_native_binding.hpp"
#include "natives.hpp"

namespace lua::native
{
	static int LUA_NATIVE_SOCIALCLUB_SC_INBOX_GET_TOTAL_NUM_MESSAGES()
	{
		auto retval = SOCIALCLUB::SC_INBOX_GET_TOTAL_NUM_MESSAGES();
		return retval;
	}

	static Hash LUA_NATIVE_SOCIALCLUB_SC_INBOX_GET_MESSAGE_TYPE_AT_INDEX(int msgIndex)
	{
		auto retval = SOCIALCLUB::SC_INBOX_GET_MESSAGE_TYPE_AT_INDEX(msgIndex);
		return retval;
	}

	static bool LUA_NATIVE_SOCIALCLUB_SC_INBOX_GET_MESSAGE_IS_READ_AT_INDEX(int msgIndex)
	{
		auto retval = (bool)SOCIALCLUB::SC_INBOX_GET_MESSAGE_IS_READ_AT_INDEX(msgIndex);
		return retval;
	}

	static bool LUA_NATIVE_SOCIALCLUB_SC_INBOX_SET_MESSAGE_AS_READ_AT_INDEX(int msgIndex)
	{
		auto retval = (bool)SOCIALCLUB::SC_INBOX_SET_MESSAGE_AS_READ_AT_INDEX(msgIndex);
		return retval;
	}

	static std::tuple<bool, int> LUA_NATIVE_SOCIALCLUB_SC_INBOX_MESSAGE_GET_DATA_INT(int p0, sol::stack_object context, int out)
	{
		std::tuple<bool, int> return_values;
		std::get<0>(return_values) = (bool)SOCIALCLUB::SC_INBOX_MESSAGE_GET_DATA_INT(p0, context.is<const char*>() ? context.as<const char*>() : nullptr, &out);
		std::get<1>(return_values) = out;

		return return_values;
	}

	static bool LUA_NATIVE_SOCIALCLUB_SC_INBOX_MESSAGE_GET_DATA_BOOL(int p0, sol::stack_object p1)
	{
		auto retval = (bool)SOCIALCLUB::SC_INBOX_MESSAGE_GET_DATA_BOOL(p0, p1.is<const char*>() ? p1.as<const char*>() : nullptr);
		return retval;
	}

	static std::tuple<bool, char> LUA_NATIVE_SOCIALCLUB_SC_INBOX_MESSAGE_GET_DATA_STRING(int p0, sol::stack_object context, char out)
	{
		std::tuple<bool, char> return_values;
		std::get<0>(return_values) = (bool)SOCIALCLUB::SC_INBOX_MESSAGE_GET_DATA_STRING(p0, context.is<const char*>() ? context.as<const char*>() : nullptr, &out);
		std::get<1>(return_values) = out;

		return return_values;
	}

	static bool LUA_NATIVE_SOCIALCLUB_SC_INBOX_MESSAGE_DO_APPLY(int p0)
	{
		auto retval = (bool)SOCIALCLUB::SC_INBOX_MESSAGE_DO_APPLY(p0);
		return retval;
	}

	static const char* LUA_NATIVE_SOCIALCLUB_SC_INBOX_MESSAGE_GET_RAW_TYPE_AT_INDEX(int p0)
	{
		auto retval = SOCIALCLUB::SC_INBOX_MESSAGE_GET_RAW_TYPE_AT_INDEX(p0);
		return retval;
	}

	static void LUA_NATIVE_SOCIALCLUB_SC_INBOX_MESSAGE_PUSH_GAMER_T0_RECIP_LIST(uintptr_t gamerHandle)
	{
		SOCIALCLUB::SC_INBOX_MESSAGE_PUSH_GAMER_T0_RECIP_LIST((Any*)gamerHandle);
	}

	static void LUA_NATIVE_SOCIALCLUB_SC_INBOX_SEND_UGCSTATUPDATE_TO_RECIP_LIST(uintptr_t data)
	{
		SOCIALCLUB::SC_INBOX_SEND_UGCSTATUPDATE_TO_RECIP_LIST((Any*)data);
	}

	static bool LUA_NATIVE_SOCIALCLUB_SC_INBOX_MESSAGE_GET_UGCDATA(int p0, uintptr_t p1)
	{
		auto retval = (bool)SOCIALCLUB::SC_INBOX_MESSAGE_GET_UGCDATA(p0, (Any*)p1);
		return retval;
	}

	static bool LUA_NATIVE_SOCIALCLUB_SC_INBOX_GET_BOUNTY_DATA_AT_INDEX(int index, uintptr_t outData)
	{
		auto retval = (bool)SOCIALCLUB::SC_INBOX_GET_BOUNTY_DATA_AT_INDEX(index, (Any*)outData);
		return retval;
	}

	static void LUA_NATIVE_SOCIALCLUB_SC_EMAIL_RETRIEVE_EMAILS(int offset, int limit)
	{
		SOCIALCLUB::SC_EMAIL_RETRIEVE_EMAILS(offset, limit);
	}

	static int LUA_NATIVE_SOCIALCLUB_SC_EMAIL_GET_RETRIEVAL_STATUS()
	{
		auto retval = SOCIALCLUB::SC_EMAIL_GET_RETRIEVAL_STATUS();
		return retval;
	}

	static int LUA_NATIVE_SOCIALCLUB_SC_EMAIL_GET_NUM_RETRIEVED_EMAILS()
	{
		auto retval = SOCIALCLUB::SC_EMAIL_GET_NUM_RETRIEVED_EMAILS();
		return retval;
	}

	static bool LUA_NATIVE_SOCIALCLUB_SC_EMAIL_GET_EMAIL_AT_INDEX(int p0, uintptr_t p1)
	{
		auto retval = (bool)SOCIALCLUB::SC_EMAIL_GET_EMAIL_AT_INDEX(p0, (Any*)p1);
		return retval;
	}

	static void LUA_NATIVE_SOCIALCLUB_SC_EMAIL_DELETE_EMAILS(uintptr_t p0, Any p1)
	{
		SOCIALCLUB::SC_EMAIL_DELETE_EMAILS((Any*)p0, p1);
	}

	static void LUA_NATIVE_SOCIALCLUB_SC_EMAIL_MESSAGE_PUSH_GAMER_TO_RECIP_LIST(uintptr_t gamerHandle)
	{
		SOCIALCLUB::SC_EMAIL_MESSAGE_PUSH_GAMER_TO_RECIP_LIST((Any*)gamerHandle);
	}

	static void LUA_NATIVE_SOCIALCLUB_SC_EMAIL_MESSAGE_CLEAR_RECIP_LIST()
	{
		SOCIALCLUB::SC_EMAIL_MESSAGE_CLEAR_RECIP_LIST();
	}

	static void LUA_NATIVE_SOCIALCLUB_SC_EMAIL_SEND_EMAIL(sol::stack_object p0)
	{
		SOCIALCLUB::SC_EMAIL_SEND_EMAIL(p0.is<const char*>() ? p0.as<const char*>() : nullptr);
	}

	static bool LUA_NATIVE_SOCIALCLUB_SC_EMAIL_SET_CURRENT_EMAIL_TAG(Any p0)
	{
		auto retval = (bool)SOCIALCLUB::SC_EMAIL_SET_CURRENT_EMAIL_TAG(p0);
		return retval;
	}

	static void LUA_NATIVE_SOCIALCLUB_SC_CACHE_NEW_ROCKSTAR_MSGS(bool toggle)
	{
		SOCIALCLUB::SC_CACHE_NEW_ROCKSTAR_MSGS(toggle);
	}

	static bool LUA_NATIVE_SOCIALCLUB_SC_HAS_NEW_ROCKSTAR_MSG()
	{
		auto retval = (bool)SOCIALCLUB::SC_HAS_NEW_ROCKSTAR_MSG();
		return retval;
	}

	static const char* LUA_NATIVE_SOCIALCLUB_SC_GET_NEW_ROCKSTAR_MSG()
	{
		auto retval = SOCIALCLUB::SC_GET_NEW_ROCKSTAR_MSG();
		return retval;
	}

	static bool LUA_NATIVE_SOCIALCLUB_SC_PRESENCE_ATTR_SET_INT(Hash attrHash, int value)
	{
		auto retval = (bool)SOCIALCLUB::SC_PRESENCE_ATTR_SET_INT(attrHash, value);
		return retval;
	}

	static bool LUA_NATIVE_SOCIALCLUB_SC_PRESENCE_ATTR_SET_FLOAT(Hash attrHash, float value)
	{
		auto retval = (bool)SOCIALCLUB::SC_PRESENCE_ATTR_SET_FLOAT(attrHash, value);
		return retval;
	}

	static bool LUA_NATIVE_SOCIALCLUB_SC_PRESENCE_ATTR_SET_STRING(Hash attrHash, sol::stack_object value)
	{
		auto retval = (bool)SOCIALCLUB::SC_PRESENCE_ATTR_SET_STRING(attrHash, value.is<const char*>() ? value.as<const char*>() : nullptr);
		return retval;
	}

	static bool LUA_NATIVE_SOCIALCLUB_SC_PRESENCE_SET_ACTIVITY_RATING(Any p0, float p1)
	{
		auto retval = (bool)SOCIALCLUB::SC_PRESENCE_SET_ACTIVITY_RATING(p0, p1);
		return retval;
	}

	static std::tuple<bool, int> LUA_NATIVE_SOCIALCLUB_SC_GAMERDATA_GET_INT(sol::stack_object name, int value)
	{
		std::tuple<bool, int> return_values;
		std::get<0>(return_values) = (bool)SOCIALCLUB::SC_GAMERDATA_GET_INT(name.is<const char*>() ? name.as<const char*>() : nullptr, &value);
		std::get<1>(return_values) = value;

		return return_values;
	}

	static std::tuple<bool, float> LUA_NATIVE_SOCIALCLUB_SC_GAMERDATA_GET_FLOAT(sol::stack_object name, float value)
	{
		std::tuple<bool, float> return_values;
		std::get<0>(return_values) = (bool)SOCIALCLUB::SC_GAMERDATA_GET_FLOAT(name.is<const char*>() ? name.as<const char*>() : nullptr, &value);
		std::get<1>(return_values) = value;

		return return_values;
	}

	static bool LUA_NATIVE_SOCIALCLUB_SC_GAMERDATA_GET_BOOL(sol::stack_object name)
	{
		auto retval = (bool)SOCIALCLUB::SC_GAMERDATA_GET_BOOL(name.is<const char*>() ? name.as<const char*>() : nullptr);
		return retval;
	}

	static std::tuple<bool, char> LUA_NATIVE_SOCIALCLUB_SC_GAMERDATA_GET_STRING(sol::stack_object name, char value)
	{
		std::tuple<bool, char> return_values;
		std::get<0>(return_values) = (bool)SOCIALCLUB::SC_GAMERDATA_GET_STRING(name.is<const char*>() ? name.as<const char*>() : nullptr, &value);
		std::get<1>(return_values) = value;

		return return_values;
	}

	static std::tuple<bool, float> LUA_NATIVE_SOCIALCLUB_SC_GAMERDATA_GET_ACTIVE_XP_BONUS(float value)
	{
		std::tuple<bool, float> return_values;
		std::get<0>(return_values) = (bool)SOCIALCLUB::SC_GAMERDATA_GET_ACTIVE_XP_BONUS(&value);
		std::get<1>(return_values) = value;

		return return_values;
	}

	static std::tuple<bool, int> LUA_NATIVE_SOCIALCLUB_SC_PROFANITY_CHECK_STRING(sol::stack_object string, int token)
	{
		std::tuple<bool, int> return_values;
		std::get<0>(return_values) = (bool)SOCIALCLUB::SC_PROFANITY_CHECK_STRING(string.is<const char*>() ? string.as<const char*>() : nullptr, &token);
		std::get<1>(return_values) = token;

		return return_values;
	}

	static std::tuple<bool, int> LUA_NATIVE_SOCIALCLUB_SC_PROFANITY_CHECK_STRING_UGC(sol::stack_object string, int token)
	{
		std::tuple<bool, int> return_values;
		std::get<0>(return_values) = (bool)SOCIALCLUB::SC_PROFANITY_CHECK_STRING_UGC(string.is<const char*>() ? string.as<const char*>() : nullptr, &token);
		std::get<1>(return_values) = token;

		return return_values;
	}

	static bool LUA_NATIVE_SOCIALCLUB_SC_PROFANITY_GET_CHECK_IS_VALID(int token)
	{
		auto retval = (bool)SOCIALCLUB::SC_PROFANITY_GET_CHECK_IS_VALID(token);
		return retval;
	}

	static bool LUA_NATIVE_SOCIALCLUB_SC_PROFANITY_GET_CHECK_IS_PENDING(int token)
	{
		auto retval = (bool)SOCIALCLUB::SC_PROFANITY_GET_CHECK_IS_PENDING(token);
		return retval;
	}

	static bool LUA_NATIVE_SOCIALCLUB_SC_PROFANITY_GET_STRING_PASSED(int token)
	{
		auto retval = (bool)SOCIALCLUB::SC_PROFANITY_GET_STRING_PASSED(token);
		return retval;
	}

	static int LUA_NATIVE_SOCIALCLUB_SC_PROFANITY_GET_STRING_STATUS(int token)
	{
		auto retval = SOCIALCLUB::SC_PROFANITY_GET_STRING_STATUS(token);
		return retval;
	}

	static std::tuple<bool, int> LUA_NATIVE_SOCIALCLUB_SC_LICENSEPLATE_CHECK_STRING(sol::stack_object p0, int p1)
	{
		std::tuple<bool, int> return_values;
		std::get<0>(return_values) = (bool)SOCIALCLUB::SC_LICENSEPLATE_CHECK_STRING(p0.is<const char*>() ? p0.as<const char*>() : nullptr, &p1);
		std::get<1>(return_values) = p1;

		return return_values;
	}

	static bool LUA_NATIVE_SOCIALCLUB_SC_LICENSEPLATE_GET_CHECK_IS_VALID(Any p0)
	{
		auto retval = (bool)SOCIALCLUB::SC_LICENSEPLATE_GET_CHECK_IS_VALID(p0);
		return retval;
	}

	static bool LUA_NATIVE_SOCIALCLUB_SC_LICENSEPLATE_GET_CHECK_IS_PENDING(Any p0)
	{
		auto retval = (bool)SOCIALCLUB::SC_LICENSEPLATE_GET_CHECK_IS_PENDING(p0);
		return retval;
	}

	static int LUA_NATIVE_SOCIALCLUB_SC_LICENSEPLATE_GET_COUNT(int token)
	{
		auto retval = SOCIALCLUB::SC_LICENSEPLATE_GET_COUNT(token);
		return retval;
	}

	static const char* LUA_NATIVE_SOCIALCLUB_SC_LICENSEPLATE_GET_PLATE(int token, int plateIndex)
	{
		auto retval = SOCIALCLUB::SC_LICENSEPLATE_GET_PLATE(token, plateIndex);
		return retval;
	}

	static const char* LUA_NATIVE_SOCIALCLUB_SC_LICENSEPLATE_GET_PLATE_DATA(int token, int plateIndex)
	{
		auto retval = SOCIALCLUB::SC_LICENSEPLATE_GET_PLATE_DATA(token, plateIndex);
		return retval;
	}

	static bool LUA_NATIVE_SOCIALCLUB_SC_LICENSEPLATE_SET_PLATE_DATA(sol::stack_object oldPlateText, sol::stack_object newPlateText, uintptr_t plateData)
	{
		auto retval = (bool)SOCIALCLUB::SC_LICENSEPLATE_SET_PLATE_DATA(oldPlateText.is<const char*>() ? oldPlateText.as<const char*>() : nullptr, newPlateText.is<const char*>() ? newPlateText.as<const char*>() : nullptr, (Any*)plateData);
		return retval;
	}

	static std::tuple<bool, int> LUA_NATIVE_SOCIALCLUB_SC_LICENSEPLATE_ADD(sol::stack_object plateText, uintptr_t plateData, int token)
	{
		std::tuple<bool, int> return_values;
		std::get<0>(return_values) = (bool)SOCIALCLUB::SC_LICENSEPLATE_ADD(plateText.is<const char*>() ? plateText.as<const char*>() : nullptr, (Any*)plateData, &token);
		std::get<1>(return_values) = token;

		return return_values;
	}

	static bool LUA_NATIVE_SOCIALCLUB_SC_LICENSEPLATE_GET_ADD_IS_PENDING(int token)
	{
		auto retval = (bool)SOCIALCLUB::SC_LICENSEPLATE_GET_ADD_IS_PENDING(token);
		return retval;
	}

	static int LUA_NATIVE_SOCIALCLUB_SC_LICENSEPLATE_GET_ADD_STATUS(int token)
	{
		auto retval = SOCIALCLUB::SC_LICENSEPLATE_GET_ADD_STATUS(token);
		return retval;
	}

	static std::tuple<bool, int> LUA_NATIVE_SOCIALCLUB_SC_LICENSEPLATE_ISVALID(sol::stack_object plateText, int token)
	{
		std::tuple<bool, int> return_values;
		std::get<0>(return_values) = (bool)SOCIALCLUB::SC_LICENSEPLATE_ISVALID(plateText.is<const char*>() ? plateText.as<const char*>() : nullptr, &token);
		std::get<1>(return_values) = token;

		return return_values;
	}

	static bool LUA_NATIVE_SOCIALCLUB_SC_LICENSEPLATE_GET_ISVALID_IS_PENDING(int token)
	{
		auto retval = (bool)SOCIALCLUB::SC_LICENSEPLATE_GET_ISVALID_IS_PENDING(token);
		return retval;
	}

	static int LUA_NATIVE_SOCIALCLUB_SC_LICENSEPLATE_GET_ISVALID_STATUS(int token)
	{
		auto retval = SOCIALCLUB::SC_LICENSEPLATE_GET_ISVALID_STATUS(token);
		return retval;
	}

	static bool LUA_NATIVE_SOCIALCLUB_SC_COMMUNITY_EVENT_IS_ACTIVE()
	{
		auto retval = (bool)SOCIALCLUB::SC_COMMUNITY_EVENT_IS_ACTIVE();
		return retval;
	}

	static int LUA_NATIVE_SOCIALCLUB_SC_COMMUNITY_EVENT_GET_EVENT_ID()
	{
		auto retval = SOCIALCLUB::SC_COMMUNITY_EVENT_GET_EVENT_ID();
		return retval;
	}

	static std::tuple<bool, int> LUA_NATIVE_SOCIALCLUB_SC_COMMUNITY_EVENT_GET_EXTRA_DATA_INT(sol::stack_object p0, int p1)
	{
		std::tuple<bool, int> return_values;
		std::get<0>(return_values) = (bool)SOCIALCLUB::SC_COMMUNITY_EVENT_GET_EXTRA_DATA_INT(p0.is<const char*>() ? p0.as<const char*>() : nullptr, &p1);
		std::get<1>(return_values) = p1;

		return return_values;
	}

	static std::tuple<bool, float> LUA_NATIVE_SOCIALCLUB_SC_COMMUNITY_EVENT_GET_EXTRA_DATA_FLOAT(sol::stack_object p0, float p1)
	{
		std::tuple<bool, float> return_values;
		std::get<0>(return_values) = (bool)SOCIALCLUB::SC_COMMUNITY_EVENT_GET_EXTRA_DATA_FLOAT(p0.is<const char*>() ? p0.as<const char*>() : nullptr, &p1);
		std::get<1>(return_values) = p1;

		return return_values;
	}

	static std::tuple<bool, char> LUA_NATIVE_SOCIALCLUB_SC_COMMUNITY_EVENT_GET_EXTRA_DATA_STRING(sol::stack_object p0, char p1)
	{
		std::tuple<bool, char> return_values;
		std::get<0>(return_values) = (bool)SOCIALCLUB::SC_COMMUNITY_EVENT_GET_EXTRA_DATA_STRING(p0.is<const char*>() ? p0.as<const char*>() : nullptr, &p1);
		std::get<1>(return_values) = p1;

		return return_values;
	}

	static std::tuple<bool, char> LUA_NATIVE_SOCIALCLUB_SC_COMMUNITY_EVENT_GET_DISPLAY_NAME(char p0)
	{
		std::tuple<bool, char> return_values;
		std::get<0>(return_values) = (bool)SOCIALCLUB::SC_COMMUNITY_EVENT_GET_DISPLAY_NAME(&p0);
		std::get<1>(return_values) = p0;

		return return_values;
	}

	static bool LUA_NATIVE_SOCIALCLUB_SC_COMMUNITY_EVENT_IS_ACTIVE_FOR_TYPE(sol::stack_object p0)
	{
		auto retval = (bool)SOCIALCLUB::SC_COMMUNITY_EVENT_IS_ACTIVE_FOR_TYPE(p0.is<const char*>() ? p0.as<const char*>() : nullptr);
		return retval;
	}

	static int LUA_NATIVE_SOCIALCLUB_SC_COMMUNITY_EVENT_GET_EVENT_ID_FOR_TYPE(sol::stack_object p0)
	{
		auto retval = SOCIALCLUB::SC_COMMUNITY_EVENT_GET_EVENT_ID_FOR_TYPE(p0.is<const char*>() ? p0.as<const char*>() : nullptr);
		return retval;
	}

	static std::tuple<bool, int> LUA_NATIVE_SOCIALCLUB_SC_COMMUNITY_EVENT_GET_EXTRA_DATA_INT_FOR_TYPE(sol::stack_object p0, int p1, sol::stack_object p2)
	{
		std::tuple<bool, int> return_values;
		std::get<0>(return_values) = (bool)SOCIALCLUB::SC_COMMUNITY_EVENT_GET_EXTRA_DATA_INT_FOR_TYPE(p0.is<const char*>() ? p0.as<const char*>() : nullptr, &p1, p2.is<const char*>() ? p2.as<const char*>() : nullptr);
		std::get<1>(return_values) = p1;

		return return_values;
	}

	static std::tuple<bool, float> LUA_NATIVE_SOCIALCLUB_SC_COMMUNITY_EVENT_GET_EXTRA_DATA_FLOAT_FOR_TYPE(sol::stack_object p0, float p1, sol::stack_object p2)
	{
		std::tuple<bool, float> return_values;
		std::get<0>(return_values) = (bool)SOCIALCLUB::SC_COMMUNITY_EVENT_GET_EXTRA_DATA_FLOAT_FOR_TYPE(p0.is<const char*>() ? p0.as<const char*>() : nullptr, &p1, p2.is<const char*>() ? p2.as<const char*>() : nullptr);
		std::get<1>(return_values) = p1;

		return return_values;
	}

	static std::tuple<bool, char> LUA_NATIVE_SOCIALCLUB_SC_COMMUNITY_EVENT_GET_EXTRA_DATA_STRING_FOR_TYPE(sol::stack_object p0, char p1, sol::stack_object p2)
	{
		std::tuple<bool, char> return_values;
		std::get<0>(return_values) = (bool)SOCIALCLUB::SC_COMMUNITY_EVENT_GET_EXTRA_DATA_STRING_FOR_TYPE(p0.is<const char*>() ? p0.as<const char*>() : nullptr, &p1, p2.is<const char*>() ? p2.as<const char*>() : nullptr);
		std::get<1>(return_values) = p1;

		return return_values;
	}

	static std::tuple<bool, char> LUA_NATIVE_SOCIALCLUB_SC_COMMUNITY_EVENT_GET_DISPLAY_NAME_FOR_TYPE(char p0, sol::stack_object p1)
	{
		std::tuple<bool, char> return_values;
		std::get<0>(return_values) = (bool)SOCIALCLUB::SC_COMMUNITY_EVENT_GET_DISPLAY_NAME_FOR_TYPE(&p0, p1.is<const char*>() ? p1.as<const char*>() : nullptr);
		std::get<1>(return_values) = p0;

		return return_values;
	}

	static bool LUA_NATIVE_SOCIALCLUB_SC_COMMUNITY_EVENT_IS_ACTIVE_BY_ID(int p0)
	{
		auto retval = (bool)SOCIALCLUB::SC_COMMUNITY_EVENT_IS_ACTIVE_BY_ID(p0);
		return retval;
	}

	static std::tuple<bool, int> LUA_NATIVE_SOCIALCLUB_SC_COMMUNITY_EVENT_GET_EXTRA_DATA_INT_BY_ID(int p0, sol::stack_object p1, int p2)
	{
		std::tuple<bool, int> return_values;
		std::get<0>(return_values) = (bool)SOCIALCLUB::SC_COMMUNITY_EVENT_GET_EXTRA_DATA_INT_BY_ID(p0, p1.is<const char*>() ? p1.as<const char*>() : nullptr, &p2);
		std::get<1>(return_values) = p2;

		return return_values;
	}

	static std::tuple<bool, float> LUA_NATIVE_SOCIALCLUB_SC_COMMUNITY_EVENT_GET_EXTRA_DATA_FLOAT_BY_ID(int p0, sol::stack_object p1, float p2)
	{
		std::tuple<bool, float> return_values;
		std::get<0>(return_values) = (bool)SOCIALCLUB::SC_COMMUNITY_EVENT_GET_EXTRA_DATA_FLOAT_BY_ID(p0, p1.is<const char*>() ? p1.as<const char*>() : nullptr, &p2);
		std::get<1>(return_values) = p2;

		return return_values;
	}

	static std::tuple<bool, char> LUA_NATIVE_SOCIALCLUB_SC_COMMUNITY_EVENT_GET_EXTRA_DATA_STRING_BY_ID(int p0, sol::stack_object p1, char p2)
	{
		std::tuple<bool, char> return_values;
		std::get<0>(return_values) = (bool)SOCIALCLUB::SC_COMMUNITY_EVENT_GET_EXTRA_DATA_STRING_BY_ID(p0, p1.is<const char*>() ? p1.as<const char*>() : nullptr, &p2);
		std::get<1>(return_values) = p2;

		return return_values;
	}

	static std::tuple<bool, char> LUA_NATIVE_SOCIALCLUB_SC_COMMUNITY_EVENT_GET_DISPLAY_NAME_BY_ID(int p0, char p1)
	{
		std::tuple<bool, char> return_values;
		std::get<0>(return_values) = (bool)SOCIALCLUB::SC_COMMUNITY_EVENT_GET_DISPLAY_NAME_BY_ID(p0, &p1);
		std::get<1>(return_values) = p1;

		return return_values;
	}

	static bool LUA_NATIVE_SOCIALCLUB_SC_TRANSITION_NEWS_SHOW(Any p0)
	{
		auto retval = (bool)SOCIALCLUB::SC_TRANSITION_NEWS_SHOW(p0);
		return retval;
	}

	static bool LUA_NATIVE_SOCIALCLUB_SC_TRANSITION_NEWS_SHOW_TIMED(Any p0, Any p1)
	{
		auto retval = (bool)SOCIALCLUB::SC_TRANSITION_NEWS_SHOW_TIMED(p0, p1);
		return retval;
	}

	static bool LUA_NATIVE_SOCIALCLUB_SC_TRANSITION_NEWS_SHOW_NEXT_ITEM()
	{
		auto retval = (bool)SOCIALCLUB::SC_TRANSITION_NEWS_SHOW_NEXT_ITEM();
		return retval;
	}

	static bool LUA_NATIVE_SOCIALCLUB_SC_TRANSITION_NEWS_HAS_EXTRA_DATA_TU()
	{
		auto retval = (bool)SOCIALCLUB::SC_TRANSITION_NEWS_HAS_EXTRA_DATA_TU();
		return retval;
	}

	static std::tuple<bool, int> LUA_NATIVE_SOCIALCLUB_SC_TRANSITION_NEWS_GET_EXTRA_DATA_INT_TU(sol::stack_object p0, int p1)
	{
		std::tuple<bool, int> return_values;
		std::get<0>(return_values) = (bool)SOCIALCLUB::SC_TRANSITION_NEWS_GET_EXTRA_DATA_INT_TU(p0.is<const char*>() ? p0.as<const char*>() : nullptr, &p1);
		std::get<1>(return_values) = p1;

		return return_values;
	}

	static void LUA_NATIVE_SOCIALCLUB_SC_TRANSITION_NEWS_END()
	{
		SOCIALCLUB::SC_TRANSITION_NEWS_END();
	}

	static bool LUA_NATIVE_SOCIALCLUB_SC_PAUSE_NEWS_INIT_STARTER_PACK(Any p0)
	{
		auto retval = (bool)SOCIALCLUB::SC_PAUSE_NEWS_INIT_STARTER_PACK(p0);
		return retval;
	}

	static bool LUA_NATIVE_SOCIALCLUB_SC_PAUSE_NEWS_GET_PENDING_STORY(Any p0)
	{
		auto retval = (bool)SOCIALCLUB::SC_PAUSE_NEWS_GET_PENDING_STORY(p0);
		return retval;
	}

	static void LUA_NATIVE_SOCIALCLUB_SC_PAUSE_NEWS_SHUTDOWN()
	{
		SOCIALCLUB::SC_PAUSE_NEWS_SHUTDOWN();
	}

	static const char* LUA_NATIVE_SOCIALCLUB_SC_ACCOUNT_INFO_GET_NICKNAME()
	{
		auto retval = SOCIALCLUB::SC_ACCOUNT_INFO_GET_NICKNAME();
		return retval;
	}

	static std::tuple<bool, int> LUA_NATIVE_SOCIALCLUB_SC_ACHIEVEMENT_INFO_STATUS(int p0)
	{
		std::tuple<bool, int> return_values;
		std::get<0>(return_values) = (bool)SOCIALCLUB::SC_ACHIEVEMENT_INFO_STATUS(&p0);
		std::get<1>(return_values) = p0;

		return return_values;
	}

	static bool LUA_NATIVE_SOCIALCLUB_SC_HAS_ACHIEVEMENT_BEEN_PASSED(int achievementId)
	{
		auto retval = (bool)SOCIALCLUB::SC_HAS_ACHIEVEMENT_BEEN_PASSED(achievementId);
		return retval;
	}

	void init_native_binding_SOCIALCLUB(sol::state& L)
	{
		auto SOCIALCLUB = L["SOCIALCLUB"].get_or_create<sol::table>();
		SOCIALCLUB.set_function("SC_INBOX_GET_TOTAL_NUM_MESSAGES", LUA_NATIVE_SOCIALCLUB_SC_INBOX_GET_TOTAL_NUM_MESSAGES);
		SOCIALCLUB.set_function("SC_INBOX_GET_MESSAGE_TYPE_AT_INDEX", LUA_NATIVE_SOCIALCLUB_SC_INBOX_GET_MESSAGE_TYPE_AT_INDEX);
		SOCIALCLUB.set_function("SC_INBOX_GET_MESSAGE_IS_READ_AT_INDEX", LUA_NATIVE_SOCIALCLUB_SC_INBOX_GET_MESSAGE_IS_READ_AT_INDEX);
		SOCIALCLUB.set_function("SC_INBOX_SET_MESSAGE_AS_READ_AT_INDEX", LUA_NATIVE_SOCIALCLUB_SC_INBOX_SET_MESSAGE_AS_READ_AT_INDEX);
		SOCIALCLUB.set_function("SC_INBOX_MESSAGE_GET_DATA_INT", LUA_NATIVE_SOCIALCLUB_SC_INBOX_MESSAGE_GET_DATA_INT);
		SOCIALCLUB.set_function("SC_INBOX_MESSAGE_GET_DATA_BOOL", LUA_NATIVE_SOCIALCLUB_SC_INBOX_MESSAGE_GET_DATA_BOOL);
		SOCIALCLUB.set_function("SC_INBOX_MESSAGE_GET_DATA_STRING", LUA_NATIVE_SOCIALCLUB_SC_INBOX_MESSAGE_GET_DATA_STRING);
		SOCIALCLUB.set_function("SC_INBOX_MESSAGE_DO_APPLY", LUA_NATIVE_SOCIALCLUB_SC_INBOX_MESSAGE_DO_APPLY);
		SOCIALCLUB.set_function("SC_INBOX_MESSAGE_GET_RAW_TYPE_AT_INDEX", LUA_NATIVE_SOCIALCLUB_SC_INBOX_MESSAGE_GET_RAW_TYPE_AT_INDEX);
		SOCIALCLUB.set_function("SC_INBOX_MESSAGE_PUSH_GAMER_T0_RECIP_LIST", LUA_NATIVE_SOCIALCLUB_SC_INBOX_MESSAGE_PUSH_GAMER_T0_RECIP_LIST);
		SOCIALCLUB.set_function("SC_INBOX_SEND_UGCSTATUPDATE_TO_RECIP_LIST", LUA_NATIVE_SOCIALCLUB_SC_INBOX_SEND_UGCSTATUPDATE_TO_RECIP_LIST);
		SOCIALCLUB.set_function("SC_INBOX_MESSAGE_GET_UGCDATA", LUA_NATIVE_SOCIALCLUB_SC_INBOX_MESSAGE_GET_UGCDATA);
		SOCIALCLUB.set_function("SC_INBOX_GET_BOUNTY_DATA_AT_INDEX", LUA_NATIVE_SOCIALCLUB_SC_INBOX_GET_BOUNTY_DATA_AT_INDEX);
		SOCIALCLUB.set_function("SC_EMAIL_RETRIEVE_EMAILS", LUA_NATIVE_SOCIALCLUB_SC_EMAIL_RETRIEVE_EMAILS);
		SOCIALCLUB.set_function("SC_EMAIL_GET_RETRIEVAL_STATUS", LUA_NATIVE_SOCIALCLUB_SC_EMAIL_GET_RETRIEVAL_STATUS);
		SOCIALCLUB.set_function("SC_EMAIL_GET_NUM_RETRIEVED_EMAILS", LUA_NATIVE_SOCIALCLUB_SC_EMAIL_GET_NUM_RETRIEVED_EMAILS);
		SOCIALCLUB.set_function("SC_EMAIL_GET_EMAIL_AT_INDEX", LUA_NATIVE_SOCIALCLUB_SC_EMAIL_GET_EMAIL_AT_INDEX);
		SOCIALCLUB.set_function("SC_EMAIL_DELETE_EMAILS", LUA_NATIVE_SOCIALCLUB_SC_EMAIL_DELETE_EMAILS);
		SOCIALCLUB.set_function("SC_EMAIL_MESSAGE_PUSH_GAMER_TO_RECIP_LIST", LUA_NATIVE_SOCIALCLUB_SC_EMAIL_MESSAGE_PUSH_GAMER_TO_RECIP_LIST);
		SOCIALCLUB.set_function("SC_EMAIL_MESSAGE_CLEAR_RECIP_LIST", LUA_NATIVE_SOCIALCLUB_SC_EMAIL_MESSAGE_CLEAR_RECIP_LIST);
		SOCIALCLUB.set_function("SC_EMAIL_SEND_EMAIL", LUA_NATIVE_SOCIALCLUB_SC_EMAIL_SEND_EMAIL);
		SOCIALCLUB.set_function("SC_EMAIL_SET_CURRENT_EMAIL_TAG", LUA_NATIVE_SOCIALCLUB_SC_EMAIL_SET_CURRENT_EMAIL_TAG);
		SOCIALCLUB.set_function("SC_CACHE_NEW_ROCKSTAR_MSGS", LUA_NATIVE_SOCIALCLUB_SC_CACHE_NEW_ROCKSTAR_MSGS);
		SOCIALCLUB.set_function("SC_HAS_NEW_ROCKSTAR_MSG", LUA_NATIVE_SOCIALCLUB_SC_HAS_NEW_ROCKSTAR_MSG);
		SOCIALCLUB.set_function("SC_GET_NEW_ROCKSTAR_MSG", LUA_NATIVE_SOCIALCLUB_SC_GET_NEW_ROCKSTAR_MSG);
		SOCIALCLUB.set_function("SC_PRESENCE_ATTR_SET_INT", LUA_NATIVE_SOCIALCLUB_SC_PRESENCE_ATTR_SET_INT);
		SOCIALCLUB.set_function("SC_PRESENCE_ATTR_SET_FLOAT", LUA_NATIVE_SOCIALCLUB_SC_PRESENCE_ATTR_SET_FLOAT);
		SOCIALCLUB.set_function("SC_PRESENCE_ATTR_SET_STRING", LUA_NATIVE_SOCIALCLUB_SC_PRESENCE_ATTR_SET_STRING);
		SOCIALCLUB.set_function("SC_PRESENCE_SET_ACTIVITY_RATING", LUA_NATIVE_SOCIALCLUB_SC_PRESENCE_SET_ACTIVITY_RATING);
		SOCIALCLUB.set_function("SC_GAMERDATA_GET_INT", LUA_NATIVE_SOCIALCLUB_SC_GAMERDATA_GET_INT);
		SOCIALCLUB.set_function("SC_GAMERDATA_GET_FLOAT", LUA_NATIVE_SOCIALCLUB_SC_GAMERDATA_GET_FLOAT);
		SOCIALCLUB.set_function("SC_GAMERDATA_GET_BOOL", LUA_NATIVE_SOCIALCLUB_SC_GAMERDATA_GET_BOOL);
		SOCIALCLUB.set_function("SC_GAMERDATA_GET_STRING", LUA_NATIVE_SOCIALCLUB_SC_GAMERDATA_GET_STRING);
		SOCIALCLUB.set_function("SC_GAMERDATA_GET_ACTIVE_XP_BONUS", LUA_NATIVE_SOCIALCLUB_SC_GAMERDATA_GET_ACTIVE_XP_BONUS);
		SOCIALCLUB.set_function("SC_PROFANITY_CHECK_STRING", LUA_NATIVE_SOCIALCLUB_SC_PROFANITY_CHECK_STRING);
		SOCIALCLUB.set_function("SC_PROFANITY_CHECK_STRING_UGC", LUA_NATIVE_SOCIALCLUB_SC_PROFANITY_CHECK_STRING_UGC);
		SOCIALCLUB.set_function("SC_PROFANITY_GET_CHECK_IS_VALID", LUA_NATIVE_SOCIALCLUB_SC_PROFANITY_GET_CHECK_IS_VALID);
		SOCIALCLUB.set_function("SC_PROFANITY_GET_CHECK_IS_PENDING", LUA_NATIVE_SOCIALCLUB_SC_PROFANITY_GET_CHECK_IS_PENDING);
		SOCIALCLUB.set_function("SC_PROFANITY_GET_STRING_PASSED", LUA_NATIVE_SOCIALCLUB_SC_PROFANITY_GET_STRING_PASSED);
		SOCIALCLUB.set_function("SC_PROFANITY_GET_STRING_STATUS", LUA_NATIVE_SOCIALCLUB_SC_PROFANITY_GET_STRING_STATUS);
		SOCIALCLUB.set_function("SC_LICENSEPLATE_CHECK_STRING", LUA_NATIVE_SOCIALCLUB_SC_LICENSEPLATE_CHECK_STRING);
		SOCIALCLUB.set_function("SC_LICENSEPLATE_GET_CHECK_IS_VALID", LUA_NATIVE_SOCIALCLUB_SC_LICENSEPLATE_GET_CHECK_IS_VALID);
		SOCIALCLUB.set_function("SC_LICENSEPLATE_GET_CHECK_IS_PENDING", LUA_NATIVE_SOCIALCLUB_SC_LICENSEPLATE_GET_CHECK_IS_PENDING);
		SOCIALCLUB.set_function("SC_LICENSEPLATE_GET_COUNT", LUA_NATIVE_SOCIALCLUB_SC_LICENSEPLATE_GET_COUNT);
		SOCIALCLUB.set_function("SC_LICENSEPLATE_GET_PLATE", LUA_NATIVE_SOCIALCLUB_SC_LICENSEPLATE_GET_PLATE);
		SOCIALCLUB.set_function("SC_LICENSEPLATE_GET_PLATE_DATA", LUA_NATIVE_SOCIALCLUB_SC_LICENSEPLATE_GET_PLATE_DATA);
		SOCIALCLUB.set_function("SC_LICENSEPLATE_SET_PLATE_DATA", LUA_NATIVE_SOCIALCLUB_SC_LICENSEPLATE_SET_PLATE_DATA);
		SOCIALCLUB.set_function("SC_LICENSEPLATE_ADD", LUA_NATIVE_SOCIALCLUB_SC_LICENSEPLATE_ADD);
		SOCIALCLUB.set_function("SC_LICENSEPLATE_GET_ADD_IS_PENDING", LUA_NATIVE_SOCIALCLUB_SC_LICENSEPLATE_GET_ADD_IS_PENDING);
		SOCIALCLUB.set_function("SC_LICENSEPLATE_GET_ADD_STATUS", LUA_NATIVE_SOCIALCLUB_SC_LICENSEPLATE_GET_ADD_STATUS);
		SOCIALCLUB.set_function("SC_LICENSEPLATE_ISVALID", LUA_NATIVE_SOCIALCLUB_SC_LICENSEPLATE_ISVALID);
		SOCIALCLUB.set_function("SC_LICENSEPLATE_GET_ISVALID_IS_PENDING", LUA_NATIVE_SOCIALCLUB_SC_LICENSEPLATE_GET_ISVALID_IS_PENDING);
		SOCIALCLUB.set_function("SC_LICENSEPLATE_GET_ISVALID_STATUS", LUA_NATIVE_SOCIALCLUB_SC_LICENSEPLATE_GET_ISVALID_STATUS);
		SOCIALCLUB.set_function("SC_COMMUNITY_EVENT_IS_ACTIVE", LUA_NATIVE_SOCIALCLUB_SC_COMMUNITY_EVENT_IS_ACTIVE);
		SOCIALCLUB.set_function("SC_COMMUNITY_EVENT_GET_EVENT_ID", LUA_NATIVE_SOCIALCLUB_SC_COMMUNITY_EVENT_GET_EVENT_ID);
		SOCIALCLUB.set_function("SC_COMMUNITY_EVENT_GET_EXTRA_DATA_INT", LUA_NATIVE_SOCIALCLUB_SC_COMMUNITY_EVENT_GET_EXTRA_DATA_INT);
		SOCIALCLUB.set_function("SC_COMMUNITY_EVENT_GET_EXTRA_DATA_FLOAT", LUA_NATIVE_SOCIALCLUB_SC_COMMUNITY_EVENT_GET_EXTRA_DATA_FLOAT);
		SOCIALCLUB.set_function("SC_COMMUNITY_EVENT_GET_EXTRA_DATA_STRING", LUA_NATIVE_SOCIALCLUB_SC_COMMUNITY_EVENT_GET_EXTRA_DATA_STRING);
		SOCIALCLUB.set_function("SC_COMMUNITY_EVENT_GET_DISPLAY_NAME", LUA_NATIVE_SOCIALCLUB_SC_COMMUNITY_EVENT_GET_DISPLAY_NAME);
		SOCIALCLUB.set_function("SC_COMMUNITY_EVENT_IS_ACTIVE_FOR_TYPE", LUA_NATIVE_SOCIALCLUB_SC_COMMUNITY_EVENT_IS_ACTIVE_FOR_TYPE);
		SOCIALCLUB.set_function("SC_COMMUNITY_EVENT_GET_EVENT_ID_FOR_TYPE", LUA_NATIVE_SOCIALCLUB_SC_COMMUNITY_EVENT_GET_EVENT_ID_FOR_TYPE);
		SOCIALCLUB.set_function("SC_COMMUNITY_EVENT_GET_EXTRA_DATA_INT_FOR_TYPE", LUA_NATIVE_SOCIALCLUB_SC_COMMUNITY_EVENT_GET_EXTRA_DATA_INT_FOR_TYPE);
		SOCIALCLUB.set_function("SC_COMMUNITY_EVENT_GET_EXTRA_DATA_FLOAT_FOR_TYPE", LUA_NATIVE_SOCIALCLUB_SC_COMMUNITY_EVENT_GET_EXTRA_DATA_FLOAT_FOR_TYPE);
		SOCIALCLUB.set_function("SC_COMMUNITY_EVENT_GET_EXTRA_DATA_STRING_FOR_TYPE", LUA_NATIVE_SOCIALCLUB_SC_COMMUNITY_EVENT_GET_EXTRA_DATA_STRING_FOR_TYPE);
		SOCIALCLUB.set_function("SC_COMMUNITY_EVENT_GET_DISPLAY_NAME_FOR_TYPE", LUA_NATIVE_SOCIALCLUB_SC_COMMUNITY_EVENT_GET_DISPLAY_NAME_FOR_TYPE);
		SOCIALCLUB.set_function("SC_COMMUNITY_EVENT_IS_ACTIVE_BY_ID", LUA_NATIVE_SOCIALCLUB_SC_COMMUNITY_EVENT_IS_ACTIVE_BY_ID);
		SOCIALCLUB.set_function("SC_COMMUNITY_EVENT_GET_EXTRA_DATA_INT_BY_ID", LUA_NATIVE_SOCIALCLUB_SC_COMMUNITY_EVENT_GET_EXTRA_DATA_INT_BY_ID);
		SOCIALCLUB.set_function("SC_COMMUNITY_EVENT_GET_EXTRA_DATA_FLOAT_BY_ID", LUA_NATIVE_SOCIALCLUB_SC_COMMUNITY_EVENT_GET_EXTRA_DATA_FLOAT_BY_ID);
		SOCIALCLUB.set_function("SC_COMMUNITY_EVENT_GET_EXTRA_DATA_STRING_BY_ID", LUA_NATIVE_SOCIALCLUB_SC_COMMUNITY_EVENT_GET_EXTRA_DATA_STRING_BY_ID);
		SOCIALCLUB.set_function("SC_COMMUNITY_EVENT_GET_DISPLAY_NAME_BY_ID", LUA_NATIVE_SOCIALCLUB_SC_COMMUNITY_EVENT_GET_DISPLAY_NAME_BY_ID);
		SOCIALCLUB.set_function("SC_TRANSITION_NEWS_SHOW", LUA_NATIVE_SOCIALCLUB_SC_TRANSITION_NEWS_SHOW);
		SOCIALCLUB.set_function("SC_TRANSITION_NEWS_SHOW_TIMED", LUA_NATIVE_SOCIALCLUB_SC_TRANSITION_NEWS_SHOW_TIMED);
		SOCIALCLUB.set_function("SC_TRANSITION_NEWS_SHOW_NEXT_ITEM", LUA_NATIVE_SOCIALCLUB_SC_TRANSITION_NEWS_SHOW_NEXT_ITEM);
		SOCIALCLUB.set_function("SC_TRANSITION_NEWS_HAS_EXTRA_DATA_TU", LUA_NATIVE_SOCIALCLUB_SC_TRANSITION_NEWS_HAS_EXTRA_DATA_TU);
		SOCIALCLUB.set_function("SC_TRANSITION_NEWS_GET_EXTRA_DATA_INT_TU", LUA_NATIVE_SOCIALCLUB_SC_TRANSITION_NEWS_GET_EXTRA_DATA_INT_TU);
		SOCIALCLUB.set_function("SC_TRANSITION_NEWS_END", LUA_NATIVE_SOCIALCLUB_SC_TRANSITION_NEWS_END);
		SOCIALCLUB.set_function("SC_PAUSE_NEWS_INIT_STARTER_PACK", LUA_NATIVE_SOCIALCLUB_SC_PAUSE_NEWS_INIT_STARTER_PACK);
		SOCIALCLUB.set_function("SC_PAUSE_NEWS_GET_PENDING_STORY", LUA_NATIVE_SOCIALCLUB_SC_PAUSE_NEWS_GET_PENDING_STORY);
		SOCIALCLUB.set_function("SC_PAUSE_NEWS_SHUTDOWN", LUA_NATIVE_SOCIALCLUB_SC_PAUSE_NEWS_SHUTDOWN);
		SOCIALCLUB.set_function("SC_ACCOUNT_INFO_GET_NICKNAME", LUA_NATIVE_SOCIALCLUB_SC_ACCOUNT_INFO_GET_NICKNAME);
		SOCIALCLUB.set_function("SC_ACHIEVEMENT_INFO_STATUS", LUA_NATIVE_SOCIALCLUB_SC_ACHIEVEMENT_INFO_STATUS);
		SOCIALCLUB.set_function("SC_HAS_ACHIEVEMENT_BEEN_PASSED", LUA_NATIVE_SOCIALCLUB_SC_HAS_ACHIEVEMENT_BEEN_PASSED);
	}
}
