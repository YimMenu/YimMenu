#pragma once
#include "lua_module.hpp"
#include "core/enums.hpp"

namespace big
{
	class lua_manager
	{
		std::mutex m_module_lock;

	public:
		lua_manager();
		~lua_manager();

		void draw_gui(rage::joaat_t tab_hash);
		void unload_module(rage::joaat_t module_id);
		void load_module(const std::string& module_name);
		std::weak_ptr<lua_module> get_module(rage::joaat_t module_id);
		const std::vector<std::shared_ptr<lua_module>>& get_modules() const;
		void reload_all_modules();
		void handle_error(const sol::error& error, const sol::state_view& state);

		template<menu_event menu_event_, typename Return = void, typename... Args>
		inline std::conditional_t<std::is_void_v<Return>, void, std::optional<Return>> trigger_event(Args&&... args)
		{
			for (auto& modules : get_modules())
			{
				if (auto vec = modules->m_event_callbacks.find(menu_event_); vec != modules->m_event_callbacks.end())
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

	private:
		void load_all_modules();
		void unload_all_modules();

		std::vector<std::shared_ptr<lua_module>> m_modules;
	};

	inline lua_manager* g_lua_manager;
}