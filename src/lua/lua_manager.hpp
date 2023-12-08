#pragma once
#include "core/enums.hpp"
#include "lua_module.hpp"

namespace big
{
	class lua_manager
	{
	private:
		std::mutex m_module_lock;
		std::vector<std::shared_ptr<lua_module>> m_modules;

		static constexpr std::chrono::seconds m_delay_between_changed_scripts_check = 3s;
		std::chrono::high_resolution_clock::time_point m_wake_time_changed_scripts_check;

		folder m_scripts_folder;
		folder m_scripts_config_folder;

	public:
		lua_manager(folder scripts_folder, folder scripts_config_folder);
		~lua_manager();

		void load_all_modules();
		void unload_all_modules();

		inline auto get_module_count() const
		{
			return m_modules.size();
		}

		inline const folder& get_scripts_folder() const
		{
			return m_scripts_folder;
		}

		inline const folder& get_scripts_config_folder() const
		{
			return m_scripts_config_folder;
		}

		std::weak_ptr<lua_module> get_module(rage::joaat_t module_id);

		bool has_gui_to_draw(rage::joaat_t tab_hash);
		void draw_independent_gui();
		void draw_gui(rage::joaat_t tab_hash);

		void unload_module(rage::joaat_t module_id);
		void load_module(const std::filesystem::path& module_path);

		void reload_changed_scripts();

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
	};

	inline lua_manager* g_lua_manager;
}