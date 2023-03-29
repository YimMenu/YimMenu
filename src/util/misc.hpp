#pragma once
#include "hooking.hpp"
#include "pointers.hpp"

namespace big::misc
{
	inline void clear_bit(int* address, int pos)
	{
		*address &= ~(1 << pos);
	}

	inline void clear_bits(int* address, int bits)
	{
		*address &= ~(bits);
	}

	inline bool has_bit_set(int* address, int pos)
	{
		return *address & 1 << pos;
	}

	template<typename T>
	inline bool has_bits_set(T* address, T bits)
	{
		return (*address & bits) == bits;
	}

	inline bool has_bits_set(int* address, int bits)
	{
		return (*address & bits) == bits;
	}

	inline void set_bit(int* address, int pos)
	{
		*address |= 1 << pos;
	}

	inline void set_bits(int* address, int bits)
	{
		*address |= bits;
	}

	inline const char* get_filename_for_audio_conversation(const char* label)
	{
		auto result = g_hooking->get_original<hooks::get_label_text>()(g_pointers->m_get_label_text_unk, label);
		if (!stricmp(result, ""))
			return "NULL";
		return result;
	}
}
