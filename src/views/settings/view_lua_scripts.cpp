#include "fiber_pool.hpp"
#include "lua/lua_manager.hpp"
#include "script.hpp"
#include "thread_pool.hpp"
#include "util/scripts.hpp"
#include "views/view.hpp"

namespace big
{
	static std::weak_ptr<lua_module> selected_module{};
	static bool show = true;

	void view::lua_scripts()
	{
		ImGui::PushItemWidth(250);
		components::sub_title("Loaded Lua Scipts");

		if (ImGui::BeginListBox("##empty", ImVec2(200, 200)))
		{
			auto& modules = g_lua_manager->get_modules();

			if (show && modules.size() > 0)
			{
				for (const auto& module : modules)
				{
					if (ImGui::Selectable(module->module_name().c_str(),
					        !selected_module.expired() && selected_module.lock().get() == module.get()))
						selected_module = module;
				}
			}
			else
			{
				ImGui::Text("No scripts loaded");
			}

			ImGui::EndListBox();
		}

		ImGui::SameLine();

		ImGui::BeginGroup();

		if (!selected_module.expired())
		{
			ImGui::Text("Scripts Registered: %d", selected_module.lock()->m_registered_scripts.size());
			ImGui::Text("Memory Patches Registered: %d", selected_module.lock()->m_registered_patches.size());
			ImGui::Text("GUI Tabs Registered: %d", selected_module.lock()->m_gui.size());

			components::button("Reload", [] {
				auto name = selected_module.lock()->module_name();
				auto id   = selected_module.lock()->module_id();

				g_lua_manager->unload_module(id);
				g_lua_manager->load_module(name);
				selected_module = g_lua_manager->get_module(id);
			});
		}

		ImGui::EndGroup();

		components::button("Reload All", [] {
			show = false;
			g_lua_manager->reload_all_modules();
			show = true;
		});
	}
}
