#include "views/view.hpp"
#include "pointers.hpp"

namespace big
{
	void view::chat_tabs() 
	{
		if (!*g_pointers->m_is_session_started) return;

		ImGui::SetNextWindowSize({ 450, 525 }, ImGuiCond_FirstUseEver);
		ImGui::SetNextWindowPos({ 1470, 250 }, ImGuiCond_FirstUseEver);

		if (ImGui::Begin("Chat", &g->window.chat, ImGuiWindowFlags_NoTitleBar))
		{
			if (ImGui::BeginTabBar("chat_tabbar"))
			{
				if (ImGui::BeginTabItem("Normal"))
				{
					view::chat();
					ImGui::EndTabItem();
				}
				if (ImGui::BeginTabItem("DM"))
				{
					view::chat_dm();
					ImGui::EndTabItem();
				}
				ImGui::EndTabBar();
			}
			ImGui::End();
		}
	}
}
