#include "../common.hpp"
#include "pattern.hpp"

namespace memory
{
	pattern::pattern(std::string_view ida_sig)
	{
		auto to_upper = [](char c) -> char
		{
			return c >= 'a' && c <= 'z' ? static_cast<char>(c + ('A' - 'a')) : static_cast<char>(c);
		};

		auto to_hex = [&](char c) -> std::optional<std::uint8_t>
		{
			switch (to_upper(c))
			{
			case '0':
				return static_cast<std::uint8_t>(0);
			case '1':
				return static_cast<std::uint8_t>(1);
			case '2':
				return static_cast<std::uint8_t>(2);
			case '3':
				return static_cast<std::uint8_t>(3);
			case '4':
				return static_cast<std::uint8_t>(4);
			case '5':
				return static_cast<std::uint8_t>(5);
			case '6':
				return static_cast<std::uint8_t>(6);
			case '7':
				return static_cast<std::uint8_t>(7);
			case '8':
				return static_cast<std::uint8_t>(8);
			case '9':
				return static_cast<std::uint8_t>(9);
			case 'A':
				return static_cast<std::uint8_t>(10);
			case 'B':
				return static_cast<std::uint8_t>(11);
			case 'C':
				return static_cast<std::uint8_t>(12);
			case 'D':
				return static_cast<std::uint8_t>(13);
			case 'E':
				return static_cast<std::uint8_t>(14);
			case 'F':
				return static_cast<std::uint8_t>(15);
			default:
				return std::nullopt;
			}
		};

		for (std::size_t i = 0; i < ida_sig.size(); ++i)
		{
			if (ida_sig[i] == ' ')
				continue;

			bool last = (i == ida_sig.size() - 1);
			if (ida_sig[i] != '?')
			{
				if (!last)
				{
					auto c1 = to_hex(ida_sig[i]);
					auto c2 = to_hex(ida_sig[i + 1]);

					if (c1 && c2)
					{
						m_bytes.emplace_back(static_cast<std::uint8_t>((*c1 * 0x10) + *c2));
					}
				}
			}
			else
			{
				m_bytes.push_back(std::nullopt);
			}
		}
	}

	pattern::pattern(const void *bytes, std::string_view mask)
	{
		for (std::size_t i = 0; i < mask.size(); ++i)
		{
			if (mask[i] != '?')
				m_bytes.emplace_back(static_cast<const std::uint8_t*>(bytes)[i]);
			else
				m_bytes.push_back(std::nullopt);
		}
	}
}
