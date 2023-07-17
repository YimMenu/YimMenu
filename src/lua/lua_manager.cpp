#include "lua_manager.hpp"

#include "file_manager.hpp"

namespace big
{
	lua_manager::lua_manager(folder scripts_folder) :
	    m_scripts_folder(scripts_folder)
	{
		m_schedule_reload_modules = false;

		m_wake_time_changed_scripts_check =
			std::chrono::high_resolution_clock::now() + m_delay_between_changed_scripts_check;

		g_lua_manager = this;

		load_all_modules();
	}

	lua_manager::~lua_manager()
	{
		unload_all_modules();

		g_lua_manager = nullptr;
	}

	bool lua_manager::has_gui_to_draw(rage::joaat_t tab_hash)
	{
		std::lock_guard guard(m_module_lock);

		for (const auto& module : m_modules)
		{
			if (const auto it = module->m_gui.find(tab_hash); it != module->m_gui.end())
			{
				if (it->second.size())
				{
					return true;
				}
			}
		}

		return false;
	}

	void lua_manager::draw_gui(rage::joaat_t tab_hash)
	{
		std::lock_guard guard(m_module_lock);

		bool add_separator = false;

		for (const auto& module : m_modules)
		{
			if (const auto it = module->m_gui.find(tab_hash); it != module->m_gui.end())
			{
				if (add_separator)
				{
					ImGui::Separator();
					add_separator = false;
				}

				for (const auto& element : it->second)
				{
					element->draw();
					add_separator = true;
				}
			}
		}
	}

	void lua_manager::unload_module(rage::joaat_t module_id)
	{
		std::lock_guard guard(m_module_lock);

		std::erase_if(m_modules, [module_id](auto& module) {
			return module_id == module->module_id();
		});
	}

	void lua_manager::load_module(const std::string& module_name)
	{
		std::lock_guard guard(m_module_lock);

		const auto id = rage::joaat(module_name);

		for (const auto& module : m_modules)
			if (module->module_id() == id)
				return;

		m_modules.push_back(std::make_shared<lua_module>(module_name));
	}

	void lua_manager::reload_changed_scripts()
	{
		if (!g.lua.enable_auto_reload_changed_scripts)
		{
			return;
		}

		if (m_wake_time_changed_scripts_check <= std::chrono::high_resolution_clock::now())
		{
			for (const auto& entry : std::filesystem::directory_iterator(m_scripts_folder.get_path()))
			{
				if (entry.is_regular_file())
				{
					const auto module_name = entry.path().filename().string();
					const auto last_write_time = entry.last_write_time();

					for (const auto& module : m_modules)
					{
						if (module->module_name() == module_name &&
							module->last_write_time() < last_write_time)
						{
							unload_module(module->module_id());
							queue_load_module(module_name, nullptr);
							break;
						}
					}
				}
			}

			m_wake_time_changed_scripts_check = std::chrono::high_resolution_clock::now() + m_delay_between_changed_scripts_check;
		}
	}

	void lua_manager::queue_load_module(const std::string& module_name, std::function<void(std::weak_ptr<lua_module>)> on_module_loaded)
	{
		m_modules_load_queue.push({module_name, on_module_loaded});
	}

	void lua_manager::load_modules_from_queue()
	{
		while (m_modules_load_queue.size())
		{
			auto& module_load_info = m_modules_load_queue.front();

			const auto id = rage::joaat(module_load_info.m_name);

			load_module(module_load_info.m_name);
			auto loaded_module = get_module(id);
			if (module_load_info.m_on_module_loaded)
				module_load_info.m_on_module_loaded(loaded_module);

			m_modules_load_queue.pop();
		}
	}

	std::weak_ptr<lua_module> lua_manager::get_module(rage::joaat_t module_id)
	{
		std::lock_guard guard(m_module_lock);

		for (const auto& module : m_modules)
			if (module->module_id() == module_id)
				return module;

		return {};
	}

	void lua_manager::handle_error(const sol::error& error, const sol::state_view& state)
	{
		LOG(FATAL) << state["!module_name"].get<std::string_view>() << ": " << error.what();
		Logger::FlushQueue();
	}

	void lua_manager::load_all_modules()
	{
		for (const auto& entry : std::filesystem::directory_iterator(m_scripts_folder.get_path()))
			if (entry.is_regular_file())
				load_module(entry.path().filename().string());
	}
	void lua_manager::unload_all_modules()
	{
		std::lock_guard guard(m_module_lock);

		for (auto& module : m_modules)
			module.reset();

		m_modules.clear();
	}
}