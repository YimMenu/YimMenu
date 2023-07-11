#pragma once
#include "common.hpp"
#include "script.hpp"

namespace big
{
	using script_list = std::vector<std::unique_ptr<script>>;

	class script_mgr
	{
	public:
		explicit script_mgr() = default;
		~script_mgr()         = default;

		script* add_script(std::unique_ptr<script> script);
		void remove_script(script* script);
		void remove_all_scripts();

		inline void for_each_script(auto func)
		{
			std::lock_guard lock(m_mutex);

			for (const auto& script : m_scripts)
			{
				func(script);
			}
		}

		void tick();

		[[nodiscard]] inline bool can_tick() const
		{
			return m_can_tick;
		}

	private:
		void ensure_main_fiber();
		void tick_internal();

	private:
		std::recursive_mutex m_mutex;
		script_list m_scripts;
		script_list m_scripts_to_add;

		bool m_can_tick = false;
	};

	inline script_mgr g_script_mgr;
}