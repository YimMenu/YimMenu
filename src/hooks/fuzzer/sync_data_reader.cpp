#include "hooking/hooking.hpp"
#include "util/fuzzer.hpp"

namespace big
{
	bool hooks::sync_reader_serialize_dword(void* _this, uint32_t* dword, int size)
	{
		auto orig = g_hooking->m_sync_data_reader_hook.get_original<decltype(&hooks::sync_reader_serialize_dword)>(1)(_this, dword, size);

		if (fuzzer::is_fuzzer_enabled()) [[unlikely]]
		{
			fuzzer::handle_vtable_write(dword, sizeof(uint32_t), __FUNCTION__);
			*dword = fuzzer::fuzz_bits(*dword, size);
			return true;
		}

		return orig;
	}

	bool hooks::sync_reader_serialize_word(void* _this, uint16_t* word, int size)
	{
		auto orig = g_hooking->m_sync_data_reader_hook.get_original<decltype(&hooks::sync_reader_serialize_word)>(2)(_this, word, size);

		if (fuzzer::is_fuzzer_enabled()) [[unlikely]]
		{
			fuzzer::handle_vtable_write(word, sizeof(uint16_t), __FUNCTION__);
			*word = fuzzer::fuzz_bits(*word, size);
			return true;
		}

		return orig;
	}

	bool hooks::sync_reader_serialize_byte(void* _this, uint8_t* byte, int size)
	{
		auto orig = g_hooking->m_sync_data_reader_hook.get_original<decltype(&hooks::sync_reader_serialize_byte)>(3)(_this, byte, size);

		if (fuzzer::is_fuzzer_enabled()) [[unlikely]]
		{
			fuzzer::handle_vtable_write(byte, sizeof(uint8_t), __FUNCTION__);
			*byte = fuzzer::fuzz_bits(*byte, size);
			return true;
		}

		return orig;
	}

	bool hooks::sync_reader_serialize_int32(void* _this, int32_t* i, int size)
	{
		auto orig = g_hooking->m_sync_data_reader_hook.get_original<decltype(&hooks::sync_reader_serialize_int32)>(4)(_this, i, size);

		if (fuzzer::is_fuzzer_enabled()) [[unlikely]]
		{
			fuzzer::handle_vtable_write(i, sizeof(int32_t), __FUNCTION__);
			*i = fuzzer::fuzz_signed_bits(*i, size);
			return true;
		}

		return orig;
	}

	bool hooks::sync_reader_serialize_int16(void* _this, int16_t* i, int size)
	{
		auto orig = g_hooking->m_sync_data_reader_hook.get_original<decltype(&hooks::sync_reader_serialize_int16)>(5)(_this, i, size);

		if (fuzzer::is_fuzzer_enabled()) [[unlikely]]
		{
			fuzzer::handle_vtable_write(i, sizeof(int16_t), __FUNCTION__);
			*i = fuzzer::fuzz_signed_bits(*i, size);
			return true;
		}

		return orig;
	}

	bool hooks::sync_reader_serialize_signed_byte(void* _this, int8_t* i, int size)
	{
		auto orig = g_hooking->m_sync_data_reader_hook.get_original<decltype(&hooks::sync_reader_serialize_signed_byte)>(6)(_this, i, size);

		if (fuzzer::is_fuzzer_enabled()) [[unlikely]]
		{
			fuzzer::handle_vtable_write(i, sizeof(int8_t), __FUNCTION__);
			*i = fuzzer::fuzz_signed_bits(*i, size);
			return true;
		}

		return orig;
	}

	bool hooks::sync_reader_serialize_bool(void* _this, bool* flag, int size)
	{
		auto orig = g_hooking->m_sync_data_reader_hook.get_original<decltype(&hooks::sync_reader_serialize_bool)>(7)(_this, flag, size);

		if (fuzzer::is_fuzzer_enabled()) [[unlikely]]
		{
			fuzzer::handle_vtable_write(flag, sizeof(bool), __FUNCTION__);
			*flag = fuzzer::fuzz_bool(*flag);
			return true;
		}

		return orig;
	}

	bool hooks::sync_reader_serialize_signed_float(void* _this, float* flt, float divisor, int size)
	{
		auto orig = g_hooking->m_sync_data_reader_hook.get_original<decltype(&hooks::sync_reader_serialize_signed_float)>(16)(_this, flt, divisor, size);

		if (fuzzer::is_fuzzer_enabled()) [[unlikely]]
		{
			fuzzer::handle_vtable_write(flt, sizeof(float), __FUNCTION__);
			*flt = fuzzer::fuzz_float(*flt, size, divisor, true);
			return true;
		}

		return orig;
	}

	bool hooks::sync_reader_serialize_float(void* _this, float* flt, float divisor, int size)
	{
		auto orig = g_hooking->m_sync_data_reader_hook.get_original<decltype(&hooks::sync_reader_serialize_float)>(17)(_this, flt, divisor, size);

		if (fuzzer::is_fuzzer_enabled()) [[unlikely]]
		{
			fuzzer::handle_vtable_write(flt, sizeof(float), __FUNCTION__);
			*flt = fuzzer::fuzz_float(*flt, size, divisor, false);
			return true;
		}

		return orig;
	}

	bool hooks::sync_reader_serialize_net_id(void* _this, uint16_t* id)
	{
		auto orig = g_hooking->m_sync_data_reader_hook.get_original<decltype(&hooks::sync_reader_serialize_net_id)>(18)(_this, id);

		if (fuzzer::is_fuzzer_enabled()) [[unlikely]]
		{
			fuzzer::handle_vtable_write(id, sizeof(uint16_t), __FUNCTION__);
			*id = fuzzer::fuzz_network_id(*id);
			return true;
		}

		return orig;
	}

	bool hooks::sync_reader_serialize_vec3(void* _this, rage::fvector3* vec, float divisor, int size)
	{
		auto orig = g_hooking->m_sync_data_reader_hook.get_original<decltype(&hooks::sync_reader_serialize_vec3)>(19)(_this, vec, divisor, size);

		if (fuzzer::is_fuzzer_enabled()) [[unlikely]]
		{
			fuzzer::handle_vtable_write(vec, sizeof(rage::fvector3), __FUNCTION__);
			*vec = fuzzer::fuzz_vector(*vec, size, divisor, false);
			return true;
		}

		return orig;
	}

	bool hooks::sync_reader_serialize_vec3_signed(void* _this, rage::fvector3* vec, float divisor, int size)
	{
		auto orig = g_hooking->m_sync_data_reader_hook.get_original<decltype(&hooks::sync_reader_serialize_vec3_signed)>(21)(_this, vec, divisor, size);

		if (fuzzer::is_fuzzer_enabled()) [[unlikely]]
		{
			fuzzer::handle_vtable_write(vec, sizeof(rage::fvector3), __FUNCTION__);
			*vec = fuzzer::fuzz_vector(*vec, size, divisor, true);
			return true;
		}

		return orig;
	}

	bool hooks::sync_reader_serialize_array(void* _this, void* array, int size)
	{
		auto orig = g_hooking->m_sync_data_reader_hook.get_original<decltype(&hooks::sync_reader_serialize_array)>(23)(_this, array, size);

		if (fuzzer::is_fuzzer_enabled()) [[unlikely]]
		{
			fuzzer::handle_vtable_write(array, size / 8, __FUNCTION__);
			fuzzer::fuzz_data(array, size / 8);
			return true;
		}

		return orig;
	}
}