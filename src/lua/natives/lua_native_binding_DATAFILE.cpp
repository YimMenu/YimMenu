#include "lua_native_binding.hpp"
#include "natives.hpp"

namespace lua::native
{
	static void LUA_NATIVE_DATAFILE_DATAFILE_WATCH_REQUEST_ID(int requestId)
	{
		DATAFILE::DATAFILE_WATCH_REQUEST_ID(requestId);
	}

	static void LUA_NATIVE_DATAFILE_DATAFILE_CLEAR_WATCH_LIST()
	{
		DATAFILE::DATAFILE_CLEAR_WATCH_LIST();
	}

	static bool LUA_NATIVE_DATAFILE_DATAFILE_IS_VALID_REQUEST_ID(int index)
	{
		auto retval = (bool)DATAFILE::DATAFILE_IS_VALID_REQUEST_ID(index);
		return retval;
	}

	static bool LUA_NATIVE_DATAFILE_DATAFILE_HAS_LOADED_FILE_DATA(int requestId)
	{
		auto retval = (bool)DATAFILE::DATAFILE_HAS_LOADED_FILE_DATA(requestId);
		return retval;
	}

	static bool LUA_NATIVE_DATAFILE_DATAFILE_HAS_VALID_FILE_DATA(int requestId)
	{
		auto retval = (bool)DATAFILE::DATAFILE_HAS_VALID_FILE_DATA(requestId);
		return retval;
	}

	static bool LUA_NATIVE_DATAFILE_DATAFILE_SELECT_ACTIVE_FILE(int requestId, Any p1)
	{
		auto retval = (bool)DATAFILE::DATAFILE_SELECT_ACTIVE_FILE(requestId, p1);
		return retval;
	}

	static bool LUA_NATIVE_DATAFILE_DATAFILE_DELETE_REQUESTED_FILE(int requestId)
	{
		auto retval = (bool)DATAFILE::DATAFILE_DELETE_REQUESTED_FILE(requestId);
		return retval;
	}

	static std::tuple<bool, Any> LUA_NATIVE_DATAFILE_UGC_CREATE_CONTENT(Any data, int dataCount, sol::stack_object contentName, sol::stack_object description, sol::stack_object tagsCsv, sol::stack_object contentTypeName, bool publish, Any p7)
	{
		std::tuple<bool, Any> return_values;
		std::get<0>(return_values) = (bool)DATAFILE::UGC_CREATE_CONTENT(&data, dataCount, contentName.is<const char*>() ? contentName.as<const char*>() : nullptr, description.is<const char*>() ? description.as<const char*>() : nullptr, tagsCsv.is<const char*>() ? tagsCsv.as<const char*>() : nullptr, contentTypeName.is<const char*>() ? contentTypeName.as<const char*>() : nullptr, publish, p7);
		std::get<1>(return_values) = data;

		return return_values;
	}

	static bool LUA_NATIVE_DATAFILE_UGC_CREATE_MISSION(sol::stack_object contentName, sol::stack_object description, sol::stack_object tagsCsv, sol::stack_object contentTypeName, bool publish, Any p5)
	{
		auto retval = (bool)DATAFILE::UGC_CREATE_MISSION(contentName.is<const char*>() ? contentName.as<const char*>() : nullptr, description.is<const char*>() ? description.as<const char*>() : nullptr, tagsCsv.is<const char*>() ? tagsCsv.as<const char*>() : nullptr, contentTypeName.is<const char*>() ? contentTypeName.as<const char*>() : nullptr, publish, p5);
		return retval;
	}

