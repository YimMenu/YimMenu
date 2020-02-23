#pragma once
#include "common.hpp"

namespace big
{
	class script_local
	{
	public:
		explicit script_local(rage::scrThread* thread, std::size_t index);
		explicit script_local(PVOID stack, std::size_t index);

		script_local at(std::ptrdiff_t index);
		script_local at(std::ptrdiff_t index, std::size_t size);

		template <typename T>
		std::enable_if_t<std::is_pointer_v<T>, T> as()
		{
			return static_cast<T>(get());
		}

		template <typename T>
		std::enable_if_t<std::is_lvalue_reference_v<T>, T> as()
		{
			return *static_cast<std::add_pointer_t<std::remove_reference_t<T>>>(get());
		}
	private:
		void *get();
		std::size_t m_index;
		PVOID m_stack;
	};
}
