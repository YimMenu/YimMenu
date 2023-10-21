#include "fiber_pool.hpp"
#include "lua/lua_manager.hpp"
#include "script.hpp"
#include "thread_pool.hpp"
#include "util/scripts.hpp"
#include "views/view.hpp"

namespace big
{
	static std::weak_ptr<lua_module> selected_module{};

	void view::lua_scripts()
	{
		ImGui::PushItemWidth(250);
		components::sub_title("VIEW_LUA_SCRIPTS_LOADED_LUA_SCRIPTS"_T);

		if (ImGui::BeginListBox("##empty", ImVec2(200, 200)))
		{
			g_lua_manager->for_each_module([](auto& module) {
				if (ImGui::Selectable(module->module_name().c_str(),
				        !selected_module.expired() && selected_module.lock().get() == module.get()))
					selected_module = module;
			});

			ImGui::EndListBox();
		}

		ImGui::SameLine();

		ImGui::BeginGroup();

		if (!selected_module.expired())
		{
			ImGui::Text(std::format("{}: {}", "VIEW_LUA_SCRIPTS_SCRIPTS_REGISTERED"_T, selected_module.lock()->m_registered_scripts.size()).c_str());
			ImGui::Text(std::format("{}: {}", "VIEW_LUA_SCRIPTS_MEMORY_PATCHES_REGISTERED"_T, selected_module.lock()->m_registered_patches.size()).c_str());
			ImGui::Text(std::format("{}: {}", "VIEW_LUA_SCRIPTS_GUI_TABS_REGISTERED"_T, selected_module.lock()->m_gui.size()).c_str());

			if (components::button("VIEW_LUA_SCRIPTS_RELOAD"_T))
			{
				const std::filesystem::path module_path = selected_module.lock()->module_path();
				const auto id = selected_module.lock()->module_id();

				g_lua_manager->unload_module(id);
				g_lua_manager->load_module(module_path);
				selected_module = g_lua_manager->get_module(id);
			}
		}

		ImGui::EndGroup();

		if (components::button("VIEW_LUA_SCRIPTS_RELOAD_ALL"_T))
		{
			g_lua_manager->unload_all_modules();
			g_lua_manager->load_all_modules();
		}
		ImGui::SameLine();
		ImGui::Checkbox("VIEW_LUA_SCRIPTS_AUTO_RELOAD_CHANGED_SCRIPTS"_T.data(), &g.lua.enable_auto_reload_changed_scripts);

		if (components::button("VIEW_LUA_SCRIPTS_OPEN_LUA_SCRIPTS_FOLDER"_T))
		{
			std::string command = "explorer.exe /select," + g_lua_manager->get_scripts_folder().get_path().string();

			std::system(command.c_str());
		}
	}
}
