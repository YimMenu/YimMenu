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

	template<typename T, typename ...Args>
	inline bool has_bits_set(T* address, T arg, Args... args)
	{
		T value = (T)0;
		value |= 1 << arg;

		([&](int pos) { value |= 1 << pos; }(args), ...);

		return (*address & value) == value;
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


	template <typename T>
	inline std::enable_if_t<std::is_same_v<T, std::string>, T> get_text_value(std::string text)
	{
		return text;
	}

	template<typename T>
	inline std::enable_if_t<!std::is_same_v<T, std::string>, T> get_text_value(std::string text)
	{
		T value = (T)NULL;
		std::stringstream(text) >> value;
		return value;
	}

	template<typename T = std::string>
	inline std::vector<T> split(std::string text, const char delim)
	{
		std::vector<T> result;
		std::string str;
		std::stringstream ss(text);
		while (std::getline(ss, str, delim))
			result.push_back(get_text_value<T>(str));
		return result;
	}
}