	static std::tuple<bool, Any> LUA_NATIVE_DATAFILE_UGC_UPDATE_CONTENT(sol::stack_object contentId, Any data, int dataCount, sol::stack_object contentName, sol::stack_object description, sol::stack_object tagsCsv, sol::stack_object contentTypeName, Any p7)
	{
		std::tuple<bool, Any> return_values;
		std::get<0>(return_values) = (bool)DATAFILE::UGC_UPDATE_CONTENT(contentId.is<const char*>() ? contentId.as<const char*>() : nullptr, &data, dataCount, contentName.is<const char*>() ? contentName.as<const char*>() : nullptr, description.is<const char*>() ? description.as<const char*>() : nullptr, tagsCsv.is<const char*>() ? tagsCsv.as<const char*>() : nullptr, contentTypeName.is<const char*>() ? contentTypeName.as<const char*>() : nullptr, p7);
		std::get<1>(return_values) = data;

		return return_values;
	}

	static bool LUA_NATIVE_DATAFILE_UGC_UPDATE_MISSION(sol::stack_object contentId, sol::stack_object contentName, sol::stack_object description, sol::stack_object tagsCsv, sol::stack_object contentTypeName, Any p5)
	{
		auto retval = (bool)DATAFILE::UGC_UPDATE_MISSION(contentId.is<const char*>() ? contentId.as<const char*>() : nullptr, contentName.is<const char*>() ? contentName.as<const char*>() : nullptr, description.is<const char*>() ? description.as<const char*>() : nullptr, tagsCsv.is<const char*>() ? tagsCsv.as<const char*>() : nullptr, contentTypeName.is<const char*>() ? contentTypeName.as<const char*>() : nullptr, p5);
		return retval;
	}

	static bool LUA_NATIVE_DATAFILE_UGC_SET_PLAYER_DATA(sol::stack_object contentId, float rating, sol::stack_object contentTypeName, Any p3)
	{
		auto retval = (bool)DATAFILE::UGC_SET_PLAYER_DATA(contentId.is<const char*>() ? contentId.as<const char*>() : nullptr, rating, contentTypeName.is<const char*>() ? contentTypeName.as<const char*>() : nullptr, p3);
		return retval;
	}

	static bool LUA_NATIVE_DATAFILE_DATAFILE_SELECT_UGC_DATA(int p0, Any p1)
	{
		auto retval = (bool)DATAFILE::DATAFILE_SELECT_UGC_DATA(p0, p1);
		return retval;
	}

	static bool LUA_NATIVE_DATAFILE_DATAFILE_SELECT_UGC_STATS(int p0, bool p1, Any p2)
	{
		auto retval = (bool)DATAFILE::DATAFILE_SELECT_UGC_STATS(p0, p1, p2);
		return retval;
	}

	static bool LUA_NATIVE_DATAFILE_DATAFILE_SELECT_UGC_PLAYER_DATA(int p0, Any p1)
	{
		auto retval = (bool)DATAFILE::DATAFILE_SELECT_UGC_PLAYER_DATA(p0, p1);
		return retval;
	}

	static bool LUA_NATIVE_DATAFILE_DATAFILE_SELECT_CREATOR_STATS(int p0, Any p1)
	{
		auto retval = (bool)DATAFILE::DATAFILE_SELECT_CREATOR_STATS(p0, p1);
		return retval;
	}

	static bool LUA_NATIVE_DATAFILE_DATAFILE_LOAD_OFFLINE_UGC(sol::stack_object filename, Any p1)
	{
		auto retval = (bool)DATAFILE::DATAFILE_LOAD_OFFLINE_UGC(filename.is<const char*>() ? filename.as<const char*>() : nullptr, p1);
		return retval;
	}

	static void LUA_NATIVE_DATAFILE_DATAFILE_CREATE(int p0)
	{
		DATAFILE::DATAFILE_CREATE(p0);
	}

	static void LUA_NATIVE_DATAFILE_DATAFILE_DELETE(int p0)
	{
		DATAFILE::DATAFILE_DELETE(p0);
	}

	static void LUA_NATIVE_DATAFILE_DATAFILE_STORE_MISSION_HEADER(int p0)
	{
		DATAFILE::DATAFILE_STORE_MISSION_HEADER(p0);
	}

