#pragma once
#include <vector>
#include "fwddec.hpp"
#include "handle.hpp"

namespace memory
{
	class range
	{
	public:
		range(handle base, std::size_t size);

		handle begin();
		handle end();
		std::size_t size();

		bool contains(handle h);

		handle scan(pattern const& sig);
		std::vector<handle> scan_all(pattern const& sig);
	protected:
		handle m_base;
		std::size_t m_size;
	};
}
