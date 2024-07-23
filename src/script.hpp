#pragma once

namespace big
{
	class script
	{
		std::string m_name;
		bool m_enabled;
		bool m_toggleable;
		bool m_done;

	public:
		using func_t = std::function<void(void)>;

	public:
		explicit script(const func_t func, const std::string& name, const bool toggleable = true, const std::optional<std::size_t> stack_size = std::nullopt);
		explicit script(const func_t func, const std::optional<std::size_t> stack_size = std::nullopt);
		~script();

		[[nodiscard]] const char* name() const;
		[[nodiscard]] bool is_enabled() const;
		void set_enabled(const bool toggle);
		[[nodiscard]] bool* toggle_ptr();

		[[nodiscard]] bool is_toggleable() const;

		[[nodiscard]] bool is_done() const;

		void tick();
		void yield(std::optional<std::chrono::high_resolution_clock::duration> time = std::nullopt);
		static script* get_current();

	private:
		void fiber_func();

	private:
		void* m_script_fiber;
		void* m_main_fiber;
		func_t m_func;
		std::optional<std::chrono::high_resolution_clock::time_point> m_wake_time;
	};
}