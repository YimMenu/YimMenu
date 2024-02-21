#include "lua_manager.hpp"

#include "file_manager.hpp"

namespace big
{
	std::optional<std::filesystem::path> move_file_relative_to_folder(const std::filesystem::path& original, const std::filesystem::path& target, const std::filesystem::path& file)
	{
		// keeps folder hierarchy intact
		const auto new_module_path = target / relative(file, original);
		g_file_manager.ensure_file_can_be_created(new_module_path);

		try
		{
			rename(file, new_module_path);
		}
		catch(const std::filesystem::filesystem_error& e)
		{
			LOG(FATAL) << "Failed to move Lua file: " << e.what();

			return std::nullopt;
		}
		return { new_module_path };
	}

	lua_manager::lua_manager(folder scripts_folder, folder scripts_config_folder) :
	    m_scripts_folder(scripts_folder),
	    m_scripts_config_folder(scripts_config_folder),
	    m_disabled_scripts_folder(scripts_folder.get_folder("./disabled"))
	{
		m_wake_time_changed_scripts_check = std::chrono::high_resolution_clock::now() + m_delay_between_changed_scripts_check;

		g_lua_manager = this;

		load_all_modules();
	}

	lua_manager::~lua_manager()
	{
		unload_all_modules();

		g_lua_manager = nullptr;
	}

	void lua_manager::disable_all_modules()
	{
		std::vector<std::filesystem::path> script_paths;

		{
			std::lock_guard guard(m_module_lock);
			for (auto& module : m_modules)
			{
				script_paths.push_back(module->module_path());

				module.reset();
			}
			m_modules.clear();
		}

		for (const auto& script_path : script_paths)
		{
			const auto new_module_path = move_file_relative_to_folder(m_scripts_folder.get_path(), m_disabled_scripts_folder.get_path(), script_path);
			if (new_module_path)
			{
				load_module(*new_module_path);
			}
		}
	}

	void lua_manager::enable_all_modules()
	{
		std::vector<std::filesystem::path> script_paths;

		{
			std::lock_guard guard(m_disabled_module_lock);
			for (auto& module : m_disabled_modules)
			{
				script_paths.push_back(module->module_path());

				module.reset();
			}
			m_disabled_modules.clear();
		}

		for (const auto& script_path : script_paths)
		{
			const auto new_module_path = move_file_relative_to_folder(m_disabled_scripts_folder.get_path(), m_scripts_folder.get_path(), script_path);
			if (new_module_path)
			{
				load_module(*new_module_path);
			}
		}
	}

	void lua_manager::load_all_modules()
	{
		for (const auto& entry : std::filesystem::recursive_directory_iterator(m_scripts_folder.get_path(), std::filesystem::directory_options::skip_permission_denied))
			if (entry.is_regular_file() && entry.path().extension() == ".lua")
				load_module(entry.path());
	}

