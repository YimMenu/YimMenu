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

	inline Vector3 fvector3_to_Vector3(rage::fvector3 vector_in)
	{
		Vector3 vector_out = { vector_in.x, vector_in.y, vector_in.z };

		return vector_out;
	}
}