	static void LUA_NATIVE_DATAFILE_DATAFILE_FLUSH_MISSION_HEADER()
	{
		DATAFILE::DATAFILE_FLUSH_MISSION_HEADER();
	}

	static Any* LUA_NATIVE_DATAFILE_DATAFILE_GET_FILE_DICT(int p0)
	{
		auto retval = DATAFILE::DATAFILE_GET_FILE_DICT(p0);
		return retval;
	}

	static bool LUA_NATIVE_DATAFILE_DATAFILE_START_SAVE_TO_CLOUD(sol::stack_object filename, Any p1)
	{
		auto retval = (bool)DATAFILE::DATAFILE_START_SAVE_TO_CLOUD(filename.is<const char*>() ? filename.as<const char*>() : nullptr, p1);
		return retval;
	}

	static std::tuple<bool, bool> LUA_NATIVE_DATAFILE_DATAFILE_UPDATE_SAVE_TO_CLOUD(bool p0)
	{
		std::tuple<bool, bool> return_values;
		std::get<0>(return_values) = (bool)DATAFILE::DATAFILE_UPDATE_SAVE_TO_CLOUD((BOOL*)&p0);
		std::get<1>(return_values) = p0;

		return return_values;
	}

	static bool LUA_NATIVE_DATAFILE_DATAFILE_IS_SAVE_PENDING()
	{
		auto retval = (bool)DATAFILE::DATAFILE_IS_SAVE_PENDING();
		return retval;
	}

	static bool LUA_NATIVE_DATAFILE_DATAFILE_LOAD_OFFLINE_UGC_FOR_ADDITIONAL_DATA_FILE(Any p0, Any p1)
	{
		auto retval = (bool)DATAFILE::DATAFILE_LOAD_OFFLINE_UGC_FOR_ADDITIONAL_DATA_FILE(p0, p1);
		return retval;
	}

	static void LUA_NATIVE_DATAFILE_DATAFILE_DELETE_FOR_ADDITIONAL_DATA_FILE(Any p0)
	{
		DATAFILE::DATAFILE_DELETE_FOR_ADDITIONAL_DATA_FILE(p0);
	}

	static Any* LUA_NATIVE_DATAFILE_DATAFILE_GET_FILE_DICT_FOR_ADDITIONAL_DATA_FILE(Any p0)
	{
		auto retval = DATAFILE::DATAFILE_GET_FILE_DICT_FOR_ADDITIONAL_DATA_FILE(p0);
		return retval;
	}

	static Any LUA_NATIVE_DATAFILE_DATADICT_SET_BOOL(Any objectData, sol::stack_object key, bool value)
	{
		DATAFILE::DATADICT_SET_BOOL(&objectData, key.is<const char*>() ? key.as<const char*>() : nullptr, value);
		return objectData;
	}

	static Any LUA_NATIVE_DATAFILE_DATADICT_SET_INT(Any objectData, sol::stack_object key, int value)
	{
		DATAFILE::DATADICT_SET_INT(&objectData, key.is<const char*>() ? key.as<const char*>() : nullptr, value);
		return objectData;
	}

	static Any LUA_NATIVE_DATAFILE_DATADICT_SET_FLOAT(Any objectData, sol::stack_object key, float value)
	{
		DATAFILE::DATADICT_SET_FLOAT(&objectData, key.is<const char*>() ? key.as<const char*>() : nullptr, value);
		return objectData;
	}

	static Any LUA_NATIVE_DATAFILE_DATADICT_SET_STRING(Any objectData, sol::stack_object key, sol::stack_object value)
	{
		DATAFILE::DATADICT_SET_STRING(&objectData, key.is<const char*>() ? key.as<const char*>() : nullptr, value.is<const char*>() ? value.as<const char*>() : nullptr);
		return objectData;
	}

