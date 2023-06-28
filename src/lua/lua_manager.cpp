#include "lua_manager.hpp"

#include "file_manager.hpp"

namespace big
{
	lua_manager::lua_manager()
	{
		load_all_modules();

		g_lua_manager = this;
	}

	lua_manager::~lua_manager()
	{
		unload_all_modules();

		g_lua_manager = nullptr;
	}

	void lua_manager::draw_gui(rage::joaat_t tab_hash)
	{
		std::lock_guard guard(m_module_lock);

		for (const auto& module : m_modules)
		{
			if (const auto it = module->m_gui.find(tab_hash); it != module->m_gui.end())
			{
				ImGui::SameLine();

				for (const auto& element : it->second)
					element->draw();
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

	std::weak_ptr<lua_module> lua_manager::get_module(rage::joaat_t module_id)
	{
		for (const auto& module : m_modules)
			if (module->module_id() == module_id)
				return module;

		return {};
	}

	const std::vector<std::shared_ptr<lua_module>>& lua_manager::get_modules() const
	{
		return m_modules;
	}

	void lua_manager::reload_all_modules()
	{
		unload_all_modules();
		load_all_modules();
	}

	void lua_manager::handle_error(const sol::error& error, const sol::state_view& state)
	{
		LOG(WARNING) << state["!module_name"].get<std::string_view>() << ": " << error.what();
	}

	void lua_manager::load_all_modules()
	{
		for (const auto& entry : std::filesystem::directory_iterator(g_file_manager->get_project_folder("scripts").get_path()))
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