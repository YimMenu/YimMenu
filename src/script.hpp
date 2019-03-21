#pragma once
#include "common.hpp"

namespace big
{
	class script
	{
	public:
		using func_t = void(*)();
	public:
		explicit script(func_t func, std::optional<std::size_t> stack_size = std::nullopt);
		~script();

		void tick();
		void yield(std::optional<std::chrono::high_resolution_clock::duration> time = std::nullopt);
		static script *get_current();
	private:
		void fiber_func();
	private:
		void *m_script_fiber;
		void *m_main_fiber;
		func_t m_func;
		std::optional<std::chrono::high_resolution_clock::time_point> m_wake_time;
	};
}