	static Any LUA_NATIVE_DATAFILE_DATADICT_SET_VECTOR(Any objectData, sol::stack_object key, float valueX, float valueY, float valueZ)
	{
		DATAFILE::DATADICT_SET_VECTOR(&objectData, key.is<const char*>() ? key.as<const char*>() : nullptr, valueX, valueY, valueZ);
		return objectData;
	}

	static std::tuple<Any*, Any> LUA_NATIVE_DATAFILE_DATADICT_CREATE_DICT(Any objectData, sol::stack_object key)
	{
		std::tuple<Any*, Any> return_values;
		std::get<0>(return_values) = DATAFILE::DATADICT_CREATE_DICT(&objectData, key.is<const char*>() ? key.as<const char*>() : nullptr);
		std::get<1>(return_values) = objectData;

		return return_values;
	}

	static std::tuple<Any*, Any> LUA_NATIVE_DATAFILE_DATADICT_CREATE_ARRAY(Any objectData, sol::stack_object key)
	{
		std::tuple<Any*, Any> return_values;
		std::get<0>(return_values) = DATAFILE::DATADICT_CREATE_ARRAY(&objectData, key.is<const char*>() ? key.as<const char*>() : nullptr);
		std::get<1>(return_values) = objectData;

		return return_values;
	}

	static std::tuple<bool, Any> LUA_NATIVE_DATAFILE_DATADICT_GET_BOOL(Any objectData, sol::stack_object key)
	{
		std::tuple<bool, Any> return_values;
		std::get<0>(return_values) = (bool)DATAFILE::DATADICT_GET_BOOL(&objectData, key.is<const char*>() ? key.as<const char*>() : nullptr);
		std::get<1>(return_values) = objectData;

		return return_values;
	}

	static std::tuple<int, Any> LUA_NATIVE_DATAFILE_DATADICT_GET_INT(Any objectData, sol::stack_object key)
	{
		std::tuple<int, Any> return_values;
		std::get<0>(return_values) = DATAFILE::DATADICT_GET_INT(&objectData, key.is<const char*>() ? key.as<const char*>() : nullptr);
		std::get<1>(return_values) = objectData;

		return return_values;
	}

	static std::tuple<float, Any> LUA_NATIVE_DATAFILE_DATADICT_GET_FLOAT(Any objectData, sol::stack_object key)
	{
		std::tuple<float, Any> return_values;
		std::get<0>(return_values) = DATAFILE::DATADICT_GET_FLOAT(&objectData, key.is<const char*>() ? key.as<const char*>() : nullptr);
		std::get<1>(return_values) = objectData;

		return return_values;
	}

	static std::tuple<const char*, Any> LUA_NATIVE_DATAFILE_DATADICT_GET_STRING(Any objectData, sol::stack_object key)
	{
		std::tuple<const char*, Any> return_values;
		std::get<0>(return_values) = DATAFILE::DATADICT_GET_STRING(&objectData, key.is<const char*>() ? key.as<const char*>() : nullptr);
		std::get<1>(return_values) = objectData;

		return return_values;
	}

	static std::tuple<Vector3, Any> LUA_NATIVE_DATAFILE_DATADICT_GET_VECTOR(Any objectData, sol::stack_object key)
	{
		std::tuple<Vector3, Any> return_values;
		std::get<0>(return_values) = DATAFILE::DATADICT_GET_VECTOR(&objectData, key.is<const char*>() ? key.as<const char*>() : nullptr);
		std::get<1>(return_values) = objectData;

		return return_values;
	}

	static std::tuple<Any*, Any> LUA_NATIVE_DATAFILE_DATADICT_GET_DICT(Any objectData, sol::stack_object key)
	{
		std::tuple<Any*, Any> return_values;
		std::get<0>(return_values) = DATAFILE::DATADICT_GET_DICT(&objectData, key.is<const char*>() ? key.as<const char*>() : nullptr);
		std::get<1>(return_values) = objectData;

		return return_values;
	}

