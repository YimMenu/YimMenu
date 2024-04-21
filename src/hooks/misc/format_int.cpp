#include "hooking/hooking.hpp"

namespace big
{
	static inline std::string format_money(int64_t amount)
	{
		std::stringstream ss;
		ss.imbue(std::locale(""));
		ss << "$" << std::put_money(static_cast<long double>(amount) * 100, false);
		std::string money = ss.str();
		size_t pos        = money.find('.');
		if (pos != std::string::npos)
		{
			money = money.substr(0, pos);
		}
		return money;
	}

	void hooks::format_int(int64_t integer_to_format, char* format_string, size_t size_always_64, bool use_commas)
	{
		void* return_address        = _ReturnAddress();
		unsigned char* return_bytes = static_cast<unsigned char*>(return_address);
		if (return_bytes[0] == 0x48 && return_bytes[1] == 0x8D && return_bytes[2] == 0x15) //lea     rdx, aHcGreenlightFo ; "~HC_GREENLIGHT~ <font size='20'>"
		{
			auto money_format = format_money(integer_to_format);
			strcpy_s(format_string, size_always_64, money_format.c_str());
			return;
		}
		g_hooking->get_original<format_int>()(integer_to_format, format_string, size_always_64, use_commas);
	}
}