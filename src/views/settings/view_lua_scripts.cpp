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
		components::sub_title("Loaded Lua Scipts");

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
			ImGui::Text("Scripts Registered: %d", selected_module.lock()->m_registered_scripts.size());
			ImGui::Text("Memory Patches Registered: %d", selected_module.lock()->m_registered_patches.size());
			ImGui::Text("GUI Tabs Registered: %d", selected_module.lock()->m_gui.size());

			if (components::button("Reload"))
			{
				auto name = selected_module.lock()->module_name();
				auto id   = selected_module.lock()->module_id();

				g_lua_manager->unload_module(id);
				g_lua_manager->queue_load_module(name, [](std::weak_ptr<big::lua_module> loaded_module) {
					selected_module = loaded_module;
				});
			}
		}

		ImGui::EndGroup();

		if (components::button("Reload All"))
		{
			g_lua_manager->m_schedule_reload_modules = true;
		}
	}
}