	static std::tuple<Any*, Any> LUA_NATIVE_DATAFILE_DATADICT_GET_ARRAY(Any objectData, sol::stack_object key)
	{
		std::tuple<Any*, Any> return_values;
		std::get<0>(return_values) = DATAFILE::DATADICT_GET_ARRAY(&objectData, key.is<const char*>() ? key.as<const char*>() : nullptr);
		std::get<1>(return_values) = objectData;

		return return_values;
	}

	static std::tuple<int, Any> LUA_NATIVE_DATAFILE_DATADICT_GET_TYPE(Any objectData, sol::stack_object key)
	{
		std::tuple<int, Any> return_values;
		std::get<0>(return_values) = DATAFILE::DATADICT_GET_TYPE(&objectData, key.is<const char*>() ? key.as<const char*>() : nullptr);
		std::get<1>(return_values) = objectData;

		return return_values;
	}

	static Any LUA_NATIVE_DATAFILE_DATAARRAY_ADD_BOOL(Any arrayData, bool value)
	{
		DATAFILE::DATAARRAY_ADD_BOOL(&arrayData, value);
		return arrayData;
	}

	static Any LUA_NATIVE_DATAFILE_DATAARRAY_ADD_INT(Any arrayData, int value)
	{
		DATAFILE::DATAARRAY_ADD_INT(&arrayData, value);
		return arrayData;
	}

	static Any LUA_NATIVE_DATAFILE_DATAARRAY_ADD_FLOAT(Any arrayData, float value)
	{
		DATAFILE::DATAARRAY_ADD_FLOAT(&arrayData, value);
		return arrayData;
	}

	static Any LUA_NATIVE_DATAFILE_DATAARRAY_ADD_STRING(Any arrayData, sol::stack_object value)
	{
		DATAFILE::DATAARRAY_ADD_STRING(&arrayData, value.is<const char*>() ? value.as<const char*>() : nullptr);
		return arrayData;
	}

	static Any LUA_NATIVE_DATAFILE_DATAARRAY_ADD_VECTOR(Any arrayData, float valueX, float valueY, float valueZ)
	{
		DATAFILE::DATAARRAY_ADD_VECTOR(&arrayData, valueX, valueY, valueZ);
		return arrayData;
	}

	static std::tuple<Any*, Any> LUA_NATIVE_DATAFILE_DATAARRAY_ADD_DICT(Any arrayData)
	{
		std::tuple<Any*, Any> return_values;
		std::get<0>(return_values) = DATAFILE::DATAARRAY_ADD_DICT(&arrayData);
		std::get<1>(return_values) = arrayData;

		return return_values;
	}

	static std::tuple<bool, Any> LUA_NATIVE_DATAFILE_DATAARRAY_GET_BOOL(Any arrayData, int arrayIndex)
	{
		std::tuple<bool, Any> return_values;
		std::get<0>(return_values) = (bool)DATAFILE::DATAARRAY_GET_BOOL(&arrayData, arrayIndex);
		std::get<1>(return_values) = arrayData;

		return return_values;
	}

	static std::tuple<int, Any> LUA_NATIVE_DATAFILE_DATAARRAY_GET_INT(Any arrayData, int arrayIndex)
	{
		std::tuple<int, Any> return_values;
		std::get<0>(return_values) = DATAFILE::DATAARRAY_GET_INT(&arrayData, arrayIndex);
		std::get<1>(return_values) = arrayData;

		return return_values;
	}

	static std::tuple<float, Any> LUA_NATIVE_DATAFILE_DATAARRAY_GET_FLOAT(Any arrayData, int arrayIndex)
	{
		std::tuple<float, Any> return_values;
		std::get<0>(return_values) = DATAFILE::DATAARRAY_GET_FLOAT(&arrayData, arrayIndex);
		std::get<1>(return_values) = arrayData;

		return return_values;
	}

