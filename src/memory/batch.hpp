#pragma once
#include "pattern.hpp"

#include <functional>
#include <vector>

namespace memory
{
	class batch
	{
	public:
		explicit batch()  = default;
		~batch() noexcept = default;

		void add(std::string name, pattern pattern, std::function<void(memory::handle)> callback);
		bool run(range region);

		struct entry
		{
			std::string m_name;
			pattern m_pattern;
			std::function<void(memory::handle)> m_callback;

			explicit entry(std::string name, pattern pattern, std::function<void(memory::handle)> callback) :
			    m_name(std::move(name)),
			    m_pattern(std::move(pattern)),
			    m_callback(std::move(callback))
			{
			}
		};

	private:
		std::vector<entry> m_entries;
	};
}
