#pragma once

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

	template<typename T>
	inline bool is_valid_ptr(T ptr)
	{
		uint64_t address = (uint64_t)ptr;
		if (address < 0x5000) return false;
		if ((address & 0xFFFFFFFF) == 0xFFFFFFFF) return false;
		if ((address & 0xFFFFFFFF) <= 0xFF) return false;
		if (address > 0xFFFFFFFFFFFF) return false;
		return true;
	}

	template<typename T>
	inline bool is_valid_vtable(T ptr)
	{
		uint64_t address = (uint64_t)ptr;
		if (!is_valid_ptr(address))
			return false;
		return address > g_main_module->begin().as<uint64_t>() && address < g_main_module->end().as<uint64_t>();
	}

	template<typename T>
	inline bool has_valid_vtable(T ptr)
	{
		if (!is_valid_ptr(ptr))
			return false;
		return is_valid_vtable(*reinterpret_cast<uint64_t*>(ptr));
	}
}