	static std::tuple<const char*, Any> LUA_NATIVE_DATAFILE_DATAARRAY_GET_STRING(Any arrayData, int arrayIndex)
	{
		std::tuple<const char*, Any> return_values;
		std::get<0>(return_values) = DATAFILE::DATAARRAY_GET_STRING(&arrayData, arrayIndex);
		std::get<1>(return_values) = arrayData;

		return return_values;
	}

	static std::tuple<Vector3, Any> LUA_NATIVE_DATAFILE_DATAARRAY_GET_VECTOR(Any arrayData, int arrayIndex)
	{
		std::tuple<Vector3, Any> return_values;
		std::get<0>(return_values) = DATAFILE::DATAARRAY_GET_VECTOR(&arrayData, arrayIndex);
		std::get<1>(return_values) = arrayData;

		return return_values;
	}

	static std::tuple<Any*, Any> LUA_NATIVE_DATAFILE_DATAARRAY_GET_DICT(Any arrayData, int arrayIndex)
	{
		std::tuple<Any*, Any> return_values;
		std::get<0>(return_values) = DATAFILE::DATAARRAY_GET_DICT(&arrayData, arrayIndex);
		std::get<1>(return_values) = arrayData;

		return return_values;
	}

	static std::tuple<int, Any> LUA_NATIVE_DATAFILE_DATAARRAY_GET_COUNT(Any arrayData)
	{
		std::tuple<int, Any> return_values;
		std::get<0>(return_values) = DATAFILE::DATAARRAY_GET_COUNT(&arrayData);
		std::get<1>(return_values) = arrayData;

		return return_values;
	}

	static std::tuple<int, Any> LUA_NATIVE_DATAFILE_DATAARRAY_GET_TYPE(Any arrayData, int arrayIndex)
	{
		std::tuple<int, Any> return_values;
		std::get<0>(return_values) = DATAFILE::DATAARRAY_GET_TYPE(&arrayData, arrayIndex);
		std::get<1>(return_values) = arrayData;

		return return_values;
	}

