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

	//https://en.wikipedia.org/wiki/Boyer%E2%80%93Moore%E2%80%93Horspool_algorithm
	//https://www.youtube.com/watch?v=AuZUeshhy-s
	static handle scan_pattern(const std::optional<std::uint8_t>* sig, std::size_t length, handle begin, std::size_t moduleSize)
	{
		std::size_t maxShift = length;
		std::size_t maxIdx = length - 1;
		//Get wildcard index, and store max shifable byte count
		std::size_t wildCardIdx{ size_t(-1) };
		for (int i{ int(maxIdx - 1) }; i >= 0; --i)
		{
			if (!sig[i])
			{
				maxShift = maxIdx - i;
				wildCardIdx = i;
				break;
			}
		}
		//Store max shiftable bytes for non wildcards.
		std::size_t shiftTable[UINT8_MAX + 1]{};
		for (std::size_t i{}; i <= UINT8_MAX; ++i)
		{
			shiftTable[i] = maxShift;
		}
		for (std::size_t i{ wildCardIdx + 1 }; i != maxIdx; ++i)
		{
			shiftTable[*sig[i]] = maxIdx - i;
		}
		//Loop data
		for (std::size_t curIdx{}; curIdx != moduleSize - length;)
		{
			for (std::size_t sigIdx = maxIdx; sigIdx >= 0; --sigIdx)
			{
				if (sig[sigIdx] && *begin.add(curIdx + sigIdx).as<uint8_t*>() != *sig[sigIdx])
				{
					curIdx += shiftTable[*begin.add(curIdx + maxIdx).as<uint8_t*>()];
					break;
				}
				else if (sigIdx == NULL)
				{
					return begin.add(curIdx);
				}
			}
		}
		return nullptr;
	};

	handle range::scan(pattern const &sig)
	{
		auto data = sig.m_bytes.data();
		auto length = sig.m_bytes.size();
		if (auto result = scan_pattern(data, length, m_base, m_size); result)
		{
			return result;
		}

		return nullptr;
	}

	bool pattern_matches(std::uint8_t* target, const std::optional<std::uint8_t>* sig, std::size_t length)
	{
		for (std::size_t i{}; i != length; ++i)
		{
			if (sig[i] && *sig[i] != target[i])
				return false;
		}

		return true;
	}
	std::vector<handle> range::scan_all(pattern const &sig)
	{
		std::vector<handle> result;

		auto data = sig.m_bytes.data();
		auto length = sig.m_bytes.size();
		for (std::uintptr_t i{}; i != m_size - length; ++i)
		{
			if (pattern_matches(m_base.add(i).as<std::uint8_t*>(), data, length))
			{
				result.push_back(m_base.add(i));
			}
		}

		return std::move(result);
	}
}
