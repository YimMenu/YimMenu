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

	static std::tuple<bool, Any> LUA_NATIVE_DATAFILE_UGC_CREATE_CONTENT(Any data, int dataCount, const char* contentName, const char* description, const char* tagsCsv, const char* contentTypeName, bool publish, Any p7)
	{
		std::tuple<bool, Any> return_values;
		std::get<0>(return_values) = (bool)DATAFILE::UGC_CREATE_CONTENT(&data, dataCount, contentName, description, tagsCsv, contentTypeName, publish, p7);
		std::get<1>(return_values) = data;

		return return_values;
	}

	static bool LUA_NATIVE_DATAFILE_UGC_CREATE_MISSION(const char* contentName, const char* description, const char* tagsCsv, const char* contentTypeName, bool publish, Any p5)
	{
		auto retval = (bool)DATAFILE::UGC_CREATE_MISSION(contentName, description, tagsCsv, contentTypeName, publish, p5);
		return retval;
	}

	static std::tuple<bool, Any> LUA_NATIVE_DATAFILE_UGC_UPDATE_CONTENT(const char* contentId, Any data, int dataCount, const char* contentName, const char* description, const char* tagsCsv, const char* contentTypeName, Any p7)
	{
		std::tuple<bool, Any> return_values;
		std::get<0>(return_values) = (bool)DATAFILE::UGC_UPDATE_CONTENT(contentId, &data, dataCount, contentName, description, tagsCsv, contentTypeName, p7);
		std::get<1>(return_values) = data;

		return return_values;
	}

	static bool LUA_NATIVE_DATAFILE_UGC_UPDATE_MISSION(const char* contentId, const char* contentName, const char* description, const char* tagsCsv, const char* contentTypeName, Any p5)
	{
		auto retval = (bool)DATAFILE::UGC_UPDATE_MISSION(contentId, contentName, description, tagsCsv, contentTypeName, p5);
		return retval;
	}

	static bool LUA_NATIVE_DATAFILE_UGC_SET_PLAYER_DATA(const char* contentId, float rating, const char* contentTypeName, Any p3)
	{
		auto retval = (bool)DATAFILE::UGC_SET_PLAYER_DATA(contentId, rating, contentTypeName, p3);
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

	static bool LUA_NATIVE_DATAFILE_DATAFILE_LOAD_OFFLINE_UGC(const char* filename, Any p1)
	{
		auto retval = (bool)DATAFILE::DATAFILE_LOAD_OFFLINE_UGC(filename, p1);
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

	static bool LUA_NATIVE_DATAFILE_DATAFILE_START_SAVE_TO_CLOUD(const char* filename, Any p1)
	{
		auto retval = (bool)DATAFILE::DATAFILE_START_SAVE_TO_CLOUD(filename, p1);
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

	static Any LUA_NATIVE_DATAFILE_DATADICT_SET_BOOL(Any objectData, const char* key, bool value)
	{
		DATAFILE::DATADICT_SET_BOOL(&objectData, key, value);
		return objectData;
	}

	static Any LUA_NATIVE_DATAFILE_DATADICT_SET_INT(Any objectData, const char* key, int value)
	{
		DATAFILE::DATADICT_SET_INT(&objectData, key, value);
		return objectData;
	}

	static Any LUA_NATIVE_DATAFILE_DATADICT_SET_FLOAT(Any objectData, const char* key, float value)
	{
		DATAFILE::DATADICT_SET_FLOAT(&objectData, key, value);
		return objectData;
	}

	static Any LUA_NATIVE_DATAFILE_DATADICT_SET_STRING(Any objectData, const char* key, const char* value)
	{
		DATAFILE::DATADICT_SET_STRING(&objectData, key, value);
		return objectData;
	}

	static Any LUA_NATIVE_DATAFILE_DATADICT_SET_VECTOR(Any objectData, const char* key, float valueX, float valueY, float valueZ)
	{
		DATAFILE::DATADICT_SET_VECTOR(&objectData, key, valueX, valueY, valueZ);
		return objectData;
	}

	static std::tuple<Any*, Any> LUA_NATIVE_DATAFILE_DATADICT_CREATE_DICT(Any objectData, const char* key)
	{
		std::tuple<Any*, Any> return_values;
		std::get<0>(return_values) = DATAFILE::DATADICT_CREATE_DICT(&objectData, key);
		std::get<1>(return_values) = objectData;

		return return_values;
	}

	static std::tuple<Any*, Any> LUA_NATIVE_DATAFILE_DATADICT_CREATE_ARRAY(Any objectData, const char* key)
	{
		std::tuple<Any*, Any> return_values;
		std::get<0>(return_values) = DATAFILE::DATADICT_CREATE_ARRAY(&objectData, key);
		std::get<1>(return_values) = objectData;

		return return_values;
	}

	static std::tuple<bool, Any> LUA_NATIVE_DATAFILE_DATADICT_GET_BOOL(Any objectData, const char* key)
	{
		std::tuple<bool, Any> return_values;
		std::get<0>(return_values) = (bool)DATAFILE::DATADICT_GET_BOOL(&objectData, key);
		std::get<1>(return_values) = objectData;

		return return_values;
	}

	static std::tuple<int, Any> LUA_NATIVE_DATAFILE_DATADICT_GET_INT(Any objectData, const char* key)
	{
		std::tuple<int, Any> return_values;
		std::get<0>(return_values) = DATAFILE::DATADICT_GET_INT(&objectData, key);
		std::get<1>(return_values) = objectData;

		return return_values;
	}

	static std::tuple<float, Any> LUA_NATIVE_DATAFILE_DATADICT_GET_FLOAT(Any objectData, const char* key)
	{
		std::tuple<float, Any> return_values;
		std::get<0>(return_values) = DATAFILE::DATADICT_GET_FLOAT(&objectData, key);
		std::get<1>(return_values) = objectData;

		return return_values;
	}

	static std::tuple<const char*, Any> LUA_NATIVE_DATAFILE_DATADICT_GET_STRING(Any objectData, const char* key)
	{
		std::tuple<const char*, Any> return_values;
		std::get<0>(return_values) = DATAFILE::DATADICT_GET_STRING(&objectData, key);
		std::get<1>(return_values) = objectData;

		return return_values;
	}

	static std::tuple<Vector3, Any> LUA_NATIVE_DATAFILE_DATADICT_GET_VECTOR(Any objectData, const char* key)
	{
		std::tuple<Vector3, Any> return_values;
		std::get<0>(return_values) = DATAFILE::DATADICT_GET_VECTOR(&objectData, key);
		std::get<1>(return_values) = objectData;

		return return_values;
	}

	static std::tuple<Any*, Any> LUA_NATIVE_DATAFILE_DATADICT_GET_DICT(Any objectData, const char* key)
	{
		std::tuple<Any*, Any> return_values;
		std::get<0>(return_values) = DATAFILE::DATADICT_GET_DICT(&objectData, key);
		std::get<1>(return_values) = objectData;

		return return_values;
	}

	static std::tuple<Any*, Any> LUA_NATIVE_DATAFILE_DATADICT_GET_ARRAY(Any objectData, const char* key)
	{
		std::tuple<Any*, Any> return_values;
		std::get<0>(return_values) = DATAFILE::DATADICT_GET_ARRAY(&objectData, key);
		std::get<1>(return_values) = objectData;

		return return_values;
	}

	static std::tuple<int, Any> LUA_NATIVE_DATAFILE_DATADICT_GET_TYPE(Any objectData, const char* key)
	{
		std::tuple<int, Any> return_values;
		std::get<0>(return_values) = DATAFILE::DATADICT_GET_TYPE(&objectData, key);
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

	static Any LUA_NATIVE_DATAFILE_DATAARRAY_ADD_STRING(Any arrayData, const char* value)
	{
		DATAFILE::DATAARRAY_ADD_STRING(&arrayData, value);
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
