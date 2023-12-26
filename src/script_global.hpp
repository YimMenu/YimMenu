#pragma once
#include "common.hpp"

namespace big
{
	class script_global
	{
	public:
		constexpr script_global(std::size_t index) :
		    m_index(index)
		{
		}

		constexpr script_global at(std::ptrdiff_t index) const
		{
			return m_index + index;
		}
		constexpr script_global at(std::ptrdiff_t index, std::size_t size) const
		{
			return m_index + 1 + (index * size);
		}

		template<typename T>
		std::enable_if_t<std::is_pointer_v<T>, T> as() const
		{
			return static_cast<T>(get());
		}

		template<typename T>
		std::enable_if_t<std::is_lvalue_reference_v<T>, T> as() const
		{
			return *static_cast<std::add_pointer_t<std::remove_reference_t<T>>>(get());
		}

	private:
		void* get() const;
		std::size_t m_index;
	};
}
