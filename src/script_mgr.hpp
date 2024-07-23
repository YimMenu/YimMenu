#pragma once
#include "lua/lua_manager.hpp"
#include "script.hpp"

namespace big
{
	using script_list = std::vector<std::unique_ptr<script>>;

	class script_mgr
	{
	public:
		explicit script_mgr() = default;
		~script_mgr()         = default;

		void add_script(std::unique_ptr<script> script);
		void remove_all_scripts();

		inline void for_each_script(auto func)
		{
			std::lock_guard lock(m_mutex);

			for (const auto& script : m_scripts)
			{
				func(script);
			}

			g_lua_manager->for_each_module([&func](const std::shared_ptr<lua_module>& module) {
				module->for_each_script([&func](script* script) {
					func(script);
				});
			});
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

		bool m_can_tick = false;
	};

	inline script_mgr g_script_mgr;
}