	void init_native_binding_DATAFILE(sol::state& L)
	{
		auto DATAFILE = L["DATAFILE"].get_or_create<sol::table>();
		DATAFILE.set_function("DATAFILE_WATCH_REQUEST_ID", LUA_NATIVE_DATAFILE_DATAFILE_WATCH_REQUEST_ID);
		DATAFILE.set_function("DATAFILE_CLEAR_WATCH_LIST", LUA_NATIVE_DATAFILE_DATAFILE_CLEAR_WATCH_LIST);
		DATAFILE.set_function("DATAFILE_IS_VALID_REQUEST_ID", LUA_NATIVE_DATAFILE_DATAFILE_IS_VALID_REQUEST_ID);
		DATAFILE.set_function("DATAFILE_HAS_LOADED_FILE_DATA", LUA_NATIVE_DATAFILE_DATAFILE_HAS_LOADED_FILE_DATA);
		DATAFILE.set_function("DATAFILE_HAS_VALID_FILE_DATA", LUA_NATIVE_DATAFILE_DATAFILE_HAS_VALID_FILE_DATA);
		DATAFILE.set_function("DATAFILE_SELECT_ACTIVE_FILE", LUA_NATIVE_DATAFILE_DATAFILE_SELECT_ACTIVE_FILE);
		DATAFILE.set_function("DATAFILE_DELETE_REQUESTED_FILE", LUA_NATIVE_DATAFILE_DATAFILE_DELETE_REQUESTED_FILE);
		DATAFILE.set_function("UGC_CREATE_CONTENT", LUA_NATIVE_DATAFILE_UGC_CREATE_CONTENT);
		DATAFILE.set_function("UGC_CREATE_MISSION", LUA_NATIVE_DATAFILE_UGC_CREATE_MISSION);
		DATAFILE.set_function("UGC_UPDATE_CONTENT", LUA_NATIVE_DATAFILE_UGC_UPDATE_CONTENT);
		DATAFILE.set_function("UGC_UPDATE_MISSION", LUA_NATIVE_DATAFILE_UGC_UPDATE_MISSION);
		DATAFILE.set_function("UGC_SET_PLAYER_DATA", LUA_NATIVE_DATAFILE_UGC_SET_PLAYER_DATA);
		DATAFILE.set_function("DATAFILE_SELECT_UGC_DATA", LUA_NATIVE_DATAFILE_DATAFILE_SELECT_UGC_DATA);
		DATAFILE.set_function("DATAFILE_SELECT_UGC_STATS", LUA_NATIVE_DATAFILE_DATAFILE_SELECT_UGC_STATS);
		DATAFILE.set_function("DATAFILE_SELECT_UGC_PLAYER_DATA", LUA_NATIVE_DATAFILE_DATAFILE_SELECT_UGC_PLAYER_DATA);
		DATAFILE.set_function("DATAFILE_SELECT_CREATOR_STATS", LUA_NATIVE_DATAFILE_DATAFILE_SELECT_CREATOR_STATS);
		DATAFILE.set_function("DATAFILE_LOAD_OFFLINE_UGC", LUA_NATIVE_DATAFILE_DATAFILE_LOAD_OFFLINE_UGC);
		DATAFILE.set_function("DATAFILE_CREATE", LUA_NATIVE_DATAFILE_DATAFILE_CREATE);
		DATAFILE.set_function("DATAFILE_DELETE", LUA_NATIVE_DATAFILE_DATAFILE_DELETE);
		DATAFILE.set_function("DATAFILE_STORE_MISSION_HEADER", LUA_NATIVE_DATAFILE_DATAFILE_STORE_MISSION_HEADER);
		DATAFILE.set_function("DATAFILE_FLUSH_MISSION_HEADER", LUA_NATIVE_DATAFILE_DATAFILE_FLUSH_MISSION_HEADER);
		DATAFILE.set_function("DATAFILE_GET_FILE_DICT", LUA_NATIVE_DATAFILE_DATAFILE_GET_FILE_DICT);
		DATAFILE.set_function("DATAFILE_START_SAVE_TO_CLOUD", LUA_NATIVE_DATAFILE_DATAFILE_START_SAVE_TO_CLOUD);
		DATAFILE.set_function("DATAFILE_UPDATE_SAVE_TO_CLOUD", LUA_NATIVE_DATAFILE_DATAFILE_UPDATE_SAVE_TO_CLOUD);
		DATAFILE.set_function("DATAFILE_IS_SAVE_PENDING", LUA_NATIVE_DATAFILE_DATAFILE_IS_SAVE_PENDING);
		DATAFILE.set_function("DATAFILE_LOAD_OFFLINE_UGC_FOR_ADDITIONAL_DATA_FILE", LUA_NATIVE_DATAFILE_DATAFILE_LOAD_OFFLINE_UGC_FOR_ADDITIONAL_DATA_FILE);
		DATAFILE.set_function("DATAFILE_DELETE_FOR_ADDITIONAL_DATA_FILE", LUA_NATIVE_DATAFILE_DATAFILE_DELETE_FOR_ADDITIONAL_DATA_FILE);
		DATAFILE.set_function("DATAFILE_GET_FILE_DICT_FOR_ADDITIONAL_DATA_FILE", LUA_NATIVE_DATAFILE_DATAFILE_GET_FILE_DICT_FOR_ADDITIONAL_DATA_FILE);
		DATAFILE.set_function("DATADICT_SET_BOOL", LUA_NATIVE_DATAFILE_DATADICT_SET_BOOL);
		DATAFILE.set_function("DATADICT_SET_INT", LUA_NATIVE_DATAFILE_DATADICT_SET_INT);
		DATAFILE.set_function("DATADICT_SET_FLOAT", LUA_NATIVE_DATAFILE_DATADICT_SET_FLOAT);
		DATAFILE.set_function("DATADICT_SET_STRING", LUA_NATIVE_DATAFILE_DATADICT_SET_STRING);
		DATAFILE.set_function("DATADICT_SET_VECTOR", LUA_NATIVE_DATAFILE_DATADICT_SET_VECTOR);
		DATAFILE.set_function("DATADICT_CREATE_DICT", LUA_NATIVE_DATAFILE_DATADICT_CREATE_DICT);
		DATAFILE.set_function("DATADICT_CREATE_ARRAY", LUA_NATIVE_DATAFILE_DATADICT_CREATE_ARRAY);
		DATAFILE.set_function("DATADICT_GET_BOOL", LUA_NATIVE_DATAFILE_DATADICT_GET_BOOL);
		DATAFILE.set_function("DATADICT_GET_INT", LUA_NATIVE_DATAFILE_DATADICT_GET_INT);
		DATAFILE.set_function("DATADICT_GET_FLOAT", LUA_NATIVE_DATAFILE_DATADICT_GET_FLOAT);
		DATAFILE.set_function("DATADICT_GET_STRING", LUA_NATIVE_DATAFILE_DATADICT_GET_STRING);
		DATAFILE.set_function("DATADICT_GET_VECTOR", LUA_NATIVE_DATAFILE_DATADICT_GET_VECTOR);
		DATAFILE.set_function("DATADICT_GET_DICT", LUA_NATIVE_DATAFILE_DATADICT_GET_DICT);
		DATAFILE.set_function("DATADICT_GET_ARRAY", LUA_NATIVE_DATAFILE_DATADICT_GET_ARRAY);
		DATAFILE.set_function("DATADICT_GET_TYPE", LUA_NATIVE_DATAFILE_DATADICT_GET_TYPE);
		DATAFILE.set_function("DATAARRAY_ADD_BOOL", LUA_NATIVE_DATAFILE_DATAARRAY_ADD_BOOL);
		DATAFILE.set_function("DATAARRAY_ADD_INT", LUA_NATIVE_DATAFILE_DATAARRAY_ADD_INT);
		DATAFILE.set_function("DATAARRAY_ADD_FLOAT", LUA_NATIVE_DATAFILE_DATAARRAY_ADD_FLOAT);
		DATAFILE.set_function("DATAARRAY_ADD_STRING", LUA_NATIVE_DATAFILE_DATAARRAY_ADD_STRING);
		DATAFILE.set_function("DATAARRAY_ADD_VECTOR", LUA_NATIVE_DATAFILE_DATAARRAY_ADD_VECTOR);
		DATAFILE.set_function("DATAARRAY_ADD_DICT", LUA_NATIVE_DATAFILE_DATAARRAY_ADD_DICT);
		DATAFILE.set_function("DATAARRAY_GET_BOOL", LUA_NATIVE_DATAFILE_DATAARRAY_GET_BOOL);
		DATAFILE.set_function("DATAARRAY_GET_INT", LUA_NATIVE_DATAFILE_DATAARRAY_GET_INT);
		DATAFILE.set_function("DATAARRAY_GET_FLOAT", LUA_NATIVE_DATAFILE_DATAARRAY_GET_FLOAT);
		DATAFILE.set_function("DATAARRAY_GET_STRING", LUA_NATIVE_DATAFILE_DATAARRAY_GET_STRING);
		DATAFILE.set_function("DATAARRAY_GET_VECTOR", LUA_NATIVE_DATAFILE_DATAARRAY_GET_VECTOR);
		DATAFILE.set_function("DATAARRAY_GET_DICT", LUA_NATIVE_DATAFILE_DATAARRAY_GET_DICT);
		DATAFILE.set_function("DATAARRAY_GET_COUNT", LUA_NATIVE_DATAFILE_DATAARRAY_GET_COUNT);
		DATAFILE.set_function("DATAARRAY_GET_TYPE", LUA_NATIVE_DATAFILE_DATAARRAY_GET_TYPE);
	}
}
