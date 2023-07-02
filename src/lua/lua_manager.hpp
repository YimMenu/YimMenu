#pragma once
#include "lua_module.hpp"
#include "core/enums.hpp"

namespace big
{
	class lua_manager
	{
		std::mutex m_module_lock;

	public:
		bool m_schedule_reload_modules;

	public:
		lua_manager();
		~lua_manager();

		void load_all_modules();
		void unload_all_modules();

		inline auto get_module_count() const
		{
			return m_modules.size();
		}

		void draw_gui(rage::joaat_t tab_hash);

		void unload_module(rage::joaat_t module_id);
		void load_module(const std::string& module_name);

		void queue_load_module(const std::string& module_name, std::function<void(std::weak_ptr<lua_module>)> on_module_loaded);
		void load_modules_from_queue();

		std::weak_ptr<lua_module> get_module(rage::joaat_t module_id);

		void handle_error(const sol::error& error, const sol::state_view& state);

		template<menu_event menu_event_, typename Return = void, typename... Args>
		inline std::conditional_t<std::is_void_v<Return>, void, std::optional<Return>> trigger_event(Args&&... args)
		{
			std::lock_guard guard(m_module_lock);

			for (auto& module : m_modules)
			{
				if (auto vec = module->m_event_callbacks.find(menu_event_); vec != module->m_event_callbacks.end())
				{
					for (auto& cb : vec->second)
					{
						auto result = cb(args...);

						if (!result.valid())
						{
							handle_error(result, result.lua_state());
							continue;
						}

						if constexpr (!std::is_void_v<Return>)
						{
							if (result.return_count() == 0)
								continue;

							if (!result[0].is<Return>())
								continue;

							return result[0].get<Return>();
						}
					}
				}
			}

			if constexpr (!std::is_void_v<Return>)
				return std::nullopt;
		}

		inline void for_each_module(auto func)
		{
			std::lock_guard guard(m_module_lock);

			for (auto& module : m_modules)
			{
				func(module);
			}
		}

	private:
		std::vector<std::shared_ptr<lua_module>> m_modules;

		struct module_load_info
		{
			std::string m_name;
			std::function<void(std::weak_ptr<lua_module>)> m_on_module_loaded;
		};
		std::queue<module_load_info> m_modules_load_queue;
	};

	inline lua_manager* g_lua_manager;
}