#pragma once

namespace big::misc
{
	template<typename T>
	inline void clear_bit(T* address, int pos)
	{
		*address &= ~(1 << pos);
	}
	
	template<typename T>
	inline void clear_bits(T* address, int bits)
	{
		*address &= ~(bits);
	}

	template<typename T>
	inline bool has_bit_set(T* address, int pos)
	{
		return *address & 1 << pos;
	}

	template<typename T>
	inline bool has_bits_set(T* address, T bits)
	{
		return (*address & bits) == bits;
	}

	template<typename T>
	inline void set_bit(T* address, int pos)
	{
		*address |= 1 << pos;
	}

	template<typename T>
	inline void set_bits(T* address, int bits)
	{
		*address |= bits;
	}
}
