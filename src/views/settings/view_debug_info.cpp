#include "pointers.hpp"

#include <imgui.h>

namespace big
{
	inline void view_debug_info()
	{
		if (ImGui::BeginTabItem("Info"))
		{
			ImGui::Text("%.0f FPS", ImGui::GetIO().Framerate);

			ImGui::Separator();

			ImGui::Text(std::format("Game Version: {}", g_pointers->m_gta.m_game_version).c_str());
			ImGui::Text(std::format("Online Version: {}", g_pointers->m_gta.m_online_version).c_str());

			ImGui::EndTabItem();
		}
	}
}