	void lua_manager::unload_all_modules()
	{
		{
			std::lock_guard guard(m_module_lock);

			for (auto& module : m_modules)
				module.reset();
			m_modules.clear();
		}
		{
			std::lock_guard guard(m_disabled_module_lock);

			for (auto& module : m_disabled_modules)
				module.reset();
			m_disabled_modules.clear();
		}
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

	void lua_manager::draw_independent_gui()
	{
		std::lock_guard guard(m_module_lock);

		for (const auto& module : m_modules)
		{
			for (const auto& element : module->m_independent_gui)
			{
				element->draw();
			}
		}
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

	std::weak_ptr<lua_module> lua_manager::enable_module(rage::joaat_t module_id)
	{
		if (auto module = get_disabled_module(module_id).lock())
		{
			const auto module_path = module->module_path();

			// unload module
			{
			std::lock_guard guard(m_disabled_module_lock);
			std::erase_if(m_disabled_modules, [module_id](auto& module) {
				return module_id == module->module_id();
			});
			}

			const auto new_module_path = move_file_relative_to_folder(m_disabled_scripts_folder.get_path(), m_scripts_folder.get_path(), module_path);
			if (new_module_path)
			{
				return load_module(*new_module_path);
			}
		}

		return {};
	}

	std::weak_ptr<lua_module> lua_manager::disable_module(rage::joaat_t module_id)
	{
		if (auto module = get_module(module_id).lock())
		{
			const auto module_path = module->module_path();

			// unload module
			{
			std::lock_guard guard(m_disabled_module_lock);
			std::erase_if(m_modules, [module_id](auto& module) {
				return module_id == module->module_id();
			});
			}

			const auto new_module_path = move_file_relative_to_folder(m_scripts_folder.get_path(), m_disabled_scripts_folder.get_path(), module_path);
			if (new_module_path)
			{
				return load_module(*new_module_path);
			}
		}
		return {};
	}

	void lua_manager::unload_module(rage::joaat_t module_id)
	{
		std::lock_guard guard(m_module_lock);
		std::erase_if(m_modules, [module_id](auto& module) {
			return module_id == module->module_id();
		});

		std::lock_guard guard2(m_disabled_module_lock);
		std::erase_if(m_disabled_modules, [module_id](auto& module) {
			return module_id == module->module_id();
		});
	}

	std::weak_ptr<lua_module> lua_manager::load_module(const std::filesystem::path& module_path)
	{
		if (!std::filesystem::exists(module_path))
		{
			LOG(WARNING) << reinterpret_cast<const char*>(module_path.u8string().c_str()) << " does not exist in the filesystem. Not loading it.";
			return {};
		}

		const auto module_name = module_path.filename().string();
		const auto id          = rage::joaat(module_name);

		std::lock_guard guard(m_module_lock);
		for (const auto& module : m_modules)
		{
			if (module->module_id() == id)
			{
				LOG(WARNING) << "Module with the name " << module_name << " already loaded.";
				return {};
			}
		}

		const auto rel                = relative(module_path, m_disabled_scripts_folder.get_path());
		const auto is_disabled_module = !rel.empty() && rel.native()[0] != '.';
		const auto module             = std::make_shared<lua_module>(module_path, m_scripts_folder, is_disabled_module);
		if (!module->is_disabled())
		{
			module->load_and_call_script();
			m_modules.push_back(module);

			return module;
		}

		std::lock_guard disabled_guard(m_disabled_module_lock);
		m_disabled_modules.push_back(module);
		return module;
	}

	void lua_manager::reload_changed_scripts()
	{
		if (!g.lua.enable_auto_reload_changed_scripts)
		{
			return;
		}

		if (m_wake_time_changed_scripts_check <= std::chrono::high_resolution_clock::now())
		{
			if (!exists(m_scripts_folder.get_path()))
			{
				// g_file_manager.ensure_folder_exists(m_scripts_folder.get_path());
				return;
			}

			for (const auto& entry : std::filesystem::recursive_directory_iterator(m_scripts_folder.get_path(), std::filesystem::directory_options::skip_permission_denied))
			{
				if (entry.is_regular_file())
				{
					const auto& module_path    = entry.path();
					const auto last_write_time = entry.last_write_time();

					for (const auto& module : m_modules)
					{
						if (module->module_path() == module_path && module->last_write_time() < last_write_time)
						{
							unload_module(module->module_id());
							load_module(module_path);
							break;
						}
					}
				}
			}

			m_wake_time_changed_scripts_check = std::chrono::high_resolution_clock::now() + m_delay_between_changed_scripts_check;
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

	std::weak_ptr<lua_module> lua_manager::get_disabled_module(rage::joaat_t module_id)
	{
		std::lock_guard guard(m_disabled_module_lock);

		for (const auto& module : m_disabled_modules)
			if (module->module_id() == module_id)
				return module;

		return {};
	}

	void lua_manager::handle_error(const sol::error& error, const sol::state_view& state)
	{
		LOG(FATAL) << state["!module_name"].get<std::string_view>() << ": " << error.what();
		Logger::FlushQueue();
	}
}