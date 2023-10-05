#include "hooking.hpp"

namespace big
{
	bool hooks::sync_reader_serialize_dword(void* _this, uint32_t* dword, int size)
	{
		auto orig = g_hooking->m_sync_data_reader_hook.get_original<decltype(&hooks::sync_reader_serialize_dword)>(1)(_this, dword, size);

		return orig;
	}

	bool hooks::sync_reader_serialize_word(void* _this, uint16_t* word, int size)
	{
		auto orig = g_hooking->m_sync_data_reader_hook.get_original<decltype(&hooks::sync_reader_serialize_word)>(2)(_this, word, size);

		return orig;
	}

	bool hooks::sync_reader_serialize_byte(void* _this, uint8_t* byte, int size)
	{
		auto orig = g_hooking->m_sync_data_reader_hook.get_original<decltype(&hooks::sync_reader_serialize_byte)>(3)(_this, byte, size);

		return orig;
	}

	bool hooks::sync_reader_serialize_int32(void* _this, int32_t* i, int size)
	{
		auto orig = g_hooking->m_sync_data_reader_hook.get_original<decltype(&hooks::sync_reader_serialize_int32)>(4)(_this, i, size);

		return orig;
	}

	bool hooks::sync_reader_serialize_int16(void* _this, int16_t* i, int size)
	{
		auto orig = g_hooking->m_sync_data_reader_hook.get_original<decltype(&hooks::sync_reader_serialize_int16)>(5)(_this, i, size);

		return orig;
	}

	bool hooks::sync_reader_serialize_signed_byte(void* _this, int8_t* i, int size)
	{
		auto orig = g_hooking->m_sync_data_reader_hook.get_original<decltype(&hooks::sync_reader_serialize_signed_byte)>(6)(_this, i, size);

		return orig;
	}

	bool hooks::sync_reader_serialize_bool(void* _this, bool* flag, int size)
	{
		auto orig = g_hooking->m_sync_data_reader_hook.get_original<decltype(&hooks::sync_reader_serialize_bool)>(7)(_this, flag, size);

		return orig;
	}

	bool hooks::sync_reader_serialize_signed_float(void* _this, float* flt, float divisor, int size)
	{
		auto orig = g_hooking->m_sync_data_reader_hook.get_original<decltype(&hooks::sync_reader_serialize_signed_float)>(16)(_this, flt, divisor, size);

		return orig;
	}

	bool hooks::sync_reader_serialize_float(void* _this, float* flt, float divisor, int size)
	{
		auto orig = g_hooking->m_sync_data_reader_hook.get_original<decltype(&hooks::sync_reader_serialize_float)>(17)(_this, flt, divisor, size);

		return orig;
	}

	bool hooks::sync_reader_serialize_net_id(void* _this, uint16_t* id)
	{
		auto orig = g_hooking->m_sync_data_reader_hook.get_original<decltype(&hooks::sync_reader_serialize_net_id)>(18)(_this, id);

		return orig;
	}

	bool hooks::sync_reader_serialize_vec3(void* _this, rage::fvector3* vec, float divisor, int size)
	{
		auto orig = g_hooking->m_sync_data_reader_hook.get_original<decltype(&hooks::sync_reader_serialize_vec3)>(19)(_this, vec, divisor, size);

		return orig;
	}

	bool hooks::sync_reader_serialize_vec3_signed(void* _this, rage::fvector3* vec, float divisor, int size)
	{
		auto orig = g_hooking->m_sync_data_reader_hook.get_original<decltype(&hooks::sync_reader_serialize_vec3_signed)>(21)(_this, vec, divisor, size);

		return orig;
	}

	bool hooks::sync_reader_serialize_array(void* _this, void* array, int size)
	{
		auto orig = g_hooking->m_sync_data_reader_hook.get_original<decltype(&hooks::sync_reader_serialize_array)>(23)(_this, array, size);

		return orig;
	}
}