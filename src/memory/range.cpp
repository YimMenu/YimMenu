#include "../common.hpp"
#include "range.hpp"
#include "pattern.hpp"

namespace memory
{
	range::range(handle base, std::size_t size) :
		m_base(base), m_size(size)
	{
	}

	handle range::begin()
	{
		return m_base;
	}

	handle range::end()
	{
		return m_base.add(m_size);
	}

	std::size_t range::size()
	{
		return m_size;
	}

	bool range::contains(handle h)
	{
		return h.as<std::uintptr_t>() >= begin().as<std::uintptr_t>() && h.as<std::uintptr_t>() <= end().as<std::uintptr_t>();
	}

	static bool pattern_matches(std::uint8_t* target, const std::optional<std::uint8_t>* sig, std::size_t length)
	{
		for (std::size_t i = 0; i < length; ++i)
		{
			if (sig[i] && *sig[i] != target[i])
				return false;
		}

		return true;
	};

	handle range::scan(pattern const &sig)
	{
		auto data = sig.m_bytes.data();
		auto length = sig.m_bytes.size();
		for (std::uintptr_t i = 0; i < m_size - length; ++i)
		{
			if (pattern_matches(m_base.add(i).as<std::uint8_t*>(), data, length))
			{
				return m_base.add(i);
			}
		}

		return nullptr;
	}

	std::vector<handle> range::scan_all(pattern const &sig)
	{
		std::vector<handle> result;

		auto data = sig.m_bytes.data();
		auto length = sig.m_bytes.size();
		for (std::uintptr_t i = 0; i < m_size - length; ++i)
		{
			if (pattern_matches(m_base.add(i).as<std::uint8_t*>(), data, length))
			{
				result.push_back(m_base.add(i));
			}
		}

		return std::move(result);
	}
}